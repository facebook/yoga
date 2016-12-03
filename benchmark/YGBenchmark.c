/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include "YGBenchmark.h"

#include <CSSLayout/Yoga.h>

static YGSize _measure(YGNodeRef node,
                        float width,
                        YGMeasureMode widthMode,
                        float height,
                        YGMeasureMode heightMode) {
  return (YGSize){
      .width = widthMode == YGMeasureModeUndefined ? 10 : width,
      .height = heightMode == YGMeasureModeUndefined ? 10 : width,
  };
}

YGBENCHMARKS({

  YGBENCHMARK("Stack with flex", {
    const YGNodeRef root = YGNodeNew();
    YGNodeStyleSetWidth(root, 100);
    YGNodeStyleSetHeight(root, 100);

    for (uint32_t i = 0; i < 10; i++) {
      const YGNodeRef child = YGNodeNew();
      YGNodeSetMeasureFunc(child, _measure);
      YGNodeStyleSetFlex(child, 1);
      YGNodeInsertChild(root, child, 0);
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

  YGBENCHMARK("Align stretch in undefined axis", {
    const YGNodeRef root = YGNodeNew();

    for (uint32_t i = 0; i < 10; i++) {
      const YGNodeRef child = YGNodeNew();
      YGNodeStyleSetHeight(child, 20);
      YGNodeSetMeasureFunc(child, _measure);
      YGNodeInsertChild(root, child, 0);
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

  YGBENCHMARK("Nested flex", {
    const YGNodeRef root = YGNodeNew();

    for (uint32_t i = 0; i < 10; i++) {
      const YGNodeRef child = YGNodeNew();
      YGNodeStyleSetFlex(child, 1);
      YGNodeInsertChild(root, child, 0);

      for (uint32_t ii = 0; ii < 10; ii++) {
        const YGNodeRef grandChild = YGNodeNew();
        YGNodeSetMeasureFunc(grandChild, _measure);
        YGNodeStyleSetFlex(grandChild, 1);
        YGNodeInsertChild(child, grandChild, 0);
      }
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

  YGBENCHMARK("Huge nested layout", {
    const YGNodeRef root = YGNodeNew();

    for (uint32_t i = 0; i < 10; i++) {
      const YGNodeRef child = YGNodeNew();
      YGNodeStyleSetFlexGrow(child, 1);
      YGNodeStyleSetWidth(child, 10);
      YGNodeStyleSetHeight(child, 10);
      YGNodeInsertChild(root, child, 0);

      for (uint32_t ii = 0; ii < 10; ii++) {
        const YGNodeRef grandChild = YGNodeNew();
        YGNodeStyleSetFlexDirection(grandChild, YGFlexDirectionRow);
        YGNodeStyleSetFlexGrow(grandChild, 1);
        YGNodeStyleSetWidth(grandChild, 10);
        YGNodeStyleSetHeight(grandChild, 10);
        YGNodeInsertChild(child, grandChild, 0);

        for (uint32_t iii = 0; iii < 10; iii++) {
          const YGNodeRef grandGrandChild = YGNodeNew();
          YGNodeStyleSetFlexGrow(grandGrandChild, 1);
          YGNodeStyleSetWidth(grandGrandChild, 10);
          YGNodeStyleSetHeight(grandGrandChild, 10);
          YGNodeInsertChild(grandChild, grandGrandChild, 0);

          for (uint32_t iii = 0; iii < 10; iii++) {
            const YGNodeRef grandGrandGrandChild = YGNodeNew();
            YGNodeStyleSetFlexDirection(grandGrandGrandChild, YGFlexDirectionRow);
            YGNodeStyleSetFlexGrow(grandGrandGrandChild, 1);
            YGNodeStyleSetWidth(grandGrandGrandChild, 10);
            YGNodeStyleSetHeight(grandGrandGrandChild, 10);
            YGNodeInsertChild(grandGrandChild, grandGrandGrandChild, 0);
          }
        }
      }
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

});
