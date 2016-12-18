/**
 * Copyright 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE-examples file in the root directory of this source tree.
 */

#import "ViewController.h"
#import <YogaKit/YogaKit.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    UIView *root = self.view;
    root.backgroundColor = [UIColor redColor];
    [root yk_setUsesYoga:YES];
    [root yk_setWidth:self.view.bounds.size.width];
    [root yk_setHeight:self.view.bounds.size.height];
    [root yk_setAlignItems:YKAlignCenter];
    [root yk_setJustifyContent:YKJustifyCenter];

    UIView *child1 = [UIView new];
    child1.backgroundColor = [UIColor blueColor];
    [child1 yk_setUsesYoga:YES];
    [child1 yk_setWidth:100];
    [child1 yk_setHeight:100];

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
    [root yk_applyLayout];
}


@end
