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

static CSSSize _measure(CSSNodeRef node
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

});
