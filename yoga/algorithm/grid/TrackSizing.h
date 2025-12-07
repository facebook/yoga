/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
*/

#pragma once

#include <yoga/algorithm/Baseline.h>
#include <yoga/algorithm/BoundAxis.h>
#include <yoga/algorithm/CalculateLayout.h>
#include <yoga/algorithm/grid/GridLayout.h>
#include <yoga/numeric/Comparison.h>
#include <yoga/style/StyleSizeLength.h>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <numeric>

namespace facebook::yoga {

struct TrackSizing {
  enum class AffectedSize {
    BaseSize,
    GrowthLimit
  };

  struct ContentDistribution {
    float startOffset = 0.0f;
    float betweenTracksOffset = 0.0f;
    float effectiveGap = 0.0f;
  };

  struct ItemConstraint {
    float width;
    float height;
    SizingMode widthSizingMode;
    SizingMode heightSizingMode;
    float containingBlockWidth;
    float containingBlockHeight;
  };

  using CrossDimensionEstimator = std::function<float(const GridItem&)>;

  struct ItemSizeContribution {
    const GridItem* item;
    std::vector<GridTrackSize*> affectedTracks;
    float sizeContribution;

    ItemSizeContribution(
      const GridItem* item,
      const std::vector<GridTrackSize*>& affectedTracks,
      float sizeContribution) :
      item(item),
      affectedTracks(affectedTracks),
      sizeContribution(sizeContribution) {}
  };

  Node* node;
  std::vector<GridTrackSize>& columnTracks;
  std::vector<GridTrackSize>& rowTracks;
  float containerInnerWidth;
  float containerInnerHeight;
  std::vector<GridItem>& gridItems;
  SizingMode widthSizingMode;
  SizingMode heightSizingMode;
  Direction direction;
  float ownerWidth;
  float ownerHeight;
  LayoutData& layoutMarkerData;
  uint32_t depth;
  uint32_t generationCount;
  CrossDimensionEstimator crossDimensionEstimator;

  // below flags are used for optimization purposes
  bool hasPercentageColumnTracks = false;
  bool hasPercentageRowTracks = false;
  bool hasNonFixedColumnTracks = false;
  bool hasNonFixedRowTracks = false;

  // Pre-computed baseline sharing groups
  BaselineItemGroups& baselineItemGroups;

  TrackSizing(
    yoga::Node* node,
    std::vector<GridTrackSize>& columnTracks,
    std::vector<GridTrackSize>& rowTracks,
    float containerInnerWidth,
    float containerInnerHeight,
    std::vector<GridItem>& gridItems,
    SizingMode widthSizingMode,
    SizingMode heightSizingMode,
    Direction direction,
    float ownerWidth,
    float ownerHeight,
    LayoutData& layoutMarkerData,
    uint32_t depth,
    uint32_t generationCount,
    BaselineItemGroups& baselineItemGroups) :
    node(node),
    columnTracks(columnTracks),
    rowTracks(rowTracks),
    containerInnerWidth(containerInnerWidth),
    containerInnerHeight(containerInnerHeight),
    gridItems(gridItems),
    widthSizingMode(widthSizingMode),
    heightSizingMode(heightSizingMode),
    direction(direction),
    ownerWidth(ownerWidth),
    ownerHeight(ownerHeight),
    layoutMarkerData(layoutMarkerData),
    depth(depth),
    generationCount(generationCount),
    baselineItemGroups(baselineItemGroups) {}

  // 11.1. Grid Sizing Algorithm
  // https://www.w3.org/TR/css-grid-1/#algo-grid-sizing
  void runGridSizingAlgorithm() {
    auto effectiveRowGap = calculateEffectiveRowGapForEstimation();
    auto estimateRowHeightStep1 = [&](const GridItem& item) -> float {
      float itemAreaHeight = 0.0f;
      for (size_t i = item.rowStart; i < item.rowEnd && i < rowTracks.size(); i++) {
        if (isFixedSizingFunction(rowTracks[i].maxSizingFunction, containerInnerHeight)) {
          itemAreaHeight += rowTracks[i].maxSizingFunction.resolve(containerInnerHeight).unwrap();
          if (i < item.rowEnd - 1) {
            itemAreaHeight += effectiveRowGap;
          }
        } else {
          return YGUndefined;
        }
      }
      return itemAreaHeight;
    };

    // 1. First, the track sizing algorithm is used to resolve the sizes of the grid columns.
    runTrackSizing(Dimension::Width, estimateRowHeightStep1);

    // Save content contributions after step 11.1.1 for Step 11.1.3
    auto columnContributionsAfterStep1 = getItemMinContentContributions(Dimension::Width, estimateRowHeightStep1);

    auto effectiveColumnGap = calculateEffectiveColumnGapFromBaseSizes();

    auto estimateColumnWidthStep2 = [&](const GridItem& item) -> float {
      float itemAreaWidth = 0.0f;
      for (size_t i = item.columnStart; i < item.columnEnd && i < columnTracks.size(); i++) {
        itemAreaWidth += columnTracks[i].baseSize;
        if (i < item.columnEnd - 1) {
          itemAreaWidth += effectiveColumnGap;
        }
      }
      return itemAreaWidth;
    };

    // 2. Next, the track sizing algorithm resolves the sizes of the grid rows.
    // Uses actual column sizes from step 11.1.1.
    runTrackSizing(Dimension::Height, estimateColumnWidthStep2);

    // Save content contributions after step 11.1.2 for Step 11.1.3
    auto rowContributionsAfterStep2 = getItemMinContentContributions(Dimension::Height, estimateColumnWidthStep2);

    effectiveRowGap = calculateEffectiveRowGapFromBaseSizes();

    auto estimateRowHeightStep3 = [&](const GridItem& item) -> float {
      float containingBlockHeight = 0.0f;
      for (size_t i = item.rowStart; i < item.rowEnd && i < rowTracks.size(); i++) {
        containingBlockHeight += rowTracks[i].baseSize;
        if (i < item.rowEnd - 1) {
          containingBlockHeight += effectiveRowGap;
        }
      }
      return containingBlockHeight;
    };

    auto columnContributionsStep3 = getItemMinContentContributions(Dimension::Width, estimateRowHeightStep3);

    // 3. Then, if the min-content contribution of any grid item has changed
    // based on the row sizes calculated in step 11.1.2, re-resolve column sizes (once only).
    if (contributionsChanged(columnContributionsAfterStep1, columnContributionsStep3)) {
      runTrackSizing(Dimension::Width, estimateRowHeightStep3);
      effectiveColumnGap = calculateEffectiveColumnGapFromBaseSizes();

      auto estimateColumnWidthStep4 = [&](const GridItem& item) -> float {
        float containingBlockWidth = 0.0f;
        for (size_t i = item.columnStart; i < item.columnEnd && i < columnTracks.size(); i++) {
          containingBlockWidth += columnTracks[i].baseSize;
          if (i < item.columnEnd - 1) {
            containingBlockWidth += effectiveColumnGap;
          }
        }
        return containingBlockWidth;
      };

      // Check if any item's row contribution changed with new column widths
      auto rowContributionsStep4 = getItemMinContentContributions(Dimension::Height, estimateColumnWidthStep4);

      // 4. Next, if the min-content contribution of any grid item has changed
      // based on the column sizes calculated in step 3, re-resolve row sizes (once only).
      if (contributionsChanged(rowContributionsAfterStep2, rowContributionsStep4)) {
        runTrackSizing(Dimension::Height, estimateColumnWidthStep4);
      }
    }

    // 5. Align/Justify content is handled in GridLayout.cpp
  }
  
  // 11.3. Track Sizing Algorithm
  // https://www.w3.org/TR/css-grid-1/#algo-track-sizing
  void runTrackSizing(Dimension dimension, CrossDimensionEstimator estimator = nullptr) {
    // Store the estimator for use in calculateItemConstraints
    crossDimensionEstimator = estimator;

    // Step 1: Initialize Track Sizes (also sets hasNonFixedTracks flag)
    initializeTrackSizes(dimension);
    // Step 2: Resolve Intrinsic Track Sizes
    resolveIntrinsicTrackSizes(dimension);
    // Step 3: Maximize Track Sizes
    maximizeTrackSizes(dimension);
    // Step 4: Expand Flexible Tracks
    expandFlexibleTracks(dimension);
    // Step 5: Stretch Auto Tracks
    stretchAutoTracks(dimension);
  }

  // 11.4 Initialize Track Sizes
  // https://www.w3.org/TR/css-grid-1/#algo-init
  void initializeTrackSizes(Dimension dimension) {
    auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    bool& hasPercentageTracks = dimension == Dimension::Width ? hasPercentageColumnTracks : hasPercentageRowTracks;
    bool& hasNonFixedTracks = dimension == Dimension::Width ? hasNonFixedColumnTracks : hasNonFixedRowTracks;
    hasNonFixedTracks = false;

    for (size_t i = 0; i < tracks.size(); i++) {
      auto& track = tracks[i];

      // detect percentage tracks for optimization purposes
      if (isPercentageSizingFunction(track.minSizingFunction) ||
          isPercentageSizingFunction(track.maxSizingFunction)) {
        hasPercentageTracks = true;
      }

      if (isFixedSizingFunction(track.minSizingFunction, containerSize)) {
        auto resolved = track.minSizingFunction.resolve(containerSize);
        track.baseSize = resolved.unwrap();
      }
      else if (isIntrinsicSizingFunction(track.minSizingFunction, containerSize)) {
        track.baseSize = 0;
        hasNonFixedTracks = true;
      }
      else {
        // THIS SHOULD NEVER HAPPEN
        track.baseSize = 0;
      }

      if (isFixedSizingFunction(track.maxSizingFunction, containerSize)) {
        auto resolved = track.maxSizingFunction.resolve(containerSize);
        track.growthLimit = resolved.unwrap();
      }
      else if (isIntrinsicSizingFunction(track.maxSizingFunction, containerSize)) {
        track.growthLimit = INFINITY;
        hasNonFixedTracks = true;
      }
      else if (isFlexibleSizingFunction(track.maxSizingFunction)) {
        track.growthLimit = INFINITY;
        hasNonFixedTracks = true;
      }
      else {
        // THIS SHOULD NEVER HAPPEN
        track.growthLimit = INFINITY;
      }

      // In all cases, if the growth limit is less than the base size, increase the growth limit to match the base size.
      if (track.growthLimit < track.baseSize) {
        track.growthLimit = track.baseSize;
      }

      // minmax(20px, 40px) type of tracks are non-fixed tracks
      if (track.baseSize < track.growthLimit) {
        hasNonFixedTracks = true;
      }
    }
  }

