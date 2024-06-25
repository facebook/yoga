/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <yoga/YGNode.h>
#include <yoga/event/event.h>
#include <functional>
#include <string_view>

namespace facebook::yoga::test {

struct TestUtil {
  static void startCountingNodes();
  static int nodeCount();
  static int stopCountingNodes();
};

struct ScopedEventSubscription {
  explicit ScopedEventSubscription(std::function<Event::Subscriber>&&);
  ~ScopedEventSubscription();
};

YGSize IntrinsicSizeMeasure(
    YGNodeConstRef node,
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode);

float longestWordWidth(std::string_view text, float widthPerChar);

float calculateHeight(
    std::string_view text,
    float measuredWidth,
    float widthPerChar,
    float heightPerChar);

} // namespace facebook::yoga::test
