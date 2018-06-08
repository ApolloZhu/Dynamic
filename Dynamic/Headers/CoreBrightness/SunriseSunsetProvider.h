//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//

#import "_CDClientContext.h"
#import "_CDContextualChangeRegistration.h"
#import "_CDContextualKeyPath.h"
#import "_CDContextualPredicate.h"

__attribute__((visibility("hidden")))
@interface SunriseSunsetProvider : NSObject
{
    _CDClientContext *_duetContextStore;
    _CDContextualKeyPath *_duetKeyPath;
    _CDContextualChangeRegistration *_duetRegistration;
    NSDictionary *_duetInfo;
    OS_dispatch_semaphore *_duetDispatchSemaphore;
    BOOL _sunriseSunsetNotificationEnabled;
    CDUnknownBlockType _callbackBlock;
    CDUnknownBlockType _duetCallback;
    _CDContextualPredicate *_predicate;
    int _logLevel;
}

@property int logLevel; // @synthesize logLevel=_logLevel;
- (void)updateSunriseSunsetInfo;
- (id)copySunriseSunsetInfo:(int)arg1;
- (void)dealloc;
- (void)cancel;
- (void)unregisterNotification;
- (void)unregisterBlock;
- (void)registerBlock:(CDUnknownBlockType)arg1;
- (id)initWithCallback:(CDUnknownBlockType)arg1;
- (id)copySunsetSunriseInfoFromContext;

@end