  // 11.5 Resolve Intrinsic Track Sizes
  // https://www.w3.org/TR/css-grid-1/#algo-content
  void resolveIntrinsicTrackSizes(Dimension dimension) {
    auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;

    // Step 1: Shim baseline-aligned items (only for height dimension i.e. align-items/align-self)
    if (dimension == Dimension::Height) {
      shimBaselineAlignedItems();
    }

    // Fast path - if tracks are fixed-sized, skip below steps
    bool hasNonFixedTracks = dimension == Dimension::Width ? hasNonFixedColumnTracks : hasNonFixedRowTracks;
    if (!hasNonFixedTracks) {
      return;
    }

    // Step 2. and Step 3 Increase sizes to accommodate spanning items
    accomodateSpanningItemsCrossingContentSizedTracks(dimension);
    // Step 4. Increase sizes to accommodate spanning items crossing flexible tracks
    accomodateSpanningItemsCrossingFlexibleTracks(dimension);
    // Step 5. If any track still has an infinite growth limit (because, for example, it had no items placed in it or it is a flexible track), set its growth limit to its base size.
    for (auto& track: tracks) {
      if (track.growthLimit == INFINITY) {
        track.growthLimit = track.baseSize;
      }
    }
  }

  // https://www.w3.org/TR/css-grid-1/#algo-baseline-shims
  void shimBaselineAlignedItems() {
    for (const auto& [rowIndex, items] : baselineItemGroups) {
      float maxBaselineWithMargin = 0.0f;
      std::vector<std::pair<GridItem*, float>> itemBaselines;
      itemBaselines.reserve(items.size());

      for (auto* itemPtr : items) {
        const auto& item = *itemPtr;

        if (itemSizeDependsOnIntrinsicTracks(item)) {
          continue;
        }

        float containingBlockWidth = crossDimensionEstimator ? crossDimensionEstimator(item) : YGUndefined;
        float containingBlockHeight = YGUndefined;

        auto itemConstraints = calculateItemConstraints(item, containingBlockWidth, containingBlockHeight);

        calculateLayoutInternal(
            item.node,
            itemConstraints.width,
            itemConstraints.height,
            node->getLayout().direction(),
            SizingMode::MaxContent,
            itemConstraints.heightSizingMode,
            itemConstraints.containingBlockWidth,
            itemConstraints.containingBlockHeight,
            true,
            LayoutPassReason::kGridLayout,
            layoutMarkerData,
            depth + 1,
            generationCount);

        const float baseline = calculateBaseline(item.node);
        const float marginTop = item.node->style().computeInlineStartMargin(
            FlexDirection::Column, direction, itemConstraints.containingBlockWidth);
        const float baselineWithMargin = baseline + marginTop;

        itemBaselines.emplace_back(itemPtr, baselineWithMargin);
        maxBaselineWithMargin = std::max(maxBaselineWithMargin, baselineWithMargin);
      }

      for (auto& [itemPtr, baselineWithMargin] : itemBaselines) {
        itemPtr->baselineShim = maxBaselineWithMargin - baselineWithMargin;
      }
    }
  }

  // https://www.w3.org/TR/css-grid-1/#algo-spanning-items
  void accomodateSpanningItemsCrossingContentSizedTracks(Dimension dimension) {
    auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    auto sizingMode = dimension == Dimension::Width ? widthSizingMode : heightSizingMode;

    auto startIndexKey = dimension == Dimension::Width ? &GridItem::columnStart : &GridItem::rowStart;
    auto endIndexKey = dimension == Dimension::Width ? &GridItem::columnEnd : &GridItem::rowEnd;
    // Sort item indices by span
    std::vector<size_t> sortedIndices(gridItems.size());
    std::iota(sortedIndices.begin(), sortedIndices.end(), 0);
    std::sort(sortedIndices.begin(), sortedIndices.end(), [&](size_t i, size_t j) {
        const auto& a = gridItems[i];
        const auto& b = gridItems[j];
        return (a.*endIndexKey - a.*startIndexKey) < (b.*endIndexKey - b.*startIndexKey);
    });

    size_t previousSpan = 1;
    std::vector<ItemSizeContribution> itemsForIntrinsicMin;
    std::vector<ItemSizeContribution> itemsForIntrinsicMax;
    std::vector<ItemSizeContribution> itemsForMaxContentMax;

    auto distributeSpaceToTracksForItemsWithTheSameSpan = [&]() {
      // Step 1: For intrinsic minimums
      if (!itemsForIntrinsicMin.empty()) {
        distributeExtraSpaceAcrossSpannedTracks(dimension, itemsForIntrinsicMin, AffectedSize::BaseSize);
        itemsForIntrinsicMin.clear();
      }

      // Step 2 and Step 3 are skipped since we're not supporting min-content and max-content yet

      // Step 4: If at this point any track's growth limit is now less than its base size, increase its growth limit to match its base size
      for (auto& track : tracks) {
        if (track.growthLimit < track.baseSize) {
          track.growthLimit = track.baseSize;
        }

        // https://www.w3.org/TR/css-grid-1/#infinitely-growable
        // reset infinitely growable flag for each track
        // This flag gets set in Step 5 and used in Step 6, so we need to reset it before running Step 5.
        track.infinitelyGrowable = false;
      }

      // Step 5: For intrinsic maximums
      if (!itemsForIntrinsicMax.empty()) {
        distributeExtraSpaceAcrossSpannedTracks(dimension, itemsForIntrinsicMax, AffectedSize::GrowthLimit);
        itemsForIntrinsicMax.clear();
      }

      // Step 6: For max-content maximums
      if (!itemsForMaxContentMax.empty()) {
        distributeExtraSpaceAcrossSpannedTracks(dimension, itemsForMaxContentMax, AffectedSize::GrowthLimit);
        itemsForMaxContentMax.clear();
      }
    };

    for (auto& index: sortedIndices) {
      const auto& item = gridItems[index];
      auto startIndex = item.*startIndexKey;
      auto endIndex = item.*endIndexKey;
      size_t span = endIndex - startIndex;

      // 2. Size tracks to fit non-spanning items
      // https://www.w3.org/TR/css-grid-1/#algo-single-span-items
      if (span == 1) {
        auto& track = tracks[startIndex];
        auto itemConstraints = calculateItemConstraints(item, dimension);
        // For auto minimums:
        if (isAutoSizingFunction(track.minSizingFunction, containerSize)) {
          float contribution = sizingMode == SizingMode::MaxContent
              ? getLimitedMinimumContentContribution(item, dimension, itemConstraints)
              : getMinimumContribution(item, dimension, itemConstraints);
          track.baseSize = std::max(track.baseSize, contribution);
        }
        
        // For max-content maximums:
        if (isAutoSizingFunction(track.maxSizingFunction, containerSize)) {
          float contribution = getMaxContentContribution(item, dimension, itemConstraints);
          if (track.growthLimit == INFINITY) {
            track.growthLimit = contribution;
          } else {
            track.growthLimit = std::max(track.growthLimit, contribution);
          }
        }
        // In all cases, if a track’s growth limit is now less than its base size, increase the growth limit to match the base size.
        if (track.growthLimit < track.baseSize) {
          track.growthLimit = track.baseSize;
        }
        previousSpan = span;

        continue;
      }

      // 3. Increase sizes to accommodate spanning items crossing content-sized tracks:
      // https://www.w3.org/TR/css-grid-1/#algo-spanning-items
      if (span > previousSpan) {
        distributeSpaceToTracksForItemsWithTheSameSpan();
        previousSpan = span;
      }

      std::vector<GridTrackSize*> intrinsicMinimumSizingFunctionTracks;
      std::vector<GridTrackSize*> intrinsicMaximumSizingFunctionTracks;
      std::vector<GridTrackSize*> maxContentMaximumSizingFunctionTracks;

      bool hasFlexibleTrack = false;
      for (size_t i = startIndex; i < endIndex; i++) {
        if (isFlexibleSizingFunction(tracks[i].maxSizingFunction)) {
          hasFlexibleTrack = true;
          break;
        }

        if (isIntrinsicSizingFunction(tracks[i].minSizingFunction, containerSize)) {
          intrinsicMinimumSizingFunctionTracks.push_back(&tracks[i]);
        }

        if (isIntrinsicSizingFunction(tracks[i].maxSizingFunction, containerSize)) {
          intrinsicMaximumSizingFunctionTracks.push_back(&tracks[i]);
        }

        // auto as max sizing function is treated as max-content sizing function
        if (isAutoSizingFunction(tracks[i].maxSizingFunction, containerSize)) {
          maxContentMaximumSizingFunctionTracks.push_back(&tracks[i]);
        }
      }

      if (hasFlexibleTrack) continue;

      auto itemConstraints = calculateItemConstraints(item, dimension);
      if (!intrinsicMinimumSizingFunctionTracks.empty()) {
        auto minimumContribution = sizingMode == SizingMode::MaxContent ? getLimitedMinimumContentContribution(item, dimension, itemConstraints) : getMinimumContribution(item, dimension, itemConstraints);
        itemsForIntrinsicMin.emplace_back(&item, std::move(intrinsicMinimumSizingFunctionTracks), minimumContribution);
      }

      if (!intrinsicMaximumSizingFunctionTracks.empty()) {
        auto minimumContentContribution = getMinimumContentContribution(item, dimension, itemConstraints);
        itemsForIntrinsicMax.emplace_back(&item, std::move(intrinsicMaximumSizingFunctionTracks), minimumContentContribution);
      }

      if (!maxContentMaximumSizingFunctionTracks.empty()) {
        auto maxContentContribution = getMaxContentContribution(item, dimension, itemConstraints);
        itemsForMaxContentMax.emplace_back(&item, std::move(maxContentMaximumSizingFunctionTracks), maxContentContribution);
      }
    }

    // Process last span
    distributeSpaceToTracksForItemsWithTheSameSpan();
  };

