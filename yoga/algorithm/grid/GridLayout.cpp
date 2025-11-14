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

namespace facebook::yoga {

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
  auto autoPlacement = resolveGridItemPlacements(node);
  // Create the grid tracks (auto and explicit = implicit grid)
  auto gridTracks = createGridTracks(node, autoPlacement);

  // Step 2: Find the size of the grid container, per § 5.2 Sizing Grid Containers.
  // Note: During this phase, cyclic <percentage>s in track sizes are treated as auto.
  const Direction direction = node->resolveDirection(ownerDirection);
  const float marginAxisRow = node->style().computeMarginForAxis(FlexDirection::Row, ownerWidth);
  const float marginAxisColumn = node->style().computeMarginForAxis(FlexDirection::Column, ownerWidth);
  const float paddingAndBorderAxisRow = paddingAndBorderForAxis(node, FlexDirection::Row, direction, ownerWidth);
  const float paddingAndBorderAxisColumn = paddingAndBorderForAxis(node, FlexDirection::Column, direction, ownerWidth);
  
  const float availableInnerWidth = calculateAvailableInnerDimension(
                                                              node,
                                                              direction,
                                                              Dimension::Width,
                                                              availableWidth - marginAxisRow,
                                                              paddingAndBorderAxisRow,
                                                              ownerWidth,
                                                              ownerWidth);
  const float availableInnerHeight = calculateAvailableInnerDimension(
                                                                node,
                                                                direction,
                                                                Dimension::Height,
                                                                availableHeight - marginAxisColumn,
                                                                paddingAndBorderAxisColumn,
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
        containerInnerWidth + paddingAndBorderAxisRow,
        ownerWidth,
        ownerWidth),
    Dimension::Width);

  node->setLayoutMeasuredDimension(
    boundAxis(
        node,
        FlexDirection::Column,
        direction,
        containerInnerHeight + paddingAndBorderAxisColumn,
        ownerHeight,
        ownerWidth),
    Dimension::Height);

  
  // Final position
  if (performLayout) {
    auto gridWidth = trackSizing.getTotalBaseSize(Dimension::Width);
    printf("gridWidth=%f\n", gridWidth);
    auto gridHeight = trackSizing.getTotalBaseSize(Dimension::Height);
    printf("gridHeight=%f\n", gridHeight);
    float gridColumnOffset = 0.0f;
    float gridRowOffset = 0.0f;
    float betweenColumnOffset = 0.0f;
    float betweenRowOffset = 0.0f;

    auto columnGap = node->style().computeGapForDimension(Dimension::Width, containerInnerWidth);
    auto rowGap = node->style().computeGapForDimension(Dimension::Height, containerInnerHeight);

    float leadingPaddingAndBorderRow = node->style().computeInlineStartPadding(FlexDirection::Row, direction, ownerWidth) +
      node->style().computeInlineStartBorder(FlexDirection::Row, direction);
    float leadingPaddingAndBorderColumn = node->style().computeInlineStartPadding(FlexDirection::Column, direction, ownerWidth) +
      node->style().computeInlineStartBorder(FlexDirection::Column, direction);

    if (gridWidth < containerInnerWidth) {
      float freeSpace = containerInnerWidth - gridWidth;
      auto justifyContent = node->style().justifyContent();
      size_t numColumnTracks = columnTracks.size();
  
      switch (justifyContent) {
        case Justify::Center:
          gridColumnOffset = freeSpace / 2.0f;
          break;
        case Justify::End:
          gridColumnOffset = freeSpace;
          break;
        case Justify::SpaceBetween:
          if (numColumnTracks > 1) {
            betweenColumnOffset = freeSpace / (numColumnTracks - 1);
          }
          gridColumnOffset = 0.0f;
          break;
        case Justify::SpaceAround:
          if (numColumnTracks > 0) {
            betweenColumnOffset = freeSpace / numColumnTracks;
            gridColumnOffset = betweenColumnOffset / 2.0f;
          }
          break;
        case Justify::SpaceEvenly:
          if (numColumnTracks > 0) {
            betweenColumnOffset = freeSpace / (numColumnTracks + 1);
            gridColumnOffset = betweenColumnOffset;
          }
          break;
        case Justify::Start:
        case Justify::FlexStart:
        case Justify::FlexEnd:
        case Justify::Stretch:
        case Justify::Auto:
        default:
          gridColumnOffset = 0.0f;
          break;
      }
    }
  
    if (gridHeight < containerInnerHeight) {
      float freeSpace = containerInnerHeight - gridHeight;
      auto alignContent = node->style().alignContent();
      size_t numRowTracks = rowTracks.size();
  
      switch (alignContent) {
        case Align::Center:
          gridRowOffset = freeSpace / 2.0f;
          break;
        case Align::End:
          gridRowOffset = freeSpace;
          break;
        case Align::SpaceBetween:
          if (numRowTracks > 1) {
            betweenRowOffset = freeSpace / (numRowTracks - 1);
          }
          gridRowOffset = 0.0f;
          break;
        case Align::SpaceAround:
          if (numRowTracks > 0) {
            betweenRowOffset = freeSpace / numRowTracks;
            gridRowOffset = betweenRowOffset / 2.0f;
          }
          break;
        case Align::SpaceEvenly:
          if (numRowTracks > 0) {
            betweenRowOffset = freeSpace / (numRowTracks + 1);
            gridRowOffset = betweenRowOffset;
          }
          break;
        case Align::Start:
        case Align::FlexStart:
        case Align::FlexEnd:
        case Align::Stretch:
        case Align::Baseline:
        case Align::Auto:
        default:
          gridRowOffset = 0.0f;
          break;
      }
    }
  
    for (auto& item : itemAreas) {
      auto [containingBlockWidth, containingBlockHeight] = trackSizing.getContainingBlockSizeForItem(item);
      float gridAreaLeft = 0.0f;
      for (int i = 0; i < item.columnStart && i < (int)columnTracks.size(); i++) {
        gridAreaLeft += columnTracks[i].baseSize;
        if (i < (int)columnTracks.size() - 1) {
          // Add both explicit gap and content-distribution spacing
          gridAreaLeft += columnGap + betweenColumnOffset;
        }
      }

      float gridAreaTop = 0.0f;
      for (int i = 0; i < item.rowStart && i < (int)rowTracks.size(); i++) {
        gridAreaTop += rowTracks[i].baseSize;
        if (i < (int)rowTracks.size() - 1) {
          // Add both explicit gap and content-distribution spacing
          gridAreaTop += rowGap + betweenRowOffset;
        }
      }

      auto marginInlineStart = item.node->style().computeInlineStartMargin(FlexDirection::Row, direction, containingBlockWidth);
      auto marginInlineEnd = item.node->style().computeInlineEndMargin(FlexDirection::Row, direction, containingBlockWidth);
      auto marginBlockStart = item.node->style().computeInlineStartMargin(FlexDirection::Column, direction, containingBlockHeight);
      auto marginBlockEnd = item.node->style().computeInlineEndMargin(FlexDirection::Column, direction, containingBlockHeight);

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

      // if justify-self or align-self compute to a value other than stretch or margins are auto, 
      // grid items will auto-size to fit their content.
      bool hasMarginInlineAuto = item.node->style().flexStartMarginIsAuto(FlexDirection::Row, direction) || item.node->style().flexEndMarginIsAuto(FlexDirection::Row, direction);
      if (justifySelf != Justify::Stretch || hasMarginInlineAuto) {
        childWidthSizingMode = SizingMode::FitContent;
      }

      bool hasMarginBlockAuto = item.node->style().flexStartMarginIsAuto(FlexDirection::Column, direction) || item.node->style().flexEndMarginIsAuto(FlexDirection::Column, direction);
      if (alignSelf != Align::Stretch || hasMarginBlockAuto) {
        childHeightSizingMode = SizingMode::FitContent;
      }
      
      if (item.node->hasDefiniteLength(Dimension::Width, containingBlockWidth)) {
        childWidth = item.node->getResolvedDimension(
            direction,
            dimension(FlexDirection::Row),
            containingBlockWidth,
            containingBlockWidth
        ).unwrap() + item.node->style().computeMarginForAxis(FlexDirection::Row, containingBlockWidth);
        childWidthSizingMode = SizingMode::StretchFit;
      }

      if (item.node->hasDefiniteLength(Dimension::Height, containingBlockHeight)) {
        childHeight = item.node->getResolvedDimension(
            direction,
            dimension(FlexDirection::Column),
            containingBlockHeight,
            containingBlockWidth
        ).unwrap() + item.node->style().computeMarginForAxis(FlexDirection::Column, containingBlockWidth);
        childHeightSizingMode = SizingMode::StretchFit;
      }
      
      childWidth = boundAxisWithinMinAndMax(
          item.node,
          direction,
          FlexDirection::Row,
          FloatOptional{childWidth},
          containingBlockWidth,
          containingBlockWidth
      ).unwrap();
      
      childHeight = boundAxisWithinMinAndMax(
          item.node,
          direction,
          FlexDirection::Column,
          FloatOptional{childHeight},
          containingBlockHeight,
          containingBlockWidth
      ).unwrap();
      
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
      // TODO: confirm that measured dimension includes padding and border
      float actualItemWidth = item.node->getLayout().measuredDimension(Dimension::Width);
      auto freeSpaceInlineAxis = containingBlockWidth - actualItemWidth - marginInlineStart - marginInlineEnd;
      float leftAutoMarginOffset = 0.0f;
      float rightAutoMarginOffset = 0.0f;
      if (item.node->style().flexStartMarginIsAuto(FlexDirection::Row, direction) 
          && item.node->style().flexEndMarginIsAuto(FlexDirection::Row, direction)) {
        leftAutoMarginOffset = freeSpaceInlineAxis / 2;
        rightAutoMarginOffset = freeSpaceInlineAxis / 2;
        freeSpaceInlineAxis = 0.0f;
      } else if (item.node->style().flexStartMarginIsAuto(FlexDirection::Row, direction)) {
        leftAutoMarginOffset = freeSpaceInlineAxis;
        freeSpaceInlineAxis = 0.0f;
      } else if (item.node->style().flexEndMarginIsAuto(FlexDirection::Row, direction)) {
        rightAutoMarginOffset = freeSpaceInlineAxis;
        freeSpaceInlineAxis = 0.0f;
      }
      
      // Justify self alignment
      float justifySelfOffset = 0.0f;
      if (justifySelf == Justify::Start) {
        justifySelfOffset = 0.0f;
      } else if (justifySelf == Justify::End) {
        justifySelfOffset = freeSpaceInlineAxis;
      } else if (justifySelf == Justify::Center) {
        justifySelfOffset = freeSpaceInlineAxis / 2;
      }
      
      float finalLeft;
      if (direction == Direction::RTL) {
        finalLeft = containerInnerWidth - gridAreaLeft - actualItemWidth - marginInlineStart - rightAutoMarginOffset - justifySelfOffset - gridColumnOffset + leadingPaddingAndBorderRow;
      } else {
        finalLeft = gridAreaLeft + marginInlineStart + leftAutoMarginOffset + justifySelfOffset + gridColumnOffset + leadingPaddingAndBorderRow;
      }

      item.node->setLayoutPosition(finalLeft, PhysicalEdge::Left);

      float actualItemHeight = item.node->getLayout().measuredDimension(Dimension::Height);
      auto freeSpaceBlockAxis = containingBlockHeight - actualItemHeight - marginBlockStart - marginBlockEnd;
      float topAutoMarginOffset = 0.0f;
      if (item.node->style().flexStartMarginIsAuto(FlexDirection::Column, direction) 
          && item.node->style().flexEndMarginIsAuto(FlexDirection::Column, direction)) {
        topAutoMarginOffset = freeSpaceBlockAxis / 2;
        freeSpaceBlockAxis = 0.0f;
      } else if (item.node->style().flexStartMarginIsAuto(FlexDirection::Column, direction)) {
        topAutoMarginOffset = freeSpaceBlockAxis;
        freeSpaceBlockAxis = 0.0f;
      } else if (item.node->style().flexEndMarginIsAuto(FlexDirection::Column, direction)) {
        freeSpaceBlockAxis = 0.0f;
      }

      float alignSelfOffset = 0.0f;
      if (alignSelf == Align::Start) {
        alignSelfOffset = 0.0f;
      } else if (alignSelf == Align::End) {
        alignSelfOffset = freeSpaceBlockAxis;
      } else if (alignSelf == Align::Center) {
        alignSelfOffset = freeSpaceBlockAxis / 2;
      }

      float finalTop = gridAreaTop + marginBlockStart + topAutoMarginOffset + alignSelfOffset + gridRowOffset + leadingPaddingAndBorderColumn;

      item.node->setLayoutPosition(finalTop, PhysicalEdge::Top);
    }
  }
}

