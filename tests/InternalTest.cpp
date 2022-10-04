/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/internal/experiments-inl.h>

using namespace facebook::yoga::internal;

struct YogaInternalTest : public testing::Test {
  void SetUp() override;
};

TEST_F(YogaInternalTest, experiments_are_initially_disabled) {
  ASSERT_EQ(isEnabled(Experiment::kDoubleMeasureCallbacks), false);
}

TEST_F(YogaInternalTest, experiments_are_can_be_enabled) {
  enable(Experiment::kDoubleMeasureCallbacks);
  ASSERT_EQ(isEnabled(Experiment::kDoubleMeasureCallbacks), true);
}

TEST_F(YogaInternalTest, experiments_are_can_be_disabled) {
  enable(Experiment::kDoubleMeasureCallbacks);
  disable(Experiment::kDoubleMeasureCallbacks);

  ASSERT_EQ(isEnabled(Experiment::kDoubleMeasureCallbacks), false);
}

TEST_F(YogaInternalTest, experiments_are_can_be_toggled_on) {
  disable(Experiment::kDoubleMeasureCallbacks);

  ASSERT_EQ(toggle(Experiment::kDoubleMeasureCallbacks), false);
  ASSERT_EQ(isEnabled(Experiment::kDoubleMeasureCallbacks), true);
}

TEST_F(YogaInternalTest, experiments_are_can_be_toggled_off) {
  enable(Experiment::kDoubleMeasureCallbacks);

  ASSERT_EQ(toggle(Experiment::kDoubleMeasureCallbacks), true);
  ASSERT_EQ(isEnabled(Experiment::kDoubleMeasureCallbacks), false);
}

void YogaInternalTest::SetUp() {
  disableAllExperiments();
}
