/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

import Yoga from 'yoga-layout';

describe('calculateLayout with non-numeric dimensions', () => {
  test('calculateLayout with undefined width and height uses auto-sizing', () => {
    const root = Yoga.Node.create();
    root.setWidth(100);
    root.setHeight(100);

    // undefined should be treated as auto-sizing (NaN internally)
    root.calculateLayout(undefined, undefined, Yoga.DIRECTION_LTR);

    expect(root.getComputedWidth()).toBe(100);
    expect(root.getComputedHeight()).toBe(100);
    expect(root.getComputedLeft()).toBe(0);
    expect(root.getComputedTop()).toBe(0);
  });

  test("calculateLayout with 'auto' width and height uses auto-sizing", () => {
    const root = Yoga.Node.create();
    root.setWidth(200);
    root.setHeight(150);

    // 'auto' should be treated as auto-sizing (NaN internally)
    root.calculateLayout('auto', 'auto', Yoga.DIRECTION_LTR);

    expect(root.getComputedWidth()).toBe(200);
    expect(root.getComputedHeight()).toBe(150);
  });

  test("calculateLayout with mixed numeric and 'auto' dimensions", () => {
    const root = Yoga.Node.create();
    root.setWidth(100);
    root.setHeight(100);

    // Mix of numeric and 'auto' should work correctly
    root.calculateLayout(300, 'auto', Yoga.DIRECTION_LTR);

    // Width should be constrained by the specified 300
    expect(root.getComputedWidth()).toBe(100);
    expect(root.getComputedHeight()).toBe(100);
  });

  test('calculateLayout with numeric width and undefined height', () => {
    const root = Yoga.Node.create();
    root.setWidth(100);
    root.setHeight(100);

    root.calculateLayout(500, undefined, Yoga.DIRECTION_LTR);

    expect(root.getComputedWidth()).toBe(100);
    expect(root.getComputedHeight()).toBe(100);
  });

  test('calculateLayout with child nodes and auto dimensions', () => {
    const root = Yoga.Node.create();
    root.setFlexDirection(Yoga.FLEX_DIRECTION_ROW);

    const child1 = Yoga.Node.create();
    child1.setWidth(50);
    child1.setHeight(50);
    root.insertChild(child1, 0);

    const child2 = Yoga.Node.create();
    child2.setWidth(50);
    child2.setHeight(75);
    root.insertChild(child2, 1);

    // Using undefined (auto) should size the root based on children
    root.calculateLayout(undefined, undefined, Yoga.DIRECTION_LTR);

    // Root should size to fit children
    expect(root.getComputedWidth()).toBe(100); // 50 + 50
    expect(root.getComputedHeight()).toBe(75); // max of 50 and 75

    // Children should be positioned correctly
    expect(child1.getComputedLeft()).toBe(0);
    expect(child1.getComputedTop()).toBe(0);
    expect(child2.getComputedLeft()).toBe(50);
    expect(child2.getComputedTop()).toBe(0);
  });

  test("calculateLayout with child nodes and 'auto' dimensions", () => {
    const root = Yoga.Node.create();
    root.setFlexDirection(Yoga.FLEX_DIRECTION_COLUMN);

    const child1 = Yoga.Node.create();
    child1.setWidth(100);
    child1.setHeight(30);
    root.insertChild(child1, 0);

    const child2 = Yoga.Node.create();
    child2.setWidth(80);
    child2.setHeight(40);
    root.insertChild(child2, 1);

    // Using 'auto' should size the root based on children
    root.calculateLayout('auto', 'auto', Yoga.DIRECTION_LTR);

    // Root should size to fit children
    expect(root.getComputedWidth()).toBe(100); // max of 100 and 80
    expect(root.getComputedHeight()).toBe(70); // 30 + 40
  });

  test('calculateLayout default parameters', () => {
    const root = Yoga.Node.create();
    root.setWidth(100);
    root.setHeight(100);

    // Call with no arguments - should use default values (NaN, NaN, LTR)
    root.calculateLayout();

    expect(root.getComputedWidth()).toBe(100);
    expect(root.getComputedHeight()).toBe(100);
  });

  test('calculateLayout with NaN width and height', () => {
    const root = Yoga.Node.create();
    root.setWidth(100);
    root.setHeight(100);

    // Explicit NaN should work the same as undefined/auto
    root.calculateLayout(NaN, NaN, Yoga.DIRECTION_LTR);

    expect(root.getComputedWidth()).toBe(100);
    expect(root.getComputedHeight()).toBe(100);
  });

  test('calculateLayout with RTL direction', () => {
    const root = Yoga.Node.create();
    root.setFlexDirection(Yoga.FLEX_DIRECTION_ROW);
    root.setWidth(200);

    const child = Yoga.Node.create();
    child.setWidth(50);
    child.setHeight(50);
    root.insertChild(child, 0);

    // RTL with auto height
    root.calculateLayout('auto', 'auto', Yoga.DIRECTION_RTL);

    // Child should be positioned from the right in RTL
    expect(child.getComputedLeft()).toBe(150); // 200 - 50
  });
});
