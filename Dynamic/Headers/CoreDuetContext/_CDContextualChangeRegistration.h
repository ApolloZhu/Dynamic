//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//

#import "_CDContextualPredicate.h"

@interface _CDContextualChangeRegistration : NSObject <NSCopying, NSSecureCoding>
{
    BOOL _mustWake;
    BOOL _isDeserialized;
    NSString *_identifier;
    _CDContextualPredicate *_predicate;
    _CDContextualPredicate *_dismissalPolicy;
    CDUnknownBlockType _callback;
    unsigned long long _deviceSet;
}

+ (BOOL)supportsSecureCoding;
+ (id)localNonWakingRegistrationWithIdentifier:(id)arg1 contextualPredicate:(id)arg2 callback:(CDUnknownBlockType)arg3;
+ (id)localWakingRegistrationWithIdentifier:(id)arg1 contextualPredicate:(id)arg2 callback:(CDUnknownBlockType)arg3;
+ (id)registrationWithIdentifier:(id)arg1 contextualPredicate:(id)arg2 dismissalPolicy:(id)arg3 deviceSet:(unsigned long long)arg4 mustWake:(BOOL)arg5 callback:(CDUnknownBlockType)arg6;
@property(nonatomic) BOOL isDeserialized; // @synthesize isDeserialized=_isDeserialized;
@property(nonatomic) BOOL mustWake; // @synthesize mustWake=_mustWake;
@property(nonatomic) unsigned long long deviceSet; // @synthesize deviceSet=_deviceSet;
@property(copy) CDUnknownBlockType callback; // @synthesize callback=_callback;
@property(retain, nonatomic) _CDContextualPredicate *dismissalPolicy; // @synthesize dismissalPolicy=_dismissalPolicy;
@property(retain, nonatomic) _CDContextualPredicate *predicate; // @synthesize predicate=_predicate;
@property(copy, nonatomic) NSString *identifier; // @synthesize identifier=_identifier;
// .cxx_destruct
- (id)description;
- (unsigned long long)hash;
- (BOOL)isEqual:(id)arg1;
- (id)initWithCoder:(id)arg1;
- (void)encodeWithCoder:(id)arg1;
- (id)copyWithZone:(struct _NSZone *)arg1;
- (id)initWithIdentifier:(id)arg1 contextualPredicate:(id)arg2 dismissalPolicy:(id)arg3 deviceSet:(unsigned long long)arg4 mustWake:(BOOL)arg5 callback:(CDUnknownBlockType)arg6;
- (id)init;

@end

