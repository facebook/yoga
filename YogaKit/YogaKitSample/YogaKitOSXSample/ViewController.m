//
//  ViewController.m
//  YogaKitOSXSample
//
//  Created by lvv on 2020/8/13.
//  Copyright © 2020 facebook. All rights reserved.
//

#import "ViewController.h"
@import YogaKit;

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSView *root = self.view;
    root.wantsLayer = YES;
    root.layer.backgroundColor = NSColor.whiteColor.CGColor;
    [root configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.alignItems = YGAlignCenter;
        layout.justifyContent = YGJustifyCenter;
    }];

    NSView *child1 = [[NSView alloc] init];
    child1.wantsLayer = YES;
    child1.layer.backgroundColor = NSColor.blueColor.CGColor;
    [child1 configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.width = YGPointValue(100);
        layout.height = YGPointValue(10);
        layout.marginBottom = YGPointValue(25);
    }];
    [root addSubview:child1];

    NSView *child2 = [[NSView alloc] init];
    child2.wantsLayer = YES;
    child2.layer.backgroundColor = NSColor.greenColor.CGColor;
    [child2 configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.alignSelf = YGAlignFlexEnd;
        layout.width = YGPointValue(200);
        layout.height = YGPointValue(200);
    }];
    [root addSubview:child2];

    NSView *child3 = [[NSView alloc] init];
    child3.wantsLayer = YES;
    child3.layer.backgroundColor = NSColor.yellowColor.CGColor;
    [child3 configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.alignSelf = YGAlignFlexStart;
        layout.width = YGPointValue(100);
        layout.height = YGPointValue(100);
    }];
    [root addSubview:child3];
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}


@end
