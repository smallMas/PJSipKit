//
//  PJSipManager.h
//  PJSipKit
//
//  Created by vargo－mac on 2017/4/10.
//  Copyright © 2017年 vargo－mac. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PJSipEnumUtil.h"
#import "PSCallModel.h"
#import "PSAccModel.h"

@interface PJSipManager : NSObject

@property (nonatomic, strong, readonly) NSString *serviceIp;
@property (nonatomic, strong, readonly) NSString *port;
@property (nonatomic, strong, readonly) NSString *encryptedMobile;
@property (nonatomic, strong, readonly) NSString *user_agent;

// 是否静音，默认NO
@property (nonatomic, assign) BOOL microphoneMuted;

+ (instancetype)instance;

/*********************** 配置 ***********************/
- (BOOL)initConfig;

/*********************** 内部接口 ***********************/

/**
 * 设置电话状态回调block
 *
 * @param block 回调
 **/
- (void)setCallBlock:(void (^)(PSCallModel *callModel))block;
/**
 * 来电通知回调block
 *
 * @param block 回调
 **/
- (void)setIncomingCallBlock:(void (^)(PSCallModel *callModel))block;

/**
 * pjsip 登录
 * 
 * @param userName 用户
 * @param password 密码
 * @param serviceIp 服务器IP
 * @param port 端口
 * @param userAgent 设置设备类型/版本号/Voip DeviceToken 例如:IOS/1.1.1/{deviceToken}
 * @param block 注册回调
 **/
- (void)pjsip_loginUserName:(NSString *)userName
                   password:(NSString *)password
                  serviceIp:(NSString *)serviceIp
                       port:(NSString *)port
                  userAgent:(NSString *)userAgent
                      block:(void (^)(PSAccModel *accModel))block;

/**
 * pjsip 呼叫 (不加密版)暂时不需要
 * 
 * @param url 地址 (需要使用[PJSipUtil callUrlWithUserId]得到的地址)
 **/
- (void)pjsip_makeCallTo:(NSString *)url;

/**
 * pjsip 呼叫 (加密版)
 * 
 * @param url 地址 (需要使用[PJSipUtil callUrlWithUserId]得到的地址)
 * @param priKey 私钥
 * @param pubKey 公钥
 **/
- (void)pjsip_makeCallTo2:(NSString *)url priKey:(NSString *)priKey pubKey:(NSString *)pubKey;

/**
 * pjsip 接听 (不加密版)暂时不需要
 * 
 * @param code status code (PJ_SC_RINGING:响铃,PJ_SC_OK:接听)
 * @param callId 呼叫ID
 **/
- (void)pjsip_answer:(PJ_STATUS_CODE)code
              callId:(int)callId;

/**
 * pjsip 接听 (加密版)
 *
 * @param code status code (PJ_SC_RINGING:响铃,PJ_SC_OK:接听)
 * @param callId 呼叫ID
 * @param priKey 私钥
 * @param pubKey 公钥
 **/
- (void)pjsip_answer2:(PJ_STATUS_CODE)code
               callId:(int)callId
               priKey:(NSString *)priKey
               pubKey:(NSString *)pubKey;

/**
 * pjsip 拒绝接听
 *
 * @param code status code (PJ_SC_BUSY_EVERYWHERE)
 * @param callId 呼叫ID
 **/
- (void)pjsip_hangup:(PJ_STATUS_CODE)code
              callId:(int)callId;

/**
 * pjsip 挂断结束
 **/
- (void)pjsip_end;

/**
 * pjsip 注销
 **/
- (void)pjsip_logout;

/**
 * 设置正常声音的比值
 **/
- (void)setRatioOfNormalVolume;

@end
