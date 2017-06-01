//
//  SGDownloadImp.h
//  SGDownload
//
//  Created by Single on 2017/3/17.
//  Copyright © 2017年 single. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <TargetConditionals.h>
#import "SGDownloadTask.h"
@class SGDownload;

NS_ASSUME_NONNULL_BEGIN


// delegate
@protocol SGDownloadDelegate <NSObject>

@optional;
- (void)downloadDidCompleteAllRunningTasks:(SGDownload *)download;      // maybe finished, canceled and failured.
- (void)download:(SGDownload *)download taskStateDidChange:(SGDownloadTask *)task;
- (void)download:(SGDownload *)download taskProgressDidChange:(SGDownloadTask *)task;

@end


extern NSString * const SGDownloadDefaultIdentifier;    // default identifier.


@interface SGDownload : NSObject


// instancetype
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)download;    // default download manager.
+ (instancetype)downloadWithIdentifier:(NSString *)identifier;


// archive
+ (NSString *)archiverDirectoryPath;
+ (NSString *)archiverFilePathWithIdentifier:(NSString *)identifier;

#if TARGET_OS_IOS || TARGET_OS_TV
// background events
+ (void)handleEventsForBackgroundURLSession:(NSString *)identifier completionHandler:(void (^)())completionHandler;
#endif


// configuration
@property (nonatomic, copy, readonly) NSString * identifier;
@property (nonatomic, strong, readonly) NSURLSessionConfiguration * sessionConfiguration;

@property (nonatomic, weak) id <SGDownloadDelegate> delegate;
@property (nonatomic, strong, readonly) dispatch_queue_t delegateQueue;       // default is main queue.
@property (nonatomic, assign) NSUInteger maxConcurrentOperationCount;       // defalut is 1.


// get task
@property (nonatomic, strong, readonly) NSArray <SGDownloadTask *> * tasks;
- (NSMutableArray <SGDownloadTask *> *)tasksRunningOrWatting;
- (NSMutableArray <SGDownloadTask *> *)tasksWithState:(SGDownloadTaskState)state;

- (nullable SGDownloadTask *)taskWithContentURL:(NSURL *)contentURL;    // if return nil, there is no task of the contentURL.


// add task
- (void)addDownloadTask:(SGDownloadTask *)task;
- (void)addDownloadTasks:(NSArray <SGDownloadTask *> *)tasks;

- (void)addSuppendTask:(SGDownloadTask *)task;
- (void)addSuppendTasks:(NSArray <SGDownloadTask *> *)tasks;


// control task
- (void)resumeAllTasks;
- (void)resumeTask:(SGDownloadTask *)task;
- (void)resumeTasks:(NSArray <SGDownloadTask *> *)tasks;

- (void)suspendAllTasks;
- (void)suspendTask:(SGDownloadTask *)task;
- (void)suspendTasks:(NSArray <SGDownloadTask *> *)tasks;

- (void)cancelAllTasks;
- (void)cancelTask:(SGDownloadTask *)task;
- (void)cancelTasks:(NSArray <SGDownloadTask *> *)tasks;

- (void)cancelAllTasksAndDeleteFiles;
- (void)cancelTaskAndDeleteFile:(SGDownloadTask *)task;
- (void)cancelTasksAndDeleteFiles:(NSArray <SGDownloadTask *> *)tasks;


// download live cycle
- (void)run;
- (void)invalidate;


@end


NS_ASSUME_NONNULL_END
