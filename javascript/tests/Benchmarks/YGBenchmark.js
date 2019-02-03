/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

var Yoga = Yoga || require("../../dist/entry-" + process.env.TEST_ENTRY);

var ITERATIONS = 2000;

YGBENCHMARK("Stack with flex", function() {
  var root = Yoga.Node.create();
  root.setWidth(100);
  root.setHeight(100);

  var measureCounter = getMeasureCounter(Yoga);

  for (var i = 0; i < ITERATIONS; i++) {
    const child = Yoga.Node.create();
    child.setMeasureFunc(measureCounter.inc);
    child.setFlex(1);
    root.insertChild(child, 0);
  }

  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);
  root.freeRecursive();
});

YGBENCHMARK("Align stretch in undefined axis", function() {
  var root = Yoga.Node.create();

  var measureCounter = getMeasureCounter(Yoga);

  for (var i = 0; i < ITERATIONS; i++) {
    var child = Yoga.Node.create();
    child.setMeasureFunc(measureCounter.inc);
    child.setHeight(20);
    root.insertChild(child, 0);
  }

  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);
  root.freeRecursive();
});

YGBENCHMARK("Nested flex", function() {
  var root = Yoga.Node.create();

  var measureCounter = getMeasureCounter(Yoga);

  var iterations = Math.pow(ITERATIONS, 1 / 2);

  for (var i = 0; i < iterations; i++) {
    var child = Yoga.Node.create();
    child.setFlex(1);
    root.insertChild(child, 0);

    for (var ii = 0; ii < iterations; ii++) {
      var grandChild = Yoga.Node.create();
      grandChild.setMeasureFunc(measureCounter.inc);
      grandChild.setFlex(1);
      child.insertChild(grandChild, 0);
    }
  }

  root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);
  root.freeRecursive();
});

YGBENCHMARK("Huge nested layout", function() {
  var root = Yoga.Node.create();

  var iterations = Math.pow(ITERATIONS, 1 / 4);

  for (var i = 0; i < iterations; i++) {
    var child = Yoga.Node.create();
    child.setFlexGrow(1);
    child.setWidth(10);
    child.setHeight(10);
    root.insertChild(child, 0);

    for (var ii = 0; ii < iterations; ii++) {
      var grandChild = Yoga.Node.create();
      grandChild.setFlexDirection(Yoga.FLEX_DIRECTION_ROW);
      grandChild.setFlexGrow(1);
      grandChild.setWidth(10);
      grandChild.setHeight(10);
      child.insertChild(grandChild, 0);

      for (var iii = 0; iii < iterations; iii++) {
        var grandGrandChild = Yoga.Node.create();
        grandGrandChild.setFlexGrow(1);
        grandGrandChild.setWidth(10);
        grandGrandChild.setHeight(10);
        grandChild.insertChild(grandGrandChild, 0);

        for (var iiii = 0; iiii < iterations; iiii++) {
          var grandGrandGrandChild = Yoga.Node.create();
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
  root.freeRecursive();
});
