/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <capture/NodeToString.h>

namespace facebook::yoga {

using namespace nlohmann;

static void appendFloatIfNotDefault(
    json& j,
    std::string_view key,
    float num,
    float defaultNum) {
  if (num != defaultNum && !YGFloatIsUndefined(num)) {
    j[key] = num;
  }
}

static void appendYGValueIfNotDefault(
    json& j,
    std::string_view key,
    const YGValue& value,
    const YGValue& defaultValue) {
  if (value != defaultValue) {
    if (value.unit == YGUnitAuto) {
      j[key] = "auto";
    } else if (value.unit == YGUnitUndefined) {
      j[key] = "undefined";
    } else {
      std::string unit = value.unit == YGUnitPoint ? "px" : "pct";
      j[key]["value"] = value.value;
      j[key]["unit"] = unit;
    }
  }
}

static void appendEnumValueIfNotDefault(
    json& j,
    std::string_view key,
    std::string_view value,
    std::string_view defaultValue) {
  if (value != defaultValue) {
    j[key] = value;
  }
}

static void appendBoolIfNotDefault(
    json& j,
    std::string_view key,
    bool value,
    bool defaultValue) {
  if (value != defaultValue) {
    j[key] = value;
  }
}

template <auto Field>
static void appendEdges(
    json& j,
    const std::string& key,
    YGNodeRef node,
    YGNodeRef defaultNode) {
  appendYGValueIfNotDefault(
      j["style"],
      key + "-left",
      (*Field)(node, YGEdgeLeft),
      (*Field)(defaultNode, YGEdgeLeft));
  appendYGValueIfNotDefault(
      j["style"],
      key + "-right",
      (*Field)(node, YGEdgeRight),
      (*Field)(defaultNode, YGEdgeRight));
  appendYGValueIfNotDefault(
      j["style"],
      key + "-top",
      (*Field)(node, YGEdgeTop),
      (*Field)(defaultNode, YGEdgeTop));
  appendYGValueIfNotDefault(
      j["style"],
      key + "-bottom",
      (*Field)(node, YGEdgeBottom),
      (*Field)(defaultNode, YGEdgeBottom));
  appendYGValueIfNotDefault(
      j["style"],
      key + "-all",
      (*Field)(node, YGEdgeAll),
      (*Field)(defaultNode, YGEdgeAll));
  appendYGValueIfNotDefault(
      j["style"],
      key + "-start",
      (*Field)(node, YGEdgeStart),
      (*Field)(defaultNode, YGEdgeStart));
  appendYGValueIfNotDefault(
      j["style"],
      key + "-end",
      (*Field)(node, YGEdgeEnd),
      (*Field)(defaultNode, YGEdgeEnd));
  appendYGValueIfNotDefault(
      j["style"],
      key + "-vertical",
      (*Field)(node, YGEdgeVertical),
      (*Field)(defaultNode, YGEdgeVertical));
  appendYGValueIfNotDefault(
      j["style"],
      key + "-horizontal",
      (*Field)(node, YGEdgeHorizontal),
      (*Field)(defaultNode, YGEdgeHorizontal));
}

YGValue borderFloatToYGValue(YGNodeRef node, YGEdge edge) {
  float val = YGNodeStyleGetBorder(node, edge);
  YGUnit unit = YGFloatIsUndefined(val) ? YGUnitUndefined : YGUnitPoint;
  return YGValue{val, unit};
}

void serializeTree(json& j, YGNodeRef node, PrintOptions options) {
  if ((options & PrintOptions::Layout) == PrintOptions::Layout) {
    j["layout"]["width"] = YGNodeStyleGetWidth(node).value;
    j["layout"]["height"] = YGNodeStyleGetHeight(node).value;
    j["layout"]["top"] = YGNodeStyleGetPosition(node, YGEdgeTop).value;
    j["layout"]["left"] = YGNodeStyleGetPosition(node, YGEdgeLeft).value;
  }
  const YGNodeRef defaultNode = YGNodeNew();

  if ((options & PrintOptions::Style) == PrintOptions::Style) {
    appendEnumValueIfNotDefault(
        j["style"],
        "flex-direction",
        YGFlexDirectionToString(YGNodeStyleGetFlexDirection(node)),
        YGFlexDirectionToString(YGNodeStyleGetFlexDirection(defaultNode)));
    appendEnumValueIfNotDefault(
        j["style"],
        "justify-content",
        YGJustifyToString(YGNodeStyleGetJustifyContent(node)),
        YGJustifyToString(YGNodeStyleGetJustifyContent(defaultNode)));
    appendEnumValueIfNotDefault(
        j["style"],
        "align-items",
        YGAlignToString(YGNodeStyleGetAlignItems(node)),
        YGAlignToString(YGNodeStyleGetAlignItems(defaultNode)));
    appendEnumValueIfNotDefault(
        j["style"],
        "align-content",
        YGAlignToString(YGNodeStyleGetAlignContent(node)),
        YGAlignToString(YGNodeStyleGetAlignContent(defaultNode)));
    appendEnumValueIfNotDefault(
        j["style"],
        "align-self",
        YGAlignToString(YGNodeStyleGetAlignSelf(node)),
        YGAlignToString(YGNodeStyleGetAlignSelf(defaultNode)));
    appendEnumValueIfNotDefault(
        j["style"],
        "flex-wrap",
        YGWrapToString(YGNodeStyleGetFlexWrap(node)),
        YGWrapToString(YGNodeStyleGetFlexWrap(defaultNode)));
    appendEnumValueIfNotDefault(
        j["style"],
        "overflow",
        YGOverflowToString(YGNodeStyleGetOverflow(node)),
        YGOverflowToString(YGNodeStyleGetOverflow(defaultNode)));
    appendEnumValueIfNotDefault(
        j["style"],
        "display",
        YGDisplayToString(YGNodeStyleGetDisplay(node)),
        YGDisplayToString(YGNodeStyleGetDisplay(defaultNode)));
    appendEnumValueIfNotDefault(
        j["style"],
        "position-type",
        YGPositionTypeToString(YGNodeStyleGetPositionType(node)),
        YGPositionTypeToString(YGNodeStyleGetPositionType(defaultNode)));

    appendFloatIfNotDefault(
        j["style"],
        "flex-grow",
        YGNodeStyleGetFlexGrow(node),
        YGNodeStyleGetFlexGrow(defaultNode));
    appendFloatIfNotDefault(
        j["style"],
        "flex-shrink",
        YGNodeStyleGetFlexShrink(node),
        YGNodeStyleGetFlexShrink(defaultNode));
    appendFloatIfNotDefault(
        j["style"],
        "flex",
        YGNodeStyleGetFlex(node),
        YGNodeStyleGetFlex(defaultNode));
    appendYGValueIfNotDefault(
        j["style"],
        "flex-basis",
        YGNodeStyleGetFlexBasis(node),
        YGNodeStyleGetFlexBasis(defaultNode));

    appendEdges<&YGNodeStyleGetMargin>(j, "margin", node, defaultNode);
    appendEdges<&YGNodeStyleGetPadding>(j, "padding", node, defaultNode);
    appendEdges<&borderFloatToYGValue>(j, "border", node, defaultNode);
    appendEdges<&YGNodeStyleGetPosition>(j, "position", node, defaultNode);

    appendFloatIfNotDefault(
        j["style"],
        "gap",
        YGNodeStyleGetGap(node, YGGutterAll),
        YGNodeStyleGetGap(defaultNode, YGGutterAll));
    appendFloatIfNotDefault(
        j["style"],
        "column-gap",
        YGNodeStyleGetGap(node, YGGutterColumn),
        YGNodeStyleGetGap(defaultNode, YGGutterColumn));
    appendFloatIfNotDefault(
        j["style"],
        "row-gap",
        YGNodeStyleGetGap(node, YGGutterRow),
        YGNodeStyleGetGap(defaultNode, YGGutterRow));

    appendYGValueIfNotDefault(
        j["style"],
        "width",
        YGNodeStyleGetWidth(node),
        YGNodeStyleGetWidth(defaultNode));
    appendYGValueIfNotDefault(
        j["style"],
        "height",
        YGNodeStyleGetHeight(node),
        YGNodeStyleGetHeight(defaultNode));
    appendYGValueIfNotDefault(
        j["style"],
        "max-width",
        YGNodeStyleGetMaxWidth(node),
        YGNodeStyleGetMaxWidth(defaultNode));
    appendYGValueIfNotDefault(
        j["style"],
        "max-height",
        YGNodeStyleGetMaxHeight(node),
        YGNodeStyleGetMaxHeight(defaultNode));
    appendYGValueIfNotDefault(
        j["style"],
        "min-width",
        YGNodeStyleGetMinWidth(node),
        YGNodeStyleGetMinWidth(defaultNode));
    appendYGValueIfNotDefault(
        j["style"],
        "min-height",
        YGNodeStyleGetMinHeight(node),
        YGNodeStyleGetMinHeight(defaultNode));
  }

  if ((options & PrintOptions::Config) == PrintOptions::Config) {
    YGConfigConstRef config = YGNodeGetConfig(node);
    YGConfigConstRef defaultConfig = YGConfigGetDefault();

    appendBoolIfNotDefault(
        j["config"],
        "use-web-defaults",
        YGConfigGetUseWebDefaults(config),
        YGConfigGetUseWebDefaults(defaultConfig));
    appendFloatIfNotDefault(
        j["config"],
        "point-scale-factor",
        YGConfigGetPointScaleFactor(config),
        YGConfigGetPointScaleFactor(defaultConfig));
    YGErrata errata = YGConfigGetErrata(config);
    if (errata == YGErrataNone || errata == YGErrataAll ||
        errata == YGErrataClassic) {
      appendEnumValueIfNotDefault(
          j["config"],
          "errata",
          YGErrataToString(errata),
          YGErrataToString(YGConfigGetErrata(defaultConfig)));
    }

    if (YGConfigIsExperimentalFeatureEnabled(
            config, YGExperimentalFeatureWebFlexBasis) !=
        YGConfigIsExperimentalFeatureEnabled(
            defaultConfig, YGExperimentalFeatureWebFlexBasis)) {
      j["config"]["experimental-features"].push_back(
          YGExperimentalFeatureToString(YGExperimentalFeatureWebFlexBasis));
    }
  }

  if ((options & PrintOptions::Node) == PrintOptions::Node) {
    appendBoolIfNotDefault(
        j["node"],
        "always-forms-containing-block",
        YGNodeGetAlwaysFormsContainingBlock(node),
        YGNodeGetAlwaysFormsContainingBlock(defaultNode));
    if (YGNodeHasMeasureFunc(node)) {
      j["node"]["has-custom-measure"] = true;
    }
  }

  YGNodeFree(defaultNode);

  const size_t childCount = YGNodeGetChildCount(node);
  if ((options & PrintOptions::Children) == PrintOptions::Children &&
      childCount > 0) {
    for (size_t i = 0; i < childCount; i++) {
      j["children"].push_back({});
      serializeTree(j["children"][i], YGNodeGetChild(node, i), options);
    }
  }
}

void serializeLayoutInputs(
    json& j,
    float availableWidth,
    float availableHeight,
    YGDirection ownerDirection) {
  j["layout-inputs"] = {
      {"available-width", availableWidth},
      {"available-height", availableHeight},
      {"owner-direction", YGDirectionToString(ownerDirection)},
  };
}

} // namespace facebook::yoga
