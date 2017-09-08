//
//  PJSipManager.m
//  PJSipKit
//
//  Created by vargo－mac on 2017/4/10.
//  Copyright © 2017年 vargo－mac. All rights reserved.
//

#import "PJSipManager.h"
#import <pjsua-lib/pjsua.h>
#import "PJSipNotificationNameUtil.h"

static void on_incoming_call(pjsua_acc_id acc_id, pjsua_call_id call_id, pjsip_rx_data *rdata);
static void on_call_state(pjsua_call_id call_id, pjsip_event *e);
static void on_call_media_state(pjsua_call_id call_id);
static void on_reg_state2(pjsua_acc_id acc_id, pjsua_reg_info *info);
static void on_reg_state(pjsua_acc_id acc_id);

@interface PJSipManager ()
{
    pjsua_acc_id acc_id;
    BOOL isInit;
    BOOL isRegisterSuccss;
}

@property (nonatomic, strong) NSString *serviceStr;

@property (nonatomic, copy) void (^ registerBlock)(PSAccModel *accModel);
@property (nonatomic, copy) void (^ callBlock)(PSCallModel *callModel);
@property (nonatomic, copy) void (^ incomingBlock)(PSCallModel *callModel);

@property (nonatomic, strong) PSCallModel *tempCModel;

@end

@implementation PJSipManager

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self name:sip_incoming_call_notification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:sip_call_state_notification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:sip_register_state_notification object:nil];
}

+ (instancetype)instance {
    static PJSipManager *manager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        manager = [[PJSipManager alloc] init];
    });
    return manager;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        
        // PJSIP配置
//        [self initConfig];
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(sip_incoming_call_notification:)
                                                     name:sip_incoming_call_notification
                                                   object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(sip_call_state_notification:)
                                                     name:sip_call_state_notification
                                                   object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(sip_register_state_notification:)
                                                     name:sip_register_state_notification
                                                   object:nil];
    }
    return self;
}

- (NSString *)serviceStr {
    if (!_serviceStr) {
        if (self.serviceIp) {
            if (self.port) {
                _serviceStr = [NSString stringWithFormat:@"%@:%@",self.serviceIp,self.port];
            }else {
                _serviceStr = self.serviceIp;
            }
        }
    }
    return _serviceStr;
}

// 配置
- (BOOL)initConfig {
    pj_status_t status;
    
    // 创建SUA
    status = pjsua_create();
    
    if (status != PJ_SUCCESS) {
        NSLog(@"error create pjsua"); return NO;
    }
    
    {
        // SUA 相关配置
        pjsua_config cfg;
        pjsua_media_config media_cfg;
        pjsua_logging_config log_cfg;
        
        pjsua_config_default(&cfg);
        
        // 设置设备类型/版本号/Voip DeviceToken
        if (self.user_agent) cfg.user_agent = pj_str(self.user_agent.UTF8String);
        
        // 回调函数配置
        cfg.cb.on_incoming_call = &on_incoming_call;            // 来电回调
        cfg.cb.on_call_media_state = &on_call_media_state;      // 媒体状态回调（通话建立后，要播放RTP流）
        cfg.cb.on_call_state = &on_call_state;                  // 电话状态回调
        cfg.cb.on_reg_state = &on_reg_state;                    // 注册状态回调
        cfg.cb.on_reg_state2 = &on_reg_state2;
        //on_call_sdp_created、pjmedia_rtp_encode_rtp、pjmedia_transport_send_rtp
        
        // 媒体相关配置
        pjsua_media_config_default(&media_cfg);
        media_cfg.clock_rate = 16000;
        media_cfg.snd_clock_rate = 16000;
        media_cfg.ec_tail_len = 0;
        
        // 日志相关配置
        pjsua_logging_config_default(&log_cfg);
#ifdef DEBUG
        log_cfg.msg_logging = PJ_TRUE;
        log_cfg.console_level = 4;
        log_cfg.level = 5;
#else
        log_cfg.msg_logging = PJ_FALSE;
        log_cfg.console_level = 0;
        log_cfg.level = 0;
#endif
        
        // 初始化PJSUA
        status = pjsua_init(&cfg, &log_cfg, &media_cfg);
        if (status != PJ_SUCCESS) {
            NSLog(@"error init pjsua"); return NO;
        }
    }
    
    // udp transport
    {
        pjsua_transport_config cfg;
        pjsua_transport_config_default(&cfg);
        
        // 传输类型配置
        status = pjsua_transport_create(PJSIP_TRANSPORT_UDP, &cfg, NULL);
        if (status != PJ_SUCCESS) {
            NSLog(@"error add transport for pjsua"); return NO;
        }
    }
    
    // 启动PJSUA
    status = pjsua_start();
    if (status != PJ_SUCCESS) {
        NSLog(@"error start pjsua"); return NO;
    }
    
    isInit = YES;
    
//    pjmedia_aud_param_set_cap input_vol
    return YES;
}