  // https://www.w3.org/TR/css-grid-1/#algo-spanning-flex-items
  void accomodateSpanningItemsCrossingFlexibleTracks(Dimension dimension) {
    auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    auto sizingMode = dimension == Dimension::Width ? widthSizingMode : heightSizingMode;
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    auto startIndexkey = dimension == Dimension::Width ? &GridItem::columnStart : &GridItem::rowStart;
    auto endIndexKey = dimension == Dimension::Width ? &GridItem::columnEnd : &GridItem::rowEnd;

    std::vector<ItemSizeContribution> itemsSpanningFlexible;

    for (const auto& item : gridItems) {
      auto start = item.*startIndexkey;
      auto end = item.*endIndexKey;
      bool hasFlexibleTrack = false;
      std::vector<GridTrackSize*> intrinsicMinFlexibleTracks;

      for (size_t i = start; i < end && i < tracks.size(); i++) {
        auto& track = tracks[i];
        if (isFlexibleSizingFunction(track.maxSizingFunction)) {
          hasFlexibleTrack = true;
          if (isIntrinsicSizingFunction(track.minSizingFunction, containerSize)) {
            intrinsicMinFlexibleTracks.push_back(&track);
          }
        }
      }

      if (hasFlexibleTrack && !intrinsicMinFlexibleTracks.empty()) {
        auto itemConstraints = calculateItemConstraints(item, dimension);
        auto minimumContribution = sizingMode == SizingMode::MaxContent
            ? getLimitedMinimumContentContribution(item, dimension, itemConstraints)
            : getMinimumContribution(item, dimension, itemConstraints);

        itemsSpanningFlexible.emplace_back(
            &item,
            std::move(intrinsicMinFlexibleTracks),
            minimumContribution
        );
      }
    }

    if (!itemsSpanningFlexible.empty()) {
      distributeSpaceToFlexibleTracksForItems(dimension, itemsSpanningFlexible);
    }
  };

  // https://www.w3.org/TR/css-grid-1/#extra-space
  void distributeExtraSpaceAcrossSpannedTracks(
    Dimension dimension,
    std::vector<ItemSizeContribution>& gridItemSizeContributions,
    AffectedSize affectedSizeType) {
    auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    auto startIndexKey = dimension == Dimension::Width ? &GridItem::columnStart : &GridItem::rowStart;
    auto endIndexKey = dimension == Dimension::Width ? &GridItem::columnEnd : &GridItem::rowEnd;
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    auto gap = node->style().computeGapForDimension(dimension, containerSize);
    std::unordered_map<GridTrackSize*, float> plannedIncrease;
    plannedIncrease.reserve(gridItemSizeContributions.size());

    // 1. Maintain separately for each affected track a planned increase, initially set to 0. (This prevents the size increases from becoming order-dependent.)
    for (const auto& itemSizeContribution : gridItemSizeContributions) {
      for (auto& track : itemSizeContribution.affectedTracks) {
        plannedIncrease[track] = 0.0f;
      }
    }

    // 2. For each accommodated item, considering only tracks the item spans:
    for (const auto& itemSizeContribution : gridItemSizeContributions) {
      std::unordered_map<GridTrackSize*, float> itemIncurredIncrease;
      itemIncurredIncrease.reserve(itemSizeContribution.affectedTracks.size());
      for (auto& track: itemSizeContribution.affectedTracks) {
        itemIncurredIncrease[track] = 0.0f;
      }

      // 2.1 Find the space to distribute
      auto start = itemSizeContribution.item->*startIndexKey;
      auto end = itemSizeContribution.item->*endIndexKey;
      float totalSpannedTracksSize = 0.0f;
      for (size_t i = start; i < end && i < tracks.size(); i++) {
        auto& track = tracks[i];
        if (affectedSizeType == AffectedSize::BaseSize) {
          totalSpannedTracksSize += track.baseSize;
        } else {
          // For infinite growth limits, substitute the track's base size
          totalSpannedTracksSize += track.growthLimit == INFINITY ? track.baseSize : track.growthLimit;
        }
        if (i < end - 1) {
          // gaps are treated as tracks of fixed size. Item can span over gaps.
          totalSpannedTracksSize += gap;
        }
      }

      float spaceToDistribute = std::max(0.0f, itemSizeContribution.sizeContribution - totalSpannedTracksSize);
      std::unordered_set<GridTrackSize*> frozenTracks;
      frozenTracks.reserve(itemSizeContribution.affectedTracks.size());

      // 2.2. Distribute space up to limits
      while (frozenTracks.size() < itemSizeContribution.affectedTracks.size() && spaceToDistribute > 0.0f && !yoga::inexactEquals(spaceToDistribute, 0.0f)) {
        auto unfrozenTrackCount = itemSizeContribution.affectedTracks.size() - frozenTracks.size();
        auto distributionPerTrack = spaceToDistribute / unfrozenTrackCount;

        for (auto& track: itemSizeContribution.affectedTracks) {
          if (frozenTracks.contains(track)) {
            continue;
          }

          float limit;
          float affectedSize;

          if (affectedSizeType == AffectedSize::BaseSize) {
            affectedSize = track->baseSize;
            limit = track->growthLimit;
          } else {
            affectedSize = track->growthLimit;
            limit = INFINITY;
            if (track->growthLimit != INFINITY && !track->infinitelyGrowable) {
              limit = track->growthLimit;
            }

            // If the affected size was a growth limit and the track is not marked infinitely growable, then each item-incurred increase will be zero.
            if (!track->infinitelyGrowable) {
              frozenTracks.insert(track);
              continue;
            }
          }

          if (affectedSize + distributionPerTrack + itemIncurredIncrease[track] > limit) {
            frozenTracks.insert(track);
            auto increase = limit - affectedSize - itemIncurredIncrease[track];
            itemIncurredIncrease[track] += increase;
            spaceToDistribute -= increase;
          } else {
            itemIncurredIncrease[track] += distributionPerTrack;
            spaceToDistribute -= distributionPerTrack;
          }
        }
      }

      // 2.3. Distribute space to non-affected tracks:
      // Currently, browsers do not implement this step.
      // https://github.com/w3c/csswg-drafts/issues/3648

      // 2.4. Distribute space beyond limits
      if (spaceToDistribute > 0.0f && !yoga::inexactEquals(spaceToDistribute, 0.0f)) {
        std::vector<GridTrackSize*> tracksToGrowBeyondLimits;
        for (auto& track: itemSizeContribution.affectedTracks) {
          if (isIntrinsicSizingFunction(track->maxSizingFunction, containerSize)) {
            tracksToGrowBeyondLimits.push_back(track);
          }
        }

        // if there are no such tracks, then all affected tracks.
        if (affectedSizeType == AffectedSize::BaseSize && tracksToGrowBeyondLimits.empty()) {
          tracksToGrowBeyondLimits = itemSizeContribution.affectedTracks;
        }

        while (spaceToDistribute > 0.0f && !yoga::inexactEquals(spaceToDistribute, 0.0f) && !tracksToGrowBeyondLimits.empty()) {
          auto unfrozenTrackCount = tracksToGrowBeyondLimits.size();
          auto distributionPerTrack = spaceToDistribute / unfrozenTrackCount;
          for (auto& track: tracksToGrowBeyondLimits) {
            itemIncurredIncrease[track] += distributionPerTrack;
            spaceToDistribute -= distributionPerTrack;
          }
        }
      }

      // 2.5. For each affected track, if the track's item-incurred increase is larger than the track's planned increase set the track's planned increase to that value.
      for (auto& track: itemSizeContribution.affectedTracks) {
        if (itemIncurredIncrease[track] > plannedIncrease[track]) {
          plannedIncrease[track] = itemIncurredIncrease[track];
        }
      }
    }

    // 3. Update the tracks affected sizes
    for (const auto& [track, increase] : plannedIncrease) {
      if (affectedSizeType == AffectedSize::BaseSize) {
        track->baseSize += increase;
      } else {
        if (track->growthLimit == INFINITY) {
          track->growthLimit = track->baseSize + increase;
          track->infinitelyGrowable = true;
        } else {
          track->growthLimit += increase;
        }
      }
    }
  }

  // https://www.w3.org/TR/css-grid-1/#extra-space
  // Similar to distribute extra space for content sized trcks, but distributes space considering flex factors.
  void distributeSpaceToFlexibleTracksForItems(
    Dimension dimension,
    const std::vector<ItemSizeContribution>& gridItemSizeContributions) {
    auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    auto gap = node->style().computeGapForDimension(dimension, containerSize);
    auto startIndexKey = dimension == Dimension::Width ? &GridItem::columnStart : &GridItem::rowStart;
    auto endIndexKey = dimension == Dimension::Width ? &GridItem::columnEnd : &GridItem::rowEnd;

    // Step 1: Maintain planned increase for each affected track
    std::unordered_map<GridTrackSize*, float> plannedIncrease;
    for (const auto& itemSizeContribution : gridItemSizeContributions) {
      for (auto& track : itemSizeContribution.affectedTracks) {
        plannedIncrease[track] = 0.0f;
      }
    }

    // Step 2: For each item
    for (const auto& itemSizeContribution : gridItemSizeContributions) {
      std::unordered_map<GridTrackSize*, float> itemIncurredIncrease;
      for (auto& track : itemSizeContribution.affectedTracks) {
        itemIncurredIncrease[track] = 0.0f;
      }

      // 2.1 Find space to distribute
      auto start = itemSizeContribution.item->*startIndexKey;
      auto end = itemSizeContribution.item->*endIndexKey;
      float totalSpannedTracksSize = 0.0f;
      for (size_t i = start; i < end && i < tracks.size(); i++) {
        totalSpannedTracksSize += tracks[i].baseSize;
        if (i < end - 1) {
          // gaps are treated as tracks of fixed size. Item can span over gaps.
          totalSpannedTracksSize += gap;
        }
      }

      float spaceToDistribute = std::max(0.0f, itemSizeContribution.sizeContribution - totalSpannedTracksSize);

      float sumOfFlexFactors = 0.0f;
      for (auto& track : itemSizeContribution.affectedTracks) {
        sumOfFlexFactors += track->maxSizingFunction.value().unwrap();
      }

      if (sumOfFlexFactors > 0.0f) {
        // Distribute space by flex ratios (normalized)
        for (auto& track : itemSizeContribution.affectedTracks) {
          auto flexFactor = track->maxSizingFunction.value().unwrap();
          auto increase = spaceToDistribute * flexFactor / sumOfFlexFactors;
          itemIncurredIncrease[track] += increase;
        }
      } else {
        // All flex factors are zero, distribute equally
        auto equalShare = spaceToDistribute / static_cast<float>(itemSizeContribution.affectedTracks.size());
        for (auto& track : itemSizeContribution.affectedTracks) {
          itemIncurredIncrease[track] += equalShare;
        }
      }

      for (auto& track : itemSizeContribution.affectedTracks) {
        if (itemIncurredIncrease[track] > plannedIncrease[track]) {
          plannedIncrease[track] = itemIncurredIncrease[track];
        }
      }
    }

    // Step 3: Update the tracks' affected sizes by adding in the planned increase
    for (const auto& [track, increase] : plannedIncrease) {
      track->baseSize += increase;
    }
  };

