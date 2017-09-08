//
//  PSCallModel.m
//  PJSipKit
//
//  Created by vargo－mac on 2017/4/25.
//  Copyright © 2017年 vargo－mac. All rights reserved.
//

#import "PSCallModel.h"

@implementation PSCallModel

- (NSString *)description {
    return [NSString stringWithFormat:@"[%@] callId : %d  state : %d",[self class],self.callId,self.state];
}

@end
