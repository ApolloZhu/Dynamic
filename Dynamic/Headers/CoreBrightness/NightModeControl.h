//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//

#import "SunriseSunsetProvider.h"
#import "NightShiftSupportProtocol-Protocol.h"
// //  NSDictionary, NSMutableDictionary, OS_dispatch_queue, OS_dispatch_source, NSString, SunriseSunsetProvider;

__attribute__((visibility("hidden")))
@interface NightModeControl : NSObject
{
    NSMutableDictionary *_properties;
    SunriseSunsetProvider *_sunriseSunsetProvider;
    int _sunriseSunsetInfoQueryTimeout;
    NSDictionary *_sunriseSunsetInfo;
    id <NightShiftSupportProtocol> _supportObj;
    OS_dispatch_queue *_queue;
    OS_dispatch_source *_nextTransitionTimer;
    OS_dispatch_source *_transitionTimer;
    OS_dispatch_source *_aggdUpdateTimer;
    struct BLRAggdInfo _aggdKeysInfo;
    int _algoState;
    float _transitionLength;
    float _transitionLengthActual;
    float _transitionsTimesCoeff;
    float _transitionRate;
    float _minFactor;
    float _maxFactor;
    struct NMFactorState _factorState;
    struct __CFTimeZone *_currentTimeZone;
    double _sunsetAbsolute;
    double _sunsetPreviousAbsolute;
    double _sunriseAbsolute;
    double _sunrisePreviousAbsolute;
    double _offTransitionTimeAbsoluteUnrestricted;
    double _offTransitionTimeAbsoluteUnrestrictedPrev;
    BOOL _transitionTimesValid;
    BOOL _isDaylight;
    int _currentScheduledTransitionType;
    double _displayOffTimestamp;
    double _untilNexTransitionTimestamp;
    float _inactivityTimeout;
    BOOL _checkInactivity;
    BOOL _displayOff;
    int _logLevel;
    CDUnknownBlockType _callbackBlock;
    CDStruct_768fa5c4 _status;
    CDStruct_6cee55f3 _backupSchedule;
    BOOL _statusUpdated;
    NSString *_currentSunriseKey;
    NSString *_currentSunsetKey;
    NSString *_previousSunriseKey;
    NSString *_previousSunsetKey;
    NSString *_nextSunriseKey;
    NSString *_nextSunsetKey;
    NSString *_isDaylightKey;
    int _notifyUserAboutScheduleCounter;
    struct __CFUserNotification *_enableNotification;
    BOOL _notificationInProgress;
    BOOL _revertToSunriseSunset;
    struct __CFString *_userName;
}

- (void)displayAlertInteractive:(BOOL)arg1;
- (id)copyTimeStringWithHour:(int)arg1 minute:(int)arg2 second:(int)arg3;
- (void)cancelTransition;
- (void)cancelSchedule;
- (void)cancelAggdPeriodicUpdate;
- (void)tearDownAllTimers;
- (void)clockChanged;
- (void)timeZoneChanged;
- (void)setAlgoState:(int)arg1;
- (void)updateOptionTimestamp:(double)arg1;
- (BOOL)updateTransitionTimesFromSunriseSunset:(double)arg1;
- (void)retrieveSunriseSunsetTimesFromBackup:(double)arg1;
- (void)updateSunriseSunsetInfo:(id)arg1;
- (void)updateSunriseSunsetBackup;
- (void)setSunPermitted:(BOOL)arg1;
- (void)reevaluateCurrentStateWithFactorFadeOption:(float)arg1;
- (void)reevaluateCurrentState;
- (void)initiateFullMinTransition;
- (void)initiateFullMaxTransition;
- (void)initiateRestrictedMaxTransition;
- (void)updateTransitionTimes:(double)arg1;
- (BOOL)updateTransitionTimesFromSchedule:(double)arg1;
- (void)transitionTimerHandler;
- (void)setNightModeFactor:(float)arg1 withFadePeriod:(float)arg2;
- (void)setNightModeFactor:(float)arg1;
- (void)scheduleAggdKeysUpdate;
- (void)aggdKeysUpdate;
- (void)scheduleNextTransition:(double)arg1 withType:(int)arg2;
- (void)initiateTransitionTo:(float)arg1 andRampLength:(float)arg2;
- (void)enableBlueLightReduction:(BOOL)arg1 withOption:(int)arg2;
- (void)setSchedule:(id)arg1;
- (void)setMode:(int)arg1;
- (BOOL)setProperty:(id)arg1 forKey:(id)arg2;
- (id)getPropertyForKey:(id)arg1;
- (void)dealloc;
- (void)switchToUser:(struct __CFString *)arg1;
- (id)initWithSupportObject:(id)arg1 queue:(id)arg2 callback:(CDUnknownBlockType)arg3;
- (id)copyLowPowerModeState;
- (void)updateLowPowerModeState:(id)arg1;
- (void)updateStatusDictionaryWithValue:(id)arg1 forKey:(id)arg2;
- (id)copyStatusDictionaryFromPrefs;
- (void)saveStatusToPrefs:(id)arg1;
- (id)copyDictionaryFromStatus:(CDStruct_768fa5c4 *)arg1;
- (BOOL)parseStatusDictionary:(id)arg1 intoStruct:(CDStruct_768fa5c4 *)arg2 shouldUpdatePrefs:(char *)arg3;

@end

