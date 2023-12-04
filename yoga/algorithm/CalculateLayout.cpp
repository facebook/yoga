/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <algorithm>
#include <atomic>
#include <cfloat>
#include <cmath>
#include <cstring>

#include <yoga/Yoga.h>

#include <yoga/algorithm/AbsoluteLayout.h>
#include <yoga/algorithm/Align.h>
#include <yoga/algorithm/Baseline.h>
#include <yoga/algorithm/BoundAxis.h>
#include <yoga/algorithm/Cache.h>
#include <yoga/algorithm/CalculateLayout.h>
#include <yoga/algorithm/FlexDirection.h>
#include <yoga/algorithm/FlexLine.h>
#include <yoga/algorithm/PixelGrid.h>
#include <yoga/algorithm/ResolveValue.h>
#include <yoga/algorithm/SizingMode.h>
#include <yoga/debug/AssertFatal.h>
#include <yoga/debug/Log.h>
#include <yoga/debug/NodeToString.h>
#include <yoga/event/event.h>
#include <yoga/node/Node.h>
#include <yoga/numeric/Comparison.h>
#include <yoga/numeric/FloatOptional.h>

namespace facebook::yoga {

std::atomic<uint32_t> gCurrentGenerationCount(0);

bool calculateLayoutInternal(
    yoga::Node* const node,
    const float availableWidth,
    const float availableHeight,
    const Direction ownerDirection,
    const SizingMode widthSizingMode,
    const SizingMode heightSizingMode,
    const float ownerWidth,
    const float ownerHeight,
    const bool performLayout,
    const LayoutPassReason reason,
    LayoutData& layoutMarkerData,
    const uint32_t depth,
    const uint32_t generationCount);

static void constrainMaxSizeForMode(
    const yoga::Node* const node,
    const enum FlexDirection axis,
    const float ownerAxisSize,
    const float ownerWidth,
    SizingMode* mode,
    float* size) {
  const FloatOptional maxSize =
      yoga::resolveValue(
          node->getStyle().maxDimension(dimension(axis)), ownerAxisSize) +
      FloatOptional(node->getMarginForAxis(axis, ownerWidth));
  switch (*mode) {
    case SizingMode::StretchFit:
    case SizingMode::FitContent:
      *size = (maxSize.isUndefined() || *size < maxSize.unwrap())
          ? *size
          : maxSize.unwrap();
      break;
    case SizingMode::MaxContent:
      if (maxSize.isDefined()) {
        *mode = SizingMode::FitContent;
        *size = maxSize.unwrap();
      }
      break;
  }
}

static void computeFlexBasisForChild(
    const yoga::Node* const node,
    yoga::Node* const child,
    const float width,
    const SizingMode widthMode,
    const float height,
    const float ownerWidth,
    const float ownerHeight,
    const SizingMode heightMode,
    const Direction direction,
    LayoutData& layoutMarkerData,
    const uint32_t depth,
    const uint32_t generationCount) {
  const FlexDirection mainAxis =
      resolveDirection(node->getStyle().flexDirection(), direction);
  const bool isMainAxisRow = isRow(mainAxis);
  const float mainAxisSize = isMainAxisRow ? width : height;
  const float mainAxisownerSize = isMainAxisRow ? ownerWidth : ownerHeight;

  float childWidth;
  float childHeight;
  SizingMode childWidthSizingMode;
  SizingMode childHeightSizingMode;

  const FloatOptional resolvedFlexBasis =
      yoga::resolveValue(child->resolveFlexBasisPtr(), mainAxisownerSize);
  const bool isRowStyleDimDefined =
      child->styleDefinesDimension(FlexDirection::Row, ownerWidth);
  const bool isColumnStyleDimDefined =
      child->styleDefinesDimension(FlexDirection::Column, ownerHeight);

  if (resolvedFlexBasis.isDefined() && yoga::isDefined(mainAxisSize)) {
    if (child->getLayout().computedFlexBasis.isUndefined() ||
        (child->getConfig()->isExperimentalFeatureEnabled(
             ExperimentalFeature::WebFlexBasis) &&
         child->getLayout().computedFlexBasisGeneration != generationCount)) {
      const FloatOptional paddingAndBorder =
          FloatOptional(paddingAndBorderForAxis(child, mainAxis, ownerWidth));
      child->setLayoutComputedFlexBasis(
          yoga::maxOrDefined(resolvedFlexBasis, paddingAndBorder));
    }
  } else if (isMainAxisRow && isRowStyleDimDefined) {
    // The width is definite, so use that as the flex basis.
    const FloatOptional paddingAndBorder = FloatOptional(
        paddingAndBorderForAxis(child, FlexDirection::Row, ownerWidth));

    child->setLayoutComputedFlexBasis(yoga::maxOrDefined(
        yoga::resolveValue(
            child->getResolvedDimension(Dimension::Width), ownerWidth),
        paddingAndBorder));
  } else if (!isMainAxisRow && isColumnStyleDimDefined) {
    // The height is definite, so use that as the flex basis.
    const FloatOptional paddingAndBorder = FloatOptional(
        paddingAndBorderForAxis(child, FlexDirection::Column, ownerWidth));
    child->setLayoutComputedFlexBasis(yoga::maxOrDefined(
        yoga::resolveValue(
            child->getResolvedDimension(Dimension::Height), ownerHeight),
        paddingAndBorder));
  } else {
    // Compute the flex basis and hypothetical main size (i.e. the clamped flex
    // basis).
    childWidth = YGUndefined;
    childHeight = YGUndefined;
    childWidthSizingMode = SizingMode::MaxContent;
    childHeightSizingMode = SizingMode::MaxContent;

    auto marginRow = child->getMarginForAxis(FlexDirection::Row, ownerWidth);
    auto marginColumn =
        child->getMarginForAxis(FlexDirection::Column, ownerWidth);

    if (isRowStyleDimDefined) {
      childWidth =
          yoga::resolveValue(
              child->getResolvedDimension(Dimension::Width), ownerWidth)
              .unwrap() +
          marginRow;
      childWidthSizingMode = SizingMode::StretchFit;
    }
    if (isColumnStyleDimDefined) {
      childHeight =
          yoga::resolveValue(
              child->getResolvedDimension(Dimension::Height), ownerHeight)
              .unwrap() +
          marginColumn;
      childHeightSizingMode = SizingMode::StretchFit;
    }

    // The W3C spec doesn't say anything about the 'overflow' property, but all
    // major browsers appear to implement the following logic.
    if ((!isMainAxisRow && node->getStyle().overflow() == Overflow::Scroll) ||
        node->getStyle().overflow() != Overflow::Scroll) {
      if (yoga::isUndefined(childWidth) && yoga::isDefined(width)) {
        childWidth = width;
        childWidthSizingMode = SizingMode::FitContent;
      }
    }

    if ((isMainAxisRow && node->getStyle().overflow() == Overflow::Scroll) ||
        node->getStyle().overflow() != Overflow::Scroll) {
      if (yoga::isUndefined(childHeight) && yoga::isDefined(height)) {
        childHeight = height;
        childHeightSizingMode = SizingMode::FitContent;
      }
    }

    const auto& childStyle = child->getStyle();
    if (childStyle.aspectRatio().isDefined()) {
      if (!isMainAxisRow && childWidthSizingMode == SizingMode::StretchFit) {
        childHeight = marginColumn +
            (childWidth - marginRow) / childStyle.aspectRatio().unwrap();
        childHeightSizingMode = SizingMode::StretchFit;
      } else if (
          isMainAxisRow && childHeightSizingMode == SizingMode::StretchFit) {
        childWidth = marginRow +
            (childHeight - marginColumn) * childStyle.aspectRatio().unwrap();
        childWidthSizingMode = SizingMode::StretchFit;
      }
    }

    // If child has no defined size in the cross axis and is set to stretch, set
    // the cross axis to be measured exactly with the available inner width

    const bool hasExactWidth =
        yoga::isDefined(width) && widthMode == SizingMode::StretchFit;
    const bool childWidthStretch =
        resolveChildAlignment(node, child) == Align::Stretch &&
        childWidthSizingMode != SizingMode::StretchFit;
    if (!isMainAxisRow && !isRowStyleDimDefined && hasExactWidth &&
        childWidthStretch) {
      childWidth = width;
      childWidthSizingMode = SizingMode::StretchFit;
      if (childStyle.aspectRatio().isDefined()) {
        childHeight =
            (childWidth - marginRow) / childStyle.aspectRatio().unwrap();
        childHeightSizingMode = SizingMode::StretchFit;
      }
    }

    const bool hasExactHeight =
        yoga::isDefined(height) && heightMode == SizingMode::StretchFit;
    const bool childHeightStretch =
        resolveChildAlignment(node, child) == Align::Stretch &&
        childHeightSizingMode != SizingMode::StretchFit;
    if (isMainAxisRow && !isColumnStyleDimDefined && hasExactHeight &&
        childHeightStretch) {
      childHeight = height;
      childHeightSizingMode = SizingMode::StretchFit;

      if (childStyle.aspectRatio().isDefined()) {
        childWidth =
            (childHeight - marginColumn) * childStyle.aspectRatio().unwrap();
        childWidthSizingMode = SizingMode::StretchFit;
      }
    }

    constrainMaxSizeForMode(
        child,
        FlexDirection::Row,
        ownerWidth,
        ownerWidth,
        &childWidthSizingMode,
        &childWidth);
    constrainMaxSizeForMode(
        child,
        FlexDirection::Column,
        ownerHeight,
        ownerWidth,
        &childHeightSizingMode,
        &childHeight);

    // Measure the child
    calculateLayoutInternal(
        child,
        childWidth,
        childHeight,
        direction,
        childWidthSizingMode,
        childHeightSizingMode,
        ownerWidth,
        ownerHeight,
        false,
        LayoutPassReason::kMeasureChild,
        layoutMarkerData,
        depth,
        generationCount);

    child->setLayoutComputedFlexBasis(FloatOptional(yoga::maxOrDefined(
        child->getLayout().measuredDimension(dimension(mainAxis)),
        paddingAndBorderForAxis(child, mainAxis, ownerWidth))));
  }
  child->setLayoutComputedFlexBasisGeneration(generationCount);
}

static void measureNodeWithMeasureFunc(
    yoga::Node* const node,
    float availableWidth,
    float availableHeight,
    const SizingMode widthSizingMode,
    const SizingMode heightSizingMode,
    const float ownerWidth,
    const float ownerHeight,
    LayoutData& layoutMarkerData,
    const LayoutPassReason reason) {
  yoga::assertFatalWithNode(
      node,
      node->hasMeasureFunc(),
      "Expected node to have custom measure function");

  if (widthSizingMode == SizingMode::MaxContent) {
    availableWidth = YGUndefined;
  }
  if (heightSizingMode == SizingMode::MaxContent) {
    availableHeight = YGUndefined;
  }

  const auto& layout = node->getLayout();
  const float paddingAndBorderAxisRow = layout.padding(Edge::Left) +
      layout.padding(Edge::Right) + layout.border(Edge::Left) +
      layout.border(Edge::Right);
  const float paddingAndBorderAxisColumn = layout.padding(Edge::Top) +
      layout.padding(Edge::Bottom) + layout.border(Edge::Top) +
      layout.border(Edge::Bottom);

  // We want to make sure we don't call measure with negative size
  const float innerWidth = yoga::isUndefined(availableWidth)
      ? availableWidth
      : yoga::maxOrDefined(0.0f, availableWidth - paddingAndBorderAxisRow);
  const float innerHeight = yoga::isUndefined(availableHeight)
      ? availableHeight
      : yoga::maxOrDefined(0.0f, availableHeight - paddingAndBorderAxisColumn);

  if (widthSizingMode == SizingMode::StretchFit &&
      heightSizingMode == SizingMode::StretchFit) {
    // Don't bother sizing the text if both dimensions are already defined.
    node->setLayoutMeasuredDimension(
        boundAxis(
            node, FlexDirection::Row, availableWidth, ownerWidth, ownerWidth),
        Dimension::Width);
    node->setLayoutMeasuredDimension(
        boundAxis(
            node,
            FlexDirection::Column,
            availableHeight,
            ownerHeight,
            ownerWidth),
        Dimension::Height);
  } else {
    Event::publish<Event::MeasureCallbackStart>(node);

    // Measure the text under the current constraints.
    const YGSize measuredSize = node->measure(
        innerWidth,
        measureMode(widthSizingMode),
        innerHeight,
        measureMode(heightSizingMode));

    layoutMarkerData.measureCallbacks += 1;
    layoutMarkerData.measureCallbackReasonsCount[static_cast<size_t>(reason)] +=
        1;

    Event::publish<Event::MeasureCallbackEnd>(
        node,
        {innerWidth,
         unscopedEnum(measureMode(widthSizingMode)),
         innerHeight,
         unscopedEnum(measureMode(heightSizingMode)),
         measuredSize.width,
         measuredSize.height,
         reason});

    node->setLayoutMeasuredDimension(
        boundAxis(
            node,
            FlexDirection::Row,
            (widthSizingMode == SizingMode::MaxContent ||
             widthSizingMode == SizingMode::FitContent)
                ? measuredSize.width + paddingAndBorderAxisRow
                : availableWidth,
            ownerWidth,
            ownerWidth),
        Dimension::Width);

    node->setLayoutMeasuredDimension(
        boundAxis(
            node,
            FlexDirection::Column,
            (heightSizingMode == SizingMode::MaxContent ||
             heightSizingMode == SizingMode::FitContent)
                ? measuredSize.height + paddingAndBorderAxisColumn
                : availableHeight,
            ownerHeight,
            ownerWidth),
        Dimension::Height);
  }
}

// For nodes with no children, use the available values if they were provided,
// or the minimum size as indicated by the padding and border sizes.
static void measureNodeWithoutChildren(
    yoga::Node* const node,
    const float availableWidth,
    const float availableHeight,
    const SizingMode widthSizingMode,
    const SizingMode heightSizingMode,
    const float ownerWidth,
    const float ownerHeight) {
  const auto& layout = node->getLayout();

  float width = availableWidth;
  if (widthSizingMode == SizingMode::MaxContent ||
      widthSizingMode == SizingMode::FitContent) {
    width = layout.padding(Edge::Left) + layout.padding(Edge::Right) +
        layout.border(Edge::Left) + layout.border(Edge::Right);
  }
  node->setLayoutMeasuredDimension(
      boundAxis(node, FlexDirection::Row, width, ownerWidth, ownerWidth),
      Dimension::Width);

  float height = availableHeight;
  if (heightSizingMode == SizingMode::MaxContent ||
      heightSizingMode == SizingMode::FitContent) {
    height = layout.padding(Edge::Top) + layout.padding(Edge::Bottom) +
        layout.border(Edge::Top) + layout.border(Edge::Bottom);
  }
  node->setLayoutMeasuredDimension(
      boundAxis(node, FlexDirection::Column, height, ownerHeight, ownerWidth),
      Dimension::Height);
}

static bool measureNodeWithFixedSize(
    yoga::Node* const node,
    const float availableWidth,
    const float availableHeight,
    const SizingMode widthSizingMode,
    const SizingMode heightSizingMode,
    const float ownerWidth,
    const float ownerHeight) {
  if ((yoga::isDefined(availableWidth) &&
       widthSizingMode == SizingMode::FitContent && availableWidth <= 0.0f) ||
      (yoga::isDefined(availableHeight) &&
       heightSizingMode == SizingMode::FitContent && availableHeight <= 0.0f) ||
      (widthSizingMode == SizingMode::StretchFit &&
       heightSizingMode == SizingMode::StretchFit)) {
    node->setLayoutMeasuredDimension(
        boundAxis(
            node,
            FlexDirection::Row,
            yoga::isUndefined(availableWidth) ||
                    (widthSizingMode == SizingMode::FitContent &&
                     availableWidth < 0.0f)
                ? 0.0f
                : availableWidth,
            ownerWidth,
            ownerWidth),
        Dimension::Width);

    node->setLayoutMeasuredDimension(
        boundAxis(
            node,
            FlexDirection::Column,
            yoga::isUndefined(availableHeight) ||
                    (heightSizingMode == SizingMode::FitContent &&
                     availableHeight < 0.0f)
                ? 0.0f
                : availableHeight,
            ownerHeight,
            ownerWidth),
        Dimension::Height);
    return true;
  }

  return false;
}

static void zeroOutLayoutRecursively(yoga::Node* const node) {
  node->getLayout() = {};
  node->setLayoutDimension(0, Dimension::Width);
  node->setLayoutDimension(0, Dimension::Height);
  node->setHasNewLayout(true);

  node->cloneChildrenIfNeeded();
  for (const auto child : node->getChildren()) {
    zeroOutLayoutRecursively(child);
  }
}

static float calculateAvailableInnerDimension(
    const yoga::Node* const node,
    const Dimension dimension,
    const float availableDim,
    const float paddingAndBorder,
    const float ownerDim) {
  float availableInnerDim = availableDim - paddingAndBorder;
  // Max dimension overrides predefined dimension value; Min dimension in turn
  // overrides both of the above
  if (yoga::isDefined(availableInnerDim)) {
    // We want to make sure our available height does not violate min and max
    // constraints
    const FloatOptional minDimensionOptional =
        yoga::resolveValue(node->getStyle().minDimension(dimension), ownerDim);
    const float minInnerDim = minDimensionOptional.isUndefined()
        ? 0.0f
        : minDimensionOptional.unwrap() - paddingAndBorder;

    const FloatOptional maxDimensionOptional =
        yoga::resolveValue(node->getStyle().maxDimension(dimension), ownerDim);

    const float maxInnerDim = maxDimensionOptional.isUndefined()
        ? FLT_MAX
        : maxDimensionOptional.unwrap() - paddingAndBorder;
    availableInnerDim = yoga::maxOrDefined(
        yoga::minOrDefined(availableInnerDim, maxInnerDim), minInnerDim);
  }

  return availableInnerDim;
}

static float computeFlexBasisForChildren(
    yoga::Node* const node,
    const float availableInnerWidth,
    const float availableInnerHeight,
    SizingMode widthSizingMode,
    SizingMode heightSizingMode,
    Direction direction,
    FlexDirection mainAxis,
    bool performLayout,
    LayoutData& layoutMarkerData,
    const uint32_t depth,
    const uint32_t generationCount) {
  float totalOuterFlexBasis = 0.0f;
  YGNodeRef singleFlexChild = nullptr;
  const auto& children = node->getChildren();
  SizingMode sizingModeMainDim =
      isRow(mainAxis) ? widthSizingMode : heightSizingMode;
  // If there is only one child with flexGrow + flexShrink it means we can set
  // the computedFlexBasis to 0 instead of measuring and shrinking / flexing the
  // child to exactly match the remaining space
  if (sizingModeMainDim == SizingMode::StretchFit) {
    for (auto child : children) {
      if (child->isNodeFlexible()) {
        if (singleFlexChild != nullptr ||
            yoga::inexactEquals(child->resolveFlexGrow(), 0.0f) ||
            yoga::inexactEquals(child->resolveFlexShrink(), 0.0f)) {
          // There is already a flexible child, or this flexible child doesn't
          // have flexGrow and flexShrink, abort
          singleFlexChild = nullptr;
          break;
        } else {
          singleFlexChild = child;
        }
      }
    }
  }

  for (auto child : children) {
    child->resolveDimension();
    if (child->getStyle().display() == Display::None) {
      zeroOutLayoutRecursively(child);
      child->setHasNewLayout(true);
      child->setDirty(false);
      continue;
    }
    if (performLayout) {
      // Set the initial position (relative to the owner).
      const Direction childDirection = child->resolveDirection(direction);
      const float mainDim =
          isRow(mainAxis) ? availableInnerWidth : availableInnerHeight;
      const float crossDim =
          isRow(mainAxis) ? availableInnerHeight : availableInnerWidth;
      child->setPosition(
          childDirection, mainDim, crossDim, availableInnerWidth);
    }

    if (child->getStyle().positionType() == PositionType::Absolute) {
      continue;
    }
    if (child == singleFlexChild) {
      child->setLayoutComputedFlexBasisGeneration(generationCount);
      child->setLayoutComputedFlexBasis(FloatOptional(0));
    } else {
      computeFlexBasisForChild(
          node,
          child,
          availableInnerWidth,
          widthSizingMode,
          availableInnerHeight,
          availableInnerWidth,
          availableInnerHeight,
          heightSizingMode,
          direction,
          layoutMarkerData,
          depth,
          generationCount);
    }

    totalOuterFlexBasis +=
        (child->getLayout().computedFlexBasis.unwrap() +
         child->getMarginForAxis(mainAxis, availableInnerWidth));
  }

  return totalOuterFlexBasis;
}

// It distributes the free space to the flexible items and ensures that the size
// of the flex items abide the min and max constraints. At the end of this
// function the child nodes would have proper size. Prior using this function
// please ensure that distributeFreeSpaceFirstPass is called.
static float distributeFreeSpaceSecondPass(
    FlexLine& flexLine,
    yoga::Node* const node,
    const FlexDirection mainAxis,
    const FlexDirection crossAxis,
    const float mainAxisownerSize,
    const float availableInnerMainDim,
    const float availableInnerCrossDim,
    const float availableInnerWidth,
    const float availableInnerHeight,
    const bool mainAxisOverflows,
    const SizingMode sizingModeCrossDim,
    const bool performLayout,
    LayoutData& layoutMarkerData,
    const uint32_t depth,
    const uint32_t generationCount) {
  float childFlexBasis = 0;
  float flexShrinkScaledFactor = 0;
  float flexGrowFactor = 0;
  float deltaFreeSpace = 0;
  const bool isMainAxisRow = isRow(mainAxis);
  const bool isNodeFlexWrap = node->getStyle().flexWrap() != Wrap::NoWrap;

  for (auto currentLineChild : flexLine.itemsInFlow) {
    childFlexBasis = boundAxisWithinMinAndMax(
                         currentLineChild,
                         mainAxis,
                         currentLineChild->getLayout().computedFlexBasis,
                         mainAxisownerSize)
                         .unwrap();
    float updatedMainSize = childFlexBasis;

    if (yoga::isDefined(flexLine.layout.remainingFreeSpace) &&
        flexLine.layout.remainingFreeSpace < 0) {
      flexShrinkScaledFactor =
          -currentLineChild->resolveFlexShrink() * childFlexBasis;
      // Is this child able to shrink?
      if (flexShrinkScaledFactor != 0) {
        float childSize;

        if (yoga::isDefined(flexLine.layout.totalFlexShrinkScaledFactors) &&
            flexLine.layout.totalFlexShrinkScaledFactors == 0) {
          childSize = childFlexBasis + flexShrinkScaledFactor;
        } else {
          childSize = childFlexBasis +
              (flexLine.layout.remainingFreeSpace /
               flexLine.layout.totalFlexShrinkScaledFactors) *
                  flexShrinkScaledFactor;
        }

        updatedMainSize = boundAxis(
            currentLineChild,
            mainAxis,
            childSize,
            availableInnerMainDim,
            availableInnerWidth);
      }
    } else if (
        yoga::isDefined(flexLine.layout.remainingFreeSpace) &&
        flexLine.layout.remainingFreeSpace > 0) {
      flexGrowFactor = currentLineChild->resolveFlexGrow();

      // Is this child able to grow?
      if (!std::isnan(flexGrowFactor) && flexGrowFactor != 0) {
        updatedMainSize = boundAxis(
            currentLineChild,
            mainAxis,
            childFlexBasis +
                flexLine.layout.remainingFreeSpace /
                    flexLine.layout.totalFlexGrowFactors * flexGrowFactor,
            availableInnerMainDim,
            availableInnerWidth);
      }
    }

    deltaFreeSpace += updatedMainSize - childFlexBasis;

    const float marginMain =
        currentLineChild->getMarginForAxis(mainAxis, availableInnerWidth);
    const float marginCross =
        currentLineChild->getMarginForAxis(crossAxis, availableInnerWidth);

    float childCrossSize;
    float childMainSize = updatedMainSize + marginMain;
    SizingMode childCrossSizingMode;
    SizingMode childMainSizingMode = SizingMode::StretchFit;

    const auto& childStyle = currentLineChild->getStyle();
    if (childStyle.aspectRatio().isDefined()) {
      childCrossSize = isMainAxisRow
          ? (childMainSize - marginMain) / childStyle.aspectRatio().unwrap()
          : (childMainSize - marginMain) * childStyle.aspectRatio().unwrap();
      childCrossSizingMode = SizingMode::StretchFit;

      childCrossSize += marginCross;
    } else if (
        !std::isnan(availableInnerCrossDim) &&
        !currentLineChild->styleDefinesDimension(
            crossAxis, availableInnerCrossDim) &&
        sizingModeCrossDim == SizingMode::StretchFit &&
        !(isNodeFlexWrap && mainAxisOverflows) &&
        resolveChildAlignment(node, currentLineChild) == Align::Stretch &&
        currentLineChild->getFlexStartMarginValue(crossAxis).unit !=
            YGUnitAuto &&
        currentLineChild->marginTrailingValue(crossAxis).unit != YGUnitAuto) {
      childCrossSize = availableInnerCrossDim;
      childCrossSizingMode = SizingMode::StretchFit;
    } else if (!currentLineChild->styleDefinesDimension(
                   crossAxis, availableInnerCrossDim)) {
      childCrossSize = availableInnerCrossDim;
      childCrossSizingMode = yoga::isUndefined(childCrossSize)
          ? SizingMode::MaxContent
          : SizingMode::FitContent;
    } else {
      childCrossSize =
          yoga::resolveValue(
              currentLineChild->getResolvedDimension(dimension(crossAxis)),
              availableInnerCrossDim)
              .unwrap() +
          marginCross;
      const bool isLoosePercentageMeasurement =
          currentLineChild->getResolvedDimension(dimension(crossAxis)).unit ==
              YGUnitPercent &&
          sizingModeCrossDim != SizingMode::StretchFit;
      childCrossSizingMode =
          yoga::isUndefined(childCrossSize) || isLoosePercentageMeasurement
          ? SizingMode::MaxContent
          : SizingMode::StretchFit;
    }

    constrainMaxSizeForMode(
        currentLineChild,
        mainAxis,
        availableInnerMainDim,
        availableInnerWidth,
        &childMainSizingMode,
        &childMainSize);
    constrainMaxSizeForMode(
        currentLineChild,
        crossAxis,
        availableInnerCrossDim,
        availableInnerWidth,
        &childCrossSizingMode,
        &childCrossSize);

    const bool requiresStretchLayout = !currentLineChild->styleDefinesDimension(
                                           crossAxis, availableInnerCrossDim) &&
        resolveChildAlignment(node, currentLineChild) == Align::Stretch &&
        currentLineChild->getFlexStartMarginValue(crossAxis).unit !=
            YGUnitAuto &&
        currentLineChild->marginTrailingValue(crossAxis).unit != YGUnitAuto;

    const float childWidth = isMainAxisRow ? childMainSize : childCrossSize;
    const float childHeight = !isMainAxisRow ? childMainSize : childCrossSize;

    const SizingMode childWidthSizingMode =
        isMainAxisRow ? childMainSizingMode : childCrossSizingMode;
    const SizingMode childHeightSizingMode =
        !isMainAxisRow ? childMainSizingMode : childCrossSizingMode;

    const bool isLayoutPass = performLayout && !requiresStretchLayout;
    // Recursively call the layout algorithm for this child with the updated
    // main size.
    calculateLayoutInternal(
        currentLineChild,
        childWidth,
        childHeight,
        node->getLayout().direction(),
        childWidthSizingMode,
        childHeightSizingMode,
        availableInnerWidth,
        availableInnerHeight,
        isLayoutPass,
        isLayoutPass ? LayoutPassReason::kFlexLayout
                     : LayoutPassReason::kFlexMeasure,
        layoutMarkerData,
        depth,
        generationCount);
    node->setLayoutHadOverflow(
        node->getLayout().hadOverflow() ||
        currentLineChild->getLayout().hadOverflow());
  }
  return deltaFreeSpace;
}

// It distributes the free space to the flexible items.For those flexible items
// whose min and max constraints are triggered, those flex item's clamped size
// is removed from the remaingfreespace.
static void distributeFreeSpaceFirstPass(
    FlexLine& flexLine,
    const FlexDirection mainAxis,
    const float mainAxisownerSize,
    const float availableInnerMainDim,
    const float availableInnerWidth) {
  float flexShrinkScaledFactor = 0;
  float flexGrowFactor = 0;
  float baseMainSize = 0;
  float boundMainSize = 0;
  float deltaFreeSpace = 0;

  for (auto currentLineChild : flexLine.itemsInFlow) {
    float childFlexBasis = boundAxisWithinMinAndMax(
                               currentLineChild,
                               mainAxis,
                               currentLineChild->getLayout().computedFlexBasis,
                               mainAxisownerSize)
                               .unwrap();

    if (flexLine.layout.remainingFreeSpace < 0) {
      flexShrinkScaledFactor =
          -currentLineChild->resolveFlexShrink() * childFlexBasis;

      // Is this child able to shrink?
      if (yoga::isDefined(flexShrinkScaledFactor) &&
          flexShrinkScaledFactor != 0) {
        baseMainSize = childFlexBasis +
            flexLine.layout.remainingFreeSpace /
                flexLine.layout.totalFlexShrinkScaledFactors *
                flexShrinkScaledFactor;
        boundMainSize = boundAxis(
            currentLineChild,
            mainAxis,
            baseMainSize,
            availableInnerMainDim,
            availableInnerWidth);
        if (yoga::isDefined(baseMainSize) && yoga::isDefined(boundMainSize) &&
            baseMainSize != boundMainSize) {
          // By excluding this item's size and flex factor from remaining, this
          // item's min/max constraints should also trigger in the second pass
          // resulting in the item's size calculation being identical in the
          // first and second passes.
          deltaFreeSpace += boundMainSize - childFlexBasis;
          flexLine.layout.totalFlexShrinkScaledFactors -=
              (-currentLineChild->resolveFlexShrink() *
               currentLineChild->getLayout().computedFlexBasis.unwrap());
        }
      }
    } else if (
        yoga::isDefined(flexLine.layout.remainingFreeSpace) &&
        flexLine.layout.remainingFreeSpace > 0) {
      flexGrowFactor = currentLineChild->resolveFlexGrow();

      // Is this child able to grow?
      if (yoga::isDefined(flexGrowFactor) && flexGrowFactor != 0) {
        baseMainSize = childFlexBasis +
            flexLine.layout.remainingFreeSpace /
                flexLine.layout.totalFlexGrowFactors * flexGrowFactor;
        boundMainSize = boundAxis(
            currentLineChild,
            mainAxis,
            baseMainSize,
            availableInnerMainDim,
            availableInnerWidth);

        if (yoga::isDefined(baseMainSize) && yoga::isDefined(boundMainSize) &&
            baseMainSize != boundMainSize) {
          // By excluding this item's size and flex factor from remaining, this
          // item's min/max constraints should also trigger in the second pass
          // resulting in the item's size calculation being identical in the
          // first and second passes.
          deltaFreeSpace += boundMainSize - childFlexBasis;
          flexLine.layout.totalFlexGrowFactors -= flexGrowFactor;
        }
      }
    }
  }
  flexLine.layout.remainingFreeSpace -= deltaFreeSpace;
}

// Do two passes over the flex items to figure out how to distribute the
// remaining space.
//
// The first pass finds the items whose min/max constraints trigger, freezes
// them at those sizes, and excludes those sizes from the remaining space.
//
// The second pass sets the size of each flexible item. It distributes the
// remaining space amongst the items whose min/max constraints didn't trigger in
// the first pass. For the other items, it sets their sizes by forcing their
// min/max constraints to trigger again.
//
// This two pass approach for resolving min/max constraints deviates from the
// spec. The spec
// (https://www.w3.org/TR/CSS-flexbox-1/#resolve-flexible-lengths) describes a
// process that needs to be repeated a variable number of times. The algorithm
// implemented here won't handle all cases but it was simpler to implement and
// it mitigates performance concerns because we know exactly how many passes
// it'll do.
//
// At the end of this function the child nodes would have the proper size
// assigned to them.
//
static void resolveFlexibleLength(
    yoga::Node* const node,
    FlexLine& flexLine,
    const FlexDirection mainAxis,
    const FlexDirection crossAxis,
    const float mainAxisownerSize,
    const float availableInnerMainDim,
    const float availableInnerCrossDim,
    const float availableInnerWidth,
    const float availableInnerHeight,
    const bool mainAxisOverflows,
    const SizingMode sizingModeCrossDim,
    const bool performLayout,
    LayoutData& layoutMarkerData,
    const uint32_t depth,
    const uint32_t generationCount) {
  const float originalFreeSpace = flexLine.layout.remainingFreeSpace;
  // First pass: detect the flex items whose min/max constraints trigger
  distributeFreeSpaceFirstPass(
      flexLine,
      mainAxis,
      mainAxisownerSize,
      availableInnerMainDim,
      availableInnerWidth);

  // Second pass: resolve the sizes of the flexible items
  const float distributedFreeSpace = distributeFreeSpaceSecondPass(
      flexLine,
      node,
      mainAxis,
      crossAxis,
      mainAxisownerSize,
      availableInnerMainDim,
      availableInnerCrossDim,
      availableInnerWidth,
      availableInnerHeight,
      mainAxisOverflows,
      sizingModeCrossDim,
      performLayout,
      layoutMarkerData,
      depth,
      generationCount);

  flexLine.layout.remainingFreeSpace = originalFreeSpace - distributedFreeSpace;
}

static void justifyMainAxis(
    yoga::Node* const node,
    FlexLine& flexLine,
    const size_t startOfLineIndex,
    const FlexDirection mainAxis,
    const FlexDirection crossAxis,
    const Direction direction,
    const SizingMode sizingModeMainDim,
    const SizingMode sizingModeCrossDim,
    const float mainAxisownerSize,
    const float ownerWidth,
    const float availableInnerMainDim,
    const float availableInnerCrossDim,
    const float availableInnerWidth,
    const bool performLayout) {
  const auto& style = node->getStyle();

  const float leadingPaddingAndBorderMain =
      node->hasErrata(Errata::StartingEndingEdgeFromFlexDirection)
      ? node->getInlineStartPaddingAndBorder(mainAxis, direction, ownerWidth)
      : node->getFlexStartPaddingAndBorder(mainAxis, direction, ownerWidth);
  const float trailingPaddingAndBorderMain =
      node->hasErrata(Errata::StartingEndingEdgeFromFlexDirection)
      ? node->getInlineEndPaddingAndBorder(mainAxis, direction, ownerWidth)
      : node->getFlexEndPaddingAndBorder(mainAxis, direction, ownerWidth);

  const float gap = node->getGapForAxis(mainAxis);
  // If we are using "at most" rules in the main axis, make sure that
  // remainingFreeSpace is 0 when min main dimension is not given
  if (sizingModeMainDim == SizingMode::FitContent &&
      flexLine.layout.remainingFreeSpace > 0) {
    if (style.minDimension(dimension(mainAxis)).isDefined() &&
        yoga::resolveValue(
            style.minDimension(dimension(mainAxis)), mainAxisownerSize)
            .isDefined()) {
      // This condition makes sure that if the size of main dimension(after
      // considering child nodes main dim, leading and trailing padding etc)
      // falls below min dimension, then the remainingFreeSpace is reassigned
      // considering the min dimension

      // `minAvailableMainDim` denotes minimum available space in which child
      // can be laid out, it will exclude space consumed by padding and border.
      const float minAvailableMainDim =
          yoga::resolveValue(
              style.minDimension(dimension(mainAxis)), mainAxisownerSize)
              .unwrap() -
          leadingPaddingAndBorderMain - trailingPaddingAndBorderMain;
      const float occupiedSpaceByChildNodes =
          availableInnerMainDim - flexLine.layout.remainingFreeSpace;
      flexLine.layout.remainingFreeSpace = yoga::maxOrDefined(
          0.0f, minAvailableMainDim - occupiedSpaceByChildNodes);
    } else {
      flexLine.layout.remainingFreeSpace = 0;
    }
  }

  int numberOfAutoMarginsOnCurrentLine = 0;
  for (size_t i = startOfLineIndex; i < flexLine.endOfLineIndex; i++) {
    auto child = node->getChild(i);
    if (child->getStyle().positionType() != PositionType::Absolute) {
      if (child->getFlexStartMarginValue(mainAxis).unit == YGUnitAuto) {
        numberOfAutoMarginsOnCurrentLine++;
      }
      if (child->marginTrailingValue(mainAxis).unit == YGUnitAuto) {
        numberOfAutoMarginsOnCurrentLine++;
      }
    }
  }

  // In order to position the elements in the main axis, we have two controls.
  // The space between the beginning and the first element and the space between
  // each two elements.
  float leadingMainDim = 0;
  float betweenMainDim = gap;
  const Justify justifyContent = node->getStyle().justifyContent();

  if (numberOfAutoMarginsOnCurrentLine == 0) {
    switch (justifyContent) {
      case Justify::Center:
        leadingMainDim = flexLine.layout.remainingFreeSpace / 2;
        break;
      case Justify::FlexEnd:
        leadingMainDim = flexLine.layout.remainingFreeSpace;
        break;
      case Justify::SpaceBetween:
        if (flexLine.itemsInFlow.size() > 1) {
          betweenMainDim +=
              yoga::maxOrDefined(flexLine.layout.remainingFreeSpace, 0.0f) /
              static_cast<float>(flexLine.itemsInFlow.size() - 1);
        }
        break;
      case Justify::SpaceEvenly:
        // Space is distributed evenly across all elements
        leadingMainDim = flexLine.layout.remainingFreeSpace /
            static_cast<float>(flexLine.itemsInFlow.size() + 1);
        betweenMainDim += leadingMainDim;
        break;
      case Justify::SpaceAround:
        // Space on the edges is half of the space between elements
        leadingMainDim = 0.5f * flexLine.layout.remainingFreeSpace /
            static_cast<float>(flexLine.itemsInFlow.size());
        betweenMainDim += leadingMainDim * 2;
        break;
      case Justify::FlexStart:
        break;
    }
  }

  flexLine.layout.mainDim = leadingPaddingAndBorderMain + leadingMainDim;
  flexLine.layout.crossDim = 0;

  float maxAscentForCurrentLine = 0;
  float maxDescentForCurrentLine = 0;
  bool isNodeBaselineLayout = isBaselineLayout(node);
  for (size_t i = startOfLineIndex; i < flexLine.endOfLineIndex; i++) {
    const auto child = node->getChild(i);
    const Style& childStyle = child->getStyle();
    const LayoutResults& childLayout = child->getLayout();
    if (childStyle.display() == Display::None) {
      continue;
    }
    if (childStyle.positionType() == PositionType::Absolute &&
        child->isInlineStartPositionDefined(mainAxis, direction)) {
      if (performLayout) {
        // In case the child is position absolute and has left/top being
        // defined, we override the position to whatever the user said (and
        // margin/border).
        child->setLayoutPosition(
            child->getInlineStartPosition(
                mainAxis, direction, availableInnerMainDim) +
                node->getInlineStartBorder(mainAxis, direction) +
                child->getInlineStartMargin(
                    mainAxis, direction, availableInnerWidth),
            flexStartEdge(mainAxis));
      }
    } else {
      // Now that we placed the element, we need to update the variables.
      // We need to do that only for relative elements. Absolute elements do not
      // take part in that phase.
      if (childStyle.positionType() != PositionType::Absolute) {
        if (child->getFlexStartMarginValue(mainAxis).unit == YGUnitAuto) {
          flexLine.layout.mainDim += flexLine.layout.remainingFreeSpace /
              static_cast<float>(numberOfAutoMarginsOnCurrentLine);
        }

        if (performLayout) {
          child->setLayoutPosition(
              childLayout.position(flexStartEdge(mainAxis)) +
                  flexLine.layout.mainDim,
              flexStartEdge(mainAxis));
        }

        if (child != flexLine.itemsInFlow.back()) {
          flexLine.layout.mainDim += betweenMainDim;
        }

        if (child->marginTrailingValue(mainAxis).unit == YGUnitAuto) {
          flexLine.layout.mainDim += flexLine.layout.remainingFreeSpace /
              static_cast<float>(numberOfAutoMarginsOnCurrentLine);
        }
        bool canSkipFlex =
            !performLayout && sizingModeCrossDim == SizingMode::StretchFit;
        if (canSkipFlex) {
          // If we skipped the flex step, then we can't rely on the measuredDims
          // because they weren't computed. This means we can't call
          // dimensionWithMargin.
          flexLine.layout.mainDim +=
              child->getMarginForAxis(mainAxis, availableInnerWidth) +
              childLayout.computedFlexBasis.unwrap();
          flexLine.layout.crossDim = availableInnerCrossDim;
        } else {
          // The main dimension is the sum of all the elements dimension plus
          // the spacing.
          flexLine.layout.mainDim +=
              child->dimensionWithMargin(mainAxis, availableInnerWidth);

          if (isNodeBaselineLayout) {
            // If the child is baseline aligned then the cross dimension is
            // calculated by adding maxAscent and maxDescent from the baseline.
            const float ascent = calculateBaseline(child) +
                child->getInlineStartMargin(
                    FlexDirection::Column, direction, availableInnerWidth);
            const float descent =
                child->getLayout().measuredDimension(Dimension::Height) +
                child->getMarginForAxis(
                    FlexDirection::Column, availableInnerWidth) -
                ascent;

            maxAscentForCurrentLine =
                yoga::maxOrDefined(maxAscentForCurrentLine, ascent);
            maxDescentForCurrentLine =
                yoga::maxOrDefined(maxDescentForCurrentLine, descent);
          } else {
            // The cross dimension is the max of the elements dimension since
            // there can only be one element in that cross dimension in the case
            // when the items are not baseline aligned
            flexLine.layout.crossDim = yoga::maxOrDefined(
                flexLine.layout.crossDim,
                child->dimensionWithMargin(crossAxis, availableInnerWidth));
          }
        }
      } else if (performLayout) {
        child->setLayoutPosition(
            childLayout.position(flexStartEdge(mainAxis)) +
                node->getInlineStartBorder(mainAxis, direction) +
                leadingMainDim,
            flexStartEdge(mainAxis));
      }
    }
  }
  flexLine.layout.mainDim += trailingPaddingAndBorderMain;

  if (isNodeBaselineLayout) {
    flexLine.layout.crossDim =
        maxAscentForCurrentLine + maxDescentForCurrentLine;
  }
}

//
// This is the main routine that implements a subset of the flexbox layout
// algorithm described in the W3C CSS documentation:
// https://www.w3.org/TR/CSS3-flexbox/.
//
// Limitations of this algorithm, compared to the full standard:
//  * Display property is always assumed to be 'flex' except for Text nodes,
//    which are assumed to be 'inline-flex'.
//  * The 'zIndex' property (or any form of z ordering) is not supported. Nodes
//    are stacked in document order.
//  * The 'order' property is not supported. The order of flex items is always
//    defined by document order.
//  * The 'visibility' property is always assumed to be 'visible'. Values of
//    'collapse' and 'hidden' are not supported.
//  * There is no support for forced breaks.
//  * It does not support vertical inline directions (top-to-bottom or
//    bottom-to-top text).
//
// Deviations from standard:
//  * Section 4.5 of the spec indicates that all flex items have a default
//    minimum main size. For text blocks, for example, this is the width of the
//    widest word. Calculating the minimum width is expensive, so we forego it
//    and assume a default minimum main size of 0.
//  * Min/Max sizes in the main axis are not honored when resolving flexible
//    lengths.
//  * The spec indicates that the default value for 'flexDirection' is 'row',
//    but the algorithm below assumes a default of 'column'.
//
// Input parameters:
//    - node: current node to be sized and laid out
//    - availableWidth & availableHeight: available size to be used for sizing
//      the node or YGUndefined if the size is not available; interpretation
//      depends on layout flags
//    - ownerDirection: the inline (text) direction within the owner
//      (left-to-right or right-to-left)
//    - widthSizingMode: indicates the sizing rules for the width (see below
//      for explanation)
//    - heightSizingMode: indicates the sizing rules for the height (see below
//      for explanation)
//    - performLayout: specifies whether the caller is interested in just the
//      dimensions of the node or it requires the entire node and its subtree to
//      be laid out (with final positions)
//
// Details:
//    This routine is called recursively to lay out subtrees of flexbox
//    elements. It uses the information in node.style, which is treated as a
//    read-only input. It is responsible for setting the layout.direction and
//    layout.measuredDimensions fields for the input node as well as the
//    layout.position and layout.lineIndex fields for its child nodes. The
//    layout.measuredDimensions field includes any border or padding for the
//    node but does not include margins.
//
//    When calling calculateLayoutImpl and calculateLayoutInternal, if the
//    caller passes an available size of undefined then it must also pass a
//    measure mode of SizingMode::MaxContent in that dimension.
//
static void calculateLayoutImpl(
    yoga::Node* const node,
    const float availableWidth,
    const float availableHeight,
    const Direction ownerDirection,
    const SizingMode widthSizingMode,
    const SizingMode heightSizingMode,
    const float ownerWidth,
    const float ownerHeight,
    const bool performLayout,
    LayoutData& layoutMarkerData,
    const uint32_t depth,
    const uint32_t generationCount,
    const LayoutPassReason reason) {
  yoga::assertFatalWithNode(
      node,
      yoga::isUndefined(availableWidth)
          ? widthSizingMode == SizingMode::MaxContent
          : true,
      "availableWidth is indefinite so widthSizingMode must be "
      "SizingMode::MaxContent");
  yoga::assertFatalWithNode(
      node,
      yoga::isUndefined(availableHeight)
          ? heightSizingMode == SizingMode::MaxContent
          : true,
      "availableHeight is indefinite so heightSizingMode must be "
      "SizingMode::MaxContent");

  (performLayout ? layoutMarkerData.layouts : layoutMarkerData.measures) += 1;

  // Set the resolved resolution in the node's layout.
  const Direction direction = node->resolveDirection(ownerDirection);
  node->setLayoutDirection(direction);

  const FlexDirection flexRowDirection =
      resolveDirection(FlexDirection::Row, direction);
  const FlexDirection flexColumnDirection =
      resolveDirection(FlexDirection::Column, direction);

  const Edge startEdge = direction == Direction::LTR ? Edge::Left : Edge::Right;
  const Edge endEdge = direction == Direction::LTR ? Edge::Right : Edge::Left;

  const float marginRowLeading =
      node->getInlineStartMargin(flexRowDirection, direction, ownerWidth);
  node->setLayoutMargin(marginRowLeading, startEdge);
  const float marginRowTrailing =
      node->getInlineEndMargin(flexRowDirection, direction, ownerWidth);
  node->setLayoutMargin(marginRowTrailing, endEdge);
  const float marginColumnLeading =
      node->getInlineStartMargin(flexColumnDirection, direction, ownerWidth);
  node->setLayoutMargin(marginColumnLeading, Edge::Top);
  const float marginColumnTrailing =
      node->getInlineEndMargin(flexColumnDirection, direction, ownerWidth);
  node->setLayoutMargin(marginColumnTrailing, Edge::Bottom);

  const float marginAxisRow = marginRowLeading + marginRowTrailing;
  const float marginAxisColumn = marginColumnLeading + marginColumnTrailing;

  node->setLayoutBorder(
      node->getInlineStartBorder(flexRowDirection, direction), startEdge);
  node->setLayoutBorder(
      node->getInlineEndBorder(flexRowDirection, direction), endEdge);
  node->setLayoutBorder(
      node->getInlineStartBorder(flexColumnDirection, direction), Edge::Top);
  node->setLayoutBorder(
      node->getInlineEndBorder(flexColumnDirection, direction), Edge::Bottom);

  node->setLayoutPadding(
      node->getInlineStartPadding(flexRowDirection, direction, ownerWidth),
      startEdge);
  node->setLayoutPadding(
      node->getInlineEndPadding(flexRowDirection, direction, ownerWidth),
      endEdge);
  node->setLayoutPadding(
      node->getInlineStartPadding(flexColumnDirection, direction, ownerWidth),
      Edge::Top);
  node->setLayoutPadding(
      node->getInlineEndPadding(flexColumnDirection, direction, ownerWidth),
      Edge::Bottom);

  if (node->hasMeasureFunc()) {
    measureNodeWithMeasureFunc(
        node,
        availableWidth - marginAxisRow,
        availableHeight - marginAxisColumn,
        widthSizingMode,
        heightSizingMode,
        ownerWidth,
        ownerHeight,
        layoutMarkerData,
        reason);
    return;
  }

  const auto childCount = node->getChildCount();
  if (childCount == 0) {
    measureNodeWithoutChildren(
        node,
        availableWidth - marginAxisRow,
        availableHeight - marginAxisColumn,
        widthSizingMode,
        heightSizingMode,
        ownerWidth,
        ownerHeight);
    return;
  }

  // If we're not being asked to perform a full layout we can skip the algorithm
  // if we already know the size
  if (!performLayout &&
      measureNodeWithFixedSize(
          node,
          availableWidth - marginAxisRow,
          availableHeight - marginAxisColumn,
          widthSizingMode,
          heightSizingMode,
          ownerWidth,
          ownerHeight)) {
    return;
  }

  // At this point we know we're going to perform work. Ensure that each child
  // has a mutable copy.
  node->cloneChildrenIfNeeded();
  // Reset layout flags, as they could have changed.
  node->setLayoutHadOverflow(false);

  // STEP 1: CALCULATE VALUES FOR REMAINDER OF ALGORITHM
  const FlexDirection mainAxis =
      resolveDirection(node->getStyle().flexDirection(), direction);
  const FlexDirection crossAxis = resolveCrossDirection(mainAxis, direction);
  const bool isMainAxisRow = isRow(mainAxis);
  const bool isNodeFlexWrap = node->getStyle().flexWrap() != Wrap::NoWrap;

  const float mainAxisownerSize = isMainAxisRow ? ownerWidth : ownerHeight;
  const float crossAxisownerSize = isMainAxisRow ? ownerHeight : ownerWidth;

  const float paddingAndBorderAxisMain =
      paddingAndBorderForAxis(node, mainAxis, ownerWidth);
  const float paddingAndBorderAxisCross =
      paddingAndBorderForAxis(node, crossAxis, ownerWidth);
  const float leadingPaddingAndBorderCross =
      node->getInlineStartPaddingAndBorder(crossAxis, direction, ownerWidth);

  SizingMode sizingModeMainDim =
      isMainAxisRow ? widthSizingMode : heightSizingMode;
  SizingMode sizingModeCrossDim =
      isMainAxisRow ? heightSizingMode : widthSizingMode;

  const float paddingAndBorderAxisRow =
      isMainAxisRow ? paddingAndBorderAxisMain : paddingAndBorderAxisCross;
  const float paddingAndBorderAxisColumn =
      isMainAxisRow ? paddingAndBorderAxisCross : paddingAndBorderAxisMain;

  // STEP 2: DETERMINE AVAILABLE SIZE IN MAIN AND CROSS DIRECTIONS

  float availableInnerWidth = calculateAvailableInnerDimension(
      node,
      Dimension::Width,
      availableWidth - marginAxisRow,
      paddingAndBorderAxisRow,
      ownerWidth);
  float availableInnerHeight = calculateAvailableInnerDimension(
      node,
      Dimension::Height,
      availableHeight - marginAxisColumn,
      paddingAndBorderAxisColumn,
      ownerHeight);

  float availableInnerMainDim =
      isMainAxisRow ? availableInnerWidth : availableInnerHeight;
  const float availableInnerCrossDim =
      isMainAxisRow ? availableInnerHeight : availableInnerWidth;

  // STEP 3: DETERMINE FLEX BASIS FOR EACH ITEM

  // Computed basis + margins + gap
  float totalMainDim = 0;
  totalMainDim += computeFlexBasisForChildren(
      node,
      availableInnerWidth,
      availableInnerHeight,
      widthSizingMode,
      heightSizingMode,
      direction,
      mainAxis,
      performLayout,
      layoutMarkerData,
      depth,
      generationCount);

  if (childCount > 1) {
    totalMainDim +=
        node->getGapForAxis(mainAxis) * static_cast<float>(childCount - 1);
  }

  const bool mainAxisOverflows =
      (sizingModeMainDim != SizingMode::MaxContent) &&
      totalMainDim > availableInnerMainDim;

  if (isNodeFlexWrap && mainAxisOverflows &&
      sizingModeMainDim == SizingMode::FitContent) {
    sizingModeMainDim = SizingMode::StretchFit;
  }
  // STEP 4: COLLECT FLEX ITEMS INTO FLEX LINES

  // Indexes of children that represent the first and last items in the line.
  size_t startOfLineIndex = 0;
  size_t endOfLineIndex = 0;

  // Number of lines.
  size_t lineCount = 0;

  // Accumulated cross dimensions of all lines so far.
  float totalLineCrossDim = 0;

  const float crossAxisGap = node->getGapForAxis(crossAxis);

  // Max main dimension of all the lines.
  float maxLineMainDim = 0;
  for (; endOfLineIndex < childCount;
       lineCount++, startOfLineIndex = endOfLineIndex) {
    auto flexLine = calculateFlexLine(
        node,
        ownerDirection,
        mainAxisownerSize,
        availableInnerWidth,
        availableInnerMainDim,
        startOfLineIndex,
        lineCount);

    endOfLineIndex = flexLine.endOfLineIndex;

    // If we don't need to measure the cross axis, we can skip the entire flex
    // step.
    const bool canSkipFlex =
        !performLayout && sizingModeCrossDim == SizingMode::StretchFit;

    // STEP 5: RESOLVING FLEXIBLE LENGTHS ON MAIN AXIS
    // Calculate the remaining available space that needs to be allocated. If
    // the main dimension size isn't known, it is computed based on the line
    // length, so there's no more space left to distribute.

    bool sizeBasedOnContent = false;
    // If we don't measure with exact main dimension we want to ensure we don't
    // violate min and max
    if (sizingModeMainDim != SizingMode::StretchFit) {
      const auto& style = node->getStyle();
      const float minInnerWidth =
          yoga::resolveValue(style.minDimension(Dimension::Width), ownerWidth)
              .unwrap() -
          paddingAndBorderAxisRow;
      const float maxInnerWidth =
          yoga::resolveValue(style.maxDimension(Dimension::Width), ownerWidth)
              .unwrap() -
          paddingAndBorderAxisRow;
      const float minInnerHeight =
          yoga::resolveValue(style.minDimension(Dimension::Height), ownerHeight)
              .unwrap() -
          paddingAndBorderAxisColumn;
      const float maxInnerHeight =
          yoga::resolveValue(style.maxDimension(Dimension::Height), ownerHeight)
              .unwrap() -
          paddingAndBorderAxisColumn;

      const float minInnerMainDim =
          isMainAxisRow ? minInnerWidth : minInnerHeight;
      const float maxInnerMainDim =
          isMainAxisRow ? maxInnerWidth : maxInnerHeight;

      if (yoga::isDefined(minInnerMainDim) &&
          flexLine.sizeConsumed < minInnerMainDim) {
        availableInnerMainDim = minInnerMainDim;
      } else if (
          yoga::isDefined(maxInnerMainDim) &&
          flexLine.sizeConsumed > maxInnerMainDim) {
        availableInnerMainDim = maxInnerMainDim;
      } else {
        bool useLegacyStretchBehaviour =
            node->hasErrata(Errata::StretchFlexBasis);

        if (!useLegacyStretchBehaviour &&
            ((yoga::isDefined(flexLine.layout.totalFlexGrowFactors) &&
              flexLine.layout.totalFlexGrowFactors == 0) ||
             (yoga::isDefined(node->resolveFlexGrow()) &&
              node->resolveFlexGrow() == 0))) {
          // If we don't have any children to flex or we can't flex the node
          // itself, space we've used is all space we need. Root node also
          // should be shrunk to minimum
          availableInnerMainDim = flexLine.sizeConsumed;
        }

        sizeBasedOnContent = !useLegacyStretchBehaviour;
      }
    }

    if (!sizeBasedOnContent && yoga::isDefined(availableInnerMainDim)) {
      flexLine.layout.remainingFreeSpace =
          availableInnerMainDim - flexLine.sizeConsumed;
    } else if (flexLine.sizeConsumed < 0) {
      // availableInnerMainDim is indefinite which means the node is being sized
      // based on its content. sizeConsumed is negative which means
      // the node will allocate 0 points for its content. Consequently,
      // remainingFreeSpace is 0 - sizeConsumed.
      flexLine.layout.remainingFreeSpace = -flexLine.sizeConsumed;
    }

    if (!canSkipFlex) {
      resolveFlexibleLength(
          node,
          flexLine,
          mainAxis,
          crossAxis,
          mainAxisownerSize,
          availableInnerMainDim,
          availableInnerCrossDim,
          availableInnerWidth,
          availableInnerHeight,
          mainAxisOverflows,
          sizingModeCrossDim,
          performLayout,
          layoutMarkerData,
          depth,
          generationCount);
    }

    node->setLayoutHadOverflow(
        node->getLayout().hadOverflow() ||
        (flexLine.layout.remainingFreeSpace < 0));

    // STEP 6: MAIN-AXIS JUSTIFICATION & CROSS-AXIS SIZE DETERMINATION

    // At this point, all the children have their dimensions set in the main
    // axis. Their dimensions are also set in the cross axis with the exception
    // of items that are aligned "stretch". We need to compute these stretch
    // values and set the final positions.

    justifyMainAxis(
        node,
        flexLine,
        startOfLineIndex,
        mainAxis,
        crossAxis,
        direction,
        sizingModeMainDim,
        sizingModeCrossDim,
        mainAxisownerSize,
        ownerWidth,
        availableInnerMainDim,
        availableInnerCrossDim,
        availableInnerWidth,
        performLayout);

    float containerCrossAxis = availableInnerCrossDim;
    if (sizingModeCrossDim == SizingMode::MaxContent ||
        sizingModeCrossDim == SizingMode::FitContent) {
      // Compute the cross axis from the max cross dimension of the children.
      containerCrossAxis =
          boundAxis(
              node,
              crossAxis,
              flexLine.layout.crossDim + paddingAndBorderAxisCross,
              crossAxisownerSize,
              ownerWidth) -
          paddingAndBorderAxisCross;
    }

    // If there's no flex wrap, the cross dimension is defined by the container.
    if (!isNodeFlexWrap && sizingModeCrossDim == SizingMode::StretchFit) {
      flexLine.layout.crossDim = availableInnerCrossDim;
    }

    // Clamp to the min/max size specified on the container.
    flexLine.layout.crossDim =
        boundAxis(
            node,
            crossAxis,
            flexLine.layout.crossDim + paddingAndBorderAxisCross,
            crossAxisownerSize,
            ownerWidth) -
        paddingAndBorderAxisCross;

    // STEP 7: CROSS-AXIS ALIGNMENT
    // We can skip child alignment if we're just measuring the container.
    if (performLayout) {
      for (size_t i = startOfLineIndex; i < endOfLineIndex; i++) {
        const auto child = node->getChild(i);
        if (child->getStyle().display() == Display::None) {
          continue;
        }
        if (child->getStyle().positionType() == PositionType::Absolute) {
          // If the child is absolutely positioned and has a
          // top/left/bottom/right set, override all the previously computed
          // positions to set it correctly.
          const bool isChildLeadingPosDefined =
              child->isInlineStartPositionDefined(crossAxis, direction);
          if (isChildLeadingPosDefined) {
            child->setLayoutPosition(
                child->getInlineStartPosition(
                    crossAxis, direction, availableInnerCrossDim) +
                    node->getInlineStartBorder(crossAxis, direction) +
                    child->getInlineStartMargin(
                        crossAxis, direction, availableInnerWidth),
                flexStartEdge(crossAxis));
          }
          // If leading position is not defined or calculations result in Nan,
          // default to border + margin
          if (!isChildLeadingPosDefined ||
              yoga::isUndefined(
                  child->getLayout().position(flexStartEdge(crossAxis)))) {
            child->setLayoutPosition(
                node->getInlineStartBorder(crossAxis, direction) +
                    child->getInlineStartMargin(
                        crossAxis, direction, availableInnerWidth),
                flexStartEdge(crossAxis));
          }
        } else {
          float leadingCrossDim = leadingPaddingAndBorderCross;

          // For a relative children, we're either using alignItems (owner) or
          // alignSelf (child) in order to determine the position in the cross
          // axis
          const Align alignItem = resolveChildAlignment(node, child);

          // If the child uses align stretch, we need to lay it out one more
          // time, this time forcing the cross-axis size to be the computed
          // cross size for the current line.
          if (alignItem == Align::Stretch &&
              child->getFlexStartMarginValue(crossAxis).unit != YGUnitAuto &&
              child->marginTrailingValue(crossAxis).unit != YGUnitAuto) {
            // If the child defines a definite size for its cross axis, there's
            // no need to stretch.
            if (!child->styleDefinesDimension(
                    crossAxis, availableInnerCrossDim)) {
              float childMainSize =
                  child->getLayout().measuredDimension(dimension(mainAxis));
              const auto& childStyle = child->getStyle();
              float childCrossSize = childStyle.aspectRatio().isDefined()
                  ? child->getMarginForAxis(crossAxis, availableInnerWidth) +
                      (isMainAxisRow
                           ? childMainSize / childStyle.aspectRatio().unwrap()
                           : childMainSize * childStyle.aspectRatio().unwrap())
                  : flexLine.layout.crossDim;

              childMainSize +=
                  child->getMarginForAxis(mainAxis, availableInnerWidth);

              SizingMode childMainSizingMode = SizingMode::StretchFit;
              SizingMode childCrossSizingMode = SizingMode::StretchFit;
              constrainMaxSizeForMode(
                  child,
                  mainAxis,
                  availableInnerMainDim,
                  availableInnerWidth,
                  &childMainSizingMode,
                  &childMainSize);
              constrainMaxSizeForMode(
                  child,
                  crossAxis,
                  availableInnerCrossDim,
                  availableInnerWidth,
                  &childCrossSizingMode,
                  &childCrossSize);

              const float childWidth =
                  isMainAxisRow ? childMainSize : childCrossSize;
              const float childHeight =
                  !isMainAxisRow ? childMainSize : childCrossSize;

              auto alignContent = node->getStyle().alignContent();
              auto crossAxisDoesNotGrow =
                  alignContent != Align::Stretch && isNodeFlexWrap;
              const SizingMode childWidthSizingMode =
                  yoga::isUndefined(childWidth) ||
                      (!isMainAxisRow && crossAxisDoesNotGrow)
                  ? SizingMode::MaxContent
                  : SizingMode::StretchFit;
              const SizingMode childHeightSizingMode =
                  yoga::isUndefined(childHeight) ||
                      (isMainAxisRow && crossAxisDoesNotGrow)
                  ? SizingMode::MaxContent
                  : SizingMode::StretchFit;

              calculateLayoutInternal(
                  child,
                  childWidth,
                  childHeight,
                  direction,
                  childWidthSizingMode,
                  childHeightSizingMode,
                  availableInnerWidth,
                  availableInnerHeight,
                  true,
                  LayoutPassReason::kStretch,
                  layoutMarkerData,
                  depth,
                  generationCount);
            }
          } else {
            const float remainingCrossDim = containerCrossAxis -
                child->dimensionWithMargin(crossAxis, availableInnerWidth);

            if (child->getFlexStartMarginValue(crossAxis).unit == YGUnitAuto &&
                child->marginTrailingValue(crossAxis).unit == YGUnitAuto) {
              leadingCrossDim +=
                  yoga::maxOrDefined(0.0f, remainingCrossDim / 2);
            } else if (
                child->marginTrailingValue(crossAxis).unit == YGUnitAuto) {
              // No-Op
            } else if (
                child->getFlexStartMarginValue(crossAxis).unit == YGUnitAuto) {
              leadingCrossDim += yoga::maxOrDefined(0.0f, remainingCrossDim);
            } else if (alignItem == Align::FlexStart) {
              // No-Op
            } else if (alignItem == Align::Center) {
              leadingCrossDim += remainingCrossDim / 2;
            } else {
              leadingCrossDim += remainingCrossDim;
            }
          }
          // And we apply the position
          child->setLayoutPosition(
              child->getLayout().position(flexStartEdge(crossAxis)) +
                  totalLineCrossDim + leadingCrossDim,
              flexStartEdge(crossAxis));
        }
      }
    }

    const float appliedCrossGap = lineCount != 0 ? crossAxisGap : 0.0f;
    totalLineCrossDim += flexLine.layout.crossDim + appliedCrossGap;
    maxLineMainDim =
        yoga::maxOrDefined(maxLineMainDim, flexLine.layout.mainDim);
  }

  // STEP 8: MULTI-LINE CONTENT ALIGNMENT
  // currentLead stores the size of the cross dim
  if (performLayout && (isNodeFlexWrap || isBaselineLayout(node))) {
    float crossDimLead = 0;
    float currentLead = leadingPaddingAndBorderCross;
    if (yoga::isDefined(availableInnerCrossDim)) {
      const float remainingAlignContentDim =
          availableInnerCrossDim - totalLineCrossDim;
      switch (node->getStyle().alignContent()) {
        case Align::FlexEnd:
          currentLead += remainingAlignContentDim;
          break;
        case Align::Center:
          currentLead += remainingAlignContentDim / 2;
          break;
        case Align::Stretch:
          if (availableInnerCrossDim > totalLineCrossDim) {
            crossDimLead =
                remainingAlignContentDim / static_cast<float>(lineCount);
          }
          break;
        case Align::SpaceAround:
          if (availableInnerCrossDim > totalLineCrossDim) {
            currentLead +=
                remainingAlignContentDim / (2 * static_cast<float>(lineCount));
            if (lineCount > 1) {
              crossDimLead =
                  remainingAlignContentDim / static_cast<float>(lineCount);
            }
          } else {
            currentLead += remainingAlignContentDim / 2;
          }
          break;
        case Align::SpaceEvenly:
          if (availableInnerCrossDim > totalLineCrossDim) {
            currentLead +=
                remainingAlignContentDim / static_cast<float>(lineCount + 1);
            if (lineCount > 1) {
              crossDimLead =
                  remainingAlignContentDim / static_cast<float>(lineCount + 1);
            }
          } else {
            currentLead += remainingAlignContentDim / 2;
          }
          break;
        case Align::SpaceBetween:
          if (availableInnerCrossDim > totalLineCrossDim && lineCount > 1) {
            crossDimLead =
                remainingAlignContentDim / static_cast<float>(lineCount - 1);
          }
          break;
        case Align::Auto:
        case Align::FlexStart:
        case Align::Baseline:
          break;
      }
    }
    size_t endIndex = 0;
    for (size_t i = 0; i < lineCount; i++) {
      const size_t startIndex = endIndex;
      size_t ii;

      // compute the line's height and find the endIndex
      float lineHeight = 0;
      float maxAscentForCurrentLine = 0;
      float maxDescentForCurrentLine = 0;
      for (ii = startIndex; ii < childCount; ii++) {
        const auto child = node->getChild(ii);
        if (child->getStyle().display() == Display::None) {
          continue;
        }
        if (child->getStyle().positionType() != PositionType::Absolute) {
          if (child->getLineIndex() != i) {
            break;
          }
          if (child->isLayoutDimensionDefined(crossAxis)) {
            lineHeight = yoga::maxOrDefined(
                lineHeight,
                child->getLayout().measuredDimension(dimension(crossAxis)) +
                    child->getMarginForAxis(crossAxis, availableInnerWidth));
          }
          if (resolveChildAlignment(node, child) == Align::Baseline) {
            const float ascent = calculateBaseline(child) +
                child->getInlineStartMargin(
                    FlexDirection::Column, direction, availableInnerWidth);
            const float descent =
                child->getLayout().measuredDimension(Dimension::Height) +
                child->getMarginForAxis(
                    FlexDirection::Column, availableInnerWidth) -
                ascent;
            maxAscentForCurrentLine =
                yoga::maxOrDefined(maxAscentForCurrentLine, ascent);
            maxDescentForCurrentLine =
                yoga::maxOrDefined(maxDescentForCurrentLine, descent);
            lineHeight = yoga::maxOrDefined(
                lineHeight, maxAscentForCurrentLine + maxDescentForCurrentLine);
          }
        }
      }
      endIndex = ii;
      lineHeight += crossDimLead;
      currentLead += i != 0 ? crossAxisGap : 0;

      if (performLayout) {
        for (ii = startIndex; ii < endIndex; ii++) {
          const auto child = node->getChild(ii);
          if (child->getStyle().display() == Display::None) {
            continue;
          }
          if (child->getStyle().positionType() != PositionType::Absolute) {
            switch (resolveChildAlignment(node, child)) {
              case Align::FlexStart: {
                child->setLayoutPosition(
                    currentLead +
                        child->getInlineStartMargin(
                            crossAxis, direction, availableInnerWidth),
                    flexStartEdge(crossAxis));
                break;
              }
              case Align::FlexEnd: {
                child->setLayoutPosition(
                    currentLead + lineHeight -
                        child->getInlineEndMargin(
                            crossAxis, direction, availableInnerWidth) -
                        child->getLayout().measuredDimension(
                            dimension(crossAxis)),
                    flexStartEdge(crossAxis));
                break;
              }
              case Align::Center: {
                float childHeight =
                    child->getLayout().measuredDimension(dimension(crossAxis));

                child->setLayoutPosition(
                    currentLead + (lineHeight - childHeight) / 2,
                    flexStartEdge(crossAxis));
                break;
              }
              case Align::Stretch: {
                child->setLayoutPosition(
                    currentLead +
                        child->getInlineStartMargin(
                            crossAxis, direction, availableInnerWidth),
                    flexStartEdge(crossAxis));

                // Remeasure child with the line height as it as been only
                // measured with the owners height yet.
                if (!child->styleDefinesDimension(
                        crossAxis, availableInnerCrossDim)) {
                  const float childWidth = isMainAxisRow
                      ? (child->getLayout().measuredDimension(
                             Dimension::Width) +
                         child->getMarginForAxis(mainAxis, availableInnerWidth))
                      : lineHeight;

                  const float childHeight = !isMainAxisRow
                      ? (child->getLayout().measuredDimension(
                             Dimension::Height) +
                         child->getMarginForAxis(
                             crossAxis, availableInnerWidth))
                      : lineHeight;

                  if (!(yoga::inexactEquals(
                            childWidth,
                            child->getLayout().measuredDimension(
                                Dimension::Width)) &&
                        yoga::inexactEquals(
                            childHeight,
                            child->getLayout().measuredDimension(
                                Dimension::Height)))) {
                    calculateLayoutInternal(
                        child,
                        childWidth,
                        childHeight,
                        direction,
                        SizingMode::StretchFit,
                        SizingMode::StretchFit,
                        availableInnerWidth,
                        availableInnerHeight,
                        true,
                        LayoutPassReason::kMultilineStretch,
                        layoutMarkerData,
                        depth,
                        generationCount);
                  }
                }
                break;
              }
              case Align::Baseline: {
                child->setLayoutPosition(
                    currentLead + maxAscentForCurrentLine -
                        calculateBaseline(child) +
                        child->getInlineStartPosition(
                            FlexDirection::Column,
                            direction,
                            availableInnerCrossDim),
                    Edge::Top);

                break;
              }
              case Align::Auto:
              case Align::SpaceBetween:
              case Align::SpaceAround:
              case Align::SpaceEvenly:
                break;
            }
          }
        }
      }
      currentLead += lineHeight;
    }
  }

  // STEP 9: COMPUTING FINAL DIMENSIONS

  node->setLayoutMeasuredDimension(
      boundAxis(
          node,
          FlexDirection::Row,
          availableWidth - marginAxisRow,
          ownerWidth,
          ownerWidth),
      Dimension::Width);

  node->setLayoutMeasuredDimension(
      boundAxis(
          node,
          FlexDirection::Column,
          availableHeight - marginAxisColumn,
          ownerHeight,
          ownerWidth),
      Dimension::Height);

  // If the user didn't specify a width or height for the node, set the
  // dimensions based on the children.
  if (sizingModeMainDim == SizingMode::MaxContent ||
      (node->getStyle().overflow() != Overflow::Scroll &&
       sizingModeMainDim == SizingMode::FitContent)) {
    // Clamp the size to the min/max size, if specified, and make sure it
    // doesn't go below the padding and border amount.
    node->setLayoutMeasuredDimension(
        boundAxis(
            node, mainAxis, maxLineMainDim, mainAxisownerSize, ownerWidth),
        dimension(mainAxis));

  } else if (
      sizingModeMainDim == SizingMode::FitContent &&
      node->getStyle().overflow() == Overflow::Scroll) {
    node->setLayoutMeasuredDimension(
        yoga::maxOrDefined(
            yoga::minOrDefined(
                availableInnerMainDim + paddingAndBorderAxisMain,
                boundAxisWithinMinAndMax(
                    node,
                    mainAxis,
                    FloatOptional{maxLineMainDim},
                    mainAxisownerSize)
                    .unwrap()),
            paddingAndBorderAxisMain),
        dimension(mainAxis));
  }

  if (sizingModeCrossDim == SizingMode::MaxContent ||
      (node->getStyle().overflow() != Overflow::Scroll &&
       sizingModeCrossDim == SizingMode::FitContent)) {
    // Clamp the size to the min/max size, if specified, and make sure it
    // doesn't go below the padding and border amount.
    node->setLayoutMeasuredDimension(
        boundAxis(
            node,
            crossAxis,
            totalLineCrossDim + paddingAndBorderAxisCross,
            crossAxisownerSize,
            ownerWidth),
        dimension(crossAxis));

  } else if (
      sizingModeCrossDim == SizingMode::FitContent &&
      node->getStyle().overflow() == Overflow::Scroll) {
    node->setLayoutMeasuredDimension(
        yoga::maxOrDefined(
            yoga::minOrDefined(
                availableInnerCrossDim + paddingAndBorderAxisCross,
                boundAxisWithinMinAndMax(
                    node,
                    crossAxis,
                    FloatOptional{
                        totalLineCrossDim + paddingAndBorderAxisCross},
                    crossAxisownerSize)
                    .unwrap()),
            paddingAndBorderAxisCross),
        dimension(crossAxis));
  }

  // As we only wrapped in normal direction yet, we need to reverse the
  // positions on wrap-reverse.
  if (performLayout && node->getStyle().flexWrap() == Wrap::WrapReverse) {
    for (size_t i = 0; i < childCount; i++) {
      const auto child = node->getChild(i);
      if (child->getStyle().positionType() != PositionType::Absolute) {
        child->setLayoutPosition(
            node->getLayout().measuredDimension(dimension(crossAxis)) -
                child->getLayout().position(flexStartEdge(crossAxis)) -
                child->getLayout().measuredDimension(dimension(crossAxis)),
            flexStartEdge(crossAxis));
      }
    }
  }

  if (performLayout) {
    // STEP 10: SIZING AND POSITIONING ABSOLUTE CHILDREN
    if (!node->hasErrata(Errata::PositionStaticBehavesLikeRelative)) {
      // Let the containing block layout its absolute descendants. By definition
      // the containing block will not be static unless we are at the root.
      if (node->getStyle().positionType() != PositionType::Static ||
          depth == 1) {
        layoutAbsoluteDescendants(
            node,
            node,
            isMainAxisRow ? sizingModeMainDim : sizingModeCrossDim,
            direction,
            layoutMarkerData,
            depth,
            generationCount,
            0.0f,
            0.0f);
      }
    } else {
      for (auto child : node->getChildren()) {
        if (child->getStyle().display() == Display::None ||
            child->getStyle().positionType() != PositionType::Absolute) {
          continue;
        }
        const bool absolutePercentageAgainstPaddingEdge =
            node->getConfig()->isExperimentalFeatureEnabled(
                ExperimentalFeature::AbsolutePercentageAgainstPaddingEdge);

        layoutAbsoluteChild(
            node,
            node,
            child,
            absolutePercentageAgainstPaddingEdge
                ? node->getLayout().measuredDimension(Dimension::Width)
                : availableInnerWidth,
            absolutePercentageAgainstPaddingEdge
                ? node->getLayout().measuredDimension(Dimension::Height)
                : availableInnerHeight,
            isMainAxisRow ? sizingModeMainDim : sizingModeCrossDim,
            direction,
            layoutMarkerData,
            depth,
            generationCount);
      }
    }

    // STEP 11: SETTING TRAILING POSITIONS FOR CHILDREN
    const bool needsMainTrailingPos = needsTrailingPosition(mainAxis);
    const bool needsCrossTrailingPos = needsTrailingPosition(crossAxis);

    if (needsMainTrailingPos || needsCrossTrailingPos) {
      for (size_t i = 0; i < childCount; i++) {
        const auto child = node->getChild(i);
        // Absolute children will be handled by their containing block since we
        // cannot guarantee that their positions are set when their parents are
        // done with layout.
        if (child->getStyle().display() == Display::None ||
            (!node->hasErrata(Errata::PositionStaticBehavesLikeRelative) &&
             child->getStyle().positionType() == PositionType::Absolute)) {
          continue;
        }
        if (needsMainTrailingPos) {
          setChildTrailingPosition(node, child, mainAxis);
        }

        if (needsCrossTrailingPos) {
          setChildTrailingPosition(node, child, crossAxis);
        }
      }
    }
  }
}

bool gPrintChanges = false;
bool gPrintSkips = false;

static const char* spacer =
    "                                                            ";

static const char* spacerWithLength(const unsigned long level) {
  const size_t spacerLen = strlen(spacer);
  if (level > spacerLen) {
    return &spacer[0];
  } else {
    return &spacer[spacerLen - level];
  }
}

static const char* sizingModeName(
    const SizingMode mode,
    const bool performLayout) {
  switch (mode) {
    case SizingMode::MaxContent:
      return performLayout ? "LAY_UNDEFINED" : "UNDEFINED";
    case SizingMode::StretchFit:
      return performLayout ? "LAY_EXACTLY" : "EXACTLY";
    case SizingMode::FitContent:
      return performLayout ? "LAY_AT_MOST" : "AT_MOST";
  }
  return "";
}

//
// This is a wrapper around the calculateLayoutImpl function. It determines
// whether the layout request is redundant and can be skipped.
//
// Parameters:
//  Input parameters are the same as calculateLayoutImpl (see above)
//  Return parameter is true if layout was performed, false if skipped
//
bool calculateLayoutInternal(
    yoga::Node* const node,
    const float availableWidth,
    const float availableHeight,
    const Direction ownerDirection,
    const SizingMode widthSizingMode,
    const SizingMode heightSizingMode,
    const float ownerWidth,
    const float ownerHeight,
    const bool performLayout,
    const LayoutPassReason reason,
    LayoutData& layoutMarkerData,
    uint32_t depth,
    const uint32_t generationCount) {
  LayoutResults* layout = &node->getLayout();

  depth++;

  const bool needToVisitNode =
      (node->isDirty() && layout->generationCount != generationCount) ||
      layout->lastOwnerDirection != ownerDirection;

  if (needToVisitNode) {
    // Invalidate the cached results.
    layout->nextCachedMeasurementsIndex = 0;
    layout->cachedLayout.availableWidth = -1;
    layout->cachedLayout.availableHeight = -1;
    layout->cachedLayout.widthSizingMode = SizingMode::MaxContent;
    layout->cachedLayout.heightSizingMode = SizingMode::MaxContent;
    layout->cachedLayout.computedWidth = -1;
    layout->cachedLayout.computedHeight = -1;
  }

  CachedMeasurement* cachedResults = nullptr;

  // Determine whether the results are already cached. We maintain a separate
  // cache for layouts and measurements. A layout operation modifies the
  // positions and dimensions for nodes in the subtree. The algorithm assumes
  // that each node gets laid out a maximum of one time per tree layout, but
  // multiple measurements may be required to resolve all of the flex
  // dimensions. We handle nodes with measure functions specially here because
  // they are the most expensive to measure, so it's worth avoiding redundant
  // measurements if at all possible.
  if (node->hasMeasureFunc()) {
    const float marginAxisRow =
        node->getMarginForAxis(FlexDirection::Row, ownerWidth);
    const float marginAxisColumn =
        node->getMarginForAxis(FlexDirection::Column, ownerWidth);

    // First, try to use the layout cache.
    if (canUseCachedMeasurement(
            widthSizingMode,
            availableWidth,
            heightSizingMode,
            availableHeight,
            layout->cachedLayout.widthSizingMode,
            layout->cachedLayout.availableWidth,
            layout->cachedLayout.heightSizingMode,
            layout->cachedLayout.availableHeight,
            layout->cachedLayout.computedWidth,
            layout->cachedLayout.computedHeight,
            marginAxisRow,
            marginAxisColumn,
            node->getConfig())) {
      cachedResults = &layout->cachedLayout;
    } else {
      // Try to use the measurement cache.
      for (size_t i = 0; i < layout->nextCachedMeasurementsIndex; i++) {
        if (canUseCachedMeasurement(
                widthSizingMode,
                availableWidth,
                heightSizingMode,
                availableHeight,
                layout->cachedMeasurements[i].widthSizingMode,
                layout->cachedMeasurements[i].availableWidth,
                layout->cachedMeasurements[i].heightSizingMode,
                layout->cachedMeasurements[i].availableHeight,
                layout->cachedMeasurements[i].computedWidth,
                layout->cachedMeasurements[i].computedHeight,
                marginAxisRow,
                marginAxisColumn,
                node->getConfig())) {
          cachedResults = &layout->cachedMeasurements[i];
          break;
        }
      }
    }
  } else if (performLayout) {
    if (yoga::inexactEquals(
            layout->cachedLayout.availableWidth, availableWidth) &&
        yoga::inexactEquals(
            layout->cachedLayout.availableHeight, availableHeight) &&
        layout->cachedLayout.widthSizingMode == widthSizingMode &&
        layout->cachedLayout.heightSizingMode == heightSizingMode) {
      cachedResults = &layout->cachedLayout;
    }
  } else {
    for (uint32_t i = 0; i < layout->nextCachedMeasurementsIndex; i++) {
      if (yoga::inexactEquals(
              layout->cachedMeasurements[i].availableWidth, availableWidth) &&
          yoga::inexactEquals(
              layout->cachedMeasurements[i].availableHeight, availableHeight) &&
          layout->cachedMeasurements[i].widthSizingMode == widthSizingMode &&
          layout->cachedMeasurements[i].heightSizingMode == heightSizingMode) {
        cachedResults = &layout->cachedMeasurements[i];
        break;
      }
    }
  }

  if (!needToVisitNode && cachedResults != nullptr) {
    layout->setMeasuredDimension(
        Dimension::Width, cachedResults->computedWidth);
    layout->setMeasuredDimension(
        Dimension::Height, cachedResults->computedHeight);

    (performLayout ? layoutMarkerData.cachedLayouts
                   : layoutMarkerData.cachedMeasures) += 1;

    if (gPrintChanges && gPrintSkips) {
      yoga::log(
          node,
          LogLevel::Verbose,
          "%s%d.{[skipped] ",
          spacerWithLength(depth),
          depth);
      node->print();
      yoga::log(
          node,
          LogLevel::Verbose,
          "wm: %s, hm: %s, aw: %f ah: %f => d: (%f, %f) %s\n",
          sizingModeName(widthSizingMode, performLayout),
          sizingModeName(heightSizingMode, performLayout),
          availableWidth,
          availableHeight,
          cachedResults->computedWidth,
          cachedResults->computedHeight,
          LayoutPassReasonToString(reason));
    }
  } else {
    if (gPrintChanges) {
      yoga::log(
          node,
          LogLevel::Verbose,
          "%s%d.{%s",
          spacerWithLength(depth),
          depth,
          needToVisitNode ? "*" : "");
      node->print();
      yoga::log(
          node,
          LogLevel::Verbose,
          "wm: %s, hm: %s, aw: %f ah: %f %s\n",
          sizingModeName(widthSizingMode, performLayout),
          sizingModeName(heightSizingMode, performLayout),
          availableWidth,
          availableHeight,
          LayoutPassReasonToString(reason));
    }

    calculateLayoutImpl(
        node,
        availableWidth,
        availableHeight,
        ownerDirection,
        widthSizingMode,
        heightSizingMode,
        ownerWidth,
        ownerHeight,
        performLayout,
        layoutMarkerData,
        depth,
        generationCount,
        reason);

    if (gPrintChanges) {
      yoga::log(
          node,
          LogLevel::Verbose,
          "%s%d.}%s",
          spacerWithLength(depth),
          depth,
          needToVisitNode ? "*" : "");
      node->print();
      yoga::log(
          node,
          LogLevel::Verbose,
          "wm: %s, hm: %s, d: (%f, %f) %s\n",
          sizingModeName(widthSizingMode, performLayout),
          sizingModeName(heightSizingMode, performLayout),
          layout->measuredDimension(Dimension::Width),
          layout->measuredDimension(Dimension::Height),
          LayoutPassReasonToString(reason));
    }

    layout->lastOwnerDirection = ownerDirection;

    if (cachedResults == nullptr) {
      layoutMarkerData.maxMeasureCache = std::max(
          layoutMarkerData.maxMeasureCache,
          layout->nextCachedMeasurementsIndex + 1u);

      if (layout->nextCachedMeasurementsIndex ==
          LayoutResults::MaxCachedMeasurements) {
        if (gPrintChanges) {
          yoga::log(node, LogLevel::Verbose, "Out of cache entries!\n");
        }
        layout->nextCachedMeasurementsIndex = 0;
      }

      CachedMeasurement* newCacheEntry;
      if (performLayout) {
        // Use the single layout cache entry.
        newCacheEntry = &layout->cachedLayout;
      } else {
        // Allocate a new measurement cache entry.
        newCacheEntry =
            &layout->cachedMeasurements[layout->nextCachedMeasurementsIndex];
        layout->nextCachedMeasurementsIndex++;
      }

      newCacheEntry->availableWidth = availableWidth;
      newCacheEntry->availableHeight = availableHeight;
      newCacheEntry->widthSizingMode = widthSizingMode;
      newCacheEntry->heightSizingMode = heightSizingMode;
      newCacheEntry->computedWidth =
          layout->measuredDimension(Dimension::Width);
      newCacheEntry->computedHeight =
          layout->measuredDimension(Dimension::Height);
    }
  }

  if (performLayout) {
    node->setLayoutDimension(
        node->getLayout().measuredDimension(Dimension::Width),
        Dimension::Width);
    node->setLayoutDimension(
        node->getLayout().measuredDimension(Dimension::Height),
        Dimension::Height);

    node->setHasNewLayout(true);
    node->setDirty(false);
  }

  layout->generationCount = generationCount;

  LayoutType layoutType;
  if (performLayout) {
    layoutType = !needToVisitNode && cachedResults == &layout->cachedLayout
        ? LayoutType::kCachedLayout
        : LayoutType::kLayout;
  } else {
    layoutType = cachedResults != nullptr ? LayoutType::kCachedMeasure
                                          : LayoutType::kMeasure;
  }
  Event::publish<Event::NodeLayout>(node, {layoutType});

  return (needToVisitNode || cachedResults == nullptr);
}

void calculateLayout(
    yoga::Node* const node,
    const float ownerWidth,
    const float ownerHeight,
    const Direction ownerDirection) {
  Event::publish<Event::LayoutPassStart>(node);
  LayoutData markerData = {};

  // Increment the generation count. This will force the recursive routine to
  // visit all dirty nodes at least once. Subsequent visits will be skipped if
  // the input parameters don't change.
  gCurrentGenerationCount.fetch_add(1, std::memory_order_relaxed);
  node->resolveDimension();
  float width = YGUndefined;
  SizingMode widthSizingMode = SizingMode::MaxContent;
  const auto& style = node->getStyle();
  if (node->styleDefinesDimension(FlexDirection::Row, ownerWidth)) {
    width =
        (yoga::resolveValue(
             node->getResolvedDimension(dimension(FlexDirection::Row)),
             ownerWidth)
             .unwrap() +
         node->getMarginForAxis(FlexDirection::Row, ownerWidth));
    widthSizingMode = SizingMode::StretchFit;
  } else if (yoga::resolveValue(
                 style.maxDimension(Dimension::Width), ownerWidth)
                 .isDefined()) {
    width = yoga::resolveValue(style.maxDimension(Dimension::Width), ownerWidth)
                .unwrap();
    widthSizingMode = SizingMode::FitContent;
  } else {
    width = ownerWidth;
    widthSizingMode = yoga::isUndefined(width) ? SizingMode::MaxContent
                                               : SizingMode::StretchFit;
  }

  float height = YGUndefined;
  SizingMode heightSizingMode = SizingMode::MaxContent;
  if (node->styleDefinesDimension(FlexDirection::Column, ownerHeight)) {
    height =
        (yoga::resolveValue(
             node->getResolvedDimension(dimension(FlexDirection::Column)),
             ownerHeight)
             .unwrap() +
         node->getMarginForAxis(FlexDirection::Column, ownerWidth));
    heightSizingMode = SizingMode::StretchFit;
  } else if (yoga::resolveValue(
                 style.maxDimension(Dimension::Height), ownerHeight)
                 .isDefined()) {
    height =
        yoga::resolveValue(style.maxDimension(Dimension::Height), ownerHeight)
            .unwrap();
    heightSizingMode = SizingMode::FitContent;
  } else {
    height = ownerHeight;
    heightSizingMode = yoga::isUndefined(height) ? SizingMode::MaxContent
                                                 : SizingMode::StretchFit;
  }
  if (calculateLayoutInternal(
          node,
          width,
          height,
          ownerDirection,
          widthSizingMode,
          heightSizingMode,
          ownerWidth,
          ownerHeight,
          true,
          LayoutPassReason::kInitial,
          markerData,
          0, // tree root
          gCurrentGenerationCount.load(std::memory_order_relaxed))) {
    node->setPosition(
        node->getLayout().direction(), ownerWidth, ownerHeight, ownerWidth);
    roundLayoutResultsToPixelGrid(node, 0.0f, 0.0f);

#ifdef DEBUG
    if (node->getConfig()->shouldPrintTree()) {
      yoga::print(
          node,
          PrintOptions::Layout | PrintOptions::Children | PrintOptions::Style);
    }
#endif
  }

  Event::publish<Event::LayoutPassEnd>(node, {&markerData});
}

} // namespace facebook::yoga