  // 11.6. Maximize Tracks
  // https://www.w3.org/TR/css-grid-1/#algo-grow-tracks
  void maximizeTrackSizes(Dimension dimension) {
    // Fast path - if tracks are fixed-sized, skip below steps
    bool hasNonFixedTracks = dimension == Dimension::Width ? hasNonFixedColumnTracks : hasNonFixedRowTracks;
    if (!hasNonFixedTracks) {
      return;
    }

    auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    
    // Save original base sizes before maximization
    std::vector<float> originalBaseSizes;
    originalBaseSizes.reserve(tracks.size());
    for (auto& track : tracks) {
      originalBaseSizes.push_back(track.baseSize);
    }
    
    // First attempt with the original container inner size
    distributeFreeSpaceToTracks(dimension, containerSize);
    
    // Check if this would cause the grid to be larger than the grid container's inner size as limited by its max-width/height
    auto totalGridSize = getTotalBaseSize(dimension);

    // Get the max constraint for this dimension
    const float paddingAndBorder = dimension == Dimension::Width
        ? paddingAndBorderForAxis(node, FlexDirection::Row, direction, ownerWidth)
        : paddingAndBorderForAxis(node, FlexDirection::Column, direction, ownerWidth);

    auto maxContainerBorderBoxSize = node->style().resolvedMaxDimension(
        direction,
        dimension,
        dimension == Dimension::Width ? ownerWidth : ownerHeight,
        ownerWidth);

    auto maxContainerInnerSize = maxContainerBorderBoxSize.isDefined()
        ? maxContainerBorderBoxSize.unwrap() - paddingAndBorder
        : YGUndefined;

    if (yoga::isDefined(maxContainerInnerSize)) {
      if (totalGridSize > maxContainerInnerSize) {
        // Redo this step, treating the available grid space as equal to the grid container's inner size when it's sized to its max-width/height
        // Reset base sizes to their values before this maximize step
        for (size_t i = 0; i < tracks.size(); i++) {
          tracks[i].baseSize = originalBaseSizes[i];
        }
        
        distributeFreeSpaceToTracks(dimension, maxContainerInnerSize);
      }
    }
  }

  // Distribute space in maximizeTrackSizes step
  // https://www.w3.org/TR/css-grid-1/#algo-grow-tracks
  void distributeFreeSpaceToTracks(Dimension dimension, float targetAvailableSize) {
    auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    auto sizingMode = dimension == Dimension::Width ? widthSizingMode : heightSizingMode;
    float freeSpace = 0.0f;
    if (yoga::isDefined(targetAvailableSize)) {
      auto totalBaseSize = getTotalBaseSize(dimension);
      freeSpace = std::max(0.0f, targetAvailableSize - totalBaseSize);
    }
    
    // For the purpose of this step: if sizing the grid container under a max-content constraint, the free space is infinite; 
    // if sizing under a min-content constraint, the free space is zero.
    if (sizingMode == SizingMode::MaxContent) {
      freeSpace = INFINITY;
    }

    // If the free space is positive, distribute it equally to the base sizes of all tracks,
    // freezing tracks as they reach their growth limits (and continuing to grow the unfrozen tracks as needed).
    if (freeSpace > 0.0f && !yoga::inexactEquals(freeSpace, 0.0f)) {
      // growth limit will not be Infinite in maximizeTrackSizes step since we had set Infinite growth limit to base size in resolveIntrinsicTrackSizes's last step - https://www.w3.org/TR/css-grid-1/#algo-finite-growth
      if (freeSpace == INFINITY) {
        for (auto& track : tracks) {
          track.baseSize = track.growthLimit;
        }
      } else {
        std::unordered_set<GridTrackSize*> frozenTracks;
        frozenTracks.reserve(tracks.size());
        auto extraSpace = freeSpace;
        
        while (frozenTracks.size() < tracks.size() && extraSpace > 0.0f && !yoga::inexactEquals(extraSpace, 0.0f)) {
          auto unfrozenTrackCount = tracks.size() - frozenTracks.size();
          auto distributionPerTrack = extraSpace / unfrozenTrackCount;
          
          for (auto& track : tracks) {
            GridTrackSize* trackPtr = &track;
            if (frozenTracks.contains(trackPtr)) {
              continue;
            }
            
            // Check if adding this distribution would exceed the growth limit
            if (track.baseSize + distributionPerTrack > track.growthLimit) {
              auto increase = std::max(0.0f, track.growthLimit - track.baseSize);
              track.baseSize += increase;
              extraSpace -= increase;
              frozenTracks.insert(trackPtr);
            } else {
              track.baseSize += distributionPerTrack;
              extraSpace -= distributionPerTrack;
            }
          }
        }
      }
    }
  }

  // 11.7. Expand Flexible Tracks
  // https://www.w3.org/TR/css-grid-1/#algo-flex-tracks
  void expandFlexibleTracks(Dimension dimension) {
    // Fast path - if tracks are fixed-sized, skip below steps
    bool hasNonFixedTracks = dimension == Dimension::Width ? hasNonFixedColumnTracks : hasNonFixedRowTracks;
    if (!hasNonFixedTracks) {
      return;
    }

    auto& gridTracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    auto gap = node->style().computeGapForDimension(dimension, containerSize);

    std::vector<GridTrackSize*> allGridTracks;
    allGridTracks.reserve(gridTracks.size());
    for (auto& track : gridTracks) {
      allGridTracks.push_back(&track);
    }

    float freeSpace = calculateFreeSpace(dimension);

    float flexFraction = 0.0f;
    // If the free space is zero or if sizing the grid container under a min-content constraint:
    if (yoga::inexactEquals(freeSpace, 0.0f)) {
      flexFraction = 0.0f;
    } 
    // Otherwise, if the free space is a definite length:
    // The used flex fraction is the result of finding the size of an fr using all of the grid tracks and a space to fill of the available grid space.
    else if (yoga::isDefined(freeSpace)) {
      flexFraction = findFrSize(dimension, 0, gridTracks.size(), containerSize, std::unordered_set<GridTrackSize*>());
    } 
    // Otherwise, if the free space is an indefinite length:
    // The used flex fraction is the maximum of:
    // For each flexible track, if the flexible track's flex factor is greater than one, the result of dividing the track's base size by its flex factor; otherwise, the track's base size.
    // For each grid item that crosses a flexible track, the result of finding the size of an fr using all the grid tracks that the item crosses and a space to fill of the item’s max-content contribution.
    else {
      for (auto& track : gridTracks) {
        if (isFlexibleSizingFunction(track.maxSizingFunction) && track.maxSizingFunction.value().isDefined()) {
          float flexFactor = track.maxSizingFunction.value().unwrap();
          if (flexFactor > 1.0f) {
            flexFraction = std::max(flexFraction, track.baseSize / flexFactor);
          } else {
            flexFraction = std::max(flexFraction, track.baseSize);
          }
        }
      }

      for (auto& item : gridItems) {
          auto start = dimension == Dimension::Width ? item.columnStart : item.rowStart;
          auto end = dimension == Dimension::Width ? item.columnEnd : item.rowEnd;
          if (!hasFlexibleTrackInRange(gridTracks, start, end)) {
            continue;
          }
          auto itemConstraints = calculateItemConstraints(item, dimension);
          auto itemMaxContentContribution = getMaxContentContribution(item, dimension, itemConstraints);
          flexFraction = std::max(flexFraction, findFrSize(dimension, start, end, itemMaxContentContribution, std::unordered_set<GridTrackSize*>()));
        }
      }

      // If using this flex fraction would cause the grid to be smaller than the grid container's min-width/height 
      // (or larger than the grid container's max-width/height), then redo this step, treating the free space as definite 
      // and the available grid space as equal to the grid container's inner size when it's sized to its min-width/height (max-width/height).
    
      // Calculate what the grid size would be with this flex fraction
      float newTotalSize = 0.0f;
      for (size_t i = 0; i < gridTracks.size(); i++) {
      auto& track = gridTracks[i];
      if (isFlexibleSizingFunction(track.maxSizingFunction) && track.maxSizingFunction.value().isDefined()) {
        float flexFactor = track.maxSizingFunction.value().unwrap();
        newTotalSize += std::max(track.baseSize, flexFraction * flexFactor);
      } else {
        newTotalSize += track.baseSize;
      }
      if (i < gridTracks.size() - 1) {
        newTotalSize += gap;
      }
    }
    
    // Check min constraint for this dimension
    const float paddingAndBorder = dimension == Dimension::Width
      ? paddingAndBorderForAxis(node, FlexDirection::Row, direction, ownerWidth)
      : paddingAndBorderForAxis(node, FlexDirection::Column, direction, ownerWidth);
    auto minContainerOuter = node->style().resolvedMinDimension(
        direction,
        dimension,
        dimension == Dimension::Width ? ownerWidth : ownerHeight,
        ownerWidth);
    auto minContainerSize = minContainerOuter.isDefined()
        ? minContainerOuter.unwrap() - paddingAndBorder
        : YGUndefined;
        
    if (yoga::isDefined(minContainerSize)) {
      if (newTotalSize < minContainerSize) {
        // Redo with min constraint
        flexFraction = findFrSize(dimension, 0, gridTracks.size(), minContainerSize, std::unordered_set<GridTrackSize*>());
      }
    }
     
    // Get the max constraint for this dimension
    auto maxContainerOuter = node->style().resolvedMaxDimension(
        direction,
        dimension,
        dimension == Dimension::Width ? ownerWidth : ownerHeight,
        ownerWidth);

    auto maxContainerSize = maxContainerOuter.isDefined()
        ? maxContainerOuter.unwrap() - paddingAndBorder
        : YGUndefined;
    
    if (yoga::isDefined(maxContainerSize)) {
      if (newTotalSize > maxContainerSize) {
        // Redo with max constraint
        flexFraction = findFrSize(dimension, 0, gridTracks.size(), maxContainerSize, std::unordered_set<GridTrackSize*>());
      }
    }
    
    // For each flexible track, if the product of the used flex fraction and the track's flex factor is greater than the track's base size, 
    // set its base size to that product.
    for (auto& track : gridTracks) {
      if (isFlexibleSizingFunction(track.maxSizingFunction) && track.maxSizingFunction.value().isDefined()) {
        float flexFactor = track.maxSizingFunction.value().unwrap();
        float newSize = flexFraction * flexFactor;
        if (newSize > track.baseSize) {
          track.baseSize = newSize;
        }
      }
    }
  };

