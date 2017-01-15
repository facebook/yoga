/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var Yoga = Yoga || require("../../sources/entry-" + process.env.TEST_ENTRY);

it("margin_start", function () {
  var root = Yoga.Node.create();
  root.setWidth(100);
  root.setHeight(100);
  root.setMargin(Yoga.EDGE_START, `10%`);

  root.calculateLayout(100, 100, Yoga.DIRECTION_LTR);

  console.assert(10 === root.getComputedMargin(Yoga.EDGE_LEFT), "10 === root.getComputedMargin(Yoga.EDGE_LEFT)");
  console.assert(0 === root.getComputedMargin(Yoga.EDGE_RIGHT), "0 === root.getComputedMargin(Yoga.EDGE_RIGHT)");

  root.calculateLayout(100, 100, Yoga.DIRECTION_RTL);

  console.assert(0 === root.getComputedMargin(Yoga.EDGE_LEFT), "0 === root.getComputedMargin(Yoga.EDGE_LEFT)");
  console.assert(10 === root.getComputedMargin(Yoga.EDGE_RIGHT), "10 === root.getComputedMargin(Yoga.EDGE_RIGHT)");

  if (typeof root !== "undefined")
    root.freeRecursive();

  (typeof gc !== "undefined") && gc();
  console.assert(0 === Yoga.getInstanceCount(), "0 === Yoga.getInstanceCount() (" + Yoga.getInstanceCount() + ")");
});
