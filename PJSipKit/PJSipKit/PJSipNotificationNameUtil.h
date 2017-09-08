//
//  PJSipNotificationNameUtil.h
//  PJSipKit
//
//  Created by vargo－mac on 2017/4/10.
//  Copyright © 2017年 vargo－mac. All rights reserved.
//

#import <Foundation/Foundation.h>

#pragma mark - 外部通知
static NSString * const sip_incoming_call_notification = @"sip_incoming_call_notification";


#pragma mark - 内部通知
static NSString * const sip_call_state_notification = @"sip_call_state_notification";

static NSString * const sip_register_state_notification = @"sip_register_state_notification";

@interface PJSipNotificationNameUtil : NSObject

@end
