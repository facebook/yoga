/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <stdarg.h>
#include <yoga/Yoga.h>

#if DEBUG

namespace {
char writeBuffer[4096];
int _unmanagedLogger(
    const YGConfigRef /*config*/,
    const YGNodeRef /*node*/,
    YGLogLevel /*level*/,
    const char* format,
    va_list args) {
  return vsnprintf(
      writeBuffer + strlen(writeBuffer),
      sizeof(writeBuffer) - strlen(writeBuffer),
      format,
      args);
}
} // namespace

TEST(YogaTest, config_print_tree_enabled) {
  writeBuffer[0] = '\0';
  const YGConfigRef config = YGConfigNew();
  YGConfigSetPrintTreeFlag(config, true);
  YGConfigSetLogger(config, _unmanagedLogger);
  const YGNodeRef root = YGNodeNewWithConfig(config);
  const YGNodeRef child0 = YGNodeNewWithConfig(config);
  const YGNodeRef child1 = YGNodeNewWithConfig(config);
  YGNodeInsertChild(root, child0, 0);
  YGNodeInsertChild(root, child1, 1);
  YGNodeCalculateLayout(root, YGUnitUndefined, YGUnitUndefined, YGDirectionLTR);
  YGConfigSetLogger(config, NULL);
  YGNodeFreeRecursive(root);

  const char* expected =
      "<div layout=\"width: 0; height: 0; top: 0; left: 0;\" style=\"\" >\n  "
      "<div layout=\"width: 0; height: 0; top: 0; left: 0;\" style=\"\" "
      "></div>\n  <div layout=\"width: 0; height: 0; top: 0; left: 0;\" "
      "style=\"\" ></div>\n</div>";
  ASSERT_STREQ(expected, writeBuffer);
}

TEST(YogaTest, config_print_tree_disabled) {
  writeBuffer[0] = '\0';
  const YGConfigRef config = YGConfigNew();
  YGConfigSetPrintTreeFlag(config, false);
  YGConfigSetLogger(config, _unmanagedLogger);
  const YGNodeRef root = YGNodeNewWithConfig(config);
  const YGNodeRef child0 = YGNodeNewWithConfig(config);
  const YGNodeRef child1 = YGNodeNewWithConfig(config);
  YGNodeInsertChild(root, child0, 0);
  YGNodeInsertChild(root, child1, 1);
  YGNodeCalculateLayout(root, YGUnitUndefined, YGUnitUndefined, YGDirectionLTR);
  YGConfigSetLogger(config, NULL);
  YGNodeFreeRecursive(root);

  const char* expected = "";
  ASSERT_STREQ(expected, writeBuffer);
}

TEST(YogaTest, logger_default_node_should_print_no_style_info) {
  writeBuffer[0] = '\0';
  const YGConfigRef config = YGConfigNew();
  YGConfigSetLogger(config, _unmanagedLogger);
  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeCalculateLayout(root, YGUnitUndefined, YGUnitUndefined, YGDirectionLTR);
  YGNodePrint(
      root,
      (YGPrintOptions) (YGPrintOptionsLayout | YGPrintOptionsChildren | YGPrintOptionsStyle));
  YGConfigSetLogger(config, NULL);
  YGNodeFree(root);

  const char* expected =
      "<div layout=\"width: 0; height: 0; top: 0; left: 0;\" style=\"\" "
      "></div>";
  ASSERT_STREQ(expected, writeBuffer);
}

TEST(YogaTest, logger_node_with_percentage_absolute_position_and_margin) {
  writeBuffer[0] = '\0';
  const YGConfigRef config = YGConfigNew();
  YGConfigSetLogger(config, _unmanagedLogger);
  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetPositionType(root, YGPositionTypeAbsolute);
  YGNodeStyleSetWidthPercent(root, 50);
  YGNodeStyleSetHeightPercent(root, 75);
  YGNodeStyleSetFlex(root, 1);
  YGNodeStyleSetMargin(root, YGEdgeRight, 10);
  YGNodeStyleSetMarginAuto(root, YGEdgeLeft);
  YGNodeCalculateLayout(root, YGUnitUndefined, YGUnitUndefined, YGDirectionLTR);
  YGNodePrint(
      root,
      (YGPrintOptions) (YGPrintOptionsLayout | YGPrintOptionsChildren | YGPrintOptionsStyle));
  YGConfigSetLogger(config, NULL);
  YGNodeFree(root);

  const char* expected =
      "<div layout=\"width: 0; height: 0; top: 0; left: 0;\" style=\"flex: 1; "
      "margin-left: auto; margin-right: 10px; width: 50%; height: 75%; "
      "position: absolute; \" ></div>";
  ASSERT_STREQ(expected, writeBuffer);
}

TEST(YogaTest, logger_node_with_children_should_print_indented) {
  writeBuffer[0] = '\0';
  const YGConfigRef config = YGConfigNew();
  YGConfigSetLogger(config, _unmanagedLogger);
  const YGNodeRef root = YGNodeNewWithConfig(config);
  const YGNodeRef child0 = YGNodeNewWithConfig(config);
  const YGNodeRef child1 = YGNodeNewWithConfig(config);
  YGNodeInsertChild(root, child0, 0);
  YGNodeInsertChild(root, child1, 1);
  YGNodeCalculateLayout(root, YGUnitUndefined, YGUnitUndefined, YGDirectionLTR);
  YGNodePrint(
      root,
      (YGPrintOptions) (YGPrintOptionsLayout | YGPrintOptionsChildren | YGPrintOptionsStyle));
  YGConfigSetLogger(config, NULL);
  YGNodeFreeRecursive(root);

  const char* expected =
      "<div layout=\"width: 0; height: 0; top: 0; left: 0;\" style=\"\" >\n  "
      "<div layout=\"width: 0; height: 0; top: 0; left: 0;\" style=\"\" "
      "></div>\n  <div layout=\"width: 0; height: 0; top: 0; left: 0;\" "
      "style=\"\" ></div>\n</div>";
  ASSERT_STREQ(expected, writeBuffer);
}

#endif
