/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var Yoga = Yoga || require("../../sources/entry-" + process.env.TEST_ENTRY);

YGBENCHMARK("Stack with flex", function() {
  var root = new Yoga.Node();
  root.setWidth(100);
  root.setHeight(100);

  var measureCounter = getMeasureCounter();

  for (var i = 0; i < 10; i++) {
    const child = new Yoga.Node();
    child.setMeasureFunc(measureCounter.inc);
    child.setFlex(child, 1);
    root.insertChild(child, 0);
  }

  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);
  //root.freeRecursive();
});

YGBENCHMARK("Align stretch in undefined axis", function() {
  var root = new Yoga.Node();

  var measureCounter = getMeasureCounter();

  for (var i = 0; i < 10; i++) {
    var child = new Yoga.Node();
    child.setMeasureFunc(measureCounter.inc);
    child.setHeight(20);
    root.insertChild(child, 0);
  }

  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);
  //root.freeRecursive();
});

YGBENCHMARK("Nested flex", function() {
  var root = new Yoga.Node();

  var measureCounter = getMeasureCounter();

  for (var i = 0; i < 10; i++) {
    var child = new Yoga.Node();
    child.setFlex(child, 1);
    root.insertChild(child, 0);

    for (var ii = 0; ii < 10; ii++) {
      var grandChild = new Yoga.Node();
      grandChild.setMeasureFunc(measureCounter.inc);
      grandChild.setFlex(1);
      child.insertChild(grandChild, 0);
    }
  }

  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);
  //root.freeRecursive();
});

YGBENCHMARK("Huge nested layout", function() {
  var root = new Yoga.Node();

  for (var i = 0; i < 10; i++) {
    var child = new Yoga.Node();
    child.setFlexGrow(1);
    child.setWidth(10);
    child.setHeight(10);
    root.insertChild(child, 0);

    for (var ii = 0; ii < 10; ii++) {
      var grandChild = new Yoga.Node();
      grandChild.setFlexDirection(Yoga.FLEX_DIRECTION_ROW);
      grandChild.setFlexGrow(1);
      grandChild.setWidth(10);
      grandChild.setHeight(10);
      child.insertChild(grandChild, 0);

      for (var iii = 0; iii < 10; iii++) {
        var grandGrandChild = new Yoga.Node();
        grandGrandChild.setFlexGrow(1);
        grandGrandChild.setWidth(10);
        grandGrandChild.setHeight(10);
        grandChild.insertChild(grandGrandChild, 0);

        for (var iiii = 0; iiii < 10; iiii++) {
          var grandGrandGrandChild = new Yoga.Node();
          grandGrandGrandChild.setFlexDirection(Yoga.FLEX_DIRECTION_ROW);
          grandGrandGrandChild.setFlexGrow(1);
          grandGrandGrandChild.setWidth(10);
          grandGrandGrandChild.setHeight(10);
          grandGrandChild.insertChild(grandGrandGrandChild, 0);
        }
      }
    }
  }

  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);
  //root.freeRecursive();
});