- (void)configServiceIp:(NSString *)serviceIp port:(NSString *)port {
    _serviceIp = serviceIp;
    _port = port;
}

#pragma mark - 接口
- (void)setCallBlock:(void (^)(PSCallModel *callModel))block {
    _callBlock = block;
}

- (void)setIncomingCallBlock:(void (^)(PSCallModel *callModel))block {
    _incomingBlock = block;
}

- (void)pjsip_loginUserName:(NSString *)userName
                   password:(NSString *)password
                  serviceIp:(NSString *)serviceIp
                       port:(NSString *)port
                 userAgent:(NSString *)userAgent
                      block:(void (^)(PSAccModel *accModel))block {
    _encryptedMobile = userName;
    _registerBlock = block;
    [self configServiceIp:serviceIp port:port];
    if (isInit == NO) {
        _user_agent = userAgent;
        [self initConfig];
    }
    
//    pjsua_acc_id acc_id;
    pjsua_acc_config cfg;
    
    pjsua_acc_config_default(&cfg);
    NSString *service = [NSString stringWithFormat:@"sip:%@", self.serviceStr];
    cfg.id = pj_str((char *)[NSString stringWithFormat:@"sip:%@@%@", userName, self.serviceStr].UTF8String);
    cfg.reg_uri = pj_str((char *)service.UTF8String);
    
    NSLog(@"register service : %@ ",service);
    
    // 如果acc_id 已经注册了，就不需要再注册了
    pj_bool_t valid = pjsua_acc_is_valid(acc_id);
    if (valid == 1) {
        return;
    }
    
    cfg.reg_retry_interval = 60;
    cfg.reg_timeout = 60;
//    cfg.reg_first_retry_interval = 60;
    // PJSUA_REG_INTERVAL
    cfg.cred_count = 1;
    cfg.cred_info[0].realm = pj_str("*");
    cfg.cred_info[0].username = pj_str((char *)userName.UTF8String);
    cfg.cred_info[0].data_type = PJSIP_CRED_DATA_PLAIN_PASSWD;
    cfg.cred_info[0].data = pj_str((char *)password.UTF8String);
    pj_status_t status = pjsua_acc_add(&cfg, PJ_TRUE, &acc_id);
    
    if (status != PJ_SUCCESS) {
        NSString *errorMessage = [NSString stringWithFormat:@"登录失败, 返回错误号:%d!", status];
        NSLog(@"register error: %@", errorMessage);
    }else {
        NSLog(@"register success");
    }
}

pj_status_t pjcall_thread_register(void)
{
    pj_thread_desc  desc;
    pj_thread_t*    thread = 0;
    
    if (!pj_thread_is_registered())
    {
        return pj_thread_register(NULL, desc, &thread);
    }
    
    return PJ_SUCCESS;
}

- (void)pjsip_makeCallTo:(NSString *)url {
    // 首先注册当前线程
    pjcall_thread_register();
    
    pj_status_t status;
    pj_str_t dest_uri = pj_str((char *)url.UTF8String);
    
    status = pjsua_call_make_call(acc_id, &dest_uri, 0, NULL, NULL, NULL);
    
    if (status != PJ_SUCCESS) {
        char  errMessage[PJ_ERR_MSG_SIZE];
        pj_strerror(status, errMessage, sizeof(errMessage));
        NSLog(@"外拨错误, 错误信息:%d(%s) !", status, errMessage);
    }
}

- (void)pjsip_makeCallTo2:(NSString *)url priKey:(NSString *)priKey pubKey:(NSString *)pubKey {
    pjsua_call_setting opt;
    pjsua_call_setting_default(&opt);
    opt.prikey = pj_str((char *)priKey.UTF8String);
    opt.pubkey = pj_str((char *)pubKey.UTF8String);
    
    // 首先注册当前线程
    pjcall_thread_register();
    
    pj_status_t status;
    pj_str_t dest_uri = pj_str((char *)url.UTF8String);
    
    status = pjsua_call_make_call(acc_id, &dest_uri, &opt, NULL, NULL, NULL);
    
    if (status != PJ_SUCCESS) {
        char  errMessage[PJ_ERR_MSG_SIZE];
        pj_strerror(status, errMessage, sizeof(errMessage));
        NSLog(@"外拨错误, 错误信息:%d(%s) !", status, errMessage);
    }
}

- (void)pjsip_answer:(PJ_STATUS_CODE)code
              callId:(int)callId {
    
    pjcall_thread_register();
    
    pjsua_call_answer((pjsua_call_id)callId, code, NULL, NULL);
}

