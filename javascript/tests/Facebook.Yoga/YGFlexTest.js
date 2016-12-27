/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

 // @Generated by gentest/gentest.rb from gentest/fixtures/YGFlexTest.html

var Yoga = Yoga || require("../../sources/entry-" + process.env.TEST_ENTRY);

it("flex_basis_flex_grow_column", function () {
  var root = new Yoga.Node();
  root.setWidth(100);
  root.setHeight(100);

  var root_child0 = new Yoga.Node();
  root_child0.setFlexGrow(1);
  root_child0.setFlexBasis(50);
  root.insertChild(root_child0, 0);

  var root_child1 = new Yoga.Node();
  root_child1.setFlexGrow(1);
  root.insertChild(root_child1, 1);
  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

  console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft()");
  console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop()");
  console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth()");
  console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight()");

  console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft()");
  console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop()");
  console.assert(100 === root_child0.getComputedWidth(), "100 === root_child0.getComputedWidth()");
  console.assert(75 === root_child0.getComputedHeight(), "75 === root_child0.getComputedHeight()");

  console.assert(0 === root_child1.getComputedLeft(), "0 === root_child1.getComputedLeft()");
  console.assert(75 === root_child1.getComputedTop(), "75 === root_child1.getComputedTop()");
  console.assert(100 === root_child1.getComputedWidth(), "100 === root_child1.getComputedWidth()");
  console.assert(25 === root_child1.getComputedHeight(), "25 === root_child1.getComputedHeight()");

  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_RTL);

  console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft()");
  console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop()");
  console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth()");
  console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight()");

  console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft()");
  console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop()");
  console.assert(100 === root_child0.getComputedWidth(), "100 === root_child0.getComputedWidth()");
  console.assert(75 === root_child0.getComputedHeight(), "75 === root_child0.getComputedHeight()");

  console.assert(0 === root_child1.getComputedLeft(), "0 === root_child1.getComputedLeft()");
  console.assert(75 === root_child1.getComputedTop(), "75 === root_child1.getComputedTop()");
  console.assert(100 === root_child1.getComputedWidth(), "100 === root_child1.getComputedWidth()");
  console.assert(25 === root_child1.getComputedHeight(), "25 === root_child1.getComputedHeight()");
});
it("flex_basis_flex_grow_row", function () {
  var root = new Yoga.Node();
  root.setFlexDirection(Yoga.FLEX_DIRECTION_ROW);
  root.setWidth(100);
  root.setHeight(100);

  var root_child0 = new Yoga.Node();
  root_child0.setFlexGrow(1);
  root_child0.setFlexBasis(50);
  root.insertChild(root_child0, 0);

  var root_child1 = new Yoga.Node();
  root_child1.setFlexGrow(1);
  root.insertChild(root_child1, 1);
  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

  console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft()");
  console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop()");
  console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth()");
  console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight()");

  console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft()");
  console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop()");
  console.assert(75 === root_child0.getComputedWidth(), "75 === root_child0.getComputedWidth()");
  console.assert(100 === root_child0.getComputedHeight(), "100 === root_child0.getComputedHeight()");

  console.assert(75 === root_child1.getComputedLeft(), "75 === root_child1.getComputedLeft()");
  console.assert(0 === root_child1.getComputedTop(), "0 === root_child1.getComputedTop()");
  console.assert(25 === root_child1.getComputedWidth(), "25 === root_child1.getComputedWidth()");
  console.assert(100 === root_child1.getComputedHeight(), "100 === root_child1.getComputedHeight()");

  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_RTL);

  console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft()");
  console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop()");
  console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth()");
  console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight()");

  console.assert(25 === root_child0.getComputedLeft(), "25 === root_child0.getComputedLeft()");
  console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop()");
  console.assert(75 === root_child0.getComputedWidth(), "75 === root_child0.getComputedWidth()");
  console.assert(100 === root_child0.getComputedHeight(), "100 === root_child0.getComputedHeight()");

  console.assert(0 === root_child1.getComputedLeft(), "0 === root_child1.getComputedLeft()");
  console.assert(0 === root_child1.getComputedTop(), "0 === root_child1.getComputedTop()");
  console.assert(25 === root_child1.getComputedWidth(), "25 === root_child1.getComputedWidth()");
  console.assert(100 === root_child1.getComputedHeight(), "100 === root_child1.getComputedHeight()");
});
it("flex_basis_flex_shrink_column", function () {
  var root = new Yoga.Node();
  root.setWidth(100);
  root.setHeight(100);

  var root_child0 = new Yoga.Node();
  root_child0.setFlexShrink(1);
  root_child0.setFlexBasis(100);
  root.insertChild(root_child0, 0);

  var root_child1 = new Yoga.Node();
  root_child1.setFlexBasis(50);
  root.insertChild(root_child1, 1);
  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

  console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft()");
  console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop()");
  console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth()");
  console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight()");

  console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft()");
  console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop()");
  console.assert(100 === root_child0.getComputedWidth(), "100 === root_child0.getComputedWidth()");
  console.assert(50 === root_child0.getComputedHeight(), "50 === root_child0.getComputedHeight()");

  console.assert(0 === root_child1.getComputedLeft(), "0 === root_child1.getComputedLeft()");
  console.assert(50 === root_child1.getComputedTop(), "50 === root_child1.getComputedTop()");
  console.assert(100 === root_child1.getComputedWidth(), "100 === root_child1.getComputedWidth()");
  console.assert(50 === root_child1.getComputedHeight(), "50 === root_child1.getComputedHeight()");

  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_RTL);

  console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft()");
  console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop()");
  console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth()");
  console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight()");

  console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft()");
  console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop()");
  console.assert(100 === root_child0.getComputedWidth(), "100 === root_child0.getComputedWidth()");
  console.assert(50 === root_child0.getComputedHeight(), "50 === root_child0.getComputedHeight()");

  console.assert(0 === root_child1.getComputedLeft(), "0 === root_child1.getComputedLeft()");
  console.assert(50 === root_child1.getComputedTop(), "50 === root_child1.getComputedTop()");
  console.assert(100 === root_child1.getComputedWidth(), "100 === root_child1.getComputedWidth()");
  console.assert(50 === root_child1.getComputedHeight(), "50 === root_child1.getComputedHeight()");
});
it("flex_basis_flex_shrink_row", function () {
  var root = new Yoga.Node();
  root.setFlexDirection(Yoga.FLEX_DIRECTION_ROW);
  root.setWidth(100);
  root.setHeight(100);

  var root_child0 = new Yoga.Node();
  root_child0.setFlexShrink(1);
  root_child0.setFlexBasis(100);
  root.insertChild(root_child0, 0);

  var root_child1 = new Yoga.Node();
  root_child1.setFlexBasis(50);
  root.insertChild(root_child1, 1);
  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

  console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft()");
  console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop()");
  console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth()");
  console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight()");

  console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft()");
  console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop()");
  console.assert(50 === root_child0.getComputedWidth(), "50 === root_child0.getComputedWidth()");
  console.assert(100 === root_child0.getComputedHeight(), "100 === root_child0.getComputedHeight()");

  console.assert(50 === root_child1.getComputedLeft(), "50 === root_child1.getComputedLeft()");
  console.assert(0 === root_child1.getComputedTop(), "0 === root_child1.getComputedTop()");
  console.assert(50 === root_child1.getComputedWidth(), "50 === root_child1.getComputedWidth()");
  console.assert(100 === root_child1.getComputedHeight(), "100 === root_child1.getComputedHeight()");

  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_RTL);

  console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft()");
  console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop()");
  console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth()");
  console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight()");

  console.assert(50 === root_child0.getComputedLeft(), "50 === root_child0.getComputedLeft()");
  console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop()");
  console.assert(50 === root_child0.getComputedWidth(), "50 === root_child0.getComputedWidth()");
  console.assert(100 === root_child0.getComputedHeight(), "100 === root_child0.getComputedHeight()");

  console.assert(0 === root_child1.getComputedLeft(), "0 === root_child1.getComputedLeft()");
  console.assert(0 === root_child1.getComputedTop(), "0 === root_child1.getComputedTop()");
  console.assert(50 === root_child1.getComputedWidth(), "50 === root_child1.getComputedWidth()");
  console.assert(100 === root_child1.getComputedHeight(), "100 === root_child1.getComputedHeight()");
});
it("flex_shrink_to_zero", function () {
  var root = new Yoga.Node();
  root.setHeight(75);

  var root_child0 = new Yoga.Node();
  root_child0.setWidth(50);
  root_child0.setHeight(50);
  root.insertChild(root_child0, 0);

  var root_child1 = new Yoga.Node();
  root_child1.setFlexShrink(1);
  root_child1.setWidth(50);
  root_child1.setHeight(50);
  root.insertChild(root_child1, 1);

  var root_child2 = new Yoga.Node();
  root_child2.setWidth(50);
  root_child2.setHeight(50);
  root.insertChild(root_child2, 2);
  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

  console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft()");
  console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop()");
  console.assert(50 === root.getComputedWidth(), "50 === root.getComputedWidth()");
  console.assert(75 === root.getComputedHeight(), "75 === root.getComputedHeight()");

  console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft()");
  console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop()");
  console.assert(50 === root_child0.getComputedWidth(), "50 === root_child0.getComputedWidth()");
  console.assert(50 === root_child0.getComputedHeight(), "50 === root_child0.getComputedHeight()");

  console.assert(0 === root_child1.getComputedLeft(), "0 === root_child1.getComputedLeft()");
  console.assert(50 === root_child1.getComputedTop(), "50 === root_child1.getComputedTop()");
  console.assert(50 === root_child1.getComputedWidth(), "50 === root_child1.getComputedWidth()");
  console.assert(0 === root_child1.getComputedHeight(), "0 === root_child1.getComputedHeight()");

  console.assert(0 === root_child2.getComputedLeft(), "0 === root_child2.getComputedLeft()");
  console.assert(50 === root_child2.getComputedTop(), "50 === root_child2.getComputedTop()");
  console.assert(50 === root_child2.getComputedWidth(), "50 === root_child2.getComputedWidth()");
  console.assert(50 === root_child2.getComputedHeight(), "50 === root_child2.getComputedHeight()");

  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_RTL);

  console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft()");
  console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop()");
  console.assert(50 === root.getComputedWidth(), "50 === root.getComputedWidth()");
  console.assert(75 === root.getComputedHeight(), "75 === root.getComputedHeight()");

  console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft()");
  console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop()");
  console.assert(50 === root_child0.getComputedWidth(), "50 === root_child0.getComputedWidth()");
  console.assert(50 === root_child0.getComputedHeight(), "50 === root_child0.getComputedHeight()");

  console.assert(0 === root_child1.getComputedLeft(), "0 === root_child1.getComputedLeft()");
  console.assert(50 === root_child1.getComputedTop(), "50 === root_child1.getComputedTop()");
  console.assert(50 === root_child1.getComputedWidth(), "50 === root_child1.getComputedWidth()");
  console.assert(0 === root_child1.getComputedHeight(), "0 === root_child1.getComputedHeight()");

  console.assert(0 === root_child2.getComputedLeft(), "0 === root_child2.getComputedLeft()");
  console.assert(50 === root_child2.getComputedTop(), "50 === root_child2.getComputedTop()");
  console.assert(50 === root_child2.getComputedWidth(), "50 === root_child2.getComputedWidth()");
  console.assert(50 === root_child2.getComputedHeight(), "50 === root_child2.getComputedHeight()");
});
it("flex_basis_overrides_main_size", function () {
  var root = new Yoga.Node();
  root.setWidth(100);
  root.setHeight(100);

  var root_child0 = new Yoga.Node();
  root_child0.setFlexGrow(1);
  root_child0.setFlexBasis(50);
  root_child0.setHeight(20);
  root.insertChild(root_child0, 0);

  var root_child1 = new Yoga.Node();
  root_child1.setFlexGrow(1);
  root_child1.setHeight(10);
  root.insertChild(root_child1, 1);

  var root_child2 = new Yoga.Node();
  root_child2.setFlexGrow(1);
  root_child2.setHeight(10);
  root.insertChild(root_child2, 2);
  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

  console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft()");
  console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop()");
  console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth()");
  console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight()");

  console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft()");
  console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop()");
  console.assert(100 === root_child0.getComputedWidth(), "100 === root_child0.getComputedWidth()");
  console.assert(60 === root_child0.getComputedHeight(), "60 === root_child0.getComputedHeight()");

  console.assert(0 === root_child1.getComputedLeft(), "0 === root_child1.getComputedLeft()");
  console.assert(60 === root_child1.getComputedTop(), "60 === root_child1.getComputedTop()");
  console.assert(100 === root_child1.getComputedWidth(), "100 === root_child1.getComputedWidth()");
  console.assert(20 === root_child1.getComputedHeight(), "20 === root_child1.getComputedHeight()");

  console.assert(0 === root_child2.getComputedLeft(), "0 === root_child2.getComputedLeft()");
  console.assert(80 === root_child2.getComputedTop(), "80 === root_child2.getComputedTop()");
  console.assert(100 === root_child2.getComputedWidth(), "100 === root_child2.getComputedWidth()");
  console.assert(20 === root_child2.getComputedHeight(), "20 === root_child2.getComputedHeight()");

  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_RTL);

  console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft()");
  console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop()");
  console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth()");
  console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight()");

  console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft()");
  console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop()");
  console.assert(100 === root_child0.getComputedWidth(), "100 === root_child0.getComputedWidth()");
  console.assert(60 === root_child0.getComputedHeight(), "60 === root_child0.getComputedHeight()");

  console.assert(0 === root_child1.getComputedLeft(), "0 === root_child1.getComputedLeft()");
  console.assert(60 === root_child1.getComputedTop(), "60 === root_child1.getComputedTop()");
  console.assert(100 === root_child1.getComputedWidth(), "100 === root_child1.getComputedWidth()");
  console.assert(20 === root_child1.getComputedHeight(), "20 === root_child1.getComputedHeight()");

  console.assert(0 === root_child2.getComputedLeft(), "0 === root_child2.getComputedLeft()");
  console.assert(80 === root_child2.getComputedTop(), "80 === root_child2.getComputedTop()");
  console.assert(100 === root_child2.getComputedWidth(), "100 === root_child2.getComputedWidth()");
  console.assert(20 === root_child2.getComputedHeight(), "20 === root_child2.getComputedHeight()");
});
it("flex_grow_shrink_at_most", function () {
  var root = new Yoga.Node();
  root.setWidth(100);
  root.setHeight(100);

  var root_child0 = new Yoga.Node();
  root.insertChild(root_child0, 0);

  var root_child0_child0 = new Yoga.Node();
  root_child0_child0.setFlexGrow(1);
  root_child0_child0.setFlexShrink(1);
  root_child0.insertChild(root_child0_child0, 0);
  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

  console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft()");
  console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop()");
  console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth()");
  console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight()");

  console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft()");
  console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop()");
  console.assert(100 === root_child0.getComputedWidth(), "100 === root_child0.getComputedWidth()");
  console.assert(0 === root_child0.getComputedHeight(), "0 === root_child0.getComputedHeight()");

  console.assert(0 === root_child0_child0.getComputedLeft(), "0 === root_child0_child0.getComputedLeft()");
  console.assert(0 === root_child0_child0.getComputedTop(), "0 === root_child0_child0.getComputedTop()");
  console.assert(100 === root_child0_child0.getComputedWidth(), "100 === root_child0_child0.getComputedWidth()");
  console.assert(0 === root_child0_child0.getComputedHeight(), "0 === root_child0_child0.getComputedHeight()");

  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_RTL);

  console.assert(0 === root.getComputedLeft(), "0 === root.getComputedLeft()");
  console.assert(0 === root.getComputedTop(), "0 === root.getComputedTop()");
  console.assert(100 === root.getComputedWidth(), "100 === root.getComputedWidth()");
  console.assert(100 === root.getComputedHeight(), "100 === root.getComputedHeight()");

  console.assert(0 === root_child0.getComputedLeft(), "0 === root_child0.getComputedLeft()");
  console.assert(0 === root_child0.getComputedTop(), "0 === root_child0.getComputedTop()");
  console.assert(100 === root_child0.getComputedWidth(), "100 === root_child0.getComputedWidth()");
  console.assert(0 === root_child0.getComputedHeight(), "0 === root_child0.getComputedHeight()");

  console.assert(0 === root_child0_child0.getComputedLeft(), "0 === root_child0_child0.getComputedLeft()");
  console.assert(0 === root_child0_child0.getComputedTop(), "0 === root_child0_child0.getComputedTop()");
  console.assert(100 === root_child0_child0.getComputedWidth(), "100 === root_child0_child0.getComputedWidth()");
  console.assert(0 === root_child0_child0.getComputedHeight(), "0 === root_child0_child0.getComputedHeight()");
});
