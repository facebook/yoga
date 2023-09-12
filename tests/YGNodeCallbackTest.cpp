/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/node/Node.h>
#include <ostream>

using namespace facebook::yoga;

inline bool operator==(const YGSize& lhs, const YGSize& rhs) {
  return lhs.width == rhs.width && lhs.height == rhs.height;
}

TEST(Node, hasMeasureFunc_initial) {
  auto n = Node{};
  ASSERT_FALSE(n.hasMeasureFunc());
}

TEST(Node, hasMeasureFunc_with_measure_fn) {
  auto n = Node{};
  n.setMeasureFunc(
      [](YGNodeConstRef, float, YGMeasureMode, float, YGMeasureMode) {
        return YGSize{};
      });
  ASSERT_TRUE(n.hasMeasureFunc());
}

TEST(Node, measure_with_measure_fn) {
  auto n = Node{};

  n.setMeasureFunc(
      [](YGNodeConstRef, float w, YGMeasureMode wm, float h, YGMeasureMode hm) {
        return YGSize{w * static_cast<float>(wm), h / static_cast<float>(hm)};
      });

  ASSERT_EQ(
      n.measure(23, YGMeasureModeExactly, 24, YGMeasureModeAtMost, nullptr),
      (YGSize{23, 12}));
}

TEST(Node, measure_with_context_measure_fn) {
  auto n = Node{};
  n.setMeasureFunc([](YGNodeConstRef,
                      float,
                      YGMeasureMode,
                      float,
                      YGMeasureMode,
                      void* ctx) { return *(YGSize*) ctx; });

  auto result = YGSize{123.4f, -56.7f};
  ASSERT_EQ(
      n.measure(0, YGMeasureModeUndefined, 0, YGMeasureModeUndefined, &result),
      result);
}

TEST(Node, switching_measure_fn_types) {
  auto n = Node{};
  n.setMeasureFunc(
      [](YGNodeConstRef, float, YGMeasureMode, float, YGMeasureMode, void*) {
        return YGSize{};
      });
  n.setMeasureFunc(
      [](YGNodeConstRef, float w, YGMeasureMode wm, float h, YGMeasureMode hm) {
        return YGSize{w * static_cast<float>(wm), h / static_cast<float>(hm)};
      });

  ASSERT_EQ(
      n.measure(23, YGMeasureModeExactly, 24, YGMeasureModeAtMost, nullptr),
      (YGSize{23, 12}));
}

TEST(Node, hasMeasureFunc_after_unset) {
  auto n = Node{};
  n.setMeasureFunc(
      [](YGNodeConstRef, float, YGMeasureMode, float, YGMeasureMode) {
        return YGSize{};
      });

  n.setMeasureFunc(nullptr);
  ASSERT_FALSE(n.hasMeasureFunc());
}

TEST(Node, hasMeasureFunc_after_unset_context) {
  auto n = Node{};
  n.setMeasureFunc(
      [](YGNodeConstRef, float, YGMeasureMode, float, YGMeasureMode, void*) {
        return YGSize{};
      });

  n.setMeasureFunc(nullptr);
  ASSERT_FALSE(n.hasMeasureFunc());
}

TEST(Node, hasBaselineFunc_initial) {
  auto n = Node{};
  ASSERT_FALSE(n.hasBaselineFunc());
}

TEST(Node, hasBaselineFunc_with_baseline_fn) {
  auto n = Node{};
  n.setBaselineFunc([](YGNodeConstRef, float, float) { return 0.0f; });
  ASSERT_TRUE(n.hasBaselineFunc());
}

TEST(Node, baseline_with_baseline_fn) {
  auto n = Node{};
  n.setBaselineFunc([](YGNodeConstRef, float w, float h) { return w + h; });

  ASSERT_EQ(n.baseline(1.25f, 2.5f, nullptr), 3.75f);
}

TEST(Node, baseline_with_context_baseline_fn) {
  auto n = Node{};
  n.setBaselineFunc([](YGNodeConstRef, float w, float h, void* ctx) {
    return w + h + *(float*) ctx;
  });

  auto ctx = -10.0f;
  ASSERT_EQ(n.baseline(1.25f, 2.5f, &ctx), -6.25f);
}

TEST(Node, hasBaselineFunc_after_unset) {
  auto n = Node{};
  n.setBaselineFunc([](YGNodeConstRef, float, float) { return 0.0f; });

  n.setBaselineFunc(nullptr);
  ASSERT_FALSE(n.hasBaselineFunc());
}

TEST(Node, hasBaselineFunc_after_unset_context) {
  auto n = Node{};
  n.setBaselineFunc([](YGNodeConstRef, float, float, void*) { return 0.0f; });

  n.setMeasureFunc(nullptr);
  ASSERT_FALSE(n.hasMeasureFunc());
}

TEST(Node, switching_baseline_fn_types) {
  auto n = Node{};
  n.setBaselineFunc([](YGNodeConstRef, float, float, void*) { return 0.0f; });
  n.setBaselineFunc([](YGNodeConstRef, float, float) { return 1.0f; });
  ASSERT_EQ(n.baseline(1, 2, nullptr), 1.0f);
}