  // 11.7.1. Find the Size of an fr
  // https://www.w3.org/TR/css-grid-1/#algo-find-fr-size
  float findFrSize(Dimension dimension, size_t startIndex, size_t endIndex, float spaceToFill, const std::unordered_set<GridTrackSize*>& nonFlexibleTracks) {
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    auto gap = node->style().computeGapForDimension(dimension, containerSize);
    auto leftoverSpace = spaceToFill;
    auto flexFactorSum = 0.0f;
    std::vector<GridTrackSize*> flexibleTracks;
    auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;

    for (size_t i = startIndex; i < endIndex; i++) {
      auto& track = tracks[i];
      // Let leftover space be the space to fill minus the base sizes of the non-flexible grid tracks.
      if (i < endIndex - 1) {
        // gap is treated as a non-flexible track
        leftoverSpace -= gap;
      }

      if (!isFlexibleSizingFunction(track.maxSizingFunction) || nonFlexibleTracks.contains(&track)) {
        leftoverSpace -= track.baseSize;
      } 
      // Let flex factor sum be the sum of the flex factors of the flexible tracks.
      else if (track.maxSizingFunction.isStretch() && track.maxSizingFunction.value().isDefined()) {
        flexFactorSum += track.maxSizingFunction.value().unwrap();
        flexibleTracks.push_back(&track);
      }
    }

    // If this value is less than 1, set it to 1 instead.
    if (flexFactorSum < 1.0f) {
      flexFactorSum = 1.0f;
    }

    // Let the hypothetical fr size be the leftover space divided by the flex factor sum.
    auto hypotheticalFrSize = leftoverSpace / flexFactorSum;
    // If the product of the hypothetical fr size and a flexible track's flex factor is less than the track's base size, restart this algorithm treating all such tracks as inflexible.
    std::unordered_set<GridTrackSize*> inflexibleTracks;
    for (auto& track : flexibleTracks) {
      if (track->maxSizingFunction.isStretch() && track->maxSizingFunction.value().isDefined()) {
        float flexFactor = track->maxSizingFunction.value().unwrap();
        if (hypotheticalFrSize * flexFactor < track->baseSize) {
          inflexibleTracks.insert(track);
        }
      }
    }

    // restart this algorithm treating all such tracks as inflexible.
    if (!inflexibleTracks.empty()) {
      inflexibleTracks.insert(nonFlexibleTracks.begin(), nonFlexibleTracks.end());
      return findFrSize(dimension, startIndex, endIndex, spaceToFill, inflexibleTracks);
    }

    return hypotheticalFrSize;
  }

  // 11.8. Stretch auto Tracks
  // https://www.w3.org/TR/css-grid-1/#algo-stretch
  void stretchAutoTracks(Dimension dimension) {
    // Fast path - if tracks are fixed-sized, skip below steps
    bool hasNonFixedTracks = dimension == Dimension::Width ? hasNonFixedColumnTracks : hasNonFixedRowTracks;
    if (!hasNonFixedTracks) {
      return;
    }

    auto& gridTracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;

    // When the content-distribution property of the grid container is normal or stretch in this axis, this step expands tracks that have an auto max track sizing function by dividing any remaining positive, definite free space equally amongst them. If the free space is indefinite, but the grid container has a definite min-width/height, use that size to calculate the free space for this step instead.
    auto shouldStretch = false;
    if (dimension == Dimension::Width) {
      shouldStretch = node->style().justifyContent() == Justify::Stretch;
    } else {
      shouldStretch = node->style().alignContent() == Align::Stretch;
    }

    if (shouldStretch) {
      // Count only auto tracks for distribution
      std::vector<GridTrackSize*> autoTracks;
      for (auto& track : gridTracks) {
        if (isAutoSizingFunction(track.maxSizingFunction, containerSize)) {
          autoTracks.push_back(&track);
        }
      }

      if (autoTracks.empty()) {
        return;
      }

      float freeSpace = calculateFreeSpace(dimension);

      // If the free space is indefinite, but the grid container has a definite min-width/height, use that size to calculate the free space for this step instead.
      if (!yoga::isDefined(freeSpace)) {
        const float paddingAndBorder = dimension == Dimension::Width
          ? paddingAndBorderForAxis(node, FlexDirection::Row, direction, ownerWidth)
          : paddingAndBorderForAxis(node, FlexDirection::Column, direction, ownerWidth);
        
        auto minContainerBorderBoxSize = node->style().resolvedMinDimension(
            direction,
            dimension,
            dimension == Dimension::Width ? ownerWidth : ownerHeight,
            ownerWidth);
        auto minContainerInnerSize = minContainerBorderBoxSize.isDefined()
            ? minContainerBorderBoxSize.unwrap() - paddingAndBorder
            : YGUndefined;
        
        if (yoga::isDefined(minContainerInnerSize)) {
          auto totalBaseSize = getTotalBaseSize(dimension);
          freeSpace = std::max(0.0f, minContainerInnerSize - totalBaseSize);
        }
      }

      if (yoga::isDefined(freeSpace) && freeSpace > 0.0f && !yoga::inexactEquals(freeSpace, 0.0f)) {
        // Divide free space equally among auto tracks only
        auto freeSpacePerAutoTrack = freeSpace / autoTracks.size();
        for (auto& track : autoTracks) {
          track->baseSize += freeSpacePerAutoTrack;
        }
      }
    }
  };

  // https://www.w3.org/TR/css-grid-1/#free-space
  float calculateFreeSpace(Dimension dimension) {
    float freeSpace = YGUndefined;
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    if (yoga::isDefined(containerSize)) {
      auto totalBaseSize = getTotalBaseSize(dimension);
      freeSpace = std::max(0.0f, containerSize - totalBaseSize);
    }

    return freeSpace;
  }
  
  float measureItem(const GridItem& item, Dimension dimension, const ItemConstraint& constraints) {
    calculateLayoutInternal(
        item.node,
        constraints.width,
        constraints.height,
        node->getLayout().direction(),
        constraints.widthSizingMode,
        constraints.heightSizingMode,
        constraints.containingBlockWidth,
        constraints.containingBlockHeight,
        false,
        LayoutPassReason::kMeasureChild,
        layoutMarkerData,
        depth + 1,
        generationCount);

    return item.node->getLayout().measuredDimension(dimension);
  }

  float getMinimumContentContribution(const GridItem& item, Dimension dimension, const ItemConstraint& itemConstraints) {
    // Yoga does not support min-content yet, so we use content size suggestion
    // TODO: review approach
    auto marginForAxis = item.node->style().computeMarginForAxis(
      dimension == Dimension::Width ? FlexDirection::Row : FlexDirection::Column,
      itemConstraints.containingBlockWidth);
    float contribution = contentSizeSuggestion(item, dimension, itemConstraints) + marginForAxis;

    if (dimension == Dimension::Height) {
      contribution += item.baselineShim;
    }
    return contribution;
  }

  float getMaxContentContribution(const GridItem& item, Dimension dimension, const ItemConstraint& itemConstraints) {
    auto marginForAxis = item.node->style().computeMarginForAxis(
      dimension == Dimension::Width ? FlexDirection::Row : FlexDirection::Column,
      itemConstraints.containingBlockWidth);
    float contribution = measureItem(item, dimension, itemConstraints) + marginForAxis;

    if (dimension == Dimension::Height) {
      contribution += item.baselineShim;
    }
    return contribution;
  }

  // https://www.w3.org/TR/css-grid-1/#min-size-auto
  float autoMinimumSize(const GridItem& item, Dimension dimension, const ItemConstraint& itemConstraints) {
    auto overflow = item.node->style().overflow();
    auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    size_t startIndex = dimension == Dimension::Width ? item.columnStart : item.rowStart;
    size_t endIndex = dimension == Dimension::Width ? item.columnEnd : item.rowEnd;
    
    bool isScrollableOverflowValue = overflow == Overflow::Scroll || overflow == Overflow::Hidden;
    bool spansAutoMinTrack = false;
    bool spansMoreThanOneTrack = (endIndex - startIndex) > 1;
    bool spansFlexibleTrack = false;
    
    for (size_t trackIndex = startIndex; trackIndex < endIndex; trackIndex++) {
      auto& track = tracks[trackIndex];
      if (track.minSizingFunction.isAuto()) {
        spansAutoMinTrack = true;
      }
      
      if (isFlexibleSizingFunction(track.maxSizingFunction)) {
        spansFlexibleTrack = true;
      }
    }
    
    // automatic minimum size in a given axis is the
    // content-based minimum size if all of the following are true:
    // 1. its computed overflow is not a scrollable overflow value
    // 2. it spans at least one track in that axis whose min track sizing function is auto
    // 3. if it spans more than one track in that axis, none of those tracks are flexible
    // Otherwise, the automatic minimum size is zero.
    if (
        !isScrollableOverflowValue &&
        spansAutoMinTrack &&
        // If it spans only one track, skip flexible check (allowed).
        // If it spans more than one track, then none may be flexible.
        (!spansMoreThanOneTrack || !spansFlexibleTrack)
    ) {
      return contentBasedMinimumSize(item, dimension, itemConstraints);
    }

    return 0.0f;
  }

