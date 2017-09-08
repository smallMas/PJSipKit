//
//  PJSipUtil.m
//  PJSipKit
//
//  Created by vargo－mac on 2017/4/25.
//  Copyright © 2017年 vargo－mac. All rights reserved.
//

#import "PJSipUtil.h"

@implementation PJSipUtil

+ (NSString *)callUrlWithUserId:(NSString *)userId serverIp:(NSString *)serverIp port:(int)port {
    return [NSString stringWithFormat:@"sip:%@@%@:%d", userId, serverIp, port];
}

+ (NSString *)serverIp {
    return [PJSipManager instance].serviceIp;
}

+ (int)serverPort {
    return [PJSipManager instance].port.intValue;
}

@end
