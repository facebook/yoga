/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

 // @Generated by gentest/gentest.rb from gentest/fixtures/YGFlexWrapTest.html

var Yoga = Yoga || require("../../sources/entry-" + process.env.TEST_ENTRY);

it("wrap_column", function () {
  (function () {
    var root = new Yoga.Node();
    root.setFlexWrap(Yoga.WRAP_WRAP);
    root.setHeight(100);

    var root_child0 = new Yoga.Node();
    root_child0.setWidth(30);
    root_child0.setHeight(30);
    root.insertChild(root_child0, 0);

    var root_child1 = new Yoga.Node();
    root_child1.setWidth(30);
    root_child1.setHeight(30);
    root.insertChild(root_child1, 1);

    var root_child2 = new Yoga.Node();
    root_child2.setWidth(30);
    root_child2.setHeight(30);
    root.insertChild(root_child2, 2);

    var root_child3 = new Yoga.Node();
    root_child3.setWidth(30);
    root_child3.setHeight(30);
    root.insertChild(root_child3, 3);
    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(60 === root.getComputedWidth(), "60 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(30 === root_child0.getComputedWidth(), "30 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(30 === root_child0.getComputedHeight(), "30 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");

    console.assert(0 === root_child1.getComputedLeft(), "0 === root_child1.getComputedLeft() (" + root_child1.getComputedLeft() + ")");
    console.assert(30 === root_child1.getComputedTop(), "30 === root_child1.getComputedTop() (" + root_child1.getComputedTop() + ")");
    console.assert(30 === root_child1.getComputedWidth(), "30 === root_child1.getComputedWidth() (" + root_child1.getComputedWidth() + ")");
    console.assert(30 === root_child1.getComputedHeight(), "30 === root_child1.getComputedHeight() (" + root_child1.getComputedHeight() + ")");

    console.assert(0 === root_child2.getComputedLeft(), "0 === root_child2.getComputedLeft() (" + root_child2.getComputedLeft() + ")");
    console.assert(60 === root_child2.getComputedTop(), "60 === root_child2.getComputedTop() (" + root_child2.getComputedTop() + ")");
    console.assert(30 === root_child2.getComputedWidth(), "30 === root_child2.getComputedWidth() (" + root_child2.getComputedWidth() + ")");
    console.assert(30 === root_child2.getComputedHeight(), "30 === root_child2.getComputedHeight() (" + root_child2.getComputedHeight() + ")");

    console.assert(30 === root_child3.getComputedLeft(), "30 === root_child3.getComputedLeft() (" + root_child3.getComputedLeft() + ")");
    console.assert(0 === root_child3.getComputedTop(), "0 === root_child3.getComputedTop() (" + root_child3.getComputedTop() + ")");
    console.assert(30 === root_child3.getComputedWidth(), "30 === root_child3.getComputedWidth() (" + root_child3.getComputedWidth() + ")");
    console.assert(30 === root_child3.getComputedHeight(), "30 === root_child3.getComputedHeight() (" + root_child3.getComputedHeight() + ")");

    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_RTL);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(60 === root.getComputedWidth(), "60 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(30 === root_child0.getComputedLeft(), "30 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(30 === root_child0.getComputedWidth(), "30 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(30 === root_child0.getComputedHeight(), "30 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");

    console.assert(30 === root_child1.getComputedLeft(), "30 === root_child1.getComputedLeft() (" + root_child1.getComputedLeft() + ")");
    console.assert(30 === root_child1.getComputedTop(), "30 === root_child1.getComputedTop() (" + root_child1.getComputedTop() + ")");
    console.assert(30 === root_child1.getComputedWidth(), "30 === root_child1.getComputedWidth() (" + root_child1.getComputedWidth() + ")");
    console.assert(30 === root_child1.getComputedHeight(), "30 === root_child1.getComputedHeight() (" + root_child1.getComputedHeight() + ")");

    console.assert(30 === root_child2.getComputedLeft(), "30 === root_child2.getComputedLeft() (" + root_child2.getComputedLeft() + ")");
    console.assert(60 === root_child2.getComputedTop(), "60 === root_child2.getComputedTop() (" + root_child2.getComputedTop() + ")");
    console.assert(30 === root_child2.getComputedWidth(), "30 === root_child2.getComputedWidth() (" + root_child2.getComputedWidth() + ")");
    console.assert(30 === root_child2.getComputedHeight(), "30 === root_child2.getComputedHeight() (" + root_child2.getComputedHeight() + ")");

    console.assert(0 === root_child3.getComputedLeft(), "0 === root_child3.getComputedLeft() (" + root_child3.getComputedLeft() + ")");
    console.assert(0 === root_child3.getComputedTop(), "0 === root_child3.getComputedTop() (" + root_child3.getComputedTop() + ")");
    console.assert(30 === root_child3.getComputedWidth(), "30 === root_child3.getComputedWidth() (" + root_child3.getComputedWidth() + ")");
    console.assert(30 === root_child3.getComputedHeight(), "30 === root_child3.getComputedHeight() (" + root_child3.getComputedHeight() + ")");

    if (typeof root !== "undefined") {
      root.freeRecursive();
    }
  }());

  if (typeof gc !== "undefined") {
    gc();
    console.assert(0 === Yoga.getInstanceCount(), "0 === Yoga.getInstanceCount() (" + Yoga.getInstanceCount() + ")");
  }
});
it("wrap_row", function () {
  (function () {
    var root = new Yoga.Node();
    root.setFlexDirection(Yoga.FLEX_DIRECTION_ROW);
    root.setFlexWrap(Yoga.WRAP_WRAP);
    root.setWidth(100);

    var root_child0 = new Yoga.Node();
    root_child0.setWidth(30);
    root_child0.setHeight(30);
    root.insertChild(root_child0, 0);

    var root_child1 = new Yoga.Node();
    root_child1.setWidth(30);
    root_child1.setHeight(30);
    root.insertChild(root_child1, 1);

    var root_child2 = new Yoga.Node();
    root_child2.setWidth(30);
    root_child2.setHeight(30);
    root.insertChild(root_child2, 2);

    var root_child3 = new Yoga.Node();
    root_child3.setWidth(30);
    root_child3.setHeight(30);
    root.insertChild(root_child3, 3);
    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(60 === root.getComputedHeight(), "60 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(30 === root_child0.getComputedWidth(), "30 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(30 === root_child0.getComputedHeight(), "30 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");

    console.assert(30 === root_child1.getComputedLeft(), "30 === root_child1.getComputedLeft() (" + root_child1.getComputedLeft() + ")");
    console.assert(0 === root_child1.getComputedTop(), "0 === root_child1.getComputedTop() (" + root_child1.getComputedTop() + ")");
    console.assert(30 === root_child1.getComputedWidth(), "30 === root_child1.getComputedWidth() (" + root_child1.getComputedWidth() + ")");
    console.assert(30 === root_child1.getComputedHeight(), "30 === root_child1.getComputedHeight() (" + root_child1.getComputedHeight() + ")");

    console.assert(60 === root_child2.getComputedLeft(), "60 === root_child2.getComputedLeft() (" + root_child2.getComputedLeft() + ")");
    console.assert(0 === root_child2.getComputedTop(), "0 === root_child2.getComputedTop() (" + root_child2.getComputedTop() + ")");
    console.assert(30 === root_child2.getComputedWidth(), "30 === root_child2.getComputedWidth() (" + root_child2.getComputedWidth() + ")");
    console.assert(30 === root_child2.getComputedHeight(), "30 === root_child2.getComputedHeight() (" + root_child2.getComputedHeight() + ")");

    console.assert(0 === root_child3.getComputedLeft(), "0 === root_child3.getComputedLeft() (" + root_child3.getComputedLeft() + ")");
    console.assert(30 === root_child3.getComputedTop(), "30 === root_child3.getComputedTop() (" + root_child3.getComputedTop() + ")");
    console.assert(30 === root_child3.getComputedWidth(), "30 === root_child3.getComputedWidth() (" + root_child3.getComputedWidth() + ")");
    console.assert(30 === root_child3.getComputedHeight(), "30 === root_child3.getComputedHeight() (" + root_child3.getComputedHeight() + ")");

    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_RTL);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(60 === root.getComputedHeight(), "60 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(70 === root_child0.getComputedLeft(), "70 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(30 === root_child0.getComputedWidth(), "30 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(30 === root_child0.getComputedHeight(), "30 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");

    console.assert(40 === root_child1.getComputedLeft(), "40 === root_child1.getComputedLeft() (" + root_child1.getComputedLeft() + ")");
    console.assert(0 === root_child1.getComputedTop(), "0 === root_child1.getComputedTop() (" + root_child1.getComputedTop() + ")");
    console.assert(30 === root_child1.getComputedWidth(), "30 === root_child1.getComputedWidth() (" + root_child1.getComputedWidth() + ")");
    console.assert(30 === root_child1.getComputedHeight(), "30 === root_child1.getComputedHeight() (" + root_child1.getComputedHeight() + ")");

    console.assert(10 === root_child2.getComputedLeft(), "10 === root_child2.getComputedLeft() (" + root_child2.getComputedLeft() + ")");
    console.assert(0 === root_child2.getComputedTop(), "0 === root_child2.getComputedTop() (" + root_child2.getComputedTop() + ")");
    console.assert(30 === root_child2.getComputedWidth(), "30 === root_child2.getComputedWidth() (" + root_child2.getComputedWidth() + ")");
    console.assert(30 === root_child2.getComputedHeight(), "30 === root_child2.getComputedHeight() (" + root_child2.getComputedHeight() + ")");

    console.assert(70 === root_child3.getComputedLeft(), "70 === root_child3.getComputedLeft() (" + root_child3.getComputedLeft() + ")");
    console.assert(30 === root_child3.getComputedTop(), "30 === root_child3.getComputedTop() (" + root_child3.getComputedTop() + ")");
    console.assert(30 === root_child3.getComputedWidth(), "30 === root_child3.getComputedWidth() (" + root_child3.getComputedWidth() + ")");
    console.assert(30 === root_child3.getComputedHeight(), "30 === root_child3.getComputedHeight() (" + root_child3.getComputedHeight() + ")");

    if (typeof root !== "undefined") {
      root.freeRecursive();
    }
  }());

  if (typeof gc !== "undefined") {
    gc();
    console.assert(0 === Yoga.getInstanceCount(), "0 === Yoga.getInstanceCount() (" + Yoga.getInstanceCount() + ")");
  }
});
it("wrap_row_align_items_flex_end", function () {
  (function () {
    var root = new Yoga.Node();
    root.setFlexDirection(Yoga.FLEX_DIRECTION_ROW);
    root.setAlignItems(Yoga.ALIGN_FLEX_END);
    root.setFlexWrap(Yoga.WRAP_WRAP);
    root.setWidth(100);

    var root_child0 = new Yoga.Node();
    root_child0.setWidth(30);
    root_child0.setHeight(10);
    root.insertChild(root_child0, 0);

    var root_child1 = new Yoga.Node();
    root_child1.setWidth(30);
    root_child1.setHeight(20);
    root.insertChild(root_child1, 1);

    var root_child2 = new Yoga.Node();
    root_child2.setWidth(30);
    root_child2.setHeight(30);
    root.insertChild(root_child2, 2);

    var root_child3 = new Yoga.Node();
    root_child3.setWidth(30);
    root_child3.setHeight(30);
    root.insertChild(root_child3, 3);
    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(60 === root.getComputedHeight(), "60 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(20 === root_child0.getComputedTop(), "20 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(30 === root_child0.getComputedWidth(), "30 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(10 === root_child0.getComputedHeight(), "10 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");

    console.assert(30 === root_child1.getComputedLeft(), "30 === root_child1.getComputedLeft() (" + root_child1.getComputedLeft() + ")");
    console.assert(10 === root_child1.getComputedTop(), "10 === root_child1.getComputedTop() (" + root_child1.getComputedTop() + ")");
    console.assert(30 === root_child1.getComputedWidth(), "30 === root_child1.getComputedWidth() (" + root_child1.getComputedWidth() + ")");
    console.assert(20 === root_child1.getComputedHeight(), "20 === root_child1.getComputedHeight() (" + root_child1.getComputedHeight() + ")");

    console.assert(60 === root_child2.getComputedLeft(), "60 === root_child2.getComputedLeft() (" + root_child2.getComputedLeft() + ")");
    console.assert(0 === root_child2.getComputedTop(), "0 === root_child2.getComputedTop() (" + root_child2.getComputedTop() + ")");
    console.assert(30 === root_child2.getComputedWidth(), "30 === root_child2.getComputedWidth() (" + root_child2.getComputedWidth() + ")");
    console.assert(30 === root_child2.getComputedHeight(), "30 === root_child2.getComputedHeight() (" + root_child2.getComputedHeight() + ")");

    console.assert(0 === root_child3.getComputedLeft(), "0 === root_child3.getComputedLeft() (" + root_child3.getComputedLeft() + ")");
    console.assert(30 === root_child3.getComputedTop(), "30 === root_child3.getComputedTop() (" + root_child3.getComputedTop() + ")");
    console.assert(30 === root_child3.getComputedWidth(), "30 === root_child3.getComputedWidth() (" + root_child3.getComputedWidth() + ")");
    console.assert(30 === root_child3.getComputedHeight(), "30 === root_child3.getComputedHeight() (" + root_child3.getComputedHeight() + ")");

    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_RTL);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(60 === root.getComputedHeight(), "60 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(70 === root_child0.getComputedLeft(), "70 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(20 === root_child0.getComputedTop(), "20 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(30 === root_child0.getComputedWidth(), "30 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(10 === root_child0.getComputedHeight(), "10 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");

    console.assert(40 === root_child1.getComputedLeft(), "40 === root_child1.getComputedLeft() (" + root_child1.getComputedLeft() + ")");
    console.assert(10 === root_child1.getComputedTop(), "10 === root_child1.getComputedTop() (" + root_child1.getComputedTop() + ")");
    console.assert(30 === root_child1.getComputedWidth(), "30 === root_child1.getComputedWidth() (" + root_child1.getComputedWidth() + ")");
    console.assert(20 === root_child1.getComputedHeight(), "20 === root_child1.getComputedHeight() (" + root_child1.getComputedHeight() + ")");

    console.assert(10 === root_child2.getComputedLeft(), "10 === root_child2.getComputedLeft() (" + root_child2.getComputedLeft() + ")");
    console.assert(0 === root_child2.getComputedTop(), "0 === root_child2.getComputedTop() (" + root_child2.getComputedTop() + ")");
    console.assert(30 === root_child2.getComputedWidth(), "30 === root_child2.getComputedWidth() (" + root_child2.getComputedWidth() + ")");
    console.assert(30 === root_child2.getComputedHeight(), "30 === root_child2.getComputedHeight() (" + root_child2.getComputedHeight() + ")");

    console.assert(70 === root_child3.getComputedLeft(), "70 === root_child3.getComputedLeft() (" + root_child3.getComputedLeft() + ")");
    console.assert(30 === root_child3.getComputedTop(), "30 === root_child3.getComputedTop() (" + root_child3.getComputedTop() + ")");
    console.assert(30 === root_child3.getComputedWidth(), "30 === root_child3.getComputedWidth() (" + root_child3.getComputedWidth() + ")");
    console.assert(30 === root_child3.getComputedHeight(), "30 === root_child3.getComputedHeight() (" + root_child3.getComputedHeight() + ")");

    if (typeof root !== "undefined") {
      root.freeRecursive();
    }
  }());

  if (typeof gc !== "undefined") {
    gc();
    console.assert(0 === Yoga.getInstanceCount(), "0 === Yoga.getInstanceCount() (" + Yoga.getInstanceCount() + ")");
  }
});
it("wrap_row_align_items_center", function () {
  (function () {
    var root = new Yoga.Node();
    root.setFlexDirection(Yoga.FLEX_DIRECTION_ROW);
    root.setAlignItems(Yoga.ALIGN_CENTER);
    root.setFlexWrap(Yoga.WRAP_WRAP);
    root.setWidth(100);

    var root_child0 = new Yoga.Node();
    root_child0.setWidth(30);
    root_child0.setHeight(10);
    root.insertChild(root_child0, 0);

    var root_child1 = new Yoga.Node();
    root_child1.setWidth(30);
    root_child1.setHeight(20);
    root.insertChild(root_child1, 1);

    var root_child2 = new Yoga.Node();
    root_child2.setWidth(30);
    root_child2.setHeight(30);
    root.insertChild(root_child2, 2);

    var root_child3 = new Yoga.Node();
    root_child3.setWidth(30);
    root_child3.setHeight(30);
    root.insertChild(root_child3, 3);
    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(60 === root.getComputedHeight(), "60 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(10 === root_child0.getComputedTop(), "10 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(30 === root_child0.getComputedWidth(), "30 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(10 === root_child0.getComputedHeight(), "10 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");

    console.assert(30 === root_child1.getComputedLeft(), "30 === root_child1.getComputedLeft() (" + root_child1.getComputedLeft() + ")");
    console.assert(5 === root_child1.getComputedTop(), "5 === root_child1.getComputedTop() (" + root_child1.getComputedTop() + ")");
    console.assert(30 === root_child1.getComputedWidth(), "30 === root_child1.getComputedWidth() (" + root_child1.getComputedWidth() + ")");
    console.assert(20 === root_child1.getComputedHeight(), "20 === root_child1.getComputedHeight() (" + root_child1.getComputedHeight() + ")");

    console.assert(60 === root_child2.getComputedLeft(), "60 === root_child2.getComputedLeft() (" + root_child2.getComputedLeft() + ")");
    console.assert(0 === root_child2.getComputedTop(), "0 === root_child2.getComputedTop() (" + root_child2.getComputedTop() + ")");
    console.assert(30 === root_child2.getComputedWidth(), "30 === root_child2.getComputedWidth() (" + root_child2.getComputedWidth() + ")");
    console.assert(30 === root_child2.getComputedHeight(), "30 === root_child2.getComputedHeight() (" + root_child2.getComputedHeight() + ")");

    console.assert(0 === root_child3.getComputedLeft(), "0 === root_child3.getComputedLeft() (" + root_child3.getComputedLeft() + ")");
    console.assert(30 === root_child3.getComputedTop(), "30 === root_child3.getComputedTop() (" + root_child3.getComputedTop() + ")");
    console.assert(30 === root_child3.getComputedWidth(), "30 === root_child3.getComputedWidth() (" + root_child3.getComputedWidth() + ")");
    console.assert(30 === root_child3.getComputedHeight(), "30 === root_child3.getComputedHeight() (" + root_child3.getComputedHeight() + ")");

    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_RTL);

    console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft() (" + root.getComputedLeft() + ")");
    console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop() (" + root.getComputedTop() + ")");
    console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth() (" + root.getComputedWidth() + ")");
    console.assert(60 === root.getComputedHeight(), "60 === root.getComputedHeight() (" + root.getComputedHeight() + ")");

    console.assert(70 === root_child0.getComputedLeft(), "70 === root_child0.getComputedLeft() (" + root_child0.getComputedLeft() + ")");
    console.assert(10 === root_child0.getComputedTop(), "10 === root_child0.getComputedTop() (" + root_child0.getComputedTop() + ")");
    console.assert(30 === root_child0.getComputedWidth(), "30 === root_child0.getComputedWidth() (" + root_child0.getComputedWidth() + ")");
    console.assert(10 === root_child0.getComputedHeight(), "10 === root_child0.getComputedHeight() (" + root_child0.getComputedHeight() + ")");

    console.assert(40 === root_child1.getComputedLeft(), "40 === root_child1.getComputedLeft() (" + root_child1.getComputedLeft() + ")");
    console.assert(5 === root_child1.getComputedTop(), "5 === root_child1.getComputedTop() (" + root_child1.getComputedTop() + ")");
    console.assert(30 === root_child1.getComputedWidth(), "30 === root_child1.getComputedWidth() (" + root_child1.getComputedWidth() + ")");
    console.assert(20 === root_child1.getComputedHeight(), "20 === root_child1.getComputedHeight() (" + root_child1.getComputedHeight() + ")");

    console.assert(10 === root_child2.getComputedLeft(), "10 === root_child2.getComputedLeft() (" + root_child2.getComputedLeft() + ")");
    console.assert(0 === root_child2.getComputedTop(), "0 === root_child2.getComputedTop() (" + root_child2.getComputedTop() + ")");
    console.assert(30 === root_child2.getComputedWidth(), "30 === root_child2.getComputedWidth() (" + root_child2.getComputedWidth() + ")");
    console.assert(30 === root_child2.getComputedHeight(), "30 === root_child2.getComputedHeight() (" + root_child2.getComputedHeight() + ")");

    console.assert(70 === root_child3.getComputedLeft(), "70 === root_child3.getComputedLeft() (" + root_child3.getComputedLeft() + ")");
    console.assert(30 === root_child3.getComputedTop(), "30 === root_child3.getComputedTop() (" + root_child3.getComputedTop() + ")");
    console.assert(30 === root_child3.getComputedWidth(), "30 === root_child3.getComputedWidth() (" + root_child3.getComputedWidth() + ")");
    console.assert(30 === root_child3.getComputedHeight(), "30 === root_child3.getComputedHeight() (" + root_child3.getComputedHeight() + ")");

    if (typeof root !== "undefined") {
      root.freeRecursive();
    }
  }());

  if (typeof gc !== "undefined") {
    gc();
    console.assert(0 === Yoga.getInstanceCount(), "0 === Yoga.getInstanceCount() (" + Yoga.getInstanceCount() + ")");
  }
});
