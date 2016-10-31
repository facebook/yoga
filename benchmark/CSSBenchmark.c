/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include "CSSBenchmark.h"

#include <CSSLayout/CSSLayout.h>

static CSSSize _measure(CSSNodeRef node,
                        float width,
                        CSSMeasureMode widthMode,
                        float height,
                        CSSMeasureMode heightMode) {
  return (CSSSize){
      .width = widthMode == CSSMeasureModeUndefined ? 10 : width,
      .height = heightMode == CSSMeasureModeUndefined ? 10 : width,
  };
}

CSS_BENCHMARKS({

  CSS_BENCHMARK("Stack with flex", {
    const CSSNodeRef root = CSSNodeNew();
    CSSNodeStyleSetWidth(root, 100);
    CSSNodeStyleSetHeight(root, 100);

    for (uint32_t i = 0; i < 10; i++) {
      const CSSNodeRef child = CSSNodeNew();
      CSSNodeSetMeasureFunc(child, _measure);
      CSSNodeStyleSetFlex(child, 1);
      CSSNodeInsertChild(root, child, 0);
    }

    CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);
    CSSNodeFreeRecursive(root);
  });

  CSS_BENCHMARK("Align stretch in undefined axis", {
    const CSSNodeRef root = CSSNodeNew();

    for (uint32_t i = 0; i < 10; i++) {
      const CSSNodeRef child = CSSNodeNew();
      CSSNodeStyleSetHeight(child, 20);
      CSSNodeSetMeasureFunc(child, _measure);
      CSSNodeInsertChild(root, child, 0);
    }

    CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);
    CSSNodeFreeRecursive(root);
  });

  CSS_BENCHMARK("Nested flex", {
    const CSSNodeRef root = CSSNodeNew();

    for (uint32_t i = 0; i < 10; i++) {
      const CSSNodeRef child = CSSNodeNew();
      CSSNodeSetMeasureFunc(child, _measure);
      CSSNodeStyleSetFlex(child, 1);
      CSSNodeInsertChild(root, child, 0);

      for (uint32_t ii = 0; ii < 10; ii++) {
        const CSSNodeRef grandChild = CSSNodeNew();
        CSSNodeSetMeasureFunc(grandChild, _measure);
        CSSNodeStyleSetFlex(grandChild, 1);
        CSSNodeInsertChild(child, grandChild, 0);
      }
    }

    CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);
    CSSNodeFreeRecursive(root);
  });

  CSS_BENCHMARK("Huge nested layout", {
    const CSSNodeRef root = CSSNodeNew();

    for (uint32_t i = 0; i < 10; i++) {
      const CSSNodeRef child = CSSNodeNew();
      CSSNodeStyleSetFlexGrow(child, 1);
      CSSNodeStyleSetWidth(child, 10);
      CSSNodeStyleSetHeight(child, 10);
      CSSNodeInsertChild(root, child, 0);

      for (uint32_t ii = 0; ii < 10; ii++) {
        const CSSNodeRef grandChild = CSSNodeNew();
        CSSNodeStyleSetFlexDirection(grandChild, CSSFlexDirectionRow);
        CSSNodeStyleSetFlexGrow(grandChild, 1);
        CSSNodeStyleSetWidth(grandChild, 10);
        CSSNodeStyleSetHeight(grandChild, 10);
        CSSNodeInsertChild(child, grandChild, 0);

        for (uint32_t iii = 0; iii < 10; iii++) {
          const CSSNodeRef grandGrandChild = CSSNodeNew();
          CSSNodeStyleSetFlexGrow(grandGrandChild, 1);
          CSSNodeStyleSetWidth(grandGrandChild, 10);
          CSSNodeStyleSetHeight(grandGrandChild, 10);
          CSSNodeInsertChild(grandChild, grandGrandChild, 0);

          for (uint32_t iii = 0; iii < 10; iii++) {
            const CSSNodeRef grandGrandGrandChild = CSSNodeNew();
            CSSNodeStyleSetFlexDirection(grandGrandGrandChild, CSSFlexDirectionRow);
            CSSNodeStyleSetFlexGrow(grandGrandGrandChild, 1);
            CSSNodeStyleSetWidth(grandGrandGrandChild, 10);
            CSSNodeStyleSetHeight(grandGrandGrandChild, 10);
            CSSNodeInsertChild(grandGrandChild, grandGrandGrandChild, 0);
          }
        }
      }
    }

    CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);
    CSSNodeFreeRecursive(root);
  });

});
