//
//  PJSipEnumUtil.h
//  PJSipKit
//
//  Created by vargo－mac on 2017/4/25.
//  Copyright © 2017年 vargo－mac. All rights reserved.
//

#import <Foundation/Foundation.h>

//typedef enum {
//    PJSIP_STATUS_CODE_OK = 200,
//    PJSIP_STATUS_CODE_BUSY_EVERYWHERE = 600,
//}PJSIP_STATUS_CODE;

typedef enum {
    PJ_INV_STATE_NULL,	    /**< Before INVITE is sent or received  */
    PJ_INV_STATE_CALLING,	    /**< After INVITE is sent		    */
    PJ_INV_STATE_INCOMING,	    /**< After INVITE is received.	    */
    PJ_INV_STATE_EARLY,	    /**< After response with To tag.	    */
    PJ_INV_STATE_CONNECTING,	    /**< After 2xx is sent/received.	    */
    PJ_INV_STATE_CONFIRMED,	    /**< After ACK is sent/received.	    */
    PJ_INV_STATE_DISCONNECTED,   /**< Session is terminated.		    */
}PJ_INV_STATE;

typedef enum {
    PJ_SC_TRYING = 100,
    PJ_SC_RINGING = 180,
    PJ_SC_CALL_BEING_FORWARDED = 181,
    PJ_SC_QUEUED = 182,
    PJ_SC_PROGRESS = 183,
    
    PJ_SC_OK = 200, /** 接听/回调成功 **/
    PJ_SC_ACCEPTED = 202,
    
    PJ_SC_MULTIPLE_CHOICES = 300,
    PJ_SC_MOVED_PERMANENTLY = 301,
    PJ_SC_MOVED_TEMPORARILY = 302,
    PJ_SC_USE_PROXY = 305,
    PJ_SC_ALTERNATIVE_SERVICE = 380,
    
    PJ_SC_BAD_REQUEST = 400,
    PJ_SC_UNAUTHORIZED = 401,
    PJ_SC_PAYMENT_REQUIRED = 402,
    PJ_SC_FORBIDDEN = 403,
    PJ_SC_NOT_FOUND = 404,
    PJ_SC_METHOD_NOT_ALLOWED = 405,
    PJ_SC_NOT_ACCEPTABLE = 406,
    PJ_SC_PROXY_AUTHENTICATION_REQUIRED = 407,
    PJ_SC_REQUEST_TIMEOUT = 408,
    PJ_SC_GONE = 410,
    PJ_SC_REQUEST_ENTITY_TOO_LARGE = 413,
    PJ_SC_REQUEST_URI_TOO_LONG = 414,
    PJ_SC_UNSUPPORTED_MEDIA_TYPE = 415,
    PJ_SC_UNSUPPORTED_URI_SCHEME = 416,
    PJ_SC_BAD_EXTENSION = 420,
    PJ_SC_EXTENSION_REQUIRED = 421,
    PJ_SC_SESSION_TIMER_TOO_SMALL = 422,
    PJ_SC_INTERVAL_TOO_BRIEF = 423,
    PJ_SC_TEMPORARILY_UNAVAILABLE = 480,
    PJ_SC_CALL_TSX_DOES_NOT_EXIST = 481,
    PJ_SC_LOOP_DETECTED = 482,
    PJ_SC_TOO_MANY_HOPS = 483,
    PJ_SC_ADDRESS_INCOMPLETE = 484,
    PJ_AC_AMBIGUOUS = 485,
    PJ_SC_BUSY_HERE = 486,
    PJ_SC_REQUEST_TERMINATED = 487,
    PJ_SC_NOT_ACCEPTABLE_HERE = 488,
    PJ_SC_BAD_EVENT = 489,
    PJ_SC_REQUEST_UPDATED = 490,
    PJ_SC_REQUEST_PENDING = 491,
    PJ_SC_UNDECIPHERABLE = 493,
    
    PJ_SC_INTERNAL_SERVER_ERROR = 500,
    PJ_SC_NOT_IMPLEMENTED = 501,
    PJ_SC_BAD_GATEWAY = 502,
    PJ_SC_SERVICE_UNAVAILABLE = 503,
    PJ_SC_SERVER_TIMEOUT = 504,
    PJ_SC_VERSION_NOT_SUPPORTED = 505,
    PJ_SC_MESSAGE_TOO_LARGE = 513,
    PJ_SC_PRECONDITION_FAILURE = 580,
    
    PJ_SC_BUSY_EVERYWHERE = 600, /** 拒绝接听 **/
    PJ_SC_DECLINE = 603,
    PJ_SC_DOES_NOT_EXIST_ANYWHERE = 604,
    PJ_SC_NOT_ACCEPTABLE_ANYWHERE = 606,
    
//    PJSIP_SC_TSX_TIMEOUT = PJSIP_SC_REQUEST_TIMEOUT,
//    /*PJSIP_SC_TSX_RESOLVE_ERROR = 702,*/
//    PJSIP_SC_TSX_TRANSPORT_ERROR = PJSIP_SC_SERVICE_UNAVAILABLE,
//    
//    /* This is not an actual status code, but rather a constant
//     * to force GCC to use 32bit to represent this enum, since
//     * we have a code in PJSUA-LIB that assigns an integer
//     * to this enum (see pjsua_acc_get_info() function).
//     */
//    PJSIP_SC__force_32bit = 0x7FFFFFFF
    
}PJ_STATUS_CODE;


@interface PJSipEnumUtil : NSObject

@end
