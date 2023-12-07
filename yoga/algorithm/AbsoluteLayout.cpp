/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <yoga/algorithm/AbsoluteLayout.h>
#include <yoga/algorithm/Align.h>
#include <yoga/algorithm/BoundAxis.h>
#include <yoga/algorithm/CalculateLayout.h>
#include <yoga/algorithm/ResolveValue.h>

namespace facebook::yoga {

static inline void setFlexStartLayoutPosition(
    const yoga::Node* const parent,
    yoga::Node* child,
    const Direction direction,
    const FlexDirection axis,
    const float containingBlockWidth) {
  child->setLayoutPosition(
      child->getFlexStartMargin(axis, direction, containingBlockWidth) +
          parent->getLayout().border(flexStartEdge(axis)) +
          parent->getLayout().padding(flexStartEdge(axis)),
      flexStartEdge(axis));
}

static inline void setFlexEndLayoutPosition(
    const yoga::Node* const parent,
    yoga::Node* child,
    const Direction direction,
    const FlexDirection axis,
    const float containingBlockWidth) {
  child->setLayoutPosition(
      getPositionOfOppositeEdge(
          parent->getLayout().border(flexEndEdge(axis)) +
              parent->getLayout().padding(flexEndEdge(axis)) +
              child->getFlexEndMargin(axis, direction, containingBlockWidth),
          axis,
          parent,
          child),
      flexStartEdge(axis));
}

static inline void setCenterLayoutPosition(
    const yoga::Node* const parent,
    yoga::Node* child,
    const Direction direction,
    const FlexDirection axis,
    const float containingBlockWidth) {
  const float parentContentBoxSize =
      parent->getLayout().measuredDimension(dimension(axis)) -
      parent->getLayout().border(flexStartEdge(axis)) -
      parent->getLayout().border(flexEndEdge(axis)) -
      parent->getLayout().padding(flexStartEdge(axis)) -
      parent->getLayout().padding(flexEndEdge(axis));
  const float childOuterSize =
      child->getLayout().measuredDimension(dimension(axis)) +
      child->getMarginForAxis(axis, containingBlockWidth);
  child->setLayoutPosition(
      (parentContentBoxSize - childOuterSize) / 2.0f +
          parent->getLayout().border(flexStartEdge(axis)) +
          parent->getLayout().padding(flexStartEdge(axis)) +
          child->getFlexStartMargin(axis, direction, containingBlockWidth),
      flexStartEdge(axis));
}

static void justifyAbsoluteChild(
    const yoga::Node* const parent,
    yoga::Node* child,
    const Direction direction,
    const FlexDirection mainAxis,
    const float containingBlockWidth) {
  const Justify parentJustifyContent = parent->getStyle().justifyContent();
  switch (parentJustifyContent) {
    case Justify::FlexStart:
    case Justify::SpaceBetween:
      setFlexStartLayoutPosition(
          parent, child, direction, mainAxis, containingBlockWidth);
      break;
    case Justify::FlexEnd:
      setFlexEndLayoutPosition(
          parent, child, direction, mainAxis, containingBlockWidth);
      break;
    case Justify::Center:
    case Justify::SpaceAround:
    case Justify::SpaceEvenly:
      setCenterLayoutPosition(
          parent, child, direction, mainAxis, containingBlockWidth);
      break;
  }
}

static void alignAbsoluteChild(
    const yoga::Node* const parent,
    yoga::Node* child,
    const Direction direction,
    const FlexDirection crossAxis,
    const float containingBlockWidth) {
  Align itemAlign = resolveChildAlignment(parent, child);
  const Wrap parentWrap = parent->getStyle().flexWrap();
  if (parentWrap == Wrap::WrapReverse) {
    if (itemAlign == Align::FlexEnd) {
      itemAlign = Align::FlexStart;
    } else if (itemAlign != Align::Center) {
      itemAlign = Align::FlexEnd;
    }
  }

  switch (itemAlign) {
    case Align::Auto:
    case Align::FlexStart:
    case Align::Baseline:
    case Align::SpaceAround:
    case Align::SpaceBetween:
    case Align::Stretch:
    case Align::SpaceEvenly:
      setFlexStartLayoutPosition(
          parent, child, direction, crossAxis, containingBlockWidth);
      break;
    case Align::FlexEnd:
      setFlexEndLayoutPosition(
          parent, child, direction, crossAxis, containingBlockWidth);
      break;
    case Align::Center:
      setCenterLayoutPosition(
          parent, child, direction, crossAxis, containingBlockWidth);
      break;
  }
}

// To ensure no breaking changes, we preserve the legacy way of positioning
// absolute children and determine if we should use it using an errata.
static void positionAbsoluteChildLegacy(
    const yoga::Node* const containingNode,
    const yoga::Node* const parent,
    yoga::Node* child,
    const Direction direction,
    const FlexDirection axis,
    const bool isMainAxis,
    const float containingBlockWidth,
    const float containingBlockHeight) {
  const bool isAxisRow = isRow(axis);
  const bool shouldCenter = isMainAxis
      ? parent->getStyle().justifyContent() == Justify::Center
      : resolveChildAlignment(parent, child) == Align::Center;
  const bool shouldFlexEnd = isMainAxis
      ? parent->getStyle().justifyContent() == Justify::FlexEnd
      : ((resolveChildAlignment(parent, child) == Align::FlexEnd) ^
         (parent->getStyle().flexWrap() == Wrap::WrapReverse));

  if (child->isFlexEndPositionDefined(axis, direction) &&
      !child->isFlexStartPositionDefined(axis, direction)) {
    child->setLayoutPosition(
        containingNode->getLayout().measuredDimension(dimension(axis)) -
            child->getLayout().measuredDimension(dimension(axis)) -
            containingNode->getFlexEndBorder(axis, direction) -
            child->getFlexEndMargin(
                axis,
                direction,
                isAxisRow ? containingBlockWidth : containingBlockHeight) -
            child->getFlexEndPosition(
                axis,
                direction,
                isAxisRow ? containingBlockWidth : containingBlockHeight),
        flexStartEdge(axis));
  } else if (
      !child->isFlexStartPositionDefined(axis, direction) && shouldCenter) {
    child->setLayoutPosition(
        (parent->getLayout().measuredDimension(dimension(axis)) -
         child->getLayout().measuredDimension(dimension(axis))) /
            2.0f,
        flexStartEdge(axis));
  } else if (
      !child->isFlexStartPositionDefined(axis, direction) && shouldFlexEnd) {
    child->setLayoutPosition(
        (parent->getLayout().measuredDimension(dimension(axis)) -
         child->getLayout().measuredDimension(dimension(axis))),
        flexStartEdge(axis));
  } else if (
      parent->getConfig()->isExperimentalFeatureEnabled(
          ExperimentalFeature::AbsolutePercentageAgainstPaddingEdge) &&
      child->isFlexStartPositionDefined(axis, direction)) {
    child->setLayoutPosition(
        child->getFlexStartPosition(
            axis,
            direction,
            containingNode->getLayout().measuredDimension(dimension(axis))) +
            containingNode->getFlexStartBorder(axis, direction) +
            child->getFlexStartMargin(
                axis,
                direction,
                isAxisRow ? containingBlockWidth : containingBlockHeight),
        flexStartEdge(axis));
  }
}

/*
 * Absolutely positioned nodes do not participate in flex layout and thus their
 * positions can be determined independently from the rest of their siblings.
 * For each axis there are essentially two cases:
 *
 * 1) The node has insets defined. In this case we can just use these to
 *    determine the position of the node.
 * 2) The node does not have insets defined. In this case we look at the style
 *    of the parent to position the node. Things like justify content and
 *    align content will move absolute children around. If none of these
 *    special properties are defined, the child is positioned at the start
 *    (defined by flex direction) of the leading flex line.
 *
 * This function does that positioning for the given axis. The spec has more
 * information on this topic: https://www.w3.org/TR/css-flexbox-1/#abspos-items
 */
static void positionAbsoluteChildImpl(
    const yoga::Node* const containingNode,
    const yoga::Node* const parent,
    yoga::Node* child,
    const Direction direction,
    const FlexDirection axis,
    const bool isMainAxis,
    const float containingBlockWidth,
    const float containingBlockHeight) {
  const bool isAxisRow = isRow(axis);
  const float containingBlockSize =
      isAxisRow ? containingBlockWidth : containingBlockHeight;

  // The inline-start position takes priority over the end position in the case
  // that they are both set and the node has a fixed width. Thus we only have 2
  // cases here: if inline-start is defined and if inline-end is defined.
  //
  // Despite checking inline-start to honor prioritization of insets, we write
  // to the flex-start edge because this algorithm works by positioning on the
  // flex-start edge and then filling in the flex-end direction at the end if
  // necessary.
  if (child->isInlineStartPositionDefined(axis, direction)) {
    const float positionRelativeToInlineStart =
        child->getInlineStartPosition(axis, direction, containingBlockSize) +
        containingNode->getInlineStartBorder(axis, direction) +
        child->getInlineStartMargin(axis, direction, containingBlockSize);
    const float positionRelativeToFlexStart =
        inlineStartEdge(axis, direction) != flexStartEdge(axis)
        ? getPositionOfOppositeEdge(
              positionRelativeToInlineStart, axis, containingNode, child)
        : positionRelativeToInlineStart;

    child->setLayoutPosition(positionRelativeToFlexStart, flexStartEdge(axis));
  } else if (child->isInlineEndPositionDefined(axis, direction)) {
    const float positionRelativeToInlineStart =
        containingNode->getLayout().measuredDimension(dimension(axis)) -
        child->getLayout().measuredDimension(dimension(axis)) -
        containingNode->getInlineEndBorder(axis, direction) -
        child->getInlineEndMargin(axis, direction, containingBlockSize) -
        child->getInlineEndPosition(axis, direction, containingBlockSize);
    const float positionRelativeToFlexStart =
        inlineStartEdge(axis, direction) != flexStartEdge(axis)
        ? getPositionOfOppositeEdge(
              positionRelativeToInlineStart, axis, containingNode, child)
        : positionRelativeToInlineStart;

    child->setLayoutPosition(positionRelativeToFlexStart, flexStartEdge(axis));
  } else {
    isMainAxis ? justifyAbsoluteChild(
                     parent, child, direction, axis, containingBlockWidth)
               : alignAbsoluteChild(
                     parent, child, direction, axis, containingBlockWidth);
  }
}

static void positionAbsoluteChild(
    const yoga::Node* const containingNode,
    const yoga::Node* const parent,
    yoga::Node* child,
    const Direction direction,
    const FlexDirection axis,
    const bool isMainAxis,
    const float containingBlockWidth,
    const float containingBlockHeight) {
  child->hasErrata(Errata::AbsolutePositioning) ? positionAbsoluteChildLegacy(
                                                      containingNode,
                                                      parent,
                                                      child,
                                                      direction,
                                                      axis,
                                                      isMainAxis,
                                                      containingBlockWidth,
                                                      containingBlockHeight)
                                                : positionAbsoluteChildImpl(
                                                      containingNode,
                                                      parent,
                                                      child,
                                                      direction,
                                                      axis,
                                                      isMainAxis,
                                                      containingBlockWidth,
                                                      containingBlockHeight);
}

void layoutAbsoluteChild(
    const yoga::Node* const containingNode,
    const yoga::Node* const node,
    yoga::Node* const child,
    const float containingBlockWidth,
    const float containingBlockHeight,
    const SizingMode widthMode,
    const Direction direction,
    LayoutData& layoutMarkerData,
    const uint32_t depth,
    const uint32_t generationCount) {
  const FlexDirection mainAxis =
      resolveDirection(node->getStyle().flexDirection(), direction);
  const FlexDirection crossAxis = resolveCrossDirection(mainAxis, direction);
  const bool isMainAxisRow = isRow(mainAxis);

  float childWidth = YGUndefined;
  float childHeight = YGUndefined;
  SizingMode childWidthSizingMode = SizingMode::MaxContent;
  SizingMode childHeightSizingMode = SizingMode::MaxContent;

  auto marginRow =
      child->getMarginForAxis(FlexDirection::Row, containingBlockWidth);
  auto marginColumn =
      child->getMarginForAxis(FlexDirection::Column, containingBlockWidth);

  if (child->styleDefinesDimension(FlexDirection::Row, containingBlockWidth)) {
    childWidth =
        yoga::resolveValue(
            child->getResolvedDimension(Dimension::Width), containingBlockWidth)
            .unwrap() +
        marginRow;
  } else {
    // If the child doesn't have a specified width, compute the width based on
    // the left/right offsets if they're defined.
    if (child->isFlexStartPositionDefined(FlexDirection::Row, direction) &&
        child->isFlexEndPositionDefined(FlexDirection::Row, direction)) {
      childWidth =
          containingNode->getLayout().measuredDimension(Dimension::Width) -
          (containingNode->getFlexStartBorder(FlexDirection::Row, direction) +
           containingNode->getFlexEndBorder(FlexDirection::Row, direction)) -
          (child->getFlexStartPosition(
               FlexDirection::Row, direction, containingBlockWidth) +
           child->getFlexEndPosition(
               FlexDirection::Row, direction, containingBlockWidth));
      childWidth = boundAxis(
          child,
          FlexDirection::Row,
          childWidth,
          containingBlockWidth,
          containingBlockWidth);
    }
  }

  if (child->styleDefinesDimension(
          FlexDirection::Column, containingBlockHeight)) {
    childHeight = yoga::resolveValue(
                      child->getResolvedDimension(Dimension::Height),
                      containingBlockHeight)
                      .unwrap() +
        marginColumn;
  } else {
    // If the child doesn't have a specified height, compute the height based
    // on the top/bottom offsets if they're defined.
    if (child->isFlexStartPositionDefined(FlexDirection::Column, direction) &&
        child->isFlexEndPositionDefined(FlexDirection::Column, direction)) {
      childHeight =
          containingNode->getLayout().measuredDimension(Dimension::Height) -
          (containingNode->getFlexStartBorder(
               FlexDirection::Column, direction) +
           containingNode->getFlexEndBorder(FlexDirection::Column, direction)) -
          (child->getFlexStartPosition(
               FlexDirection::Column, direction, containingBlockHeight) +
           child->getFlexEndPosition(
               FlexDirection::Column, direction, containingBlockHeight));
      childHeight = boundAxis(
          child,
          FlexDirection::Column,
          childHeight,
          containingBlockHeight,
          containingBlockWidth);
    }
  }

  // Exactly one dimension needs to be defined for us to be able to do aspect
  // ratio calculation. One dimension being the anchor and the other being
  // flexible.
  const auto& childStyle = child->getStyle();
  if (yoga::isUndefined(childWidth) ^ yoga::isUndefined(childHeight)) {
    if (childStyle.aspectRatio().isDefined()) {
      if (yoga::isUndefined(childWidth)) {
        childWidth = marginRow +
            (childHeight - marginColumn) * childStyle.aspectRatio().unwrap();
      } else if (yoga::isUndefined(childHeight)) {
        childHeight = marginColumn +
            (childWidth - marginRow) / childStyle.aspectRatio().unwrap();
      }
    }
  }

  // If we're still missing one or the other dimension, measure the content.
  if (yoga::isUndefined(childWidth) || yoga::isUndefined(childHeight)) {
    childWidthSizingMode = yoga::isUndefined(childWidth)
        ? SizingMode::MaxContent
        : SizingMode::StretchFit;
    childHeightSizingMode = yoga::isUndefined(childHeight)
        ? SizingMode::MaxContent
        : SizingMode::StretchFit;

    // If the size of the owner is defined then try to constrain the absolute
    // child to that size as well. This allows text within the absolute child
    // to wrap to the size of its owner. This is the same behavior as many
    // browsers implement.
    if (!isMainAxisRow && yoga::isUndefined(childWidth) &&
        widthMode != SizingMode::MaxContent &&
        yoga::isDefined(containingBlockWidth) && containingBlockWidth > 0) {
      childWidth = containingBlockWidth;
      childWidthSizingMode = SizingMode::FitContent;
    }

    calculateLayoutInternal(
        child,
        childWidth,
        childHeight,
        direction,
        childWidthSizingMode,
        childHeightSizingMode,
        containingBlockWidth,
        containingBlockHeight,
        false,
        LayoutPassReason::kAbsMeasureChild,
        layoutMarkerData,
        depth,
        generationCount);
    childWidth = child->getLayout().measuredDimension(Dimension::Width) +
        child->getMarginForAxis(FlexDirection::Row, containingBlockWidth);
    childHeight = child->getLayout().measuredDimension(Dimension::Height) +
        child->getMarginForAxis(FlexDirection::Column, containingBlockWidth);
  }

  calculateLayoutInternal(
      child,
      childWidth,
      childHeight,
      direction,
      SizingMode::StretchFit,
      SizingMode::StretchFit,
      containingBlockWidth,
      containingBlockHeight,
      true,
      LayoutPassReason::kAbsLayout,
      layoutMarkerData,
      depth,
      generationCount);

  positionAbsoluteChild(
      containingNode,
      node,
      child,
      direction,
      mainAxis,
      true /*isMainAxis*/,
      containingBlockWidth,
      containingBlockHeight);
  positionAbsoluteChild(
      containingNode,
      node,
      child,
      direction,
      crossAxis,
      false /*isMainAxis*/,
      containingBlockWidth,
      containingBlockHeight);
}

void layoutAbsoluteDescendants(
    yoga::Node* containingNode,
    yoga::Node* currentNode,
    SizingMode widthSizingMode,
    Direction currentNodeDirection,
    LayoutData& layoutMarkerData,
    uint32_t currentDepth,
    uint32_t generationCount,
    float currentNodeMainOffsetFromContainingBlock,
    float currentNodeCrossOffsetFromContainingBlock) {
  const FlexDirection mainAxis = resolveDirection(
      currentNode->getStyle().flexDirection(), currentNodeDirection);
  const FlexDirection crossAxis =
      resolveCrossDirection(mainAxis, currentNodeDirection);
  for (auto child : currentNode->getChildren()) {
    if (child->getStyle().display() == Display::None) {
      continue;
    } else if (child->getStyle().positionType() == PositionType::Absolute) {
      layoutAbsoluteChild(
          containingNode,
          currentNode,
          child,
          containingNode->getLayout().measuredDimension(Dimension::Width) -
              containingNode->getBorderForAxis(FlexDirection::Row),
          containingNode->getLayout().measuredDimension(Dimension::Height) -
              containingNode->getBorderForAxis(FlexDirection::Column),
          widthSizingMode,
          currentNodeDirection,
          layoutMarkerData,
          currentDepth,
          generationCount);

      const bool isMainAxisRow = isRow(mainAxis);
      const bool mainInsetsDefined = isMainAxisRow
          ? child->getStyle().horizontalInsetsDefined()
          : child->getStyle().verticalInsetsDefined();
      const bool crossInsetsDefined = isMainAxisRow
          ? child->getStyle().verticalInsetsDefined()
          : child->getStyle().horizontalInsetsDefined();

      const float childMainOffsetFromParent = mainInsetsDefined
          ? (child->getLayout().position(flexStartEdge(mainAxis)) -
             currentNodeMainOffsetFromContainingBlock)
          : child->getLayout().position(flexStartEdge(mainAxis));
      const float childCrossOffsetFromParent = crossInsetsDefined
          ? (child->getLayout().position(flexStartEdge(crossAxis)) -
             currentNodeCrossOffsetFromContainingBlock)
          : child->getLayout().position(flexStartEdge(crossAxis));

      child->setLayoutPosition(
          childMainOffsetFromParent, flexStartEdge(mainAxis));
      child->setLayoutPosition(
          childCrossOffsetFromParent, flexStartEdge(crossAxis));

      if (needsTrailingPosition(mainAxis)) {
        setChildTrailingPosition(currentNode, child, mainAxis);
      }
      if (needsTrailingPosition(crossAxis)) {
        setChildTrailingPosition(currentNode, child, crossAxis);
      }
    } else if (child->getStyle().positionType() == PositionType::Static) {
      const Direction childDirection =
          child->resolveDirection(currentNodeDirection);
      const float childMainOffsetFromContainingBlock =
          currentNodeMainOffsetFromContainingBlock +
          child->getLayout().position(flexStartEdge(mainAxis));
      const float childCrossOffsetFromContainingBlock =
          currentNodeCrossOffsetFromContainingBlock +
          child->getLayout().position(flexStartEdge(crossAxis));

      layoutAbsoluteDescendants(
          containingNode,
          child,
          widthSizingMode,
          childDirection,
          layoutMarkerData,
          currentDepth + 1,
          generationCount,
          childMainOffsetFromContainingBlock,
          childCrossOffsetFromContainingBlock);
    }
  }
}
} // namespace facebook::yoga