  // https://www.w3.org/TR/css-grid-1/#content-based-minimum-size
  float contentBasedMinimumSize(const GridItem& item, Dimension dimension, const ItemConstraint& itemConstraints) {
    float result = 0.0f;
    auto containingBlockWidth = itemConstraints.containingBlockWidth;
    auto containingBlockHeight = itemConstraints.containingBlockHeight;
    auto containingBlockSize = dimension == Dimension::Width ? containingBlockWidth : containingBlockHeight;
    auto aspectRatio = item.node->style().aspectRatio();
    Dimension orthogonalDimension = dimension == Dimension::Width ? Dimension::Height : Dimension::Width;
    auto orthogonalContainingBlockSize = orthogonalDimension == Dimension::Width ? containingBlockWidth : containingBlockHeight;

    // Check if the orthogonal dimension is effectively definite.
    // This is true if:
    // 1. The item has a definite styled length in the orthogonal dimension, OR
    // 2. The item is stretch-aligned with a definite containing block in that dimension
    //    (the item constraints will have StretchFit mode in this case)
    auto orthogonalSizingMode = orthogonalDimension == Dimension::Width
        ? itemConstraints.widthSizingMode
        : itemConstraints.heightSizingMode;
    bool orthogonalDimensionIsDefinite =
        item.node->hasDefiniteLength(orthogonalDimension, orthogonalContainingBlockSize) ||
            (orthogonalSizingMode == SizingMode::StretchFit && yoga::isDefined(orthogonalContainingBlockSize));

    // For border-box model, definite sizes already include padding and border
    if (item.node->hasDefiniteLength(dimension, containingBlockSize)) {
      result = item.node->getResolvedDimension(
          direction,
          dimension,
          containingBlockSize,
          containingBlockSize
      ).unwrap();
    }
    else if (aspectRatio.isDefined() && orthogonalDimensionIsDefinite) {
      // Use transferred size suggestion when aspect-ratio is defined and
      // the orthogonal dimension is effectively definite (either by styled size
      // or by stretch alignment with a known containing block size)
      auto suggestedSize = transferredSizeSuggestion(item, dimension, itemConstraints);
      if (suggestedSize.isDefined()) {
        result = suggestedSize.unwrap();
      }
    } else {
      // Content size suggestion: min-content clamped by opposite-axis min/max through aspect ratio
      result = contentSizeSuggestion(item, dimension, itemConstraints);
    }

    // However, if in a given dimension the grid item spans only grid tracks 
    // that have a fixed max track sizing function, then its specified size suggestion 
    // and content size suggestion in that dimension (and its input from this dimension 
    // to the transferred size suggestion in the opposite dimension) are further clamped 
    // to less than or equal to the stretch fit into the grid area’s maximum size in that dimension, 
    // as represented by the sum of those grid tracks’ max track sizing functions plus any intervening fixed gutters.)
    auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    float containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    auto gap = node->style().computeGapForDimension(dimension, containerSize);
    size_t startIndex = dimension == Dimension::Width ? item.columnStart : item.rowStart;
    size_t endIndex = dimension == Dimension::Width ? item.columnEnd : item.rowEnd;

    bool allTracksHaveFixedMax = true;
    float stretchFitMax = 0.0f;
    for (size_t trackIndex = startIndex; trackIndex < endIndex; trackIndex++) {
      auto& track = tracks[trackIndex];
      if (!isFixedSizingFunction(track.maxSizingFunction, containerSize)) {
        allTracksHaveFixedMax = false;
        break;
      }

      auto resolved = track.maxSizingFunction.resolve(containerSize);
      if (resolved.isDefined()) {
        stretchFitMax += resolved.unwrap();
      }

      // Add gap (except after last track)
      if (trackIndex < endIndex - 1) {
        stretchFitMax += gap;
      }
    }

    if (allTracksHaveFixedMax) {
      result = std::min(result, stretchFitMax);
    }

    // In all cases, the size suggestion is additionally clamped by the maximum size in the affected axis, if it's definite.
    auto maxSize = item.node->style().maxDimension(dimension);
    if (maxSize.isDefined()) {
      auto resolvedMaxSize = maxSize.resolve(containingBlockSize);
      if (resolvedMaxSize.isDefined()) {
        result = std::min(result, resolvedMaxSize.unwrap());
      }
    }

    return result;
  }

  // https://www.w3.org/TR/css-grid-1/#content-size-suggestion
  float contentSizeSuggestion(const GridItem& item, Dimension dimension, const ItemConstraint& itemConstraints) {
    float minContentSize = measureItem(item, dimension, itemConstraints);

    // Clamp by opposite-axis min/max sizes converted through aspect ratio
    auto aspectRatio = item.node->style().aspectRatio();
    if (aspectRatio.isDefined()) {
      minContentSize = clampByOrthogonalMinMax(item, dimension, itemConstraints, minContentSize);
    }

    return minContentSize;
  }

  // Helper to clamp a size by orthogonal min/max converted through aspect ratio
  float clampByOrthogonalMinMax(const GridItem& item, Dimension dimension, const ItemConstraint& itemConstraints, float size) {
    auto aspectRatio = item.node->style().aspectRatio();
    if (!aspectRatio.isDefined()) {
      return size;
    }

    Dimension orthogonalDimension = dimension == Dimension::Width ? Dimension::Height : Dimension::Width;
    auto orthogonalContainingBlockSize = orthogonalDimension == Dimension::Width
        ? itemConstraints.containingBlockWidth
        : itemConstraints.containingBlockHeight;

    // Clamp by opposite-axis minimum size (converted through aspect ratio)
    auto orthogonalMinSize = item.node->style().minDimension(orthogonalDimension);
    if (orthogonalMinSize.isDefined()) {
      auto resolvedOrthogonalMinSize = orthogonalMinSize.resolve(orthogonalContainingBlockSize);
      if (resolvedOrthogonalMinSize.isDefined()) {
        float convertedMinSize = convertThroughAspectRatio(
            resolvedOrthogonalMinSize.unwrap(), aspectRatio.unwrap(), dimension);
        size = std::max(size, convertedMinSize);
      }
    }

    // Clamp by opposite-axis maximum size (converted through aspect ratio)
    auto orthogonalMaxSize = item.node->style().maxDimension(orthogonalDimension);
    if (orthogonalMaxSize.isDefined()) {
      auto resolvedOrthogonalMaxSize = orthogonalMaxSize.resolve(orthogonalContainingBlockSize);
      if (resolvedOrthogonalMaxSize.isDefined()) {
        float convertedMaxSize = convertThroughAspectRatio(
            resolvedOrthogonalMaxSize.unwrap(), aspectRatio.unwrap(), dimension);
        size = std::min(size, convertedMaxSize);
      }
    }

    return size;
  }

  float convertThroughAspectRatio(float orthogonalSize, float aspectRatio, Dimension targetDimension) {
    if (targetDimension == Dimension::Width) {
      // width = height * aspectRatio
      return orthogonalSize * aspectRatio;
    } else {
      // height = width / aspectRatio
      return orthogonalSize / aspectRatio;
    }
  }
  
  // https://www.w3.org/TR/css-grid-1/#minimum-contribution
  float getMinimumContribution(const GridItem& item, Dimension dimension, const ItemConstraint& itemConstraints) {
    auto preferredSize = item.node->style().dimension(dimension);
    auto containingBlockSize = dimension == Dimension::Width ? itemConstraints.containingBlockWidth : itemConstraints.containingBlockHeight;

    float contribution = 0.0f;
    if (preferredSize.isAuto() || preferredSize.isPercent()) {
      auto minSize = item.node->style().minDimension(dimension);
      // CSS spec has initial min-width size to auto, but yoga keeps it undefined.
      if (minSize.isAuto() || !minSize.isDefined()) {
        auto newMinimumSize = autoMinimumSize(item, dimension, itemConstraints);
        auto marginForAxis = item.node->style().computeMarginForAxis(
          dimension == Dimension::Width ? FlexDirection::Row : FlexDirection::Column,
          itemConstraints.containingBlockWidth);
        contribution = newMinimumSize + marginForAxis;
      } else {
        auto resolvedMinSize = minSize.resolve(containingBlockSize);
        auto marginForAxis = item.node->style().computeMarginForAxis(
          dimension == Dimension::Width ? FlexDirection::Row : FlexDirection::Column,
          itemConstraints.containingBlockWidth);
        contribution = resolvedMinSize.unwrap() + marginForAxis;
      }
    } else {
      return getMinimumContentContribution(item, dimension, itemConstraints);
    }

    if (dimension == Dimension::Height) {
      contribution += item.baselineShim;
    }
    return contribution;
  }

  FloatOptional transferredSizeSuggestion(const GridItem& item, Dimension dimension, const ItemConstraint& itemConstraints) {
    auto aspectRatio = item.node->style().aspectRatio();
    if (!aspectRatio.isDefined()) {
      return yoga::FloatOptional();
    }

    Dimension orthogonalDimension = dimension == Dimension::Width ? Dimension::Height : Dimension::Width;
    auto containingBlockWidth = itemConstraints.containingBlockWidth;
    auto containingBlockHeight = itemConstraints.containingBlockHeight;
    auto orthogonalContainingBlockSize = orthogonalDimension == Dimension::Width ? containingBlockWidth : containingBlockHeight;
    auto containingBlockSize = dimension == Dimension::Width ? containingBlockWidth : containingBlockHeight;

    float resolvedOrthogonalSize;
    auto orthogonalSizingMode = orthogonalDimension == Dimension::Width
        ? itemConstraints.widthSizingMode
        : itemConstraints.heightSizingMode;
    auto orthogonalAvailableSize = orthogonalDimension == Dimension::Width
        ? itemConstraints.width
        : itemConstraints.height;

    if (orthogonalSizingMode == SizingMode::StretchFit && yoga::isDefined(orthogonalAvailableSize)) {
      // For stretch-fit items, use the available size (minus margins which are already factored in)
      auto orthogonalMargin = item.node->style().computeMarginForAxis(
          orthogonalDimension == Dimension::Width ? FlexDirection::Row : FlexDirection::Column,
          containingBlockWidth);
      resolvedOrthogonalSize = orthogonalAvailableSize - orthogonalMargin;
    } else if (item.node->hasDefiniteLength(orthogonalDimension, orthogonalContainingBlockSize)) {
      // Fall back to styled size if available
      auto orthogonalSize = item.node->style().dimension(orthogonalDimension);
      resolvedOrthogonalSize = orthogonalSize.resolve(orthogonalContainingBlockSize).unwrap();
    } else {
      return yoga::FloatOptional();
    }

    // Clamp by opposite-axis min size if definite
    auto orthogonalMinSize = item.node->style().minDimension(orthogonalDimension);
    if (orthogonalMinSize.isDefined()) {
      auto resolvedOrthogonalMinSize = orthogonalMinSize.resolve(orthogonalContainingBlockSize);
      if (resolvedOrthogonalMinSize.isDefined()) {
        resolvedOrthogonalSize = std::max(resolvedOrthogonalSize, resolvedOrthogonalMinSize.unwrap());
      }
    }

    // Clamp by opposite-axis max size if definite
    auto orthogonalMaxSize = item.node->style().maxDimension(orthogonalDimension);
    if (orthogonalMaxSize.isDefined()) {
      auto resolvedOrthogonalMaxSize = orthogonalMaxSize.resolve(orthogonalContainingBlockSize);
      if (resolvedOrthogonalMaxSize.isDefined()) {
        resolvedOrthogonalSize = std::min(resolvedOrthogonalSize, resolvedOrthogonalMaxSize.unwrap());
      }
    }

    // Convert through aspect ratio
    float result;
    if (dimension == Dimension::Width) {
      result = resolvedOrthogonalSize * aspectRatio.unwrap();
    } else {
      result = resolvedOrthogonalSize / aspectRatio.unwrap();
    }

    // Cap by definite preferred size in the relevant axis
    auto preferredSize = item.node->style().dimension(dimension);
    if (preferredSize.isDefined()) {
      auto resolvedPreferredSize = preferredSize.resolve(containingBlockSize);
      if (resolvedPreferredSize.isDefined()) {
        result = std::min(result, resolvedPreferredSize.unwrap());
      }
    }

    // Cap by definite maximum size in the relevant axis
    auto maxSize = item.node->style().maxDimension(dimension);
    if (maxSize.isDefined()) {
      auto resolvedMaxSize = maxSize.resolve(containingBlockSize);
      if (resolvedMaxSize.isDefined()) {
        result = std::min(result, resolvedMaxSize.unwrap());
      }
    }

    return yoga::FloatOptional(result);
  }

