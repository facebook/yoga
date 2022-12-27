/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// @generated by gentest/gentest.rb from gentest/fixtures/YGAlignSelfTest.html

var Yoga = Yoga || require("../../sources/entry-" + process.env.TEST_ENTRY);

it("align_self_center", function () {
  var config = Yoga.Config.create();

  try {
    var root = Yoga.Node.create(config);
    root.setWidth(100);
    root.setHeight(100);

    var root_child0 = Yoga.Node.create(config);
    root_child0.setAlignSelf(Yoga.ALIGN_CENTER);
    root_child0.setWidth(10);
    root_child0.setHeight(10);
    root.insertChild(root_child0, 0);
    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(45 === root_child0.getComputedLeft(), "45 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(10 === root_child0.getComputedWidth(), "10 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(10 === root_child0.getComputedHeight(), "10 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");

    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_RTL);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(45 === root_child0.getComputedLeft(), "45 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(10 === root_child0.getComputedWidth(), "10 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(10 === root_child0.getComputedHeight(), "10 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");
  } finally {
    if (typeof root !== "undefined") {
      root.freeRecursive();
    }

    config.free();
  }
});
it("align_self_center_undefined_max_height", function () {
  var config = Yoga.Config.create();

  try {
    var root = Yoga.Node.create(config);
    root.setFlexDirection(Yoga.FLEX_DIRECTION_ROW);
    root.setWidth(280);
    root.setMinHeight(52);

    var root_child0 = Yoga.Node.create(config);
    root_child0.setWidth(240);
    root_child0.setHeight(44);
    root.insertChild(root_child0, 0);

    var root_child1 = Yoga.Node.create(config);
    root_child1.setAlignSelf(Yoga.ALIGN_CENTER);
    root_child1.setWidth(40);
    root_child1.setHeight(56);
    root.insertChild(root_child1, 1);
    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(280 === root.getComputedWidth(), "280 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(56 === root.getComputedHeight(), "56 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(240 === root_child0.getComputedWidth(), "240 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(44 === root_child0.getComputedHeight(), "44 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");

    console.assert(240 === root_child1.getComputedLeft(), "240 === root_child1.getComputedLeft() (" + root_child1.getComputedLeft() + ")");
    console.assert(0 === root_child1.getComputedTop(), "0 === root_child1.getComputedTop() (" + root_child1.getComputedTop() + ")");
    console.assert(40 === root_child1.getComputedWidth(), "40 === root_child1.getComputedWidth() (" + root_child1.getComputedWidth() + ")");
    console.assert(56 === root_child1.getComputedHeight(), "56 === root_child1.getComputedHeight() (" + root_child1.getComputedHeight() + ")");

    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_RTL);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(280 === root.getComputedWidth(), "280 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(56 === root.getComputedHeight(), "56 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(40 === root_child0.getComputedLeft(), "40 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(240 === root_child0.getComputedWidth(), "240 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(44 === root_child0.getComputedHeight(), "44 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");

    console.assert(0 === root_child1.getComputedLeft(), "0 === root_child1.getComputedLeft() (" + root_child1.getComputedLeft() + ")");
    console.assert(0 === root_child1.getComputedTop(), "0 === root_child1.getComputedTop() (" + root_child1.getComputedTop() + ")");
    console.assert(40 === root_child1.getComputedWidth(), "40 === root_child1.getComputedWidth() (" + root_child1.getComputedWidth() + ")");
    console.assert(56 === root_child1.getComputedHeight(), "56 === root_child1.getComputedHeight() (" + root_child1.getComputedHeight() + ")");
  } finally {
    if (typeof root !== "undefined") {
      root.freeRecursive();
    }

    config.free();
  }
});
it("align_self_flex_end", function () {
  var config = Yoga.Config.create();

  try {
    var root = Yoga.Node.create(config);
    root.setWidth(100);
    root.setHeight(100);

    var root_child0 = Yoga.Node.create(config);
    root_child0.setAlignSelf(Yoga.ALIGN_FLEX_END);
    root_child0.setWidth(10);
    root_child0.setHeight(10);
    root.insertChild(root_child0, 0);
    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(90 === root_child0.getComputedLeft(), "90 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(10 === root_child0.getComputedWidth(), "10 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(10 === root_child0.getComputedHeight(), "10 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");

    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_RTL);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(10 === root_child0.getComputedWidth(), "10 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(10 === root_child0.getComputedHeight(), "10 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");
  } finally {
    if (typeof root !== "undefined") {
      root.freeRecursive();
    }

    config.free();
  }
});
it("align_self_flex_start", function () {
  var config = Yoga.Config.create();

  try {
    var root = Yoga.Node.create(config);
    root.setWidth(100);
    root.setHeight(100);

    var root_child0 = Yoga.Node.create(config);
    root_child0.setAlignSelf(Yoga.ALIGN_FLEX_START);
    root_child0.setWidth(10);
    root_child0.setHeight(10);
    root.insertChild(root_child0, 0);
    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(10 === root_child0.getComputedWidth(), "10 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(10 === root_child0.getComputedHeight(), "10 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");

    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_RTL);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(90 === root_child0.getComputedLeft(), "90 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(10 === root_child0.getComputedWidth(), "10 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(10 === root_child0.getComputedHeight(), "10 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");
  } finally {
    if (typeof root !== "undefined") {
      root.freeRecursive();
    }

    config.free();
  }
});
it("align_self_flex_end_override_flex_start", function () {
  var config = Yoga.Config.create();

  try {
    var root = Yoga.Node.create(config);
    root.setAlignItems(Yoga.ALIGN_FLEX_START);
    root.setWidth(100);
    root.setHeight(100);

    var root_child0 = Yoga.Node.create(config);
    root_child0.setAlignSelf(Yoga.ALIGN_FLEX_END);
    root_child0.setWidth(10);
    root_child0.setHeight(10);
    root.insertChild(root_child0, 0);
    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(90 === root_child0.getComputedLeft(), "90 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(10 === root_child0.getComputedWidth(), "10 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(10 === root_child0.getComputedHeight(), "10 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");

    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_RTL);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(10 === root_child0.getComputedWidth(), "10 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(10 === root_child0.getComputedHeight(), "10 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");
  } finally {
    if (typeof root !== "undefined") {
      root.freeRecursive();
    }

    config.free();
  }
});
it("align_self_baseline", function () {
  var config = Yoga.Config.create();

  try {
    var root = Yoga.Node.create(config);
    root.setFlexDirection(Yoga.FLEX_DIRECTION_ROW);
    root.setWidth(100);
    root.setHeight(100);

    var root_child0 = Yoga.Node.create(config);
    root_child0.setAlignSelf(Yoga.ALIGN_BASELINE);
    root_child0.setWidth(50);
    root_child0.setHeight(50);
    root.insertChild(root_child0, 0);

    var root_child1 = Yoga.Node.create(config);
    root_child1.setAlignSelf(Yoga.ALIGN_BASELINE);
    root_child1.setWidth(50);
    root_child1.setHeight(20);
    root.insertChild(root_child1, 1);

    var root_child1_child0 = Yoga.Node.create(config);
    root_child1_child0.setWidth(50);
    root_child1_child0.setHeight(10);
    root_child1.insertChild(root_child1_child0, 0);
    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(50 === root_child0.getComputedWidth(), "50 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(50 === root_child0.getComputedHeight(), "50 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");

    console.assert(50 === root_child1.getComputedLeft(), "50 === root_child1.getComputedLeft() (" + root_child1.getComputedLeft() + ")");
    console.assert(40 === root_child1.getComputedTop(), "40 === root_child1.getComputedTop() (" + root_child1.getComputedTop() + ")");
    console.assert(50 === root_child1.getComputedWidth(), "50 === root_child1.getComputedWidth() (" + root_child1.getComputedWidth() + ")");
    console.assert(20 === root_child1.getComputedHeight(), "20 === root_child1.getComputedHeight() (" + root_child1.getComputedHeight() + ")");

    console.assert(0 === root_child1_child0.getComputedLeft(), "0 === root_child1_child0.getComputedLeft() (" + root_child1_child0.getComputedLeft() + ")");
    console.assert(0 === root_child1_child0.getComputedTop(), "0 === root_child1_child0.getComputedTop() (" + root_child1_child0.getComputedTop() + ")");
    console.assert(50 === root_child1_child0.getComputedWidth(), "50 === root_child1_child0.getComputedWidth() (" + root_child1_child0.getComputedWidth() + ")");
    console.assert(10 === root_child1_child0.getComputedHeight(), "10 === root_child1_child0.getComputedHeight() (" + root_child1_child0.getComputedHeight() + ")");

    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_RTL);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(50 === root_child0.getComputedLeft(), "50 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(50 === root_child0.getComputedWidth(), "50 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(50 === root_child0.getComputedHeight(), "50 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");

    console.assert(0 === root_child1.getComputedLeft(), "0 === root_child1.getComputedLeft() (" + root_child1.getComputedLeft() + ")");
    console.assert(40 === root_child1.getComputedTop(), "40 === root_child1.getComputedTop() (" + root_child1.getComputedTop() + ")");
    console.assert(50 === root_child1.getComputedWidth(), "50 === root_child1.getComputedWidth() (" + root_child1.getComputedWidth() + ")");
    console.assert(20 === root_child1.getComputedHeight(), "20 === root_child1.getComputedHeight() (" + root_child1.getComputedHeight() + ")");

    console.assert(0 === root_child1_child0.getComputedLeft(), "0 === root_child1_child0.getComputedLeft() (" + root_child1_child0.getComputedLeft() + ")");
    console.assert(0 === root_child1_child0.getComputedTop(), "0 === root_child1_child0.getComputedTop() (" + root_child1_child0.getComputedTop() + ")");
    console.assert(50 === root_child1_child0.getComputedWidth(), "50 === root_child1_child0.getComputedWidth() (" + root_child1_child0.getComputedWidth() + ")");
    console.assert(10 === root_child1_child0.getComputedHeight(), "10 === root_child1_child0.getComputedHeight() (" + root_child1_child0.getComputedHeight() + ")");
  } finally {
    if (typeof root !== "undefined") {
      root.freeRecursive();
    }

    config.free();
  }
});
