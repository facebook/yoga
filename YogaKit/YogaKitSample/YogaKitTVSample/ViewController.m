//
//  ViewController.m
//  YogaKitTVSample
//
//  Created by lvv on 2020/8/13.
//  Copyright © 2020 facebook. All rights reserved.
//

#import "ViewController.h"
@import YogaKit;

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    CGSize containerSize = self.view.bounds.size;

    UIView *root = self.view;
    root.backgroundColor = UIColor.whiteColor;
    [root configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.width = YGPointValue(containerSize.width);
        layout.height = YGPointValue(containerSize.height);
        layout.alignItems = YGAlignCenter;
        layout.justifyContent = YGJustifyCenter;
    }];

    UIView *child1 = [[UIView alloc] init];
    child1.backgroundColor = UIColor.blueColor;
    [child1 configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.width = YGPointValue(100);
        layout.height = YGPointValue(10);
        layout.marginBottom = YGPointValue(25);
    }];
    [root addSubview:child1];

    UIView *child2 = [[UIView alloc] init];
    child2.backgroundColor = UIColor.greenColor;
    [child2 configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.alignSelf = YGAlignFlexEnd;
        layout.width = YGPointValue(200);
        layout.height = YGPointValue(200);
    }];
    [root addSubview:child2];

    UIView *child3 = [[UIView alloc] init];
    child3.backgroundColor = UIColor.yellowColor;
    [child3 configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.alignSelf = YGAlignFlexStart;
        layout.width = YGPointValue(100);
        layout.height = YGPointValue(100);
    }];
    [root addSubview:child3];
}

@end
