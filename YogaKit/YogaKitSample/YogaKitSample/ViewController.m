/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import "ViewController.h"

#import <YogaKit/UIView+Yoga.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    UIView *root = self.view;
    root.backgroundColor = [UIColor redColor];
    [root yg_setUsesYoga:YES];
    [root yg_setWidth:self.view.bounds.size.width];
    [root yg_setHeight:self.view.bounds.size.height];
    [root yg_setAlignItems:YGAlignCenter];
    [root yg_setJustifyContent:YGJustifyCenter];

    UIView *child1 = [UIView new];
    child1.backgroundColor = [UIColor blueColor];
    [child1 yg_setUsesYoga:YES];
    [child1 yg_setWidth:100];
    [child1 yg_setHeight:100];

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
    [root yg_applyLayout];
}


@end