  // https://www.w3.org/TR/css-grid-1/#limited-contribution
  float getLimitedMinimumContentContribution(const GridItem& item, Dimension dimension, const ItemConstraint& itemConstraints) {
    auto fixedTracksLimit = getFixedTracksLimit(item, dimension);
    auto minContentContribution = getMinimumContentContribution(item, dimension, itemConstraints);
    auto minimumContribution = getMinimumContribution(item, dimension, itemConstraints);
    
    if (yoga::isDefined(fixedTracksLimit)) {
      auto limitedContribution = std::min(minContentContribution, fixedTracksLimit);
      return std::max(limitedContribution, minimumContribution);
    }
    
    return std::max(minContentContribution, minimumContribution);
  }

  float getFixedTracksLimit(const GridItem& item, Dimension dimension) {
    float fixedTracksLimit = 0.0f;
    auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    
    size_t startIndex = dimension == Dimension::Width ? item.columnStart : item.rowStart;
    size_t endIndex = dimension == Dimension::Width ? item.columnEnd : item.rowEnd;
    auto gap = node->style().computeGapForDimension(dimension, containerSize);
    
    for (size_t trackIndex = startIndex; trackIndex < endIndex; trackIndex++) {
      auto& track = tracks[trackIndex];
      if (isFixedSizingFunction(track.maxSizingFunction, containerSize)) {
        auto resolved = track.maxSizingFunction.resolve(containerSize);
        if (resolved.isDefined()) {
          fixedTracksLimit += resolved.unwrap();
        }
        if (trackIndex < endIndex - 1) {
          fixedTracksLimit += gap;
        }
      } else {
        fixedTracksLimit = YGUndefined;
        break;
      }
    }
    
    return fixedTracksLimit;
  }

  bool isFixedSizingFunction(const StyleSizeLength& sizingFunction, float referenceLength) const {
    return sizingFunction.isDefined() && sizingFunction.resolve(referenceLength).isDefined();
  }

  bool isIntrinsicSizingFunction(const StyleSizeLength& sizingFunction, float referenceLength) const {
    return isAutoSizingFunction(sizingFunction, referenceLength);
  }

  bool isAutoSizingFunction(const StyleSizeLength& sizingFunction, float referenceLength) const {
    return sizingFunction.isAuto() || (sizingFunction.isPercent() && !yoga::isDefined(referenceLength));
  }

  bool isFlexibleSizingFunction(const StyleSizeLength& sizingFunction) const {
    return sizingFunction.isStretch();
  }

  bool isPercentageSizingFunction(const StyleSizeLength& sizingFunction) const {
    return sizingFunction.isPercent();
  }


  bool hasFlexibleTrackInRange(const std::vector<GridTrackSize>& tracks, size_t start, size_t end) {
    for (size_t i = start; i < end && i < tracks.size(); i++) {
      if (isFlexibleSizingFunction(tracks[i].maxSizingFunction)) {
        return true;
      }
    }
    return false;
  }

  float getTotalBaseSize(Dimension dimension) {
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    const auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    auto gap = node->style().computeGapForDimension(dimension, containerSize);

    float totalBaseSize = 0.0f;
    for (size_t i = 0; i < tracks.size(); i++) {
      totalBaseSize += tracks[i].baseSize;
      if (i < tracks.size() - 1) {
        totalBaseSize += gap;
      }
    }
    return totalBaseSize;
  }

  bool hasPercentageTracks(Dimension dimension) const {
    return dimension == Dimension::Width ? hasPercentageColumnTracks : hasPercentageRowTracks;
  }

  std::pair<float, float> getContainingBlockSizeForItem(const GridItem& item, float effectiveColumnGap, float effectiveRowGap) {
    float containingBlockWidth = 0.0f;
    float containingBlockHeight = 0.0f;
    
    // Calculate width: sum of spanned column tracks + gaps
    for (size_t i = item.columnStart; i < item.columnEnd && i < columnTracks.size(); i++) {
      containingBlockWidth += columnTracks[i].baseSize;
      // Add column gap if not the last spanned track
      if (i < item.columnEnd - 1) {
        containingBlockWidth += effectiveColumnGap;
      }
    }
    
    // Calculate height: sum of spanned row tracks + gaps
    for (size_t i = item.rowStart; i < item.rowEnd && i < rowTracks.size(); i++) {
      containingBlockHeight += rowTracks[i].baseSize;
      // Add row gap if not the last spanned track
      if (i < item.rowEnd - 1) {
        containingBlockHeight += effectiveRowGap;
      }
    }
    
    return std::make_pair(containingBlockWidth, containingBlockHeight);
  }

  ContentDistribution calculateContentDistribution(
    Dimension dimension,
    float freeSpace) {
    auto numTracks = dimension == Dimension::Width ? columnTracks.size() : rowTracks.size();
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    auto baseGap = node->style().computeGapForDimension(dimension, containerSize);
    
    ContentDistribution result;
    result.effectiveGap = baseGap;

    if (yoga::inexactEquals(freeSpace, 0.0f)) {
      return result;
    }

    if (dimension == Dimension::Width) {
      auto justifyContent = node->style().justifyContent();
      switch (justifyContent) {
        case Justify::Center:
          result.startOffset = freeSpace / 2.0f;
          break;

        case Justify::End:
          result.startOffset = freeSpace;
          break;

        case Justify::SpaceBetween:
          if (numTracks > 1) {
            // negative free space is not distributed with space between, checkout grid_justify_content_space_between_negative_space_gap fixture
            result.betweenTracksOffset = std::max(0.0f, freeSpace / (numTracks - 1));
          }
          break;

        case Justify::SpaceAround:
          if (numTracks > 0) {
            // negative free space is not distributed with space around, checkout grid_justify_content_space_around_negative_space_gap fixture
            result.betweenTracksOffset = std::max(0.0f, freeSpace / numTracks);
            result.startOffset = std::max(0.0f, result.betweenTracksOffset / 2.0f);
          }
          break;

        case Justify::SpaceEvenly:
          // negative free space is not distributed with space evenly, checkout grid_justify_content_space_evenly_negative_space_gap fixture
          result.betweenTracksOffset = std::max(0.0f, freeSpace / (numTracks + 1));
          result.startOffset = result.betweenTracksOffset;
          break;

        case Justify::Start:
        case Justify::FlexStart:
        case Justify::FlexEnd:
        case Justify::Stretch:
        case Justify::Auto:
        default:
          break;
      }
    } else {
      auto alignContent = node->style().alignContent();
      switch (alignContent) {
        case Align::Center:
          // content center works with negative free space too
          // refer grid_align_content_center_negative_space_gap fixture
          result.startOffset = freeSpace / 2.0f;
          break;
        case Align::End:
          result.startOffset = freeSpace;
          break;
        case Align::SpaceBetween:
          if (numTracks > 1) {
            // negative free space is not distributed with space between, checkout grid_align_content_space_between_negative_space_gap fixture
            result.betweenTracksOffset = std::max(0.0f, freeSpace / (numTracks - 1));
          }
          break;

        case Align::SpaceAround:
          if (numTracks > 0) {
            // negative free space is not distributed with space around, checkout grid_align_content_space_around_negative_space_gap fixture
            result.betweenTracksOffset = std::max(0.0f, freeSpace / numTracks);
            result.startOffset = std::max(0.0f, result.betweenTracksOffset / 2.0f);
          }
          break;

        case Align::SpaceEvenly:
          // negative free space is not distributed with space evenly, checkout grid_align_content_space_evenly_negative_space_gap fixture
          result.betweenTracksOffset = std::max(0.0f, freeSpace / (numTracks + 1));
          result.startOffset = result.betweenTracksOffset;
          break;

        case Align::Auto:
        case Align::FlexStart:
        case Align::FlexEnd:
        case Align::Stretch:
        case Align::Baseline:
        case Align::Start:
        default:
          break;
      }
    }

    result.effectiveGap = baseGap + result.betweenTracksOffset;
    return result;
  }

  ItemConstraint calculateItemConstraints(const GridItem& item, Dimension dimension) {
    float containingBlockWidth = YGUndefined;
    float containingBlockHeight = YGUndefined;
    if (dimension == Dimension::Width) {
      containingBlockHeight = crossDimensionEstimator(item);
    } else {
      containingBlockWidth = crossDimensionEstimator(item);
    }

    return calculateItemConstraints(item, containingBlockWidth, containingBlockHeight);
  }

