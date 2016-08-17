/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include <stdlib.h>

#include "CSSLayoutTestUtils.h"

#ifdef _MSC_VER
#include <float.h>
#define isnan _isnan

/* define fmaxf & fminf if < VC12 */
#if _MSC_VER < 1800
__forceinline const float fmaxf(const float a, const float b) {
  return (a > b) ? a : b;
}
__forceinline const float fminf(const float a, const float b) {
  return (a < b) ? a : b;
}
#endif
#endif

static bool eq(float a, float b) {
  return fabs(a - b) < 0.0001;
}

static bool are_layout_equal(CSSNode *a, CSSNode *b) {
  if (!eq(a->layout.dimensions[CSSDimensionWidth], b->layout.dimensions[CSSDimensionWidth]) ||
      !eq(a->layout.dimensions[CSSDimensionHeight], b->layout.dimensions[CSSDimensionHeight]) ||
      !eq(a->layout.position[CSSEdgeTop], b->layout.position[CSSEdgeTop]) ||
      !eq(a->layout.position[CSSEdgeLeft], b->layout.position[CSSEdgeLeft]) ||
      !eq(CSSNodeChildCount(a), CSSNodeChildCount(b))) {
    return false;
  }
  for (int i = 0; i < CSSNodeChildCount(a); ++i) {
    if (!are_layout_equal(CSSNodeGetChild(a, i), CSSNodeGetChild(b, i))) {
      return false;
    }
  }
  return true;
}

CSSSize measure(void *context,
                float width,
                CSSMeasureMode widthMode,
                float height,
                CSSMeasureMode heightMode) {
  const char *text = (const char *) context;
  CSSSize result;
  if (strcmp(text, SMALL_TEXT) == 0) {
    if (widthMode == CSSMeasureModeUndefined) {
      width = 1000000;
    }
    result.width = fminf(SMALL_WIDTH, width);
    result.height = SMALL_WIDTH > width ? BIG_HEIGHT : SMALL_HEIGHT;
    return result;
  }
  if (strcmp(text, LONG_TEXT) == 0) {
    if (widthMode == CSSMeasureModeUndefined) {
      width = 1000000;
    }
    result.width = fminf(BIG_WIDTH, width);
    result.height = BIG_WIDTH > width ? BIG_HEIGHT : SMALL_HEIGHT;
    return result;
  }

  if (strcmp(text, MEASURE_WITH_RATIO_2) == 0) {
    if (widthMode == CSSMeasureModeExactly) {
      result.width = width;
      result.height = width * 2;
    } else if (heightMode == CSSMeasureModeExactly) {
      result.width = height * 2;
      result.height = height;
    } else if (widthMode == CSSMeasureModeAtMost) {
      result.width = width;
      result.height = width * 2;
    } else if (heightMode == CSSMeasureModeAtMost) {
      result.width = height * 2;
      result.height = height;
    } else {
      result.width = 99999;
      result.height = 99999;
    }
    return result;
  }

  if (strcmp(text, MEASURE_WITH_MATCH_PARENT) == 0) {
    if (widthMode == CSSMeasureModeUndefined) {
      width = 99999;
    }
    if (heightMode == CSSMeasureModeUndefined) {
      height = 99999;
    }
    result.width = width;
    result.height = height;
    return result;
  }

  // Should not go here
  result.width = CSSUndefined;
  result.height = CSSUndefined;
  return result;
}

bool test(CSSNode *style, CSSNode *expected_layout) {
  CSSNodeCalculateLayout(style, CSSUndefined, CSSUndefined, (CSSDirection) -1);
  return are_layout_equal(style, expected_layout);
}

CSSNode *new_test_css_node(void) {
  CSSNode *node = CSSNodeNew();
  return node;
}

void init_css_node_children(CSSNode *node, int childCount) {
  for (int i = 0; i < childCount; ++i) {
    CSSNodeInsertChild(node, new_test_css_node(), 0);
  }
}
