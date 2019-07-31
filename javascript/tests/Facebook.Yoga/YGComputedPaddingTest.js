/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

var Yoga = Yoga || require("../../sources/entry-" + process.env.TEST_ENTRY);

it("padding_start", function () {
  var root = Yoga.Node.create();
  root.setWidth(100);
  root.setHeight(100);
  root.setPadding(Yoga.EDGE_START, `10%`);

  root.calculateLayout(100, 100, Yoga.DIRECTION_LTR);

  console.assert(10 === root.getComputedPadding(Yoga.EDGE_LEFT), "10 === root.getComputedPadding(Yoga.EDGE_LEFT)");
  console.assert(0 === root.getComputedPadding(Yoga.EDGE_RIGHT), "0 === root.getComputedPadding(Yoga.EDGE_RIGHT)");

  root.calculateLayout(100, 100, Yoga.DIRECTION_RTL);

  console.assert(0 === root.getComputedPadding(Yoga.EDGE_LEFT), "0 === root.getComputedPadding(Yoga.EDGE_LEFT)");
  console.assert(10 === root.getComputedPadding(Yoga.EDGE_RIGHT), "10 === root.getComputedPadding(Yoga.EDGE_RIGHT)");

  if (typeof root !== "undefined")
    root.freeRecursive();

  (typeof gc !== "undefined") && gc();
  // TODO Add event support in js and check instace allocation and de allocation using that
});
