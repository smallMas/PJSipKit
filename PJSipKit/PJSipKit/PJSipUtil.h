//
//  PJSipUtil.h
//  PJSipKit
//
//  Created by vargo－mac on 2017/4/25.
//  Copyright © 2017年 vargo－mac. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PJSipUtil : NSObject

+ (NSString *)callUrlWithUserId:(NSString *)userId serverIp:(NSString *)serverIp port:(int)port;

+ (NSString *)serverIp;
+ (int)serverPort;

@end
