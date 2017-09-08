//
//  PJSipKit.h
//  PJSipKit
//
//  Created by vargo－mac on 2017/4/10.
//  Copyright © 2017年 vargo－mac. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for PJSipKit.
FOUNDATION_EXPORT double PJSipKitVersionNumber;

//! Project version string for PJSipKit.
FOUNDATION_EXPORT const unsigned char PJSipKitVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <PJSipKit/PublicHeader.h>

/**
 --------------------------------- 参考文献 ---------------------------------
 http://svn.pjsip.org/repos/pjproject/tags/2.5.5/
 https://trac.pjsip.org/repos/wiki/Getting-Started/iPhone
 http://www.tuicool.com/articles/Z7VjMn
 
 --------------------------------- PJSipKit本身配置说明 ---------------------------------
 1、将编译成功后的PJSIP库导入PJSipKit （include文件夹不要导入）
    .a文件需要支持 i386、armv7、armv7s、arm64、x86_64
 2、配置 Build settings -> Search Paths -> Header Search Paths :
 (1)/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include
 (2)$(PROJECT_DIR)/SimpleSipPhone/PJSIP/includes/pjlib
 (3)$(PROJECT_DIR)/SimpleSipPhone/PJSIP/includes/pjmedia
 (4)$(PROJECT_DIR)/SimpleSipPhone/PJSIP/includes/pjnath
 (5)$(PROJECT_DIR)/SimpleSipPhone/PJSIP/includes/pjsip
 (6)$(PROJECT_DIR)/SimpleSipPhone/PJSIP/includes/pjlib-util
 3、在PJSipKit-Prefix.pch 添加 #define PJ_AUTOCONF 1
 
 --------------------------------- 使用说明 ---------------------------------
 1、应用登录后需要调用 PJSipManager -> pjsip_loginUserName:password:serviceIp:port:block
 2、呼叫 (使用加密版) PJSipManager -> pjsip_makeCallTo2:priKey:pubKey
 3、接收到来电通知后 调用响铃 (PJ_SC_RINGING) PJSipManager -> pjsip_answer2:callId:priKey:pubKey
 4、接听 (PJ_SC_OK) PJSipManager -> pjsip_answer2:callId:priKey:pubKey
 5、拒绝接听 PJSipManager -> pjsip_hangup:callId
 6、挂断结束 PJSipManager -> pjsip_end
 7、注销 PJSipManager -> pjsip_logout
 **/

#import "PJSipEnumUtil.h"
#import "PJSipUtil.h"
#import "PJSipManager.h"
#import "PJSipNotificationNameUtil.h"
#import "PSCallModel.h"
#import "PSAccModel.h"
#import "SM2Coded.h"



