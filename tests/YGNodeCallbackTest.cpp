/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/YGNode.h>
#include <ostream>

inline bool operator==(const YGSize& lhs, const YGSize& rhs) {
  return lhs.width == rhs.width && lhs.height == rhs.height;
}

void PrintTo(const YGSize&, std::ostream*);

TEST(YGNode, hasMeasureFunc_initial) {
  auto n = YGNode{};
  ASSERT_FALSE(n.hasMeasureFunc());
}

TEST(YGNode, hasMeasureFunc_with_measure_fn) {
  auto n = YGNode{};
  n.setMeasureFunc([](YGNode*, double, YGMeasureMode, double, YGMeasureMode) {
    return YGSize{};
  });
  ASSERT_TRUE(n.hasMeasureFunc());
}

TEST(YGNode, measure_with_measure_fn) {
  auto n = YGNode{};

  n.setMeasureFunc(
      [](YGNode*, double w, YGMeasureMode wm, double h, YGMeasureMode hm) {
        return YGSize{w * wm, h / hm};
      });

  ASSERT_EQ(
      n.measure(23, YGMeasureModeExactly, 24, YGMeasureModeAtMost, nullptr),
      (YGSize{23, 12}));
}

TEST(YGNode, measure_with_context_measure_fn) {
  auto n = YGNode{};
  n.setMeasureFunc(
      [](YGNode*, double, YGMeasureMode, double, YGMeasureMode, void* ctx) {
        return *(YGSize*) ctx;
      });

  auto result = YGSize{123.4, -56.7};
  ASSERT_EQ(
      n.measure(0, YGMeasureModeUndefined, 0, YGMeasureModeUndefined, &result),
      result);
}

TEST(YGNode, switching_measure_fn_types) {
  auto n = YGNode{};
  n.setMeasureFunc(
      [](YGNode*, double, YGMeasureMode, double, YGMeasureMode, void*) {
        return YGSize{};
      });
  n.setMeasureFunc(
      [](YGNode*, double w, YGMeasureMode wm, double h, YGMeasureMode hm) {
        return YGSize{w * wm, h / hm};
      });

  ASSERT_EQ(
      n.measure(23, YGMeasureModeExactly, 24, YGMeasureModeAtMost, nullptr),
      (YGSize{23, 12}));
}

TEST(YGNode, hasMeasureFunc_after_unset) {
  auto n = YGNode{};
  n.setMeasureFunc([](YGNode*, double, YGMeasureMode, double, YGMeasureMode) {
    return YGSize{};
  });

  n.setMeasureFunc(nullptr);
  ASSERT_FALSE(n.hasMeasureFunc());
}

TEST(YGNode, hasMeasureFunc_after_unset_context) {
  auto n = YGNode{};
  n.setMeasureFunc(
      [](YGNode*, double, YGMeasureMode, double, YGMeasureMode, void*) {
        return YGSize{};
      });

  n.setMeasureFunc(nullptr);
  ASSERT_FALSE(n.hasMeasureFunc());
}

TEST(YGNode, hasBaselineFunc_initial) {
  auto n = YGNode{};
  ASSERT_FALSE(n.hasBaselineFunc());
}

TEST(YGNode, hasBaselineFunc_with_baseline_fn) {
  auto n = YGNode{};
  n.setBaselineFunc([](YGNode*, double, double) { return 0.0; });
  ASSERT_TRUE(n.hasBaselineFunc());
}

TEST(YGNode, baseline_with_baseline_fn) {
  auto n = YGNode{};
  n.setBaselineFunc([](YGNode*, double w, double h) { return w + h; });

  ASSERT_EQ(n.baseline(1.25, 2.5, nullptr), 3.75);
}

TEST(YGNode, baseline_with_context_baseline_fn) {
  auto n = YGNode{};
  n.setBaselineFunc([](YGNode*, double w, double h, void* ctx) {
    return w + h + *(double*) ctx;
  });

  auto ctx = -10.0;
  ASSERT_EQ(n.baseline(1.25, 2.5, &ctx), -6.25);
}

TEST(YGNode, hasBaselineFunc_after_unset) {
  auto n = YGNode{};
  n.setBaselineFunc([](YGNode*, double, double) { return 0.0; });

  n.setBaselineFunc(nullptr);
  ASSERT_FALSE(n.hasBaselineFunc());
}

TEST(YGNode, hasBaselineFunc_after_unset_context) {
  auto n = YGNode{};
  n.setBaselineFunc([](YGNode*, double, double, void*) { return 0.0; });

  n.setMeasureFunc(nullptr);
  ASSERT_FALSE(n.hasMeasureFunc());
}

TEST(YGNode, switching_baseline_fn_types) {
  auto n = YGNode{};
  n.setBaselineFunc([](YGNode*, double, double, void*) { return 0.0; });
  n.setBaselineFunc([](YGNode*, double, double) { return 1.0; });
  ASSERT_EQ(n.baseline(1, 2, nullptr), 1.0);
}

void PrintTo(const YGSize& size, std::ostream* os) {
  *os << "YGSize{" << size.width << ", " << size.height << "}";
}
