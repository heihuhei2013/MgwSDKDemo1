//
//  MgwSDK.h
//
//  Created by Berry Shum on 17-11-16.
//  Copyright (c) 2017 Think Fly. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#ifdef __cplusplus
#define MgwSDK_EXTERN		extern "C" __attribute__((visibility ("default")))
#else
#define MgwSDK_EXTERN	    extern __attribute__((visibility ("default")))
#endif

/// 游戏角色相关事件
typedef NS_ENUM(NSInteger, GameOperateType)
{
    GameOperateTypeCreateRole = 1,  //创建角色
    GameOperateTypeEnterGame,      //进入游戏
    GameOperateTypeLevelUp,       //角色升级
    GameOperateTypeExitGame      //退出游戏,切换账号后调用
};

//resultType;msg;code;
typedef void (^CompletionHandler)(NSDictionary *resultDic,NSError *error);
typedef void (^OrderIDCallback)(NSString *orderID);
typedef void (^OrderResultHandler)(NSInteger code,NSError *orderError);//code(1:success, 404:fail ,-1:cancel, -100:unknown,999:未登录)
typedef void (^LogoutHandler)(BOOL isClickConfirm);

@interface MgwOrderInfo : NSObject

@property (nonatomic, copy) NSString *price;          //订单对应的金额，单位元
@property (nonatomic, copy) NSString *productID;      //内购项在itunes connect的product ID
@property (nonatomic, copy) NSString *productName;    //商品名称
@property (nonatomic, copy) NSString *productDesc;    //商品描述
@property (nonatomic, copy, readonly) NSString *code; //eagle订单号,无需填写,备用
@property (nonatomic, copy) NSString *notifyUrl;      //发货地址,不建议填写，建议在SDK服务器配置
@property (nonatomic, copy) NSString *roleID;         //角色ID
@property (nonatomic, copy) NSString *roleName;       //角色名称
@property (nonatomic, copy) NSString *roleLevel;      //角色等级
@property (nonatomic, copy) NSString *serverID;       //角色所在服务器ID
@property (nonatomic, copy) NSString *serverName;     //角色所在服务器名称
@property (nonatomic, copy) NSString *ext;            //扩展信息,支付成功后原信息回调到服务器，通常方游戏自己订单号

@end

@protocol MgwDelegate <NSObject>

@required

- (void)logoutCallbackWithTokenExpired:(BOOL)isTokenExpired;

@end

@interface MgwSDK : NSObject

/**
 init SDK
 
 @param gameID <#gameID description#>
 @param gameKey <#gameKey description#>
 @param reYunAppkey <#reYunAppkey description#>
 @param eagleAppID <#eagleAppID description#>
 @param eagleAppKey <#eagleAppKey description#>
 @param eagleCID <#eagleCID description#>
 @param delegate <#delegate description#>
 */
+ (void)initWithGameID:(NSNumber *)gameID
               gameKey:(NSString *)gameKey
           reYunAppkey:(NSString *)reYunAppkey
            eagleAppID:(NSNumber *)eagleAppID
           eagleAppKey:(NSString *)eagleAppKey
        eagleChannelID:(NSNumber *)eagleCID
              delegate:(id<MgwDelegate>)delegate;

//token;userID;username;from

/**
 login SDK

 @param loginResult <#loginResult description#>
 */
+ (void)loginWithCompletionHandler:(CompletionHandler)loginResult;

//orderID,from
+ (void)makeAnOrder:(MgwOrderInfo *)orderInfo orderIDCallback:(OrderIDCallback)orderIDCallback orderResultHandler:(OrderResultHandler)orderResult;

//msg from
+ (void)showUserCenterWithCompletionHandler:(CompletionHandler)showResult;

+ (void)logoutWihtHandler:(LogoutHandler)logoutHandler;

/**此方法请必须调用
 *type: 操作类型，具体看GameOperateType
 *serverID: 服务器ID
 *roleID: 角色ID
 *serverName: 服务器名称
 *roleName: 角色当前名称
 *roleLevel: 角色当前等级
 */
+ (void)roleEventWithGameOperateType:(GameOperateType)type
                            serverID:(NSString *)serverID
                              roleID:(NSString *)roleID
                          serverName:(NSString *)serverName
                            roleName:(NSString *)roleName
                           roleLevel:(NSString *)roleLevel;


/**
 <#Description#>

 @return <#return value description#>
 */
+ (NSString *)getSDKVersion;

//开启打印日志   正式上线包请关掉 默认不打印
+ (void)setPrintLog :(BOOL)print;

+ (BOOL)isCustomWindow:(UIWindow *)window;

#pragma mark url处理
//dictionary key : msg  code(1:success, 404:fail ,-1:cancel, -100:unknown)
+ (void)handleOpenURL:(NSURL *)url completionHandler:(OrderResultHandler)urlHandler;

// UIApplicationDelegate事件
#pragma mark Application生命周期
+ (void)applicationWillResignActive:(UIApplication *)application;

+ (void)applicationDidEnterBackground:(UIApplication *)application;

+ (void)applicationWillEnterForeground:(UIApplication *)application;

+ (void)applicationDidBecomeActive:(UIApplication *)application;

+ (void)applicationWillTerminate:(UIApplication *)application;

@end
