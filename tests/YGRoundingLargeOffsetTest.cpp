/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

static YGSize _measureTwoLines(
    YGNodeConstRef /*node*/,
    float /*width*/,
    YGMeasureMode /*widthMode*/,
    float /*height*/,
    YGMeasureMode /*heightMode*/) {
  return YGSize{292.0f, 44.0f};
}

TEST(YogaTest, rounding_measured_height_is_exact_across_float_steps) {
  for (const float spacer :
       {1012.0f + 1.0f / 3.0f,
        1012.0f + 2.0f / 3.0f,
        2004.0f + 1.0f / 3.0f,
        2028.0f + 2.0f / 3.0f,
        4052.0f + 2.0f / 3.0f}) {
    YGConfigRef config = YGConfigNew();
    YGConfigSetPointScaleFactor(config, 3.0f);

    YGNodeRef root = YGNodeNewWithConfig(config);
    YGNodeStyleSetWidth(root, 300);

    YGNodeRef spacerNode = YGNodeNewWithConfig(config);
    YGNodeStyleSetHeight(spacerNode, spacer);
    YGNodeInsertChild(root, spacerNode, 0);

    YGNodeRef text = YGNodeNewWithConfig(config);
    YGNodeSetMeasureFunc(text, _measureTwoLines);
    YGNodeInsertChild(root, text, 1);

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

    ASSERT_EQ(44.0f, YGNodeLayoutGetHeight(text)) << "spacer " << spacer;

    YGNodeFreeRecursive(root);
    YGConfigFree(config);
  }
}
