/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifdef DEBUG

#include <stdarg.h>

#include <yoga/YGEnums.h>

#include <yoga/debug/NodeToString.h>
#include <yoga/numeric/Comparison.h>

namespace facebook::yoga {

static void indent(std::string& base, uint32_t level) {
  for (uint32_t i = 0; i < level; ++i) {
    base.append("  ");
  }
}

static bool areFourValuesEqual(const Style::Edges& four) {
  return yoga::inexactEquals(four[0], four[1]) &&
      yoga::inexactEquals(four[0], four[2]) &&
      yoga::inexactEquals(four[0], four[3]);
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
    const FloatOptional num) {
  if (!num.isUndefined()) {
    appendFormattedString(base, "%s: %g; ", key.c_str(), num.unwrap());
  }
}

static void appendNumberIfNotUndefined(
    std::string& base,
    const std::string key,
    const YGValue number) {
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
    const YGValue number) {
  if (number.unit != YGUnitAuto) {
    appendNumberIfNotUndefined(base, key, number);
  }
}

static void appendNumberIfNotZero(
    std::string& base,
    const std::string& str,
    const YGValue number) {
  if (number.unit == YGUnitAuto) {
    base.append(str + ": auto; ");
  } else if (!yoga::inexactEquals(number.value, 0)) {
    appendNumberIfNotUndefined(base, str, number);
  }
}

static void appendEdges(
    std::string& base,
    const std::string& key,
    const Style::Edges& edges) {
  if (areFourValuesEqual(edges)) {
    auto edgeValue = yoga::Node::computeEdgeValueForColumn(
        edges, YGEdgeLeft, CompactValue::ofZero());
    appendNumberIfNotZero(base, key, edgeValue);
  } else {
    for (int edge = YGEdgeLeft; edge != YGEdgeAll; ++edge) {
      std::string str = key + "-" + YGEdgeToString(static_cast<YGEdge>(edge));
      appendNumberIfNotZero(base, str, edges[static_cast<size_t>(edge)]);
    }
  }
}

static void appendEdgeIfNotUndefined(
    std::string& base,
    const std::string& str,
    const Style::Edges& edges,
    const YGEdge edge) {
  // TODO: this doesn't take RTL / YGEdgeStart / YGEdgeEnd into account
  auto value = (edge == YGEdgeLeft || edge == YGEdgeRight)
      ? yoga::Node::computeEdgeValueForRow(
            edges, edge, edge, CompactValue::ofUndefined())
      : yoga::Node::computeEdgeValueForColumn(
            edges, edge, CompactValue::ofUndefined());
  appendNumberIfNotUndefined(base, str, value);
}

void nodeToString(
    std::string& str,
    yoga::Node* node,
    YGPrintOptions options,
    uint32_t level) {
  indent(str, level);
  appendFormattedString(str, "<div ");

  if (options & YGPrintOptionsLayout) {
    appendFormattedString(str, "layout=\"");
    appendFormattedString(
        str, "width: %g; ", node->getLayout().dimensions[YGDimensionWidth]);
    appendFormattedString(
        str, "height: %g; ", node->getLayout().dimensions[YGDimensionHeight]);
    appendFormattedString(
        str, "top: %g; ", node->getLayout().position[YGEdgeTop]);
    appendFormattedString(
        str, "left: %g;", node->getLayout().position[YGEdgeLeft]);
    appendFormattedString(str, "\" ");
  }

  if (options & YGPrintOptionsStyle) {
    appendFormattedString(str, "style=\"");
    const auto& style = node->getStyle();
    if (style.flexDirection() != yoga::Node{}.getStyle().flexDirection()) {
      appendFormattedString(
          str,
          "flex-direction: %s; ",
          YGFlexDirectionToString(style.flexDirection()));
    }
    if (style.justifyContent() != yoga::Node{}.getStyle().justifyContent()) {
      appendFormattedString(
          str,
          "justify-content: %s; ",
          YGJustifyToString(style.justifyContent()));
    }
    if (style.alignItems() != yoga::Node{}.getStyle().alignItems()) {
      appendFormattedString(
          str, "align-items: %s; ", YGAlignToString(style.alignItems()));
    }
    if (style.alignContent() != yoga::Node{}.getStyle().alignContent()) {
      appendFormattedString(
          str, "align-content: %s; ", YGAlignToString(style.alignContent()));
    }
    if (style.alignSelf() != yoga::Node{}.getStyle().alignSelf()) {
      appendFormattedString(
          str, "align-self: %s; ", YGAlignToString(style.alignSelf()));
    }
    appendFloatOptionalIfDefined(str, "flex-grow", style.flexGrow());
    appendFloatOptionalIfDefined(str, "flex-shrink", style.flexShrink());
    appendNumberIfNotAuto(str, "flex-basis", style.flexBasis());
    appendFloatOptionalIfDefined(str, "flex", style.flex());

    if (style.flexWrap() != yoga::Node{}.getStyle().flexWrap()) {
      appendFormattedString(
          str, "flex-wrap: %s; ", YGWrapToString(style.flexWrap()));
    }

    if (style.overflow() != yoga::Node{}.getStyle().overflow()) {
      appendFormattedString(
          str, "overflow: %s; ", YGOverflowToString(style.overflow()));
    }

    if (style.display() != yoga::Node{}.getStyle().display()) {
      appendFormattedString(
          str, "display: %s; ", YGDisplayToString(style.display()));
    }
    appendEdges(str, "margin", style.margin());
    appendEdges(str, "padding", style.padding());
    appendEdges(str, "border", style.border());

    if (yoga::Node::computeColumnGap(
            style.gap(), CompactValue::ofUndefined()) !=
        yoga::Node::computeColumnGap(
            yoga::Node{}.getStyle().gap(), CompactValue::ofUndefined())) {
      appendNumberIfNotUndefined(
          str, "column-gap", style.gap()[YGGutterColumn]);
    }
    if (yoga::Node::computeRowGap(style.gap(), CompactValue::ofUndefined()) !=
        yoga::Node::computeRowGap(
            yoga::Node{}.getStyle().gap(), CompactValue::ofUndefined())) {
      appendNumberIfNotUndefined(str, "row-gap", style.gap()[YGGutterRow]);
    }

    appendNumberIfNotAuto(str, "width", style.dimensions()[YGDimensionWidth]);
    appendNumberIfNotAuto(str, "height", style.dimensions()[YGDimensionHeight]);
    appendNumberIfNotAuto(
        str, "max-width", style.maxDimensions()[YGDimensionWidth]);
    appendNumberIfNotAuto(
        str, "max-height", style.maxDimensions()[YGDimensionHeight]);
    appendNumberIfNotAuto(
        str, "min-width", style.minDimensions()[YGDimensionWidth]);
    appendNumberIfNotAuto(
        str, "min-height", style.minDimensions()[YGDimensionHeight]);

    if (style.positionType() != yoga::Node{}.getStyle().positionType()) {
      appendFormattedString(
          str, "position: %s; ", YGPositionTypeToString(style.positionType()));
    }

    appendEdgeIfNotUndefined(str, "left", style.position(), YGEdgeLeft);
    appendEdgeIfNotUndefined(str, "right", style.position(), YGEdgeRight);
    appendEdgeIfNotUndefined(str, "top", style.position(), YGEdgeTop);
    appendEdgeIfNotUndefined(str, "bottom", style.position(), YGEdgeBottom);
    appendFormattedString(str, "\" ");

    if (node->hasMeasureFunc()) {
      appendFormattedString(str, "has-custom-measure=\"true\"");
    }
  }
  appendFormattedString(str, ">");

  const uint32_t childCount = static_cast<uint32_t>(node->getChildren().size());
  if (options & YGPrintOptionsChildren && childCount > 0) {
    for (uint32_t i = 0; i < childCount; i++) {
      appendFormattedString(str, "\n");
      nodeToString(str, node->getChild(i), options, level + 1);
    }
    appendFormattedString(str, "\n");
    indent(str, level);
  }
  appendFormattedString(str, "</div>");
}

} // namespace facebook::yoga
#endif
