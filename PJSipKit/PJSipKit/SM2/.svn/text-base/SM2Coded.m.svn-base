//
//  SM2Coded.m
//  SM2Simple
//
//  Created by bolei on 16/12/6.
//  Copyright © 2016年 pingan. All rights reserved.
//

#import "SM2Coded.h"
#import <Sm2/sm2.h>
#import "NSData+HexString.h"

//int test_GM_encryption_and_decryption()
//{
//    printf("\n********\n* GM sm2 asym encryption and decryption test\n********\n");
//    printf("...you can check the route on \"Public Key Cryptographic Algorithm SM2 Based on Elliptic Curves\" page [90]...\n");
//    printf("...to check, please make sure that the sm2lib is a debug version, make it under \'-D_DEBUG\' when compile...\n\n\n");
//    unsigned char buff[64] = {0};unsigned long buffLen = 64;
//    unsigned char prikeyBuff[200] = {0};unsigned long priLen = 200;
//    int ret = 0;
//    char * plain = "encryption standard";
//    unsigned char encData[1000] = {0};
//    unsigned long encLen = 1000;
//    unsigned char decData[1000] = {0};
//    unsigned long decLen = 1000;
//    //#ifdef _DEBUG
////    char * pubkey_B_XY = "435B39CCA8F3B508C1488AFC67BE491A0F7BA07E581A0E4849A5CF70628A7E0A75DDBA78F15FEECB4C7895E2C1CDF5FE01DEBB2CDBADF45399CCF77BBA076A42";
////    char * prikey = "1649AB77A00637BD5E2EFE283FBF353534AA7F7CB89463F208DDBC2920BB0DA0";
////    char * pubkey_B_XY = "4120C39BD637659ED81447A0606CD84E3F3175F3A766F539DED4E56718ED530EC5A5ACA9E2823AC8AF492F7FC9265B7B0C063019B05784896722180614D76460";
////    char * prikey = "3DAA02EC4056785306AC4DCC7483686B8DCCB3D434CB0C1245D8AE5BAB126A54";
////    @"044120C39BD637659ED81447A0606CD84E3F3175F3A766F539DED4E56718ED530EC5A5ACA9E2823AC8AF492F7FC9265B7B0C063019B05784896722180614D76460"
//    
//    char * pubkey_B_XY = "9dedc269d3a76b44fd8e3d88b8e7857f5b658a983c858bf1c76efdce5a6f6673af30d2c7acf1d43529ae369693f4dfdd26300705f00e228eb813d91af500df48";
//    char * prikey = "37503364450f93fdb5c230b14bb166af209d5e0393575e8ec277a92dc6ec9b15";
//    
//    NSLog(@"strlen(pubkey_B_XY) length : %d",strlen(pubkey_B_XY));
//    ret = hexCharStr2unsignedCharStr(pubkey_B_XY, strlen(pubkey_B_XY), 0, buff, &buffLen);
//    CHECK_RET(ret);
//    ret = hexCharStr2unsignedCharStr(prikey, strlen(prikey),0, prikeyBuff, &priLen);
//    CHECK_RET(ret);
//    //#else
//    //	ret = GM_GenSM2keypair(prikeyBuff, &priLen, buff);
//    //	CHECK_RET(ret);
//    //#endif
//    printf("...public key\n");
//    printf("XB=");
////    BYTE_print(buff, 32);
//    printf("YB=");
////    BYTE_print(buff+32, 32);
//    
//    printf("...plain text:\n%s\n", plain);
//    
//    ret = GM_SM2Encrypt(encData, &encLen, (unsigned char *)plain, strlen(plain), buff, buffLen, 1);
//    //	LOGI("sm2test ...ret2: %d, plain text: %s", ret, plain);
//    NSLog(@"ret1 >>> %d",ret);
//    if (ret != MP_OKAY) {
//        NSLog(@"加密出错");
//    }else {
//        NSData *data = [NSData dataWithBytes:encData + 1 length:encLen - 1];
//        NSString *s = [data hexStringFromData:data];
//        NSLog(@"s >>> %@",s);
//    }
//    CHECK_RET(ret);
//    ret = GM_SM2Decrypt(decData, &decLen, encData, encLen, prikeyBuff, priLen, 1);
//    //	LOGI("sm2test...ret2: %d, decdata: %s", ret, decData);
//    NSLog(@"ret2 >>> %d",ret);
//    if (ret != MP_OKAY) {
//        NSLog(@"解密出错");
//    }else {
//        NSData *d = [NSData dataWithBytes:encData length:encLen];
//        NSLog(@"encData >>> %@",d);
//        NSString *sd = [[NSString alloc] initWithData:d encoding:NSUTF8StringEncoding];
//        NSLog(@"sd >> %@",sd);
//        NSString *resultStr = [[NSString alloc] initWithBytes:encData length:encLen encoding:NSUTF8StringEncoding];
//        NSLog(@"resultStr >>> %@",resultStr);
//    }
//    CHECK_RET(ret);
//    
//    printf("\n...decdata:%s\n", decData);
//    
//END:
//    
//    printf("********\n* test end\n********\n");
//    return ret;
//}