  ItemConstraint calculateItemConstraints(
      const GridItem& item,
      float containingBlockWidth,
      float containingBlockHeight) {
    auto availableWidth = YGUndefined;
    auto availableHeight = YGUndefined;
    auto itemWidthSizingMode = SizingMode::MaxContent;
    auto itemHeightSizingMode = SizingMode::MaxContent;

    if (yoga::isDefined(containingBlockWidth)) {
      itemWidthSizingMode = SizingMode::FitContent;
      availableWidth = containingBlockWidth;
    }

    if (yoga::isDefined(containingBlockHeight)) {
      itemHeightSizingMode = SizingMode::FitContent;
      availableHeight = containingBlockHeight;
    }

    const auto marginInline = item.node->style().computeMarginForAxis(FlexDirection::Row, containingBlockWidth);
    if (item.node->hasDefiniteLength(Dimension::Width, containingBlockWidth)) {
      itemWidthSizingMode = SizingMode::StretchFit;
      auto resolvedWidth = item.node->getResolvedDimension(
        direction,
        Dimension::Width,
        containingBlockWidth,
        containingBlockWidth).unwrap();
      resolvedWidth = boundAxis(
        item.node,
        FlexDirection::Row,
        direction,
        resolvedWidth,
        containingBlockWidth,
        containingBlockWidth);
      availableWidth = resolvedWidth + marginInline;
    }

    const auto marginBlock = item.node->style().computeMarginForAxis(FlexDirection::Column, containingBlockWidth);
    if (item.node->hasDefiniteLength(Dimension::Height, containingBlockHeight)) {
      itemHeightSizingMode = SizingMode::StretchFit;
      auto resolvedHeight = item.node->getResolvedDimension(
        direction,
        Dimension::Height,
        containingBlockHeight,
        containingBlockWidth).unwrap();
      resolvedHeight = boundAxis(
        item.node,
        FlexDirection::Column,
        direction,
        resolvedHeight,
        containingBlockHeight,
        containingBlockWidth);
      availableHeight = resolvedHeight + marginBlock;
    }

    auto justifySelf = item.node->style().justifySelf();
    if (justifySelf == Justify::Auto) {
      justifySelf = node->style().justifyItems();
    }

    auto alignSelf = item.node->style().alignSelf();
    if (alignSelf == Align::Auto) {
      alignSelf = node->style().alignItems();
    }

    bool hasMarginInlineAuto = item.node->style().inlineStartMarginIsAuto(FlexDirection::Row, direction)
      || item.node->style().inlineEndMarginIsAuto(FlexDirection::Row, direction);
    bool hasMarginBlockAuto = item.node->style().inlineStartMarginIsAuto(FlexDirection::Column, direction)
      || item.node->style().inlineEndMarginIsAuto(FlexDirection::Column, direction);

    // For stretch-aligned items with a definite containing block size and no auto margins,
    // treat the item as having a definite size in that axis (it will stretch to fill).
    const auto& itemStyle = item.node->style();

    if (yoga::isDefined(containingBlockWidth) &&
        !item.node->hasDefiniteLength(Dimension::Width, containingBlockWidth) &&
        justifySelf == Justify::Stretch &&
        !hasMarginInlineAuto) {
      itemWidthSizingMode = SizingMode::StretchFit;
      availableWidth = containingBlockWidth;
    }

    if (yoga::isDefined(containingBlockHeight) &&
        !item.node->hasDefiniteLength(Dimension::Height, containingBlockHeight) &&
        alignSelf == Align::Stretch &&
        !hasMarginBlockAuto) {
      itemHeightSizingMode = SizingMode::StretchFit;
      availableHeight = containingBlockHeight;
    }

    // Handle aspect-ratio per CSS Sizing Level 4
    // https://drafts.csswg.org/css-sizing-4/#aspect-ratio
    if (itemStyle.aspectRatio().isDefined() &&
        !yoga::inexactEquals(itemStyle.aspectRatio().unwrap(), 0.0f)) {
      const float aspectRatio = itemStyle.aspectRatio().unwrap();
      auto maxHeight = itemStyle.maxDimension(Dimension::Height).resolve(containingBlockHeight);
      auto maxWidth = itemStyle.maxDimension(Dimension::Width).resolve(containingBlockWidth);

      // grid_aspect_ratio_fill_child_max_width fixture
      if (itemWidthSizingMode == SizingMode::StretchFit &&
          itemHeightSizingMode == SizingMode::StretchFit) {
        if (maxHeight.isDefined()) {
          float constrainedHeight = std::min(availableHeight - marginBlock, maxHeight.unwrap());
          availableHeight = marginBlock + constrainedHeight;
          availableWidth = marginInline + constrainedHeight * aspectRatio;
        } else if (maxWidth.isDefined()) {
          float constrainedWidth = std::min(availableWidth - marginInline, maxWidth.unwrap());
          availableWidth = marginInline + constrainedWidth;
          availableHeight = marginBlock + constrainedWidth / aspectRatio;
        }
      } else if (itemWidthSizingMode == SizingMode::StretchFit &&
                 itemHeightSizingMode != SizingMode::StretchFit) {
        availableHeight = marginBlock + (availableWidth - marginInline) / aspectRatio;
        if (maxHeight.isDefined() && availableHeight - marginBlock > maxHeight.unwrap()) {
          availableHeight = marginBlock + maxHeight.unwrap();
          availableWidth = marginInline + maxHeight.unwrap() * aspectRatio;
        }
        itemHeightSizingMode = SizingMode::StretchFit;
      } else if (itemHeightSizingMode == SizingMode::StretchFit &&
                 itemWidthSizingMode != SizingMode::StretchFit) {
        availableWidth = marginInline + (availableHeight - marginBlock) * aspectRatio;
        if (maxWidth.isDefined() && availableWidth - marginInline > maxWidth.unwrap()) {
          availableWidth = marginInline + maxWidth.unwrap();
          availableHeight = marginBlock + maxWidth.unwrap() / aspectRatio;
        }
        itemWidthSizingMode = SizingMode::StretchFit;
      }
    }

    constrainMaxSizeForMode(item.node,
      direction,
      FlexDirection::Row,
      containingBlockWidth,
      containingBlockWidth,
      &itemWidthSizingMode,
      &availableWidth);
    constrainMaxSizeForMode(item.node,
      direction,
      FlexDirection::Column,
      containingBlockHeight,
      containingBlockWidth,
      &itemHeightSizingMode,
      &availableHeight);

    return ItemConstraint{
      availableWidth,
      availableHeight,
      itemWidthSizingMode,
      itemHeightSizingMode,
      containingBlockWidth,
      containingBlockHeight
    };
  }

  float calculateEffectiveRowGapForEstimation() {
    auto rowGap = node->style().computeGapForDimension(Dimension::Height, containerInnerHeight);

    if (!yoga::isDefined(containerInnerHeight)) {
      return rowGap;
    }

    bool allTracksDefinite = true;
    float totalTrackSize = 0.0f;
    for (auto& track : rowTracks) {
      if (isFixedSizingFunction(track.maxSizingFunction, containerInnerHeight)) {
        totalTrackSize += track.maxSizingFunction.resolve(containerInnerHeight).unwrap();
      } else {
        allTracksDefinite = false;
        break;
      }
    }

    if (!allTracksDefinite) {
      return rowGap;
    }

    float totalGapSize = rowTracks.size() > 1 ? rowGap * (rowTracks.size() - 1) : 0.0f;
    float freeSpace = containerInnerHeight - totalTrackSize - totalGapSize;

    auto distribution = calculateContentDistribution(Dimension::Height, freeSpace);

    return distribution.effectiveGap;
  }

  float calculateEffectiveRowGapFromBaseSizes() {
    auto rowGap = node->style().computeGapForDimension(Dimension::Height, containerInnerHeight);

    if (!yoga::isDefined(containerInnerHeight)) {
      return rowGap;
    }

    float totalTrackSize = 0.0f;
    for (auto& track : rowTracks) {
      totalTrackSize += track.baseSize;
    }

    float totalGapSize = rowTracks.size() > 1 ? rowGap * (rowTracks.size() - 1) : 0.0f;
    float freeSpace = containerInnerHeight - totalTrackSize - totalGapSize;

    auto distribution = calculateContentDistribution(Dimension::Height, freeSpace);

    return distribution.effectiveGap;
  }

  float calculateEffectiveColumnGapFromBaseSizes() {
    auto columnGap = node->style().computeGapForDimension(Dimension::Width, containerInnerWidth);

    if (!yoga::isDefined(containerInnerWidth)) {
      return columnGap;
    }

    float totalTrackSize = 0.0f;
    for (auto& track : columnTracks) {
      totalTrackSize += track.baseSize;
    }

    float totalGapSize = columnTracks.size() > 1 ? columnGap * (columnTracks.size() - 1) : 0.0f;
    float freeSpace = containerInnerWidth - totalTrackSize - totalGapSize;

    auto distribution = calculateContentDistribution(Dimension::Width, freeSpace);

    return distribution.effectiveGap;
  }

  std::vector<float> getItemMinContentContributions(Dimension dimension,
    CrossDimensionEstimator estimator) {
    std::vector<float> contributions;
    contributions.reserve(gridItems.size());

    for (const auto& item : gridItems) {
      float crossDimSize = estimator ? estimator(item) : YGUndefined;
      float containingBlockWidth = dimension == Dimension::Width ? YGUndefined : crossDimSize;
      float containingBlockHeight = dimension == Dimension::Width ? crossDimSize : YGUndefined;
      auto itemConstraints = calculateItemConstraints(item, containingBlockWidth, containingBlockHeight);
      float contribution = getMinimumContentContribution(item, dimension, itemConstraints);
      contributions.push_back(contribution);
    }
    return contributions;
  }

  bool contributionsChanged(const std::vector<float>& before, const std::vector<float>& after) {
    if (before.size() != after.size()) {
      return true;
    }

    for (size_t i = 0; i < before.size(); i++) {
      if (before[i] != after[i]) {
        return true;
      }
    }
    return false;
  }

  bool itemSizeDependsOnIntrinsicTracks(const GridItem& item) const {
    auto heightStyle = item.node->style().dimension(Dimension::Height);
    if (heightStyle.isPercent()) {
      for (size_t i = item.rowStart; i < item.rowEnd && i < rowTracks.size(); i++) {
        if (isIntrinsicSizingFunction(rowTracks[i].minSizingFunction, containerInnerHeight) ||
            isIntrinsicSizingFunction(rowTracks[i].maxSizingFunction, containerInnerHeight)) {
          return true;
        }
      }
    }
    return false;
  }
};

} // namespace facebook::yoga
