/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @generated SignedSource<<2e9d73d454aa734212a0ad3a58988ca7>>
 * generated by gentest/gentest-driver.ts from gentest/fixtures/YGBorderTest.html
 */

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

test('border_no_size', () => {
  const config = Yoga.Config.create();
  let root;

  config.setExperimentalFeatureEnabled(ExperimentalFeature.AbsolutePercentageAgainstPaddingEdge, true);

  try {
    root = Yoga.Node.create(config);
    root.setPositionType(PositionType.Absolute);
    root.setBorder(Edge.Left, 10);
    root.setBorder(Edge.Top, 10);
    root.setBorder(Edge.Right, 10);
    root.setBorder(Edge.Bottom, 10);
    root.calculateLayout(undefined, undefined, Direction.LTR);

    expect(root.getComputedLeft()).toBe(0);
    expect(root.getComputedTop()).toBe(0);
    expect(root.getComputedWidth()).toBe(20);
    expect(root.getComputedHeight()).toBe(20);

    root.calculateLayout(undefined, undefined, Direction.RTL);

    expect(root.getComputedLeft()).toBe(0);
    expect(root.getComputedTop()).toBe(0);
    expect(root.getComputedWidth()).toBe(20);
    expect(root.getComputedHeight()).toBe(20);
  } finally {
    if (typeof root !== 'undefined') {
      root.freeRecursive();
    }

    config.free();
  }
});
test('border_container_match_child', () => {
  const config = Yoga.Config.create();
  let root;

  config.setExperimentalFeatureEnabled(ExperimentalFeature.AbsolutePercentageAgainstPaddingEdge, true);

  try {
    root = Yoga.Node.create(config);
    root.setPositionType(PositionType.Absolute);
    root.setBorder(Edge.Left, 10);
    root.setBorder(Edge.Top, 10);
    root.setBorder(Edge.Right, 10);
    root.setBorder(Edge.Bottom, 10);

    const root_child0 = Yoga.Node.create(config);
    root_child0.setWidth(10);
    root_child0.setHeight(10);
    root.insertChild(root_child0, 0);
    root.calculateLayout(undefined, undefined, Direction.LTR);

    expect(root.getComputedLeft()).toBe(0);
    expect(root.getComputedTop()).toBe(0);
    expect(root.getComputedWidth()).toBe(30);
    expect(root.getComputedHeight()).toBe(30);

    expect(root_child0.getComputedLeft()).toBe(10);
    expect(root_child0.getComputedTop()).toBe(10);
    expect(root_child0.getComputedWidth()).toBe(10);
    expect(root_child0.getComputedHeight()).toBe(10);

    root.calculateLayout(undefined, undefined, Direction.RTL);

    expect(root.getComputedLeft()).toBe(0);
    expect(root.getComputedTop()).toBe(0);
    expect(root.getComputedWidth()).toBe(30);
    expect(root.getComputedHeight()).toBe(30);

    expect(root_child0.getComputedLeft()).toBe(10);
    expect(root_child0.getComputedTop()).toBe(10);
    expect(root_child0.getComputedWidth()).toBe(10);
    expect(root_child0.getComputedHeight()).toBe(10);
  } finally {
    if (typeof root !== 'undefined') {
      root.freeRecursive();
    }

    config.free();
  }
});
test('border_flex_child', () => {
  const config = Yoga.Config.create();
  let root;

  config.setExperimentalFeatureEnabled(ExperimentalFeature.AbsolutePercentageAgainstPaddingEdge, true);

  try {
    root = Yoga.Node.create(config);
    root.setPositionType(PositionType.Absolute);
    root.setBorder(Edge.Left, 10);
    root.setBorder(Edge.Top, 10);
    root.setBorder(Edge.Right, 10);
    root.setBorder(Edge.Bottom, 10);
    root.setWidth(100);
    root.setHeight(100);

    const root_child0 = Yoga.Node.create(config);
    root_child0.setFlexGrow(1);
    root_child0.setWidth(10);
    root.insertChild(root_child0, 0);
    root.calculateLayout(undefined, undefined, Direction.LTR);

    expect(root.getComputedLeft()).toBe(0);
    expect(root.getComputedTop()).toBe(0);
    expect(root.getComputedWidth()).toBe(100);
    expect(root.getComputedHeight()).toBe(100);

    expect(root_child0.getComputedLeft()).toBe(10);
    expect(root_child0.getComputedTop()).toBe(10);
    expect(root_child0.getComputedWidth()).toBe(10);
    expect(root_child0.getComputedHeight()).toBe(80);

    root.calculateLayout(undefined, undefined, Direction.RTL);

    expect(root.getComputedLeft()).toBe(0);
    expect(root.getComputedTop()).toBe(0);
    expect(root.getComputedWidth()).toBe(100);
    expect(root.getComputedHeight()).toBe(100);

    expect(root_child0.getComputedLeft()).toBe(80);
    expect(root_child0.getComputedTop()).toBe(10);
    expect(root_child0.getComputedWidth()).toBe(10);
    expect(root_child0.getComputedHeight()).toBe(80);
  } finally {
    if (typeof root !== 'undefined') {
      root.freeRecursive();
    }

    config.free();
  }
});
test('border_stretch_child', () => {
  const config = Yoga.Config.create();
  let root;

  config.setExperimentalFeatureEnabled(ExperimentalFeature.AbsolutePercentageAgainstPaddingEdge, true);

  try {
    root = Yoga.Node.create(config);
    root.setPositionType(PositionType.Absolute);
    root.setBorder(Edge.Left, 10);
    root.setBorder(Edge.Top, 10);
    root.setBorder(Edge.Right, 10);
    root.setBorder(Edge.Bottom, 10);
    root.setWidth(100);
    root.setHeight(100);

    const root_child0 = Yoga.Node.create(config);
    root_child0.setHeight(10);
    root.insertChild(root_child0, 0);
    root.calculateLayout(undefined, undefined, Direction.LTR);

    expect(root.getComputedLeft()).toBe(0);
    expect(root.getComputedTop()).toBe(0);
    expect(root.getComputedWidth()).toBe(100);
    expect(root.getComputedHeight()).toBe(100);

    expect(root_child0.getComputedLeft()).toBe(10);
    expect(root_child0.getComputedTop()).toBe(10);
    expect(root_child0.getComputedWidth()).toBe(80);
    expect(root_child0.getComputedHeight()).toBe(10);

    root.calculateLayout(undefined, undefined, Direction.RTL);

    expect(root.getComputedLeft()).toBe(0);
    expect(root.getComputedTop()).toBe(0);
    expect(root.getComputedWidth()).toBe(100);
    expect(root.getComputedHeight()).toBe(100);

    expect(root_child0.getComputedLeft()).toBe(10);
    expect(root_child0.getComputedTop()).toBe(10);
    expect(root_child0.getComputedWidth()).toBe(80);
    expect(root_child0.getComputedHeight()).toBe(10);
  } finally {
    if (typeof root !== 'undefined') {
      root.freeRecursive();
    }

    config.free();
  }
});
test('border_center_child', () => {
  const config = Yoga.Config.create();
  let root;

  config.setExperimentalFeatureEnabled(ExperimentalFeature.AbsolutePercentageAgainstPaddingEdge, true);

  try {
    root = Yoga.Node.create(config);
    root.setJustifyContent(Justify.Center);
    root.setAlignItems(Align.Center);
    root.setPositionType(PositionType.Absolute);
    root.setBorder(Edge.Start, 10);
    root.setBorder(Edge.End, 20);
    root.setBorder(Edge.Bottom, 20);
    root.setWidth(100);
    root.setHeight(100);

    const root_child0 = Yoga.Node.create(config);
    root_child0.setWidth(10);
    root_child0.setHeight(10);
    root.insertChild(root_child0, 0);
    root.calculateLayout(undefined, undefined, Direction.LTR);

    expect(root.getComputedLeft()).toBe(0);
    expect(root.getComputedTop()).toBe(0);
    expect(root.getComputedWidth()).toBe(100);
    expect(root.getComputedHeight()).toBe(100);

    expect(root_child0.getComputedLeft()).toBe(40);
    expect(root_child0.getComputedTop()).toBe(35);
    expect(root_child0.getComputedWidth()).toBe(10);
    expect(root_child0.getComputedHeight()).toBe(10);

    root.calculateLayout(undefined, undefined, Direction.RTL);

    expect(root.getComputedLeft()).toBe(0);
    expect(root.getComputedTop()).toBe(0);
    expect(root.getComputedWidth()).toBe(100);
    expect(root.getComputedHeight()).toBe(100);

    expect(root_child0.getComputedLeft()).toBe(50);
    expect(root_child0.getComputedTop()).toBe(35);
    expect(root_child0.getComputedWidth()).toBe(10);
    expect(root_child0.getComputedHeight()).toBe(10);
  } finally {
    if (typeof root !== 'undefined') {
      root.freeRecursive();
    }

    config.free();
  }
});
