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

CSS_BENCHMARKS({

  CSS_BENCHMARK("Stack with flex", {
    CSSNodeRef root = CSSNodeNew();
    CSSNodeStyleSetWidth(root, 100);
    CSSNodeStyleSetHeight(root, 100);

    for (int i = 0; i < 3; i++) {
      CSSNodeRef child = CSSNodeNew();
      CSSNodeStyleSetHeight(child, 20);
      CSSNodeStyleSetFlex(child, 1);
      CSSNodeInsertChild(root, child, 0);
    }

    CSSNodeCalculateLayout(root, 100, 100, CSSDirectionLTR);
  });

});
