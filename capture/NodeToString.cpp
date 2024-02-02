/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <capture/NodeToString.h>
#include <nlohmann/json.hpp>

namespace facebook::yoga {

using namespace nlohmann;

static void appendFloatIfNotDefault(
    json& j,
    std::string_view key,
    float num,
    float defaultNum) {
  if (num != defaultNum && !YGFloatIsUndefined(num)) {
    j["style"][key] = num;
  }
}

static void appendYGValueIfNotDefault(
    json& j,
    std::string_view key,
    const YGValue& value,
    const YGValue& defaultValue) {
  if (value != defaultValue) {
    if (value.unit == YGUnitAuto) {
      j["style"][key]["unit"] = "auto";
    } else if (value.unit == YGUnitUndefined) {
      j["style"][key]["unit"] = "undefined";
    } else {
      std::string unit = value.unit == YGUnitPoint ? "px" : "%%";
      j["style"][key]["value"] = value.value;
      j["style"][key]["unit"] = unit;
    }
  }
}

static void appendEnumValueIfNotDefault(
    json& j,
    std::string_view key,
    std::string_view value,
    std::string_view defaultValue) {
  if (value != defaultValue) {
    j["style"][key] = value;
  }
}

template <auto Field>
static void appendEdges(
    json& j,
    const std::string& key,
    YGNodeRef node,
    YGNodeRef defaultNode) {
  appendYGValueIfNotDefault(
      j,
      key + "-left",
      (*Field)(node, YGEdgeLeft),
      (*Field)(defaultNode, YGEdgeLeft));
  appendYGValueIfNotDefault(
      j,
      key + "-right",
      (*Field)(node, YGEdgeRight),
      (*Field)(defaultNode, YGEdgeRight));
  appendYGValueIfNotDefault(
      j,
      key + "-top",
      (*Field)(node, YGEdgeTop),
      (*Field)(defaultNode, YGEdgeTop));
  appendYGValueIfNotDefault(
      j,
      key + "-bottom",
      (*Field)(node, YGEdgeBottom),
      (*Field)(defaultNode, YGEdgeBottom));
  appendYGValueIfNotDefault(
      j,
      key + "-all",
      (*Field)(node, YGEdgeAll),
      (*Field)(defaultNode, YGEdgeAll));
  appendYGValueIfNotDefault(
      j,
      key + "-start",
      (*Field)(node, YGEdgeStart),
      (*Field)(defaultNode, YGEdgeStart));
  appendYGValueIfNotDefault(
      j,
      key + "-end",
      (*Field)(node, YGEdgeEnd),
      (*Field)(defaultNode, YGEdgeEnd));
  appendYGValueIfNotDefault(
      j,
      key + "-vertical",
      (*Field)(node, YGEdgeVertical),
      (*Field)(defaultNode, YGEdgeVertical));
  appendYGValueIfNotDefault(
      j,
      key + "-horizontal",
      (*Field)(node, YGEdgeHorizontal),
      (*Field)(defaultNode, YGEdgeHorizontal));
}

YGValue borderFloatToYGValue(YGNodeRef node, YGEdge edge) {
  float val = YGNodeStyleGetBorder(node, edge);
  YGUnit unit = YGFloatIsUndefined(val) ? YGUnitUndefined : YGUnitPoint;
  return YGValue{val, unit};
}

static void nodeToStringImpl(json& j, YGNodeRef node, YGPrintOptions options) {
  if ((options & YGPrintOptionsLayout) == YGPrintOptionsLayout) {
    j["layout"]["width"] = YGNodeStyleGetWidth(node).value;
    j["layout"]["height"] = YGNodeStyleGetHeight(node).value;
    j["layout"]["top"] = YGNodeStyleGetPosition(node, YGEdgeTop).value;
    j["layout"]["left"] = YGNodeStyleGetPosition(node, YGEdgeLeft).value;
  }

  if ((options & YGPrintOptionsStyle) == YGPrintOptionsStyle) {
    const YGNodeRef defaultNode = YGNodeNew();
    appendEnumValueIfNotDefault(
        j,
        "flex-direction",
        YGFlexDirectionToString(YGNodeStyleGetFlexDirection(node)),
        YGFlexDirectionToString(YGNodeStyleGetFlexDirection(defaultNode)));
    appendEnumValueIfNotDefault(
        j,
        "justify-content",
        YGJustifyToString(YGNodeStyleGetJustifyContent(node)),
        YGJustifyToString(YGNodeStyleGetJustifyContent(defaultNode)));
    appendEnumValueIfNotDefault(
        j,
        "align-items",
        YGAlignToString(YGNodeStyleGetAlignItems(node)),
        YGAlignToString(YGNodeStyleGetAlignItems(defaultNode)));
    appendEnumValueIfNotDefault(
        j,
        "align-content",
        YGAlignToString(YGNodeStyleGetAlignContent(node)),
        YGAlignToString(YGNodeStyleGetAlignContent(defaultNode)));
    appendEnumValueIfNotDefault(
        j,
        "align-self",
        YGAlignToString(YGNodeStyleGetAlignSelf(node)),
        YGAlignToString(YGNodeStyleGetAlignSelf(defaultNode)));
    appendEnumValueIfNotDefault(
        j,
        "flex-wrap",
        YGWrapToString(YGNodeStyleGetFlexWrap(node)),
        YGWrapToString(YGNodeStyleGetFlexWrap(defaultNode)));
    appendEnumValueIfNotDefault(
        j,
        "overflow",
        YGOverflowToString(YGNodeStyleGetOverflow(node)),
        YGOverflowToString(YGNodeStyleGetOverflow(defaultNode)));
    appendEnumValueIfNotDefault(
        j,
        "display",
        YGDisplayToString(YGNodeStyleGetDisplay(node)),
        YGDisplayToString(YGNodeStyleGetDisplay(defaultNode)));
    appendEnumValueIfNotDefault(
        j,
        "position-type",
        YGPositionTypeToString(YGNodeStyleGetPositionType(node)),
        YGPositionTypeToString(YGNodeStyleGetPositionType(defaultNode)));

    appendFloatIfNotDefault(
        j,
        "flex-grow",
        YGNodeStyleGetFlexGrow(node),
        YGNodeStyleGetFlexGrow(defaultNode));
    appendFloatIfNotDefault(
        j,
        "flex-shrink",
        YGNodeStyleGetFlexShrink(node),
        YGNodeStyleGetFlexShrink(defaultNode));
    appendFloatIfNotDefault(
        j, "flex", YGNodeStyleGetFlex(node), YGNodeStyleGetFlex(defaultNode));
    appendYGValueIfNotDefault(
        j,
        "flex-basis",
        YGNodeStyleGetFlexBasis(node),
        YGNodeStyleGetFlexBasis(defaultNode));

    appendEdges<&YGNodeStyleGetMargin>(j, "margin", node, defaultNode);
    appendEdges<&YGNodeStyleGetPadding>(j, "padding", node, defaultNode);
    appendEdges<&borderFloatToYGValue>(j, "border", node, defaultNode);
    appendEdges<&YGNodeStyleGetPosition>(j, "position", node, defaultNode);

    appendFloatIfNotDefault(
        j,
        "gap",
        YGNodeStyleGetGap(node, YGGutterAll),
        YGNodeStyleGetGap(defaultNode, YGGutterAll));
    appendFloatIfNotDefault(
        j,
        "column-gap",
        YGNodeStyleGetGap(node, YGGutterColumn),
        YGNodeStyleGetGap(defaultNode, YGGutterColumn));
    appendFloatIfNotDefault(
        j,
        "row-gap",
        YGNodeStyleGetGap(node, YGGutterRow),
        YGNodeStyleGetGap(defaultNode, YGGutterRow));

    appendYGValueIfNotDefault(
        j,
        "width",
        YGNodeStyleGetWidth(node),
        YGNodeStyleGetWidth(defaultNode));
    appendYGValueIfNotDefault(
        j,
        "height",
        YGNodeStyleGetHeight(node),
        YGNodeStyleGetHeight(defaultNode));
    appendYGValueIfNotDefault(
        j,
        "max-width",
        YGNodeStyleGetMaxWidth(node),
        YGNodeStyleGetMaxWidth(defaultNode));
    appendYGValueIfNotDefault(
        j,
        "max-height",
        YGNodeStyleGetMaxHeight(node),
        YGNodeStyleGetMaxHeight(defaultNode));
    appendYGValueIfNotDefault(
        j,
        "min-width",
        YGNodeStyleGetMinWidth(node),
        YGNodeStyleGetMinWidth(defaultNode));
    appendYGValueIfNotDefault(
        j,
        "min-height",
        YGNodeStyleGetMinHeight(node),
        YGNodeStyleGetMinHeight(defaultNode));

    if (YGNodeHasMeasureFunc(node)) {
      j["style"]["has-custom-measure"] = true;
    }
  }

  const size_t childCount = YGNodeGetChildCount(node);
  if ((options & YGPrintOptionsChildren) == YGPrintOptionsChildren &&
      childCount > 0) {
    for (size_t i = 0; i < childCount; i++) {
      j["children"].push_back({});
      nodeToStringImpl(j["children"][i], YGNodeGetChild(node, i), options);
    }
  }
}

void nodeToString(std::string& str, YGNodeRef node, YGPrintOptions options) {
  json j;
  nodeToStringImpl(j, node, options);
  str = j.dump(2);
}

} // namespace facebook::yoga
