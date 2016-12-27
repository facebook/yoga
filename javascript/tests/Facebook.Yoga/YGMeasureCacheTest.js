/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var Yoga = Yoga || require("../../sources/entry-" + process.env.TEST_ENTRY);

it("measure_once_single_flexible_child", function () {
    var root = new Yoga.Node();
    root.setFlexDirection(Yoga.FLEX_DIRECTION_ROW);
    root.setAlignItems(Yoga.ALIGN_FLEX_START);
    root.setWidth(100);
    root.setHeight(100);

    var measureCounter = getMeasureCounterMax();

    var root_child0 = new Yoga.Node();
    root_child0.setMeasureFunc(measureCounter.inc);
    root_child0.setFlexGrow(1);
    root.insertChild(root_child0, 0);

    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

    console.assert(1 === measureCounter.get(), "1 === measureCounter.get()");
});
