/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// @generated by gentest/gentest.rb from gentest/fixtures/YGAspectRatioTest.html

import Yoga from 'yoga-layout';
import {
  Align,
  Direction,
  Display,
  Edge,
  Errata,
  ExperimentalFeature,
  FlexDirection,
  Gutter,
  Justify,
  MeasureMode,
  Overflow,
  PositionType,
  Unit,
  Wrap,
} from 'yoga-layout';

test.skip('aspect_ratio_does_not_stretch_cross_axis_dim', () => {
  const config = Yoga.Config.create();
  let root;

  config.setExperimentalFeatureEnabled(ExperimentalFeature.AbsolutePercentageAgainstPaddingEdge, true);

  try {
    root = Yoga.Node.create(config);
    root.setWidth(300);
    root.setHeight(300);

    const root_child0 = Yoga.Node.create(config);
    root_child0.setOverflow(Overflow.Scroll);
    root_child0.setFlexGrow(1);
    root_child0.setFlexShrink(1);
    root_child0.setFlexBasis("0%");
    root.insertChild(root_child0, 0);

    const root_child0_child0 = Yoga.Node.create(config);
    root_child0_child0.setFlexDirection(FlexDirection.Row);
    root_child0.insertChild(root_child0_child0, 0);

    const root_child0_child0_child0 = Yoga.Node.create(config);
    root_child0_child0_child0.setFlexGrow(2);
    root_child0_child0_child0.setFlexShrink(1);
    root_child0_child0_child0.setFlexBasis("0%");
    root_child0_child0_child0.setAspectRatio(1 / 1);
    root_child0_child0.insertChild(root_child0_child0_child0, 0);

    const root_child0_child0_child1 = Yoga.Node.create(config);
    root_child0_child0_child1.setWidth(5);
    root_child0_child0.insertChild(root_child0_child0_child1, 1);

    const root_child0_child0_child2 = Yoga.Node.create(config);
    root_child0_child0_child2.setFlexGrow(1);
    root_child0_child0_child2.setFlexShrink(1);
    root_child0_child0_child2.setFlexBasis("0%");
    root_child0_child0.insertChild(root_child0_child0_child2, 2);

    const root_child0_child0_child2_child0 = Yoga.Node.create(config);
    root_child0_child0_child2_child0.setFlexGrow(1);
    root_child0_child0_child2_child0.setFlexShrink(1);
    root_child0_child0_child2_child0.setFlexBasis("0%");
    root_child0_child0_child2_child0.setAspectRatio(1 / 1);
    root_child0_child0_child2.insertChild(root_child0_child0_child2_child0, 0);

    const root_child0_child0_child2_child0_child0 = Yoga.Node.create(config);
    root_child0_child0_child2_child0_child0.setWidth(5);
    root_child0_child0_child2_child0.insertChild(root_child0_child0_child2_child0_child0, 0);

    const root_child0_child0_child2_child0_child1 = Yoga.Node.create(config);
    root_child0_child0_child2_child0_child1.setFlexGrow(1);
    root_child0_child0_child2_child0_child1.setFlexShrink(1);
    root_child0_child0_child2_child0_child1.setFlexBasis("0%");
    root_child0_child0_child2_child0_child1.setAspectRatio(1 / 1);
    root_child0_child0_child2_child0.insertChild(root_child0_child0_child2_child0_child1, 1);
    root.calculateLayout(undefined, undefined, Direction.LTR);

    expect(root.getComputedLeft()).toBe(0);
    expect(root.getComputedTop()).toBe(0);
    expect(root.getComputedWidth()).toBe(300);
    expect(root.getComputedHeight()).toBe(300);

    expect(root_child0.getComputedLeft()).toBe(0);
    expect(root_child0.getComputedTop()).toBe(0);
    expect(root_child0.getComputedWidth()).toBe(300);
    expect(root_child0.getComputedHeight()).toBe(300);

    expect(root_child0_child0.getComputedLeft()).toBe(0);
    expect(root_child0_child0.getComputedTop()).toBe(0);
    expect(root_child0_child0.getComputedWidth()).toBe(285);
    expect(root_child0_child0.getComputedHeight()).toBe(187);

    expect(root_child0_child0_child0.getComputedLeft()).toBe(0);
    expect(root_child0_child0_child0.getComputedTop()).toBe(0);
    expect(root_child0_child0_child0.getComputedWidth()).toBe(187);
    expect(root_child0_child0_child0.getComputedHeight()).toBe(187);

    expect(root_child0_child0_child1.getComputedLeft()).toBe(187);
    expect(root_child0_child0_child1.getComputedTop()).toBe(0);
    expect(root_child0_child0_child1.getComputedWidth()).toBe(5);
    expect(root_child0_child0_child1.getComputedHeight()).toBe(187);

    expect(root_child0_child0_child2.getComputedLeft()).toBe(192);
    expect(root_child0_child0_child2.getComputedTop()).toBe(0);
    expect(root_child0_child0_child2.getComputedWidth()).toBe(93);
    expect(root_child0_child0_child2.getComputedHeight()).toBe(187);

    expect(root_child0_child0_child2_child0.getComputedLeft()).toBe(0);
    expect(root_child0_child0_child2_child0.getComputedTop()).toBe(0);
    expect(root_child0_child0_child2_child0.getComputedWidth()).toBe(93);
    expect(root_child0_child0_child2_child0.getComputedHeight()).toBe(187);

    expect(root_child0_child0_child2_child0_child0.getComputedLeft()).toBe(0);
    expect(root_child0_child0_child2_child0_child0.getComputedTop()).toBe(0);
    expect(root_child0_child0_child2_child0_child0.getComputedWidth()).toBe(5);
    expect(root_child0_child0_child2_child0_child0.getComputedHeight()).toBe(0);

    expect(root_child0_child0_child2_child0_child1.getComputedLeft()).toBe(0);
    expect(root_child0_child0_child2_child0_child1.getComputedTop()).toBe(0);
    expect(root_child0_child0_child2_child0_child1.getComputedWidth()).toBe(93);
    expect(root_child0_child0_child2_child0_child1.getComputedHeight()).toBe(187);

    root.calculateLayout(undefined, undefined, Direction.RTL);

    expect(root.getComputedLeft()).toBe(0);
    expect(root.getComputedTop()).toBe(0);
    expect(root.getComputedWidth()).toBe(300);
    expect(root.getComputedHeight()).toBe(300);

    expect(root_child0.getComputedLeft()).toBe(0);
    expect(root_child0.getComputedTop()).toBe(0);
    expect(root_child0.getComputedWidth()).toBe(300);
    expect(root_child0.getComputedHeight()).toBe(300);

    expect(root_child0_child0.getComputedLeft()).toBe(30);
    expect(root_child0_child0.getComputedTop()).toBe(0);
    expect(root_child0_child0.getComputedWidth()).toBe(285);
    expect(root_child0_child0.getComputedHeight()).toBe(187);

    expect(root_child0_child0_child0.getComputedLeft()).toBe(98);
    expect(root_child0_child0_child0.getComputedTop()).toBe(0);
    expect(root_child0_child0_child0.getComputedWidth()).toBe(187);
    expect(root_child0_child0_child0.getComputedHeight()).toBe(187);

    expect(root_child0_child0_child1.getComputedLeft()).toBe(93);
    expect(root_child0_child0_child1.getComputedTop()).toBe(0);
    expect(root_child0_child0_child1.getComputedWidth()).toBe(5);
    expect(root_child0_child0_child1.getComputedHeight()).toBe(187);

    expect(root_child0_child0_child2.getComputedLeft()).toBe(0);
    expect(root_child0_child0_child2.getComputedTop()).toBe(0);
    expect(root_child0_child0_child2.getComputedWidth()).toBe(93);
    expect(root_child0_child0_child2.getComputedHeight()).toBe(187);

    expect(root_child0_child0_child2_child0.getComputedLeft()).toBe(0);
    expect(root_child0_child0_child2_child0.getComputedTop()).toBe(0);
    expect(root_child0_child0_child2_child0.getComputedWidth()).toBe(93);
    expect(root_child0_child0_child2_child0.getComputedHeight()).toBe(187);

    expect(root_child0_child0_child2_child0_child0.getComputedLeft()).toBe(88);
    expect(root_child0_child0_child2_child0_child0.getComputedTop()).toBe(0);
    expect(root_child0_child0_child2_child0_child0.getComputedWidth()).toBe(5);
    expect(root_child0_child0_child2_child0_child0.getComputedHeight()).toBe(0);

    expect(root_child0_child0_child2_child0_child1.getComputedLeft()).toBe(0);
    expect(root_child0_child0_child2_child0_child1.getComputedTop()).toBe(0);
    expect(root_child0_child0_child2_child0_child1.getComputedWidth()).toBe(93);
    expect(root_child0_child0_child2_child0_child1.getComputedHeight()).toBe(187);
  } finally {
    if (typeof root !== 'undefined') {
      root.freeRecursive();
    }

    config.free();
  }
});
