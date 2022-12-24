/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

test("dirtied", function () {
  const root = Yoga.Node.create();
  root.setAlignItems(Yoga.ALIGN_FLEX_START);
  root.setWidth(100);
  root.setHeight(100);

  root.calculateLayout(undefined, undefined, Yoga.DIRECTION_LTR);

  let dirtied = 0;
  root.setDirtiedFunc(function () {
    dirtied++;
  });
  // only nodes with a measure function can be marked dirty
  root.setMeasureFunc(function () {});

  expect(dirtied).toBe(0);

  // dirtied func MUST be called in case of explicit dirtying.
  root.markDirty();
  expect(dirtied).toBe(1);

  // dirtied func MUST be called ONCE.
  root.markDirty();
  expect(dirtied).toBe(1);

  root.freeRecursive();
});

test("dirtied_propagation", function () {
  const root = Yoga.Node.create();
  root.setAlignItems(Yoga.ALIGN_FLEX_START);
  root.setWidth(100);
  root.setHeight(100);

  const root_child0 = Yoga.Node.create();
  root_child0.setAlignItems(Yoga.ALIGN_FLEX_START);
  root_child0.setWidth(50);
  root_child0.setHeight(20);
  root_child0.setMeasureFunc(function () {});
  root.insertChild(root_child0, 0);

  const root_child1 = Yoga.Node.create();
  root_child1.setAlignItems(Yoga.ALIGN_FLEX_START);
  root_child1.setWidth(50);
  root_child1.setHeight(20);
  root.insertChild(root_child1, 0);

  root.calculateLayout(undefined, undefined, Yoga.DIRECTION_LTR);

  let dirtied = 0;
  root.setDirtiedFunc(function () {
    dirtied++;
  });

  expect(dirtied).toBe(0);

  // dirtied func MUST be called for the first time.
  root_child0.markDirty();
  expect(dirtied).toBe(1);

  // dirtied func must NOT be called for the second time.
  root_child0.markDirty();
  expect(dirtied).toBe(1);

  root.freeRecursive();
});

test("dirtied_hierarchy", function () {
  const root = Yoga.Node.create();
  root.setAlignItems(Yoga.ALIGN_FLEX_START);
  root.setWidth(100);
  root.setHeight(100);

  const root_child0 = Yoga.Node.create();
  root_child0.setAlignItems(Yoga.ALIGN_FLEX_START);
  root_child0.setWidth(50);
  root_child0.setHeight(20);
  root_child0.setMeasureFunc(function () {});
  root.insertChild(root_child0, 0);

  const root_child1 = Yoga.Node.create();
  root_child1.setAlignItems(Yoga.ALIGN_FLEX_START);
  root_child1.setWidth(50);
  root_child1.setHeight(20);
  root_child1.setMeasureFunc(function () {});
  root.insertChild(root_child1, 0);

  root.calculateLayout(undefined, undefined, Yoga.DIRECTION_LTR);

  let dirtied = 0;
  root_child0.setDirtiedFunc(function () {
    dirtied++;
  });

  expect(dirtied).toBe(0);

  // dirtied func must NOT be called for descendants.
  // NOTE: nodes without a measure function cannot be marked dirty manually,
  // but nodes with a measure function can not have children.
  // Update the width to dirty the node instead.
  root.setWidth(110);
  expect(dirtied).toBe(0);

  // dirtied func MUST be called in case of explicit dirtying.
  root_child0.markDirty();
  expect(dirtied).toBe(1);

  root.freeRecursive();
});

test("dirtied_reset", function () {
  const root = Yoga.Node.create();
  root.setAlignItems(Yoga.ALIGN_FLEX_START);
  root.setWidth(100);
  root.setHeight(100);
  root.setMeasureFunc(function () {});

  root.calculateLayout(undefined, undefined, Yoga.DIRECTION_LTR);

  let dirtied = 0;
  root.setDirtiedFunc(function () {
    dirtied++;
  });

  expect(dirtied).toBe(0);

  // dirtied func MUST be called in case of explicit dirtying.
  root.markDirty();
  expect(dirtied).toBe(1);

  // recalculate so the root is no longer dirty
  root.calculateLayout(undefined, undefined, Yoga.DIRECTION_LTR);

  root.reset();
  root.setAlignItems(Yoga.ALIGN_FLEX_START);
  root.setWidth(100);
  root.setHeight(100);
  root.setMeasureFunc(function () {});

  root.markDirty();

  // dirtied func must NOT be called after reset.
  root.markDirty();
  expect(dirtied).toBe(1);

  root.freeRecursive();
});
