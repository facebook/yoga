/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#ifndef __CSS_LAYOUT_TEST_UTILS_H
#define __CSS_LAYOUT_TEST_UTILS_H

#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

#include <CSSLayout/CSSMacros.h>
#include <CSSLayout/CSSLayout-internal.h>
#include <CSSLayout/CSSNodeList.h>

#define SMALL_WIDTH 35
#define SMALL_HEIGHT 18
#define BIG_WIDTH 172
#define BIG_HEIGHT 36
#define SMALL_TEXT "small"
#define LONG_TEXT "loooooooooong with space"
#define MEASURE_WITH_RATIO_2 "measureWithRatio2"
#define MEASURE_WITH_MATCH_PARENT "measureWithMatchParent"

CSS_EXTERN_C_BEGIN

bool test(CSSNode *style, CSSNode *expected_layout);
CSSSize measure(void *context, float width, CSSMeasureMode widthMode, float height, CSSMeasureMode heightMode);
void init_css_node_children(CSSNode *node, int childCount);
CSSNode *new_test_css_node(void);

CSS_EXTERN_C_END

#endif
