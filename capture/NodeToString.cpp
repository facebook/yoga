/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <stdarg.h>

#include <capture/NodeToString.h>
#include <algorithm>

namespace facebook::yoga {

static void indent(std::string& base, uint32_t level) {
  for (uint32_t i = 0; i < level; ++i) {
    base.append("  ");
  }
}

static void appendFormattedString(std::string& str, const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  va_list argsCopy;
  va_copy(argsCopy, args);
  std::vector<char> buf(1 + static_cast<size_t>(vsnprintf(NULL, 0, fmt, args)));
  va_end(args);
  vsnprintf(buf.data(), buf.size(), fmt, argsCopy);
  va_end(argsCopy);
  std::string result = std::string(buf.begin(), buf.end() - 1);
  str.append(result);
}

static void appendFloatOptionalIfDefined(
    std::string& base,
    const std::string key,
    const float num) {
  if (num != YGUndefined) {
    appendFormattedString(base, "%s: %g; ", key.c_str(), num);
  }
}

static void appendNumberIfNotUndefined(
    std::string& base,
    const std::string key,
    const YGValue& number) {
  if (number.unit != YGUnitUndefined) {
    if (number.unit == YGUnitAuto) {
      base.append(key + ": auto; ");
    } else {
      std::string unit = number.unit == YGUnitPoint ? "px" : "%%";
      appendFormattedString(
          base, "%s: %g%s; ", key.c_str(), number.value, unit.c_str());
    }
  }
}

static void appendNumberIfNotAuto(
    std::string& base,
    const std::string& key,
    const YGValue& number) {
  if (number.unit != YGUnitAuto) {
    appendNumberIfNotUndefined(base, key, number);
  }
}

static void appendNumberIfNotZero(
    std::string& base,
    const std::string& str,
    const YGValue& number) {
  if (number.unit == YGUnitAuto) {
    base.append(str + ": auto; ");
  } else if (number.value != 0) {
    appendNumberIfNotUndefined(base, str, number);
  }
}

template <auto Field>
static void
appendEdges(std::string& base, const std::string& key, YGNodeRef node) {
  appendNumberIfNotZero(base, key + "-left", (*Field)(node, YGEdgeLeft));
  appendNumberIfNotZero(base, key + "-right", (*Field)(node, YGEdgeRight));
  appendNumberIfNotZero(base, key + "-top", (*Field)(node, YGEdgeTop));
  appendNumberIfNotZero(base, key + "-bottom", (*Field)(node, YGEdgeBottom));
  appendNumberIfNotZero(base, key + "-all", (*Field)(node, YGEdgeAll));
  appendNumberIfNotZero(base, key + "-start", (*Field)(node, YGEdgeStart));
  appendNumberIfNotZero(base, key + "-end", (*Field)(node, YGEdgeEnd));
  appendNumberIfNotZero(
      base, key + "-horizontal", (*Field)(node, YGEdgeHorizontal));
  appendNumberIfNotZero(
      base, key + "-vertical", (*Field)(node, YGEdgeVertical));
}

YGValue borderFloatToYGValue(YGNodeRef node, YGEdge edge) {
  float val = YGNodeStyleGetBorder(node, edge);
  YGUnit unit = val == YGUndefined ? YGUnitUndefined : YGUnitPoint;
  return YGValue{val, unit};
}

void nodeToString(
    std::string& str,
    YGNodeRef node,
    YGPrintOptions options,
    uint32_t level) {
  indent(str, level);
  appendFormattedString(str, "<div ");

  if ((options & YGPrintOptionsLayout) == YGPrintOptionsLayout) {
    appendFormattedString(str, "layout=\"");
    appendFormattedString(str, "width: %g; ", YGNodeLayoutGetWidth(node));
    appendFormattedString(str, "height: %g; ", YGNodeLayoutGetHeight(node));
    appendFormattedString(str, "top: %g; ", YGNodeLayoutGetTop(node));
    appendFormattedString(str, "left: %g;", YGNodeLayoutGetLeft(node));
    appendFormattedString(str, "\" ");
  }

  if ((options & YGPrintOptionsStyle) == YGPrintOptionsStyle) {
    const YGNodeRef defaultNode = YGNodeNew();
    appendFormattedString(str, "style=\"");
    if (YGNodeStyleGetFlexDirection(node) !=
        YGNodeStyleGetFlexDirection(defaultNode)) {
      appendFormattedString(
          str,
          "flex-direction: %s; ",
          YGFlexDirectionToString(YGNodeStyleGetFlexDirection(node)));
    }
    if (YGNodeStyleGetJustifyContent(node) !=
        YGNodeStyleGetJustifyContent(defaultNode)) {
      appendFormattedString(
          str,
          "justify-content: %s; ",
          YGJustifyToString(YGNodeStyleGetJustifyContent(node)));
    }
    if (YGNodeStyleGetAlignItems(node) !=
        YGNodeStyleGetAlignItems(defaultNode)) {
      appendFormattedString(
          str,
          "align-items: %s; ",
          YGAlignToString(YGNodeStyleGetAlignItems(node)));
    }
    if (YGNodeStyleGetAlignContent(node) !=
        YGNodeStyleGetAlignContent(defaultNode)) {
      appendFormattedString(
          str,
          "align-content: %s; ",
          YGAlignToString(YGNodeStyleGetAlignContent(node)));
    }
    if (YGNodeStyleGetAlignSelf(node) != YGNodeStyleGetAlignSelf(defaultNode)) {
      appendFormattedString(
          str,
          "align-self: %s; ",
          YGAlignToString(YGNodeStyleGetAlignSelf(node)));
    }
    appendFloatOptionalIfDefined(
        str, "flex-grow", YGNodeStyleGetFlexGrow(node));
    appendFloatOptionalIfDefined(
        str, "flex-shrink", YGNodeStyleGetFlexShrink(node));
    appendNumberIfNotAuto(str, "flex-basis", YGNodeStyleGetFlexBasis(node));
    appendFloatOptionalIfDefined(str, "flex", YGNodeStyleGetFlex(node));

    if (YGNodeStyleGetFlexWrap(node) != YGNodeStyleGetFlexWrap(defaultNode)) {
      appendFormattedString(
          str, "flex-wrap: %s; ", YGWrapToString(YGNodeStyleGetFlexWrap(node)));
    }

    if (YGNodeStyleGetOverflow(node) != YGNodeStyleGetOverflow(defaultNode)) {
      appendFormattedString(
          str,
          "overflow: %s; ",
          YGOverflowToString(YGNodeStyleGetOverflow(node)));
    }

    if (YGNodeStyleGetDisplay(node) != YGNodeStyleGetDisplay(defaultNode)) {
      appendFormattedString(
          str, "display: %s; ", YGDisplayToString(YGNodeStyleGetDisplay(node)));
    }
    appendEdges<&YGNodeStyleGetMargin>(str, "margin", node);
    appendEdges<&YGNodeStyleGetPadding>(str, "padding", node);
    appendEdges<&borderFloatToYGValue>(str, "border", node);

    if (YGNodeStyleGetGap(node, YGGutterAll) != YGUndefined) {
      appendFloatOptionalIfDefined(
          str, "gap", YGNodeStyleGetGap(node, YGGutterAll));
    } else {
      appendFloatOptionalIfDefined(
          str, "column-gap", YGNodeStyleGetGap(node, YGGutterColumn));
      appendFloatOptionalIfDefined(
          str, "row-gap", YGNodeStyleGetGap(node, YGGutterRow));
    }

    appendNumberIfNotAuto(str, "width", YGNodeStyleGetWidth(node));
    appendNumberIfNotAuto(str, "height", YGNodeStyleGetHeight(node));
    appendNumberIfNotAuto(str, "max-width", YGNodeStyleGetMaxWidth(node));
    appendNumberIfNotAuto(str, "max-height", YGNodeStyleGetMaxHeight(node));
    appendNumberIfNotAuto(str, "min-width", YGNodeStyleGetMinWidth(node));
    appendNumberIfNotAuto(str, "min-height", YGNodeStyleGetMinHeight(node));

    if (YGNodeStyleGetPositionType(node) !=
        YGNodeStyleGetPositionType(defaultNode)) {
      appendFormattedString(
          str,
          "position: %s; ",
          YGPositionTypeToString(YGNodeStyleGetPositionType(node)));
    }

    appendEdges<&YGNodeStyleGetPosition>(str, "position", node);
    appendFormattedString(str, "\" ");

    if (YGNodeHasMeasureFunc(node)) {
      appendFormattedString(str, "has-custom-measure=\"true\"");
    }
  }
  appendFormattedString(str, ">");

  const size_t childCount = YGNodeGetChildCount(node);
  if ((options & YGPrintOptionsChildren) == YGPrintOptionsChildren &&
      childCount > 0) {
    for (size_t i = 0; i < childCount; i++) {
      appendFormattedString(str, "\n");
      nodeToString(str, YGNodeGetChild(node, i), options, level + 1);
    }
    appendFormattedString(str, "\n");
    indent(str, level);
  }
  appendFormattedString(str, "</div>");
}

} // namespace facebook::yoga