GridTracks createGridTracks(yoga::Node* node, const AutoPlacement& autoPlacement) {
  auto gridExplicitColumns = node->style().gridTemplateColumns();
  auto gridExplicitRows = node->style().gridTemplateRows();

  std::vector<GridTrackSize> columnTracks;
  std::vector<GridTrackSize> rowTracks;
  columnTracks.reserve(autoPlacement.maxColumnEnd - autoPlacement.minColumnStart);
  rowTracks.reserve(autoPlacement.maxRowEnd - autoPlacement.minRowStart);

  // TODO: add grid auto columns and rows support here.
  auto autoColumnTrack = GridTrackSize::auto_();
  auto autoRowTrack = GridTrackSize::auto_();

  for (auto i = autoPlacement.minColumnStart; i < 0; i++) {
    columnTracks.push_back(autoColumnTrack);
  }
  for (auto i = 0; i < gridExplicitColumns.size(); i++) {
    columnTracks.push_back(gridExplicitColumns[i]);
  }
  for (auto i = gridExplicitColumns.size(); i < autoPlacement.maxColumnEnd; i++) {
    columnTracks.push_back(autoColumnTrack);
  }

  for (auto i = autoPlacement.minRowStart; i < 0; i++) {
    rowTracks.push_back(autoRowTrack);
  }
  for (auto i = 0; i < gridExplicitRows.size(); i++) {
    rowTracks.push_back(gridExplicitRows[i]);
  }
  for (auto i = gridExplicitRows.size(); i < autoPlacement.maxRowEnd; i++) {
    rowTracks.push_back(autoRowTrack);
  }

  return {
    columnTracks,
    rowTracks
  };
}

AutoPlacement resolveGridItemPlacements(Node* node) {
  auto autoPlacement = AutoPlacement::performAutoPlacement(node);

  auto minColumnStart = autoPlacement.minColumnStart;
  auto minRowStart = autoPlacement.minRowStart;

  // offset placements to start from 0 to avoid negative indices
  for (auto& placement: autoPlacement.gridItemAreas) {
    placement.columnStart -= minColumnStart;
    placement.columnEnd -= minColumnStart;
    placement.rowStart -= minRowStart;
    placement.rowEnd -= minRowStart;
    // TODO: find a better place to call this
    placement.node->processDimensions();
  }

  return autoPlacement;
}

} // namespace facebook::yoga