- (void)pjsip_answer2:(PJ_STATUS_CODE)code
              callId:(int)callId
               priKey:(NSString *)priKey
               pubKey:(NSString *)pubKey {
    pjsua_call_setting opt;
    pjsua_call_setting_default(&opt);
    if (priKey && pubKey) {
        opt.prikey = pj_str((char *)priKey.UTF8String);
        opt.pubkey = pj_str((char *)pubKey.UTF8String);
    }
    
    pjcall_thread_register();
    
    pjsua_call_answer2((pjsua_call_id)callId, &opt, code, NULL, NULL);
}

- (void)pjsip_hangup:(PJ_STATUS_CODE)code
              callId:(int)callId {
    pjsua_call_hangup((pjsua_call_id)callId, code, NULL, NULL);
}

- (void)pjsip_end {
    pjsua_call_hangup_all();
}

- (void)pjsip_logout {
    if (isInit) {
        if (isRegisterSuccss) {
            pjsua_acc_del(acc_id);
        }
        pjsua_destroy();
        isInit = NO;
        self.serviceStr = nil;
    }
}

- (void)setRatioOfNormalVolume {
//    pjmedia_aud_param inputParam;
//    inputParam.input_vol = 0;
//    pjmedia_aud_dev_cap intputPval = PJMEDIA_AUD_DEV_CAP_INPUT_VOLUME_SETTING;
//    pj_status_t input = pjmedia_aud_param_set_cap(&inputParam, PJMEDIA_AUD_DEV_CAP_INPUT_VOLUME_SETTING, &intputPval);
//    NSLog(@"input : %d",input);
//    
//    pjmedia_aud_param outputParam;
//    inputParam.output_vol = 0;
//    pjmedia_aud_dev_cap outputPval = PJMEDIA_AUD_DEV_CAP_OUTPUT_VOLUME_SETTING;
//    pj_status_t output = pjmedia_aud_param_set_cap(&outputParam, PJMEDIA_AUD_DEV_CAP_OUTPUT_VOLUME_SETTING, &outputPval);
//    NSLog(@"output : %d",output);
    
    pjsua_call_info callInfo;
    pjsua_call_get_info(self.tempCModel.callId, &callInfo);
    pjsua_conf_adjust_rx_level(callInfo.conf_slot, 1.5);
    pjsua_conf_adjust_tx_level(callInfo.conf_slot, 1.5);
}

- (void)setMicrophoneMuted:(BOOL)microphoneMuted {
    // 自己发不发出音频流
    if (microphoneMuted) {
        // 设置静音
        pjsua_call_info callInfo;
        pjsua_call_get_info(self.tempCModel.callId, &callInfo);
        pj_status_t status = pjsua_conf_disconnect(0, callInfo.conf_slot);
        if (status == PJ_SUCCESS) {
            NSLog(@"设置静音成功");
            _microphoneMuted = microphoneMuted;
        }else {
            NSLog(@"设置静音Error muting microphone in call %@", self);
        }
    }else {
        // 设置不静音
        pjsua_call_info callInfo;
        pjsua_call_get_info(self.tempCModel.callId, &callInfo);
        pj_status_t status = pjsua_conf_connect(0, callInfo.conf_slot);
        if (status == PJ_SUCCESS) {
            NSLog(@"设置非静音成功");
            _microphoneMuted = microphoneMuted;
        } else {
            NSLog(@"设置非静音Error unmuting microphone in call %@", self);
        }
    }
}

- (void)isSendAudioStream:(BOOL)isSend {
    // 设置语音流不播放
    if (isSend) {
        // 设置静音
        pjsua_call_info callInfo;
        pjsua_call_get_info(self.tempCModel.callId, &callInfo);
        
        pj_status_t status = pjsua_conf_adjust_tx_level(0, 0);
        if (status == PJ_SUCCESS) {
            NSLog(@"设置静音成功");
//            _microphoneMuted = microphoneMuted;
        }else {
            NSLog(@"设置静音Error muting microphone in call %@", self);
        }
    }else {
        // 设置不静音
        pjsua_call_info callInfo;
        pjsua_call_get_info(self.tempCModel.callId, &callInfo);
        pj_status_t status = pjsua_conf_adjust_tx_level(0, 1);
        if (status == PJ_SUCCESS) {
            NSLog(@"设置非静音成功");
//            _microphoneMuted = microphoneMuted;
        } else {
            NSLog(@"设置非静音Error unmuting microphone in call %@", self);
        }
    }
}

- (void)setVolume {
//    pjsua_player_get_conf_port(<#pjsua_player_id id#>)
//    pjsua_conf_adjust_rx_level(<#pjsua_conf_port_id slot#>, <#float level#>)
//    pjsua_conf_adjust_tx_level(<#pjsua_conf_port_id slot#>, <#float level#>)
    
//    pjsua_set_snd_dev(<#int capture_dev#>, <#int playback_dev#>)
//    pjsua_set
}

