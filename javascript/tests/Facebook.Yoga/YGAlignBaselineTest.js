/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

var Yoga = Yoga || require("../../sources/entry-" + process.env.TEST_ENTRY);

it("align_baseline_parent_using_child_in_column_as_reference", function () {
  var config = Yoga.Config.create();

  try {
    var root = Yoga.Node.create(config);
    root.setFlexDirection(Yoga.FLEX_DIRECTION_ROW);
    root.setWidth(1000);
    root.setHeight(1000);
    root.setAlignItems(Yoga.ALIGN_BASELINE);

    var root_child0 = Yoga.Node.create(config);
    root_child0.setFlexDirection(Yoga.FLEX_DIRECTION_COLUMN);
    root_child0.setWidth(500);
    root_child0.setHeight(600);
    root.insertChild(root_child0, 0);

    var root_child1 = Yoga.Node.create(config);
    root_child1.setFlexDirection(Yoga.FLEX_DIRECTION_COLUMN);
    root_child1.setWidth(500);
    root_child1.setHeight(800);
    root.insertChild(root_child1, 1);

    var root_child1_child0 = Yoga.Node.create(config);
    root_child1_child0.setFlexDirection(Yoga.FLEX_DIRECTION_COLUMN);
    root_child1_child0.setWidth(500);
    root_child1_child0.setHeight(300);
    root_child1.insertChild(root_child1_child0, 0);

    var root_child1_child1 = Yoga.Node.create(config);
    root_child1_child1.setFlexDirection(Yoga.FLEX_DIRECTION_COLUMN);
    root_child1_child1.setWidth(500);
    root_child1_child1.setHeight(400);
    root_child1_child1.setIsReferenceBaseline(true);
    root_child1.insertChild(root_child1_child1, 1);

    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

    console.assert(0 === root_child0.getComputedLeft(),
        "0 === root_child0.getComputedLeft() (" +
        root_child0.getComputedLeft() + ")");
    console.assert(100 === root_child0.getComputedTop(),
        "100 === root_child0.getComputedTop() (" +
        root_child0.getComputedTop() + ")");

    console.assert(500 === root_child1.getComputedLeft(),
        "500 === root_child1.getComputedLeft() (" +
        root_child1.getComputedLeft() + ")");
    console.assert(0 === root_child1.getComputedTop(),
        "0 === root_child1.getComputedTop() (" +
        root_child1.getComputedTop() + ")");

    console.assert(0 === root_child1_child0.getComputedLeft(),
        "0 === root_child1_child0.getComputedLeft() (" +
        root_child1_child0.getComputedLeft() + ")");
    console.assert(0 === root_child1_child0.getComputedTop(),
        "0 === root_child1_child0.getComputedTop() (" +
        root_child1_child0.getComputedTop() + ")");

    console.assert(0 === root_child1_child1.getComputedLeft(),
        "0 === root_child1_child1.getComputedLeft() (" +
        root_child1_child1.getComputedLeft() + ")");
    console.assert(300 === root_child1_child1.getComputedTop(),
        "300 === root_child1_child1.getComputedTop() (" +
        root_child1_child1.getComputedTop() + ")");

  } finally {
    if (typeof root !== "undefined") {
      root.freeRecursive();
    }

    config.free();
  }
});

it("align_baseline_parent_using_child_in_row_as_reference", function () {
  var config = Yoga.Config.create();

  try {
    var root = Yoga.Node.create(config);
    root.setFlexDirection(Yoga.FLEX_DIRECTION_ROW);
    root.setWidth(1000);
    root.setHeight(1000);
    root.setAlignItems(Yoga.ALIGN_BASELINE);

    var root_child0 = Yoga.Node.create(config);
    root_child0.setFlexDirection(Yoga.FLEX_DIRECTION_COLUMN);
    root_child0.setWidth(500);
    root_child0.setHeight(600);
    root.insertChild(root_child0, 0);

    var root_child1 = Yoga.Node.create(config);
    root_child1.setFlexDirection(Yoga.FLEX_DIRECTION_ROW);
    root_child1.setWidth(500);
    root_child1.setHeight(800);
    root.insertChild(root_child1, 1);

    var root_child1_child0 = Yoga.Node.create(config);
    root_child1_child0.setFlexDirection(Yoga.FLEX_DIRECTION_COLUMN);
    root_child1_child0.setWidth(500);
    root_child1_child0.setHeight(500);
    root_child1.insertChild(root_child1_child0, 0);

    var root_child1_child1 = Yoga.Node.create(config);
    root_child1_child1.setFlexDirection(Yoga.FLEX_DIRECTION_COLUMN);
    root_child1_child1.setWidth(500);
    root_child1_child1.setHeight(400);
    root_child1_child1.setIsReferenceBaseline(true);
    root_child1.insertChild(root_child1_child1, 1);

    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

    console.assert(0 === root_child0.getComputedLeft(),
        "0 === root_child0.getComputedLeft() (" +
        root_child0.getComputedLeft() + ")");
    console.assert(0 === root_child0.getComputedTop(),
        "0 === root_child0.getComputedTop() (" +
        root_child0.getComputedTop() + ")");

    console.assert(500 === root_child1.getComputedLeft(),
        "500 === root_child1.getComputedLeft() (" +
        root_child1.getComputedLeft() + ")");
    console.assert(200 === root_child1.getComputedTop(),
        "200 === root_child1.getComputedTop() (" +
        root_child1.getComputedTop() + ")");

    console.assert(0 === root_child1_child0.getComputedLeft(),
        "0 === root_child1_child0.getComputedLeft() (" +
        root_child1_child0.getComputedLeft() + ")");
    console.assert(0 === root_child1_child0.getComputedTop(),
        "0 === root_child1_child0.getComputedTop() (" +
        root_child1_child0.getComputedTop() + ")");

    console.assert(500 === root_child1_child1.getComputedLeft(),
        "500 === root_child1_child1.getComputedLeft() (" +
        root_child1_child1.getComputedLeft() + ")");
    console.assert(0 === root_child1_child1.getComputedTop(),
        "0 === root_child1_child1.getComputedTop() (" +
        root_child1_child1.getComputedTop() + ")");

  } finally {
    if (typeof root !== "undefined") {
      root.freeRecursive();
    }

    config.free();
  }
});
