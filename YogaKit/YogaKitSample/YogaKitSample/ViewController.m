/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "ViewController.h"

#import <YogaKit/UIView+Yoga.h>

@implementation ViewController

- (void)viewDidLoad
{
    UIView *root = self.view;
    root.backgroundColor = [UIColor redColor];
    root.yoga.isEnabled = YES;
    root.yoga.width = YGPointValue(self.view.bounds.size.width);
    root.yoga.height = YGPointValue(self.view.bounds.size.height);
    root.yoga.alignItems = YGAlignCenter;
    root.yoga.justifyContent = YGJustifyCenter;

    UIView *child1 = [UIView new];
    child1.backgroundColor = [UIColor blueColor];
    child1.yoga.isEnabled = YES;
    child1.yoga.width = YGPointValue(100);
    child1.yoga.height = YGPointValue(100);

    UIView *child2 = [UIView new];
    child2.backgroundColor = [UIColor greenColor];
    child2.frame = (CGRect) {
        .size = {
            .width = 200,
            .height = 100,
        }
    };

    UIView *child3 = [UIView new];
    child3.backgroundColor = [UIColor yellowColor];
    child3.frame = (CGRect) {
        .size = {
            .width = 100,
            .height = 100,
        }
    };

    [child2 addSubview:child3];
    [root addSubview:child1];
    [root addSubview:child2];
    [root.yoga applyLayoutPreservingOrigin:NO];
}


@end