#pragma mark - 通知 
- (void)sip_incoming_call_notification:(NSNotification *)notification {
    PSCallModel *model = notification.object;
    NSLog(@"来电通知 incoming model : %@",model);
    self.tempCModel = model;
    if (self.incomingBlock) {
        self.incomingBlock(model);
    }
}

- (void)sip_call_state_notification:(NSNotification *)notification {
    PSCallModel *model = notification.object;
    NSLog(@"电话状态通知 call model : %@",model);
    self.tempCModel = model;
    if (self.callBlock) {
        self.callBlock(model);
    }
}

- (void)sip_register_state_notification:(NSNotification *)notification {
    PSAccModel *model = notification.object;
    NSLog(@"FS注册返回 PSAccModel  model : %@",model);
    if (model.state == PJ_SC_OK) {
        isRegisterSuccss = YES;
    }
    if (self.registerBlock) {
        self.registerBlock(model);
    }
}

@end




static void on_incoming_call(pjsua_acc_id acc_id, pjsua_call_id call_id, pjsip_rx_data *rdata) {
    pjsua_call_info ci;
    pjsua_call_get_info(call_id, &ci);
    
    NSString *remote_info = [NSString stringWithUTF8String:ci.remote_info.ptr];

    NSUInteger startIndex = [remote_info rangeOfString:@"<"].location;
    NSUInteger endIndex = [remote_info rangeOfString:@">"].location;
    
    NSString *remote_address = [remote_info substringWithRange:NSMakeRange(startIndex + 1, endIndex - startIndex - 1)];
    remote_address = [remote_address componentsSeparatedByString:@":"][1];
    remote_address = [remote_address componentsSeparatedByString:@"@"].firstObject;
    
//
//    id argument = @{
//                    @"call_id"          : @(call_id),
//                    @"remote_address"   : remote_address
//                    };
    
    PSCallModel *model = [PSCallModel new];
    model.callId = call_id;
    model.state = (PJ_INV_STATE)ci.state;///pjsip_inv_state
    model.mapedMobile = remote_address;
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [[NSNotificationCenter defaultCenter] postNotificationName:sip_incoming_call_notification object:model userInfo:nil];
    });
    
}

static void on_call_state(pjsua_call_id call_id, pjsip_event *e) {
    pjsua_call_info ci;
    pjsua_call_get_info(call_id, &ci);
    
//    id argument = @{
//                    @"call_id"  : @(call_id),
//                    @"state"    : @(ci.state)
//                    };
    
    PSCallModel *model = [PSCallModel new];
    model.callId = call_id;
    model.state = (PJ_INV_STATE)ci.state;//pjsip_inv_state
    
    NSString *s = [NSString stringWithFormat:@"%s",ci.buf_.call_id];
    model.callIdString = s;
//    NSLog(@"call state callId : %d  acc_id : %d callIdString : %@",ci.id,ci.acc_id,s);
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [[NSNotificationCenter defaultCenter] postNotificationName:sip_call_state_notification object:model userInfo:nil];
    });
}

static void on_call_media_state(pjsua_call_id call_id) {
    NSLog(@"音频通知");
    pjsua_call_info ci;
    pjsua_call_get_info(call_id, &ci);
    
    if (ci.media_status == PJSUA_CALL_MEDIA_ACTIVE) {
        // When media is active, connect call to sound device.
        pjsua_conf_connect(ci.conf_slot, 0);
        pjsua_conf_connect(0, ci.conf_slot);
    }
}

static void on_reg_state(pjsua_acc_id acc_id) {
    pj_status_t status;
    pjsua_acc_info info;
    
    status = pjsua_acc_get_info(acc_id, &info);
    if (status != PJ_SUCCESS)
        return;
    
//    id argument = @{
//                    @"acc_id"       : @(acc_id),
//                    @"status_text"  : [NSString stringWithUTF8String:info.status_text.ptr],
//                    @"status"       : @(info.status)
//                    };
    
    NSString *acc_uri = [NSString stringWithUTF8String:info.acc_uri.ptr];
    NSLog(@"register info : %@  status : %d",acc_uri,info.status);
    
    PSAccModel *model = [PSAccModel new];
    model.accId = acc_id;
    model.state = info.status;
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [[NSNotificationCenter defaultCenter] postNotificationName:sip_register_state_notification object:model userInfo:nil];
    });
}

static void on_reg_state2(pjsua_acc_id acc_id, pjsua_reg_info *info) {
//    NSLog(@"acc_id : %d  info->cbparam->code : %d",acc_id,info->cbparam->code);
}