@implementation SM2Coded


+ (void)test {
//    test_GM_encryption_and_decryption();
}

+ (NSString *)sm2Encode:(NSString *)str key:(NSString *)key {
    if ([str length] == 0 || [key length] == 0) {
        return @"";
    }
    
    NSString *pubKey = key;
    if (key.length == 130) {
        pubKey = [key substringFromIndex:2];
    }
    
    unsigned char result[1024] = {0};
    unsigned long outlen = 1024;
    const char *encryptData = [str cStringUsingEncoding:NSUTF8StringEncoding];
    NSData *keyData =  [NSData dataFromHexString:pubKey];
    
    int ret = GM_SM2Encrypt(result,&outlen,(unsigned char *)encryptData,strlen(encryptData),(unsigned char *)keyData.bytes,keyData.length,1);
    
    if (outlen < 2 || ret != MP_OKAY) {
        //加密出错了
        return @"";
    }
    
    NSData *data = [NSData dataWithBytes:result length:outlen];
    NSString *cipher = [data hexStringFromData:data];
    
//    //多一位\x04 需要去掉
//    NSData *data = [NSData dataWithBytes:result + 1 length:outlen - 1];
//    
//    NSString *cipher = [data hexStringFromData:data];
//    
//    if (key.length == 130) {
//        cipher = [NSString stringWithFormat:@"04%@",cipher];
//    }
    
    return cipher;
}

+ (NSString *)sm2Decode:(NSString *)str key:(NSString *)key {
    //密文长度至少也需要64+32位
    if ([str length] < 64 + 32 || [key length] == 0) {
        return @"";
    }
    
//    NSString *cipher = str;
//    NSString *top2 = [cipher substringToIndex:2];
//    if ([top2 isEqualToString:@"04"]) {
//        cipher = [str substringFromIndex:2];
//    }
    
    unsigned char result[1024 * 8] = {0};
    
//    unsigned char pass[1024] = {0};
    
    NSData *keyData =  [NSData dataFromHexString:key];
    
    NSData *data = [NSData dataFromHexString:str];
//    pass[0] = '\x04'; //需要补一位\x04
//    memcpy(pass + 1, data.bytes, data.length);
    
    unsigned long outlen = 1024;
    
//    int ret = GM_SM2Decrypt((unsigned char *)result, &outlen, pass, data.length + 1, (unsigned char *)keyData.bytes, keyData.length,1);
    int ret = GM_SM2Decrypt((unsigned char *)result, &outlen, (unsigned char *)data.bytes, data.length, (unsigned char *)keyData.bytes, keyData.length,1);

    if (outlen == 0 || ret != MP_OKAY) {
        //加密出错了
        return @"";
    }
    NSString *resultStr = [[NSString alloc] initWithBytes:result length:outlen encoding:NSUTF8StringEncoding];
    
    return resultStr;
}


@end
