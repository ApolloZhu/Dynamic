//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//

#import "CDStructures.h"

@interface CBModule : NSObject
{
    CDUnknownBlockType _notificationBlock;
    OS_os_log *_logHandle;
    OS_dispatch_queue *_queue;
}

- (void)unregisterNotificationBlock;
- (void)registerNotificationBlock:(CDUnknownBlockType)arg1;
- (void)dealloc;
- (id)initWithQueue:(id)arg1;

@end

