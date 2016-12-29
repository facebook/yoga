/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */


var _measure = Yoga.addFunction(
function (retAddr, node, width, widthMode, height, heightMode) {
  Yoga.setValue(retAddr + 0, widthMode == Yoga.MeasureModeUndefined ? 10 : width, 'float');
  Yoga.setValue(retAddr + 4, heightMode == Yoga.MeasureModeUndefined ? 10 : width, 'float');
});

YGBENCHMARK("Stack with flex", () => {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  for (let i = 0; i < 10; i++) {
    const child = Yoga.nodeNew();
    Yoga.nodeSetMeasureFunc(child, _measure);
    Yoga.nodeStyleSetFlex(child, 1);
    Yoga.nodeInsertChild(root, child, 0);
  }

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);
  Yoga.nodeFreeRecursive(root);
});

YGBENCHMARK("Align stretch in undefined axis", () => {
  const root = Yoga.nodeNew();

  for (let i = 0; i < 10; i++) {
    const child = Yoga.nodeNew();
    Yoga.nodeStyleSetHeight(child, 20);
    Yoga.nodeSetMeasureFunc(child, _measure);
    Yoga.nodeInsertChild(root, child, 0);
  }

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);
  Yoga.nodeFreeRecursive(root);
});

YGBENCHMARK("Nested flex", () => {
  const root = Yoga.nodeNew();

  for (let i = 0; i < 10; i++) {
    const child = Yoga.nodeNew();
    Yoga.nodeStyleSetFlex(child, 1);
    Yoga.nodeInsertChild(root, child, 0);

    for (let ii = 0; ii < 10; ii++) {
      const grandChild = Yoga.nodeNew();
      Yoga.nodeSetMeasureFunc(grandChild, _measure);
      Yoga.nodeStyleSetFlex(grandChild, 1);
      Yoga.nodeInsertChild(child, grandChild, 0);
    }
  }

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);
  Yoga.nodeFreeRecursive(root);
});

YGBENCHMARK("Huge nested layout", () => {
  const root = Yoga.nodeNew();

  for (let i = 0; i < 10; i++) {
    const child = Yoga.nodeNew();
    Yoga.nodeStyleSetFlexGrow(child, 1);
    Yoga.nodeStyleSetWidth(child, 10);
    Yoga.nodeStyleSetHeight(child, 10);
    Yoga.nodeInsertChild(root, child, 0);

    for (let ii = 0; ii < 10; ii++) {
      const grandChild = Yoga.nodeNew();
      Yoga.nodeStyleSetFlexDirection(grandChild, Yoga.FlexDirectionRow);
      Yoga.nodeStyleSetFlexGrow(grandChild, 1);
      Yoga.nodeStyleSetWidth(grandChild, 10);
      Yoga.nodeStyleSetHeight(grandChild, 10);
      Yoga.nodeInsertChild(child, grandChild, 0);

      for (let iii = 0; iii < 10; iii++) {
        const grandGrandChild = Yoga.nodeNew();
        Yoga.nodeStyleSetFlexGrow(grandGrandChild, 1);
        Yoga.nodeStyleSetWidth(grandGrandChild, 10);
        Yoga.nodeStyleSetHeight(grandGrandChild, 10);
        Yoga.nodeInsertChild(grandChild, grandGrandChild, 0);

        for (let iii = 0; iii < 10; iii++) {
          const grandGrandGrandChild = Yoga.nodeNew();
          Yoga.nodeStyleSetFlexDirection(grandGrandGrandChild, Yoga.FlexDirectionRow);
          Yoga.nodeStyleSetFlexGrow(grandGrandGrandChild, 1);
          Yoga.nodeStyleSetWidth(grandGrandGrandChild, 10);
          Yoga.nodeStyleSetHeight(grandGrandGrandChild, 10);
          Yoga.nodeInsertChild(grandGrandChild, grandGrandGrandChild, 0);
        }
      }
    }
  }

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);
  Yoga.nodeFreeRecursive(root);
});
