//
//  BKPasscodeViewController.h
//  BKPasscodeViewDemo
//
//  Created by Byungkook Jang on 2014. 4. 20..
//  Copyright (c) 2014년 Byungkook Jang. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BKPasscodeInputView.h"

typedef enum : NSUInteger {
    BKPasscodeViewControllerNewPasscodeType,
    BKPasscodeViewControllerChangePasscodeType,
    BKPasscodeViewControllerCheckPasscodeType
} BKPasscodeViewControllerType;

@protocol BKPasscodeViewControllerDelegate;

@interface BKPasscodeViewController : UIViewController <BKPasscodeInputViewDelegate>

@property (nonatomic, assign) id<BKPasscodeViewControllerDelegate> delegate;

@property (nonatomic) BKPasscodeViewControllerType      type;
@property (nonatomic) BKPasscodeInputViewPasscodeStyle  passcodeStyle;
@property (nonatomic) UIKeyboardType                    keyboardType;


/**
 * Customize passcode input view
 * You may override to customize passcode input view appearance.
 */
- (void)customizePasscodeInputView:(BKPasscodeInputView *)aPasscodeInputView;

@end

@protocol BKPasscodeViewControllerDelegate <NSObject>

/**
 * Tells the delegate that passcode is created or authenticated successfully.
 */
- (void)passcodeViewController:(BKPasscodeViewController *)aViewController didFinishWithPasscode:(NSString *)aPasscode;

@optional

/**
 * Ask the delegate to verify that a passcode is correct. You must call the resultHandler with result.
 * You can check passcode asynchronously and show progress view (e.g. UIActivityIndicator) in the view controller if authentication takes too long.
 * You must call result handler in main thread.
 */
- (void)passcodeViewController:(BKPasscodeViewController *)aViewController authenticatePasscode:(NSString *)aPasscode resultHandler:(void(^)(BOOL succeed))aResultHandler;

/**
 * Tells the delegate that user entered incorrect passcode. 
 * You should manage failed attempts yourself and it should be returned by -[BKPasscodeViewControllerDelegate passcodeViewControllerNumberOfFailedAttempts:] method.
 */
- (void)passcodeViewControllerDidFailAttempt:(BKPasscodeViewController *)aViewController;

/**
 * Ask the delegate that how many times incorrect passcode entered to display failed attempt count.
 */
- (NSUInteger)passcodeViewControllerNumberOfFailedAttempts:(BKPasscodeViewController *)aViewController;

/**
 * Ask the delegate that whether passcode view should lock or unlock.
 * If you return nil, passcode view will unlock otherwise it will lock until the date.
 */
- (NSDate *)passcodeViewControllerLockUntilDate:(BKPasscodeViewController *)aViewController;

@end