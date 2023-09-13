/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>
#include <yoga/config/Config.h>
#include <yoga/node/Node.h>

#include <functional>
#include <memory>

using namespace facebook;

struct ConfigCloningTest : public ::testing::Test {
  std::unique_ptr<yoga::Config, std::function<void(yoga::Config*)>> config;
  void SetUp() override;
  void TearDown() override;

  static yoga::Node clonedNode;
  static YGNodeRef cloneNode(YGNodeConstRef, YGNodeConstRef, size_t) {
    return &clonedNode;
  }
  static YGNodeRef doNotClone(YGNodeConstRef, YGNodeConstRef, size_t) {
    return nullptr;
  }
};

TEST_F(ConfigCloningTest, uses_values_provided_by_cloning_callback) {
  config->setCloneNodeCallback(cloneNode);

  yoga::Node node{}, owner{};
  auto clone = config->cloneNode(&node, &owner, 0);

  ASSERT_EQ(clone, &clonedNode);
}

TEST_F(
    ConfigCloningTest,
    falls_back_to_regular_cloning_if_callback_returns_null) {
  config->setCloneNodeCallback(doNotClone);

  yoga::Node node{}, owner{};
  auto clone = config->cloneNode(&node, &owner, 0);

  ASSERT_NE(clone, nullptr);
  YGNodeFree(clone);
}

void ConfigCloningTest::SetUp() {
  config = {static_cast<yoga::Config*>(YGConfigNew()), YGConfigFree};
}

void ConfigCloningTest::TearDown() {
  config.reset();
}

yoga::Node ConfigCloningTest::clonedNode = {};
