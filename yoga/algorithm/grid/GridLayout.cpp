/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
*/

#include <yoga/algorithm/grid/GridLayout.h>
#include <yoga/algorithm/grid/CalculateAvailableInnerDimension.h>
#include <yoga/algorithm/BoundAxis.h>
#include <yoga/algorithm/grid/TrackSizing.h>
#include <yoga/algorithm/AbsoluteLayout.h>

namespace facebook::yoga {

  
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

static void cleanupContentsNodesRecursively(yoga::Node* const node) {
  if (node->hasContentsChildren()) [[unlikely]] {
    node->cloneContentsChildrenIfNeeded();
    for (auto child : node->getChildren()) {
      if (child->style().display() == Display::Contents) {
        child->getLayout() = {};
        child->setLayoutDimension(0, Dimension::Width);
        child->setLayoutDimension(0, Dimension::Height);
        child->setHasNewLayout(true);
        child->setDirty(false);
        child->cloneChildrenIfNeeded();

        cleanupContentsNodesRecursively(child);
      }
    }
  }
}

// Follows - https://www.w3.org/TR/css-grid-1/#layout-algorithm
void calculateGridLayoutInternal(Node* node,
                                float availableWidth,
                                float availableHeight,
                                Direction ownerDirection,
                                SizingMode widthSizingMode,
                                SizingMode heightSizingMode,
                                float ownerWidth,
                                float ownerHeight,
                                bool performLayout,
                                LayoutPassReason reason,
                                LayoutData& layoutMarkerData,
                                uint32_t depth,
                                uint32_t generationCount) {

  // Step 1: Run the Grid Item Placement Algorithm to resolve the placement of all grid items in the grid.
  auto autoPlacement = ResolvedAutoPlacement::resolveGridItemPlacements(node);
  // Create the grid tracks (auto and explicit = implicit grid)
  auto gridTracks = createGridTracks(node, autoPlacement);

  // Step 2: Find the size of the grid container, per § 5.2 Sizing Grid Containers.
  // Note: During this phase, cyclic <percentage>s in track sizes are treated as auto.
  const Direction direction = node->resolveDirection(ownerDirection);
  const float marginInline = node->style().computeMarginForAxis(FlexDirection::Row, ownerWidth);
  const float marginBlock = node->style().computeMarginForAxis(FlexDirection::Column, ownerWidth);
  const float paddingAndBorderInline = paddingAndBorderForAxis(node, FlexDirection::Row, direction, ownerWidth);
  const float paddingAndBorderBlock = paddingAndBorderForAxis(node, FlexDirection::Column, direction, ownerWidth);
  
  const float availableInnerWidth = calculateAvailableInnerDimension(
                                                              node,
                                                              direction,
                                                              Dimension::Width,
                                                              availableWidth - marginInline,
                                                              paddingAndBorderInline,
                                                              ownerWidth,
                                                              ownerWidth);
  const float availableInnerHeight = calculateAvailableInnerDimension(
                                                                node,
                                                                direction,
                                                                Dimension::Height,
                                                                availableHeight - marginBlock,
                                                                paddingAndBorderBlock,
                                                                ownerHeight,
                                                                ownerWidth);

  auto widthIsDefinite = (widthSizingMode == SizingMode::StretchFit &&
    yoga::isDefined(availableWidth));
  auto heightIsDefinite = (heightSizingMode == SizingMode::StretchFit &&
     yoga::isDefined(availableHeight));

  float containerInnerWidth = widthIsDefinite ? availableInnerWidth : YGUndefined;
  float containerInnerHeight = heightIsDefinite ? availableInnerHeight : YGUndefined;
  auto rowTracks = gridTracks.rowTracks;
  auto columnTracks = gridTracks.columnTracks;
  auto itemAreas = autoPlacement.gridItemAreas;

  if (!widthIsDefinite || !heightIsDefinite) {
    auto trackSizing = TrackSizing(
      node,
      columnTracks,
      rowTracks,
      containerInnerWidth,
      containerInnerHeight,
      itemAreas,
      widthSizingMode,
      heightSizingMode,
      direction,
      ownerWidth,
      ownerHeight,
      layoutMarkerData,
      depth,
      generationCount);

    if (!widthIsDefinite) {
      trackSizing.runTrackSizing(Dimension::Width);
      auto totalTrackWidth = trackSizing.getTotalBaseSize(Dimension::Width);
      containerInnerWidth = boundAxis(
        node,
        FlexDirection::Row,
        direction,
        totalTrackWidth,
        ownerWidth,
        ownerWidth);
    }

    if (!heightIsDefinite) {
      // run the track sizing with width first because row track sizing depends on column track base sizes
      trackSizing.runTrackSizing(Dimension::Width);
      trackSizing.runTrackSizing(Dimension::Height);
      auto totalTrackHeight = trackSizing.getTotalBaseSize(Dimension::Height);
      containerInnerHeight = boundAxis(
        node,
        FlexDirection::Column,
        direction,
        totalTrackHeight,
        ownerHeight,
        ownerWidth);
    }
  }

  // Step 3: Given the resulting grid container size, run the Grid Sizing Algorithm to size the grid.
  // Run track sizing with the new container dimensions
  // Note: During this phase, <percentage>s in track sizes are resolved against the grid container size.
  auto trackSizing = TrackSizing(
    node,
    columnTracks, 
    rowTracks, 
    containerInnerWidth,
    containerInnerHeight, 
    itemAreas,
    widthSizingMode,
    heightSizingMode,
    direction,
    ownerWidth,
    ownerHeight,
    layoutMarkerData,
    depth,
    generationCount);

  // https://www.w3.org/TR/css-grid-1/#algo-grid-sizing
  trackSizing.runTrackSizing(Dimension::Width);
  trackSizing.runTrackSizing(Dimension::Height);

  node->setLayoutMeasuredDimension(
    boundAxis(
        node,
        FlexDirection::Row,
        direction,
        containerInnerWidth + paddingAndBorderInline,
        ownerWidth,
        ownerWidth),
    Dimension::Width);

  node->setLayoutMeasuredDimension(
    boundAxis(
        node,
        FlexDirection::Column,
        direction,
        containerInnerHeight + paddingAndBorderBlock,
        ownerHeight,
        ownerWidth),
    Dimension::Height);

  
  // Layout grid items
  // Step 4: Lay out the grid items into their respective containing blocks. Each grid area’s width and height are considered definite for this purpose.
  if (performLayout) {
    auto gridWidth = trackSizing.getTotalBaseSize(Dimension::Width);
    auto gridHeight = trackSizing.getTotalBaseSize(Dimension::Height);

    auto columnGap = node->style().computeGapForDimension(Dimension::Width, containerInnerWidth);
    auto rowGap = node->style().computeGapForDimension(Dimension::Height, containerInnerHeight);

    float leadingPaddingAndBorderInline = node->style().computeInlineStartPadding(FlexDirection::Row, direction, ownerWidth) +
      node->style().computeInlineStartBorder(FlexDirection::Row, direction);
    float trailingPaddingAndBorderInline = node->style().computeInlineEndPaddingAndBorder(FlexDirection::Row, direction, ownerWidth);
    float leadingPaddingAndBorderBlock = node->style().computeInlineStartPadding(FlexDirection::Column, direction, ownerWidth) +
      node->style().computeInlineStartBorder(FlexDirection::Column, direction);

    float gridInlineOffset = 0.0f;
    float betweenInlineOffset = 0.0f;
    float freeSpaceInlineAxis = containerInnerWidth - gridWidth;
    if (!yoga::inexactEquals(freeSpaceInlineAxis, 0.0f)) {
      auto justifyContent = node->style().justifyContent();
      size_t numColumnTracks = columnTracks.size();
  
      switch (justifyContent) {
        case Justify::Center:
          gridInlineOffset = freeSpaceInlineAxis / 2.0f;
          break;
        case Justify::End:
          gridInlineOffset = freeSpaceInlineAxis;
          break;
        case Justify::SpaceBetween:
          if (numColumnTracks > 1) {
            betweenInlineOffset = freeSpaceInlineAxis / (numColumnTracks - 1);
          }
          break;
        case Justify::SpaceAround:
          if (numColumnTracks > 0) {
            betweenInlineOffset = freeSpaceInlineAxis / numColumnTracks;
            gridInlineOffset = betweenInlineOffset / 2.0f;
          }
          break;
        case Justify::SpaceEvenly:
          if (numColumnTracks > 0) {
            betweenInlineOffset = freeSpaceInlineAxis / (numColumnTracks + 1);
            gridInlineOffset = betweenInlineOffset;
          }
          break;
        case Justify::Start:
        case Justify::FlexStart:
        case Justify::FlexEnd:
        case Justify::Stretch:
        case Justify::Auto:
        default:
          break;
      }
    }
  
    float gridBlockOffset = 0.0f;
    float betweenBlockOffset = 0.0f;
    float freeSpaceBlockAxis = containerInnerHeight - gridHeight;
    printf("freeSpaceBlockAxis: %f\n", freeSpaceBlockAxis);
    if (!yoga::inexactEquals(freeSpaceBlockAxis, 0.0f)) {
      auto alignContent = node->style().alignContent();
      size_t numRowTracks = rowTracks.size();
  
      switch (alignContent) {
        case Align::Center:
          // content center works with negative free space too
          // refer grid_align_content_center_negative_space_gap fixture
          gridBlockOffset = freeSpaceBlockAxis / 2.0f;
          break;
        case Align::End:
          gridBlockOffset = freeSpaceBlockAxis;
          break;
        case Align::SpaceBetween:
          if (numRowTracks > 1) {
            // negative free space is not distributed with space between, checkout grid_align_content_space_between_negative_space_gap fixture
            betweenBlockOffset = std::max(0.0f, freeSpaceBlockAxis / (numRowTracks - 1));
          }
          break;
        case Align::SpaceAround:
          if (numRowTracks > 0) {
            // negative free space is not distributed with space around, checkout grid_align_content_space_around_negative_space_gap fixture
            betweenBlockOffset = std::max(0.0f, freeSpaceBlockAxis / numRowTracks);
            gridBlockOffset = std::max(0.0f, betweenBlockOffset / 2.0f);
          }
          break;
        case Align::SpaceEvenly:
          if (numRowTracks > 0) {
            betweenBlockOffset = std::max(0.0f, freeSpaceBlockAxis / (numRowTracks + 1));
            gridBlockOffset = betweenBlockOffset;
          }
          break;
        case Align::Start:
        case Align::FlexStart:
        case Align::FlexEnd:
        case Align::Stretch:
        case Align::Baseline:
        case Align::Auto:
        default:
          break;
      }
    }
  
    for (auto& item : itemAreas) {
      auto [containingBlockWidth, containingBlockHeight] = trackSizing.getContainingBlockSizeForItem(item);
      float gridAreaLeft = 0.0f;
      for (size_t i = 0; i < item.columnStart && i < columnTracks.size(); i++) {
        gridAreaLeft += columnTracks[i].baseSize;
        if (i < columnTracks.size() - 1) {
          // Add both explicit gap and content-distribution spacing
          gridAreaLeft += columnGap + betweenInlineOffset;
        }
      }

      float gridAreaTop = 0.0f;
      for (size_t i = 0; i < item.rowStart && i < rowTracks.size(); i++) {
        gridAreaTop += rowTracks[i].baseSize;
        if (i < rowTracks.size() - 1) {
          // Add both explicit gap and content-distribution spacing
          gridAreaTop += rowGap + betweenBlockOffset;
        }
      }

      const auto marginInlineStart = item.node->style().computeInlineStartMargin(FlexDirection::Row, direction, containingBlockWidth);
      const auto marginInlineEnd = item.node->style().computeInlineEndMargin(FlexDirection::Row, direction, containingBlockWidth);
      const auto marginBlockStart = item.node->style().computeInlineStartMargin(FlexDirection::Column, direction, containingBlockWidth);
      const auto marginBlockEnd = item.node->style().computeInlineEndMargin(FlexDirection::Column, direction, containingBlockWidth);

      auto justifySelf = item.node->style().justifySelf();
      if (justifySelf == Justify::Auto) {
        justifySelf = node->style().justifyItems();
      }

      auto alignSelf = item.node->style().alignSelf();
      if (alignSelf == Align::Auto) {
        alignSelf = node->style().alignItems();
      }
      
      SizingMode childWidthSizingMode = SizingMode::StretchFit;
      SizingMode childHeightSizingMode = SizingMode::StretchFit;
      float childWidth = containingBlockWidth;
      float childHeight = containingBlockHeight;

      // https://www.w3.org/TR/css-grid-1/#alignment
      // if justify-self or align-self compute to a value other than stretch or margins are auto, 
      // grid items will auto-size to fit their content.
      bool hasMarginInlineAuto = item.node->style().flexStartMarginIsAuto(FlexDirection::Row, direction) 
        || item.node->style().flexEndMarginIsAuto(FlexDirection::Row, direction);
      if (justifySelf != Justify::Stretch || hasMarginInlineAuto) {
        childWidthSizingMode = SizingMode::FitContent;
      }

      bool hasMarginBlockAuto = item.node->style().flexStartMarginIsAuto(FlexDirection::Column, direction) 
        || item.node->style().flexEndMarginIsAuto(FlexDirection::Column, direction);
      if (alignSelf != Align::Stretch || hasMarginBlockAuto) {
        childHeightSizingMode = SizingMode::FitContent;
      }
      
      if (item.node->hasDefiniteLength(Dimension::Width, containingBlockWidth)) {
        childWidth = item.node->getResolvedDimension(
            direction,
            dimension(FlexDirection::Row),
            containingBlockWidth,
            containingBlockWidth).unwrap() + marginInlineStart + marginInlineEnd;
        childWidthSizingMode = SizingMode::StretchFit;
      }

      if (item.node->hasDefiniteLength(Dimension::Height, containingBlockHeight)) {
        childHeight = item.node->getResolvedDimension(
            direction,
            dimension(FlexDirection::Column),
            containingBlockHeight,
            containingBlockWidth).unwrap() + marginBlockStart + marginBlockEnd;
        childHeightSizingMode = SizingMode::StretchFit;
      }

      const auto& childStyle = item.node->style();
      if (childStyle.aspectRatio().isDefined()) {
        // https://drafts.csswg.org/css-sizing-4/#aspect-ratio
        // a non-replaced absolutely-positioned box treats justify-self: normal as stretch, not as start (CSS Box Alignment 3 § 6.1.2 Absolutely-Positioned Boxes), even if it has a preferred aspect ratio
        // i.e. aspect ratio is only applied when item is not stretch aligned or margin is auto (auto margin items are not stretched) 
        if (childWidthSizingMode == SizingMode::StretchFit &&
            childHeightSizingMode != SizingMode::StretchFit && (alignSelf != Align::Stretch || hasMarginBlockAuto)) {
          if (!yoga::inexactEquals(childStyle.aspectRatio().unwrap(), 0.0f)) {
            childHeight = marginBlockStart + marginBlockEnd +
            (childWidth - marginInlineStart - marginInlineEnd) / childStyle.aspectRatio().unwrap();
            childHeightSizingMode = SizingMode::StretchFit;
          }
        } else if (childHeightSizingMode == SizingMode::StretchFit &&
                   childWidthSizingMode != SizingMode::StretchFit && (justifySelf != Justify::Stretch || hasMarginInlineAuto)) {
          childWidth = marginInlineStart + marginInlineEnd +
              (childHeight - marginBlockStart - marginBlockEnd) * childStyle.aspectRatio().unwrap();
          childWidthSizingMode = SizingMode::StretchFit;
        }
      }

      calculateLayoutInternal(
          item.node,
          childWidth,
          childHeight,
          direction,
          childWidthSizingMode,
          childHeightSizingMode,
          containingBlockWidth,
          containingBlockHeight,
          true,
          LayoutPassReason::kGridLayout,
          layoutMarkerData,
          depth,
          generationCount);

      // since we know the item width and grid width, we can do the alignment here.
      // alignment of grid items happen in the grid area
      // measured dimension includes padding and border
      float actualItemWidth = item.node->getLayout().measuredDimension(Dimension::Width);
      auto freeSpaceInlineAxisItem = containingBlockWidth - actualItemWidth - marginInlineStart - marginInlineEnd;
      float leftAutoMarginOffset = 0.0f;
      float rightAutoMarginOffset = 0.0f;
      // https://www.w3.org/TR/css-grid-1/#auto-margins
      // auto margins in either axis absorb positive free space prior to alignment via the box alignment properties, thereby disabling the effects of any self-alignment properties in that axis.
      if (item.node->style().flexStartMarginIsAuto(FlexDirection::Row, direction) 
          && item.node->style().flexEndMarginIsAuto(FlexDirection::Row, direction)) {
        leftAutoMarginOffset = freeSpaceInlineAxisItem / 2;
        rightAutoMarginOffset = freeSpaceInlineAxisItem / 2;
        freeSpaceInlineAxisItem = 0.0f;
      } else if (item.node->style().flexStartMarginIsAuto(FlexDirection::Row, direction)) {
        leftAutoMarginOffset = freeSpaceInlineAxisItem;
        freeSpaceInlineAxisItem = 0.0f;
      } else if (item.node->style().flexEndMarginIsAuto(FlexDirection::Row, direction)) {
        rightAutoMarginOffset = freeSpaceInlineAxisItem;
        freeSpaceInlineAxisItem = 0.0f;
      }
      
      float justifySelfOffset = 0.0f;
      if (justifySelf == Justify::End) {
        justifySelfOffset = freeSpaceInlineAxisItem;
      } else if (justifySelf == Justify::Center) {
        justifySelfOffset = freeSpaceInlineAxisItem / 2;
      }
      
      float finalLeft;
      if (direction == Direction::RTL) {
        finalLeft = containerInnerWidth + trailingPaddingAndBorderInline - gridAreaLeft - actualItemWidth - marginInlineStart - rightAutoMarginOffset - justifySelfOffset - gridInlineOffset;
      } else {
        finalLeft = gridAreaLeft + marginInlineStart + leftAutoMarginOffset + justifySelfOffset + gridInlineOffset + leadingPaddingAndBorderInline;
      }

      item.node->setLayoutPosition(finalLeft, PhysicalEdge::Left);

      float actualItemHeight = item.node->getLayout().measuredDimension(Dimension::Height);
      auto freeSpaceBlockAxisItem = containingBlockHeight - actualItemHeight - marginBlockStart - marginBlockEnd;
      float topAutoMarginOffset = 0.0f;
      if (item.node->style().flexStartMarginIsAuto(FlexDirection::Column, direction) 
            && item.node->style().flexEndMarginIsAuto(FlexDirection::Column, direction)) {
        topAutoMarginOffset = freeSpaceBlockAxisItem / 2;
        freeSpaceBlockAxisItem = 0.0f;
      } else if (item.node->style().flexStartMarginIsAuto(FlexDirection::Column, direction)) {
        topAutoMarginOffset = freeSpaceBlockAxisItem;
        freeSpaceBlockAxisItem = 0.0f;
      } else if (item.node->style().flexEndMarginIsAuto(FlexDirection::Column, direction)) {
        freeSpaceBlockAxisItem = 0.0f;
      }

      float alignSelfOffset = 0.0f;
      if (alignSelf == Align::End) {
        alignSelfOffset = freeSpaceBlockAxisItem;
      } else if (alignSelf == Align::Center) {
        alignSelfOffset = freeSpaceBlockAxisItem / 2;
      }

      float finalTop = gridAreaTop + marginBlockStart + topAutoMarginOffset + alignSelfOffset + gridBlockOffset + leadingPaddingAndBorderBlock;

      item.node->setLayoutPosition(finalTop, PhysicalEdge::Top);
    }
    
    // Perform layout of absolute children
    // https://www.w3.org/TR/css-grid-1/#abspos
    // TODO: support grid-[row|column]-[start|end] as containing blocks
    if (node->style().positionType() != PositionType::Static ||
        node->alwaysFormsContainingBlock() || depth == 1) {
      for (auto child : node->getLayoutChildren()) {
        if (child->style().display() == Display::None) {
          zeroOutLayoutRecursively(child);
          child->setHasNewLayout(true);
          child->setDirty(false);
          continue;
        }

        if (child->style().positionType() == PositionType::Absolute) {
          child->processDimensions();
        }
      }

      layoutAbsoluteDescendants(
          node,
          node,
          widthSizingMode,
          direction,
          layoutMarkerData,
          depth,
          generationCount,
          0.0f,
          0.0f,
          availableInnerWidth,
          availableInnerHeight);
    }
  }

  // Clean and update all display: contents nodes with a direct path to the
  // current node as they will not be traversed
  cleanupContentsNodesRecursively(node);
}

GridTracks createGridTracks(yoga::Node* node, const ResolvedAutoPlacement& autoPlacement) {
  auto gridExplicitColumns = node->style().gridTemplateColumns();
  auto gridExplicitRows = node->style().gridTemplateRows();

  std::vector<GridTrackSize> columnTracks;
  std::vector<GridTrackSize> rowTracks;
  columnTracks.reserve(autoPlacement.maxColumnEnd - autoPlacement.minColumnStart);
  rowTracks.reserve(autoPlacement.maxRowEnd - autoPlacement.minRowStart);

  // https://www.w3.org/TR/css-grid-1/#auto-tracks
  auto autoRowTracks = node->style().gridAutoRows().empty() ?
      GridTrackList{GridTrackSize{StyleSizeLength::ofAuto(), StyleSizeLength::ofAuto()}} :
      node->style().gridAutoRows();
  auto autoColumnTracks = node->style().gridAutoColumns().empty() ?
      GridTrackList{GridTrackSize{StyleSizeLength::ofAuto(), StyleSizeLength::ofAuto()}} :
      node->style().gridAutoColumns();
  
  // The last implicit grid track before the explicit grid receives the last specified size, and so on backwards.
  // i.e. The pattern repeats backwards
  auto negativeImplicitGridColumnTrackCount = -autoPlacement.minColumnStart;
  auto autoColumnTracksSize = autoColumnTracks.size();
  for (auto i = 0; i < negativeImplicitGridColumnTrackCount; i++) {
    auto currentColumnTrackIndex = (negativeImplicitGridColumnTrackCount - i - 1) % autoColumnTracksSize;
    auto autoColumnTrack = autoColumnTracks[autoColumnTracksSize - currentColumnTrackIndex - 1];
    columnTracks.push_back(autoColumnTrack);
  }

  for (size_t i = 0; i < gridExplicitColumns.size(); i++) {
    columnTracks.push_back(gridExplicitColumns[i]);
  }

  // The first track after the last explicitly-sized track receives the first specified size
  // i.e. the pattern repeats forwards
  for (size_t i = 0; i < static_cast<size_t>(autoPlacement.maxColumnEnd) - gridExplicitColumns.size(); i++) {
    auto autoColumnTrack = autoColumnTracks[i % autoColumnTracksSize];
    columnTracks.push_back(autoColumnTrack);
  }

  auto negativeImplicitGridRowTrackCount = -autoPlacement.minRowStart;
  auto autoRowTracksSize = autoRowTracks.size();
  for (auto i = 0; i < negativeImplicitGridRowTrackCount; i++) {
    auto currentRowTrackIndex = (negativeImplicitGridRowTrackCount - i - 1) % autoRowTracksSize;
    auto autoRowTrack = autoRowTracks[autoRowTracksSize - currentRowTrackIndex - 1];
    rowTracks.push_back(autoRowTrack);
  }
  for (size_t i = 0; i < gridExplicitRows.size(); i++) {
    rowTracks.push_back(gridExplicitRows[i]);
  }
  for (size_t i = 0; i < static_cast<size_t>(autoPlacement.maxRowEnd) - gridExplicitRows.size(); i++) {
    auto autoRowTrack = autoRowTracks[i % autoRowTracksSize];
    rowTracks.push_back(autoRowTrack);
  }

  return {
    columnTracks,
    rowTracks
  };
}

} // namespace facebook::yoga
