/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

var Yoga = Yoga || require("../../sources/entry-" + process.env.TEST_ENTRY);

it("dirtied", function() {
  var root = Yoga.Node.create();
  root.setAlignItems(Yoga.ALIGN_FLEX_START);
  root.setWidth(100);
  root.setHeight(100);

  root.calculateLayout(undefined, undefined, Yoga.DIRECTION_LTR);

  let dirtied = 0;
  root.setDirtiedFunc(function() { dirtied++; });
  // only nodes with a measure function can be marked dirty
  root.setMeasureFunc(function() {});

  console.assert(0 === dirtied, "0 === dirtied");

  // dirtied func MUST be called in case of explicit dirtying.
  root.markDirty();
  console.assert(1 === dirtied, "1 === dirtied");

  // dirtied func MUST be called ONCE.
  root.markDirty();
  console.assert(1 === dirtied, "1 === dirtied");

  if (typeof root !== "undefined")
    root.freeRecursive();

  typeof gc !== "undefined" && gc();
  // TODO Add event support in js and check instace allocation and de allocation using that
});

it("dirtied_propagation", function() {
  var root = Yoga.Node.create();
  root.setAlignItems(Yoga.ALIGN_FLEX_START);
  root.setWidth(100);
  root.setHeight(100);

  var root_child0 = Yoga.Node.create();
  root_child0.setAlignItems(Yoga.ALIGN_FLEX_START);
  root_child0.setWidth(50);
  root_child0.setHeight(20);
  root_child0.setMeasureFunc(function() {});
  root.insertChild(root_child0, 0);

  var root_child1 = Yoga.Node.create();
  root_child1.setAlignItems(Yoga.ALIGN_FLEX_START);
  root_child1.setWidth(50);
  root_child1.setHeight(20);
  root.insertChild(root_child1, 0);

  root.calculateLayout(undefined, undefined, Yoga.DIRECTION_LTR);

  let dirtied = 0;
  root.setDirtiedFunc(function() { dirtied++; });

  console.assert(0 === dirtied, "0 === dirtied");

  // dirtied func MUST be called for the first time.
  root_child0.markDirty();
  console.assert(1 === dirtied, "1 === dirtied");

  // dirtied func must NOT be called for the second time.
  root_child0.markDirty();
  console.assert(1 === dirtied, "1 === dirtied");

  if (typeof root !== "undefined")
    root.freeRecursive();

  typeof gc !== "undefined" && gc();
  // TODO Add event support in js and check instace allocation and de allocation using that
});

it("dirtied_hierarchy", function() {
  var root = Yoga.Node.create();
  root.setAlignItems(Yoga.ALIGN_FLEX_START);
  root.setWidth(100);
  root.setHeight(100);

  var root_child0 = Yoga.Node.create();
  root_child0.setAlignItems(Yoga.ALIGN_FLEX_START);
  root_child0.setWidth(50);
  root_child0.setHeight(20);
  root_child0.setMeasureFunc(function() {});
  root.insertChild(root_child0, 0);

  var root_child1 = Yoga.Node.create();
  root_child1.setAlignItems(Yoga.ALIGN_FLEX_START);
  root_child1.setWidth(50);
  root_child1.setHeight(20);
  root_child1.setMeasureFunc(function() {});
  root.insertChild(root_child1, 0);

  root.calculateLayout(undefined, undefined, Yoga.DIRECTION_LTR);

  let dirtied = 0;
  root_child0.setDirtiedFunc(function() {
    dirtied++;
  });

  console.assert(0 === dirtied, "0 === dirtied");

  // dirtied func must NOT be called for descendants.
  // NOTE: nodes without a measure function cannot be marked dirty manually,
  // but nodes with a measure function can not have children.
  // Update the width to dirty the node instead.
  root.setWidth(110);
  console.assert(0 === dirtied, "0 === dirtied");

  // dirtied func MUST be called in case of explicit dirtying.
  root_child0.markDirty();
  console.assert(1 === dirtied, "1 === dirtied");

  if (typeof root !== "undefined")
    root.freeRecursive();

  typeof gc !== "undefined" && gc();
  // TODO Add event support in js and check instace allocation and de allocation using that
});

it("dirtied_reset", function() {
  var root = Yoga.Node.create();
  root.setAlignItems(Yoga.ALIGN_FLEX_START);
  root.setWidth(100);
  root.setHeight(100);
  root.setMeasureFunc(function() {});

  root.calculateLayout(undefined, undefined, Yoga.DIRECTION_LTR);

  let dirtied = 0;
  root.setDirtiedFunc(function() {
    dirtied++;
  });

  console.assert(0 === dirtied, "0 === dirtied");

  // dirtied func MUST be called in case of explicit dirtying.
  root.markDirty();
  console.assert(1 === dirtied, "1 === dirtied");

  // recalculate so the root is no longer dirty
  root.calculateLayout(undefined, undefined, Yoga.DIRECTION_LTR);

  root.reset();
  root.setAlignItems(Yoga.ALIGN_FLEX_START);
  root.setWidth(100);
  root.setHeight(100);
  root.setMeasureFunc(function() {});

  root.markDirty();

  // dirtied func must NOT be called after reset.
  root.markDirty();
  console.assert(1 === dirtied, "1 === dirtied");

  if (typeof root !== "undefined")
    root.freeRecursive();

  typeof gc !== "undefined" && gc();
  // TODO Add event support in js and check instace allocation and de allocation using that
});
