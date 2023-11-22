/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <deque>

#include <gtest/gtest.h>
#include <yoga/enums/Edge.h>

namespace facebook::yoga {

TEST(Ordinals, iteration) {
  std::deque expectedEdges{
      Edge::Left,
      Edge::Top,
      Edge::Right,
      Edge::Bottom,
      Edge::Start,
      Edge::End,
      Edge::Horizontal,
      Edge::Vertical,
      Edge::All};

  for (auto edge : yoga::ordinals<Edge>()) {
    ASSERT_EQ(edge, expectedEdges.front());
    expectedEdges.pop_front();
  }

  ASSERT_TRUE(expectedEdges.empty());
}

} // namespace facebook::yoga
