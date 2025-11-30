/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
*/
#include <yoga/algorithm/BoundAxis.h>
#include <yoga/algorithm/CalculateLayout.h>
#include <yoga/algorithm/grid/GridLayout.h>
#include <yoga/numeric/Comparison.h>
#include <yoga/style/StyleSizeLength.h>
#include <unordered_set>
#include <unordered_map>
#include <map>

namespace facebook::yoga {

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

// Function type for estimating cross-dimension containing block size
// Takes an item and returns the estimated containing block size in the cross dimension
using CrossDimensionEstimator = std::function<float(const GridItemArea&)>;

struct TrackSizing {
  Node* node;
  std::vector<GridTrackSize>& columnTracks;
  std::vector<GridTrackSize>& rowTracks;
  float containerInnerWidth;
  float containerInnerHeight;
  std::vector<GridItemArea>& gridItemAreas;
  SizingMode widthSizingMode;
  SizingMode heightSizingMode;
  Direction direction;
  float ownerWidth;
  float ownerHeight;
  LayoutData& layoutMarkerData;
  uint32_t depth;
  uint32_t generationCount;
  CrossDimensionEstimator crossDimensionEstimator;

  TrackSizing(
    yoga::Node* node,
    std::vector<GridTrackSize>& columnTracks,
    std::vector<GridTrackSize>& rowTracks, 
    float containerInnerWidth, 
    float containerInnerHeight,
    std::vector<GridItemArea>& gridItemAreas,
    SizingMode widthSizingMode,
    SizingMode heightSizingMode,
    Direction direction,
    float ownerWidth,
    float ownerHeight,
    LayoutData& layoutMarkerData,
    uint32_t depth,
    uint32_t generationCount) : 
    node(node),
    columnTracks(columnTracks), 
    rowTracks(rowTracks), 
    containerInnerWidth(containerInnerWidth), 
    containerInnerHeight(containerInnerHeight), 
    gridItemAreas(gridItemAreas),
    widthSizingMode(widthSizingMode),
    heightSizingMode(heightSizingMode),
    direction(direction),
    ownerWidth(ownerWidth),
    ownerHeight(ownerHeight),
    layoutMarkerData(layoutMarkerData),
    depth(depth),
    generationCount(generationCount) {}

  // https://www.w3.org/TR/css-grid-1/#algo-track-sizing
  void runTrackSizing(Dimension dimension, CrossDimensionEstimator estimator = nullptr) {
    // Store the estimator for use in calculateItemConstraints
    crossDimensionEstimator = estimator;

    // Step 1: Initialize Track Sizes
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

  // Calculate min-content contributions for all items in a dimension
  std::vector<float> getItemMinContentContributions(
      Dimension dimension,
      CrossDimensionEstimator estimator) {
    std::vector<float> contributions;
    contributions.reserve(gridItemAreas.size());

    for (const auto& item : gridItemAreas) {
      float crossDimSize = estimator ? estimator(item) : YGUndefined;
      float containingBlockWidth = dimension == Dimension::Width ? YGUndefined : crossDimSize;
      float containingBlockHeight = dimension == Dimension::Width ? crossDimSize : YGUndefined;
      auto itemConstraints = calculateItemConstraints(item, containingBlockWidth, containingBlockHeight);
      float contribution = getMinimumContentContribution(item, dimension, itemConstraints);
      contributions.push_back(contribution);
    }
    return contributions;
  }

  // Check if any item's min-content contribution changed
  bool contributionsChanged(
      const std::vector<float>& before,
      const std::vector<float>& after) {
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

  // https://www.w3.org/TR/css-grid-1/#algo-grid-sizing
  // Runs all 4 steps of the Grid Sizing Algorithm (11.1.1 through 11.1.4)
  void runGridSizingAlgorithm() {
    // 11.1.1 First, the track sizing algorithm is used to resolve the sizes of the grid columns.
    // For items needing block-axis size: use definite row sizes if available, else undefined.
    auto effectiveRowGap = calculateEffectiveRowGapForEstimation();

    auto estimateRowHeightStep1 = [&](const GridItemArea& item) -> float {
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

    runTrackSizing(Dimension::Width, estimateRowHeightStep1);

    // Save column contributions after step 11.1.1
    auto columnContributionsAfterStep1 = getItemMinContentContributions(Dimension::Width, estimateRowHeightStep1);

    // 11.1.2 Next, the track sizing algorithm resolves the sizes of the grid rows.
    // Uses actual column sizes from step 11.1.1.
    auto effectiveColumnGap = calculateEffectiveColumnGapFromBaseSizes();

    auto estimateColumnWidthStep2 = [&](const GridItemArea& item) -> float {
      float itemAreaWidth = 0.0f;
      for (size_t i = item.columnStart; i < item.columnEnd && i < columnTracks.size(); i++) {
        itemAreaWidth += columnTracks[i].baseSize;
        if (i < item.columnEnd - 1) {
          itemAreaWidth += effectiveColumnGap;
        }
      }
      return itemAreaWidth;
    };

    runTrackSizing(Dimension::Height, estimateColumnWidthStep2);

    // Save row contributions after step 11.1.2
    auto rowContributionsAfterStep2 = getItemMinContentContributions(Dimension::Height, estimateColumnWidthStep2);

    // 11.1.3 Then, if the min-content contribution of any grid item has changed
    // based on the row sizes calculated in step 2, re-resolve column sizes (once only).
    effectiveRowGap = calculateEffectiveRowGapFromBaseSizes();

    auto estimateRowHeightStep3 = [&](const GridItemArea& item) -> float {
      float containingBlockHeight = 0.0f;
      for (size_t i = item.rowStart; i < item.rowEnd && i < rowTracks.size(); i++) {
        containingBlockHeight += rowTracks[i].baseSize;
        if (i < item.rowEnd - 1) {
          containingBlockHeight += effectiveRowGap;
        }
      }
      return containingBlockHeight;
    };

    // Check if any item's column contribution changed with actual row heights
    auto columnContributionsStep3 = getItemMinContentContributions(Dimension::Width, estimateRowHeightStep3);

    if (contributionsChanged(columnContributionsAfterStep1, columnContributionsStep3)) {
      runTrackSizing(Dimension::Width, estimateRowHeightStep3);

      // 11.1.4 Next, if the min-content contribution of any grid item has changed
      // based on the column sizes calculated in step 3, re-resolve row sizes (once only).
      effectiveColumnGap = calculateEffectiveColumnGapFromBaseSizes();

      auto estimateColumnWidthStep4 = [&](const GridItemArea& item) -> float {
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

      if (contributionsChanged(rowContributionsAfterStep2, rowContributionsStep4)) {
        runTrackSizing(Dimension::Height, estimateColumnWidthStep4);
      }
    }
  }

  // https://www.w3.org/TR/css-grid-1/#algo-init
  void initializeTrackSizes(Dimension dimension) {
    auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;

    for (size_t i = 0; i < tracks.size(); i++) {
      auto& track = tracks[i];
      if (isFixedSizingFunction(track.minSizingFunction, containerSize)) {
        auto resolved = track.minSizingFunction.resolve(containerSize);
        track.baseSize = resolved.unwrap();
      }
      else if (isIntrinsicSizingFunction(track.minSizingFunction, containerSize)) {
        track.baseSize = 0;
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
      }
      else if (isFlexibleSizingFunction(track.maxSizingFunction)) {
        track.growthLimit = INFINITY;
      }
      else {
        // THIS SHOULD NEVER HAPPEN
        track.growthLimit = INFINITY;
      }
  
      // In all cases, if the growth limit is less than the base size, increase the growth limit to match the base size.
      if (track.growthLimit < track.baseSize) {
        track.growthLimit = track.baseSize;
      }
    }
  }

  // 11.5 https://www.w3.org/TR/css-grid-1/#algo-content
  void resolveIntrinsicTrackSizes(Dimension dimension) {
    auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    // TODO: 1. Shim baseline-aligned items

    // Step. 2 and Step. 3 Increase sizes to accommodate spanning items
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

  // https://www.w3.org/TR/css-grid-1/#algo-spanning-items
  void accomodateSpanningItemsCrossingContentSizedTracks(Dimension dimension) {
    auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    auto sizingMode = dimension == Dimension::Width ? widthSizingMode : heightSizingMode;
    std::vector<GridItemArea> sortedItems = gridItemAreas;
    std::sort(sortedItems.begin(), sortedItems.end(), [dimension](const GridItemArea& a, const GridItemArea& b) {
      size_t spanA = dimension == Dimension::Width
        ? (a.columnEnd - a.columnStart)
        : (a.rowEnd - a.rowStart);
      size_t spanB = dimension == Dimension::Width
        ? (b.columnEnd - b.columnStart)
        : (b.rowEnd - b.rowStart);
      return spanA < spanB;
    });

    size_t previousSpan = 1;
    std::vector<std::tuple<GridItemArea, std::vector<GridTrackSize*>, std::vector<GridTrackSize*>, float>> itemsForIntrinsicMin;
    std::vector<std::tuple<GridItemArea, std::vector<GridTrackSize*>, std::vector<GridTrackSize*>, float>> itemsForIntrinsicMax;
    std::vector<std::tuple<GridItemArea, std::vector<GridTrackSize*>, std::vector<GridTrackSize*>, float>> itemsForMaxContentMax;

    auto distributeSpaceToTracksForItemsWithTheSameSpan = [&]() {
      // Step 1: For intrinsic minimums
      if (!itemsForIntrinsicMin.empty()) {
        distributeExtraSpaceAcrossSpannedTracks(dimension, itemsForIntrinsicMin, true);
        itemsForIntrinsicMin.clear();
      }

      // Step 2 and Step 3 are skipped since we're not supporting min-content and max-content yet

      // Step 4: If at this point any track's growth limit is now less than its base size, increase its growth limit to match its base size
      for (auto& track : tracks) {
        if (track.growthLimit < track.baseSize) {
          track.growthLimit = track.baseSize;
        }
      }

      // Step 5: For intrinsic maximums
      if (!itemsForIntrinsicMax.empty()) {
        distributeExtraSpaceAcrossSpannedTracks(dimension, itemsForIntrinsicMax, false);
        itemsForIntrinsicMax.clear();
      }

      // Step 6: For max-content maximums
      if (!itemsForMaxContentMax.empty()) {
        distributeExtraSpaceAcrossSpannedTracks(dimension, itemsForMaxContentMax, false);
        itemsForMaxContentMax.clear();
      }
    };

    for (auto& item: sortedItems) {
      auto startIndex = dimension == Dimension::Width ? item.columnStart : item.rowStart;
      auto endIndex = dimension == Dimension::Width ? item.columnEnd : item.rowEnd;
      size_t span = endIndex - startIndex;

      // span changed, start distributing space to intrinsic sizing tracks
      if (span > previousSpan) {
        distributeSpaceToTracksForItemsWithTheSameSpan();
        previousSpan = span;
      }

      std::vector<GridTrackSize*> intrinsicMinimumSizingFunctionTracks;
      std::vector<GridTrackSize*> intrinsicMaximumSizingFunctionTracks;
      std::vector<GridTrackSize*> maxContentMaximumSizingFunctionTracks;
      std::vector<GridTrackSize*> spannedTracks;

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

        spannedTracks.push_back(&tracks[i]);
      }

      if (hasFlexibleTrack) continue;

      auto itemConstraints = calculateItemConstraints(item, dimension);
      if (!intrinsicMinimumSizingFunctionTracks.empty()) {
        auto minimumContribution = sizingMode == SizingMode::MaxContent ? getLimitedMinimumContentContribution(item, dimension, itemConstraints) : getMinimumContribution(item, dimension, itemConstraints);
        itemsForIntrinsicMin.emplace_back(item, std::move(intrinsicMinimumSizingFunctionTracks), spannedTracks, minimumContribution);
      }

      if (!intrinsicMaximumSizingFunctionTracks.empty()) {
        auto minimumContentContribution = getMinimumContentContribution(item, dimension, itemConstraints);
        itemsForIntrinsicMax.emplace_back(item, std::move(intrinsicMaximumSizingFunctionTracks), spannedTracks, minimumContentContribution);
      }

      if (!maxContentMaximumSizingFunctionTracks.empty()) {
        auto maxContentContribution = getMaxContentContribution(item, dimension, itemConstraints);
        itemsForMaxContentMax.emplace_back(item, std::move(maxContentMaximumSizingFunctionTracks), std::move(spannedTracks), maxContentContribution);
      }
    }

    // Process last span
    distributeSpaceToTracksForItemsWithTheSameSpan();
    
  };

  void accomodateSpanningItemsCrossingFlexibleTracks(Dimension dimension) {
    auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    auto sizingMode = dimension == Dimension::Width ? widthSizingMode : heightSizingMode;
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;

    std::vector<std::tuple<GridItemArea, std::vector<GridTrackSize*>, std::vector<GridTrackSize*>, float>> itemsSpanningFlexible;

    for (auto& item : gridItemAreas) {
      auto spannedTracks = getTracksSpannedByItem(item, tracks, dimension);
      bool hasFlexibleTrack = false;
      std::vector<GridTrackSize*> intrinsicMinFlexibleTracks;

      for (auto& track : spannedTracks) {
        if (isFlexibleSizingFunction(track->maxSizingFunction)) {
          hasFlexibleTrack = true;

          if (isIntrinsicSizingFunction(track->minSizingFunction, containerSize)) {
            intrinsicMinFlexibleTracks.push_back(track);
          }
        }
      }

      if (hasFlexibleTrack && !intrinsicMinFlexibleTracks.empty()) {
        auto itemConstraints = calculateItemConstraints(item, dimension);
        auto minimumContribution = sizingMode == SizingMode::MaxContent
            ? getLimitedMinimumContentContribution(item, dimension, itemConstraints)
            : getMinimumContribution(item, dimension, itemConstraints);

        itemsSpanningFlexible.emplace_back(
            item,
            std::move(intrinsicMinFlexibleTracks),
            std::move(spannedTracks),
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
    std::vector<std::tuple<GridItemArea, std::vector<GridTrackSize*>, std::vector<GridTrackSize*>, float>>& items,
    bool isAffectedSizeBaseSize) {
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    std::unordered_map<GridTrackSize*, float> plannedIncrease;
    plannedIncrease.reserve(items.size());

    // 1. Maintain separately for each affected track a planned increase, initially set to 0. (This prevents the size increases from becoming order-dependent.)
    for (const auto& [item, affectedTracks, spannedTracks, sizeContribution] : items) {
      for (auto& track : affectedTracks) {
        plannedIncrease[track] = 0.0f;
      }
    }

    // 2. For each accommodated item, considering only tracks the item spans:
    for (const auto& [item, affectedTracks, spannedTracks, sizeContribution] : items) {
      std::unordered_map<GridTrackSize*, float> itemIncurredIncrease;
      itemIncurredIncrease.reserve(affectedTracks.size());
      for (auto& track: affectedTracks) {
        itemIncurredIncrease[track] = 0.0f;
      }

      // 2.1 Find the space to distribute
      float totalSpannedTracksSize = 0.0f;
      auto gap = node->style().computeGapForDimension(dimension, containerSize);
      for (auto& track: spannedTracks) {
        if (isAffectedSizeBaseSize) {
          totalSpannedTracksSize += track->baseSize;
        } else {
          // For infinite growth limits, substitute the track's base size
          totalSpannedTracksSize += track->growthLimit == INFINITY ? track->baseSize : track->growthLimit;
        }
        if (track != spannedTracks.back()) {
          // gaps are treated as tracks of fixed size. Item can span over gaps.
          totalSpannedTracksSize += gap;
        }
      }

      float spaceToDistribute = std::max(0.0f, sizeContribution - totalSpannedTracksSize);
      std::unordered_set<GridTrackSize*> frozenTracks;
      frozenTracks.reserve(affectedTracks.size());

      // 2.2. Distribute space up to limits
      while (frozenTracks.size() < affectedTracks.size() && spaceToDistribute > 0.0f && !yoga::inexactEquals(spaceToDistribute, 0.0f)) {
        auto unfrozenTrackCount = affectedTracks.size() - frozenTracks.size();
        auto distributionPerTrack = spaceToDistribute / unfrozenTrackCount;

        for (auto& track: affectedTracks) {
          if (frozenTracks.contains(track)) {
            continue;
          }

          float limit;
          float affectedSize;

          if (isAffectedSizeBaseSize) {
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
        for (auto& track: affectedTracks) {
          if (isIntrinsicSizingFunction(track->maxSizingFunction, containerSize)) {
            tracksToGrowBeyondLimits.push_back(track);
          }
        }

        // if there are no such tracks, then all affected tracks.
        if (isAffectedSizeBaseSize && tracksToGrowBeyondLimits.empty()) {
          tracksToGrowBeyondLimits = affectedTracks;
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
      for (auto& track: affectedTracks) {
        if (itemIncurredIncrease[track] > plannedIncrease[track]) {
          plannedIncrease[track] = itemIncurredIncrease[track];
        }
      }
    }

    // 3. Update the tracks affected sizes
    for (const auto& [track, increase] : plannedIncrease) {
      if (isAffectedSizeBaseSize) {
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
  // Distribute space to flexible tracks for multiple items using planned increase pattern
  void distributeSpaceToFlexibleTracksForItems(
    Dimension dimension,
    const std::vector<std::tuple<GridItemArea, std::vector<GridTrackSize*>, std::vector<GridTrackSize*>, float>>& items) {

    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    auto gap = node->style().computeGapForDimension(dimension, containerSize);

    // Step 1: Maintain planned increase for each affected track
    std::unordered_map<GridTrackSize*, float> plannedIncrease;
    for (const auto& [item, affectedTracks, spannedTracks, contribution] : items) {
      for (auto& track : affectedTracks) {
        plannedIncrease[track] = 0.0f;
      }
    }

    // Step 2: For each item
    for (const auto& [item, affectedTracks, spannedTracks, sizeContribution] : items) {
      std::unordered_map<GridTrackSize*, float> itemIncurredIncrease;
      for (auto& track : affectedTracks) {
        itemIncurredIncrease[track] = 0.0f;
      }

      // 2.1 Find space to distribute
      float totalSpannedTracksSize = 0.0f;
      for (auto& track : spannedTracks) {
        totalSpannedTracksSize += track->baseSize;
        if (track != spannedTracks.back()) {
          // gaps are treated as tracks of fixed size. Item can span over gaps.
          totalSpannedTracksSize += gap;
        }
      }

      float spaceToDistribute = std::max(0.0f, sizeContribution - totalSpannedTracksSize);

      float sumOfFlexFactors = 0.0f;
      for (auto& track : affectedTracks) {
        sumOfFlexFactors += track->maxSizingFunction.value().unwrap();
      }

      if (sumOfFlexFactors > 0.0f && !yoga::inexactEquals(sumOfFlexFactors, 0.0f)) {
        for (auto& track : affectedTracks) {
          auto flexFactor = track->maxSizingFunction.value().unwrap();
          auto increase = spaceToDistribute * flexFactor / sumOfFlexFactors;
          itemIncurredIncrease[track] += increase;
        }
      } else {
        auto equalShare = spaceToDistribute / affectedTracks.size();
        for (auto& track : affectedTracks) {
          itemIncurredIncrease[track] += equalShare;
        }
      }

      for (auto& track : affectedTracks) {
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

  // https://www.w3.org/TR/css-grid-1/#algo-grow-tracks
  void maximizeTrackSizes(Dimension dimension) {
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

  // https://www.w3.org/TR/css-grid-1/#algo-find-fr-size
  float findFrSize(Dimension dimension, const std::vector<GridTrackSize*>& tracks, float spaceToFill, std::unordered_set<GridTrackSize*> nonFlexibleTracks) {
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    auto gap = node->style().computeGapForDimension(dimension, containerSize);
    auto leftoverSpace = spaceToFill;
    auto flexFactorSum = 0.0f;
    std::vector<GridTrackSize*> flexibleTracks;

    for (size_t i = 0; i < tracks.size(); i++) {
      auto& track = tracks[i];
      // Let leftover space be the space to fill minus the base sizes of the non-flexible grid tracks.
      if (i < tracks.size() - 1) {
        // gap is treated as a non-flexible track
        leftoverSpace -= gap;
      }

      if (!isFlexibleSizingFunction(track->maxSizingFunction) || nonFlexibleTracks.contains(track)) {
        leftoverSpace -= track->baseSize;
      } 
      // Let flex factor sum be the sum of the flex factors of the flexible tracks.
      else if (track->maxSizingFunction.isStretch() && track->maxSizingFunction.value().isDefined()) {
        flexFactorSum += track->maxSizingFunction.value().unwrap();
        flexibleTracks.push_back(track);
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
      return findFrSize(dimension, tracks, spaceToFill, inflexibleTracks);
    }

    return hypotheticalFrSize;
  }

  // https://www.w3.org/TR/css-grid-1/#algo-flex-tracks
  void expandFlexibleTracks(Dimension dimension) {
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
      flexFraction = findFrSize(dimension, allGridTracks, containerSize, std::unordered_set<GridTrackSize*>());
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

      for (auto& item : gridItemAreas) {
          auto spannedTracks = getTracksSpannedByItem(item, gridTracks, dimension);
          if (!includesFlexibleTrack(spannedTracks)) {
            continue;
          }
          std::vector<GridTrackSize*> spannedTrackPointers;
          spannedTrackPointers.reserve(spannedTracks.size());
          for (auto& track : spannedTracks) {
            spannedTrackPointers.push_back(track);
          }
          auto itemConstraints = calculateItemConstraints(item, dimension);
          auto itemMaxContentContribution = getMaxContentContribution(item, dimension, itemConstraints);
          flexFraction = std::max(flexFraction, findFrSize(dimension, spannedTrackPointers, itemMaxContentContribution, std::unordered_set<GridTrackSize*>()));
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
        flexFraction = findFrSize(dimension, allGridTracks, minContainerSize, std::unordered_set<GridTrackSize*>());
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
        flexFraction = findFrSize(dimension, allGridTracks, maxContainerSize, std::unordered_set<GridTrackSize*>());
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

  void stretchAutoTracks(Dimension dimension) {
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

  float measureItem(const GridItemArea& item, Dimension dimension, const ItemConstraint& constraints) {
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

  float getMinimumContentContribution(const GridItemArea& item, Dimension dimension, const ItemConstraint& itemConstraints) {
    // Yoga does not support min-content yet, so we use content size suggestion
    // TODO: review approach
    auto marginForAxis = item.node->style().computeMarginForAxis(
      dimension == Dimension::Width ? FlexDirection::Row : FlexDirection::Column,
      itemConstraints.containingBlockWidth);
    return contentSizeSuggestion(item, dimension, itemConstraints) + marginForAxis;
  }

  float getMaxContentContribution(const GridItemArea& item, Dimension dimension, const ItemConstraint& itemConstraints) {
    auto marginForAxis = item.node->style().computeMarginForAxis(
      dimension == Dimension::Width ? FlexDirection::Row : FlexDirection::Column,
      itemConstraints.containingBlockWidth);
    return measureItem(item, dimension, itemConstraints) + marginForAxis;
  }

  // https://www.w3.org/TR/css-grid-1/#min-size-auto
  float autoMinimumSize(const GridItemArea& item, Dimension dimension, const ItemConstraint& itemConstraints) {
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
  float contentBasedMinimumSize(const GridItemArea& item, Dimension dimension, const ItemConstraint& itemConstraints) {
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
  float contentSizeSuggestion(const GridItemArea& item, Dimension dimension, const ItemConstraint& itemConstraints) {
    float minContentSize = measureItem(item, dimension, itemConstraints);

    // Clamp by opposite-axis min/max sizes converted through aspect ratio
    auto aspectRatio = item.node->style().aspectRatio();
    if (aspectRatio.isDefined()) {
      minContentSize = clampByOrthogonalMinMax(item, dimension, itemConstraints, minContentSize);
    }

    return minContentSize;
  }

  // Helper to clamp a size by orthogonal min/max converted through aspect ratio
  float clampByOrthogonalMinMax(const GridItemArea& item, Dimension dimension, const ItemConstraint& itemConstraints, float size) {
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
  float getMinimumContribution(const GridItemArea& item, Dimension dimension, const ItemConstraint& itemConstraints) {
    auto preferredSize = item.node->style().dimension(dimension);
    auto containingBlockSize = dimension == Dimension::Width ? itemConstraints.containingBlockWidth : itemConstraints.containingBlockHeight;

    if (preferredSize.isAuto() || preferredSize.isPercent()) {
      auto minSize = item.node->style().minDimension(dimension);
      // CSS spec has initial min-width size to auto, but yoga keeps it undefined.
      if (minSize.isAuto() || !minSize.isDefined()) {
        auto newMinimumSize = autoMinimumSize(item, dimension, itemConstraints);
        auto marginForAxis = item.node->style().computeMarginForAxis(
          dimension == Dimension::Width ? FlexDirection::Row : FlexDirection::Column,
          itemConstraints.containingBlockWidth);
        return newMinimumSize + marginForAxis;
      } else {
        auto resolvedMinSize = minSize.resolve(containingBlockSize);
        auto marginForAxis = item.node->style().computeMarginForAxis(
          dimension == Dimension::Width ? FlexDirection::Row : FlexDirection::Column,
          itemConstraints.containingBlockWidth);
        return resolvedMinSize.unwrap() + marginForAxis;
      }
    } else {
      return getMinimumContentContribution(item, dimension, itemConstraints);
    }
  }

  FloatOptional transferredSizeSuggestion(const GridItemArea& item, Dimension dimension, const ItemConstraint& itemConstraints) {
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
  float getLimitedMinimumContentContribution(const GridItemArea& item, Dimension dimension, const ItemConstraint& itemConstraints) {
    auto fixedTracksLimit = getFixedTracksLimit(item, dimension);
    auto minContentContribution = getMinimumContentContribution(item, dimension, itemConstraints);
    auto minimumContribution = getMinimumContribution(item, dimension, itemConstraints);
    
    if (yoga::isDefined(fixedTracksLimit)) {
      auto limitedContribution = std::min(minContentContribution, fixedTracksLimit);
      return std::max(limitedContribution, minimumContribution);
    }
    
    return std::max(minContentContribution, minimumContribution);
  }

  float getFixedTracksLimit(const GridItemArea& item, Dimension dimension) {
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


  bool isFixedSizingFunction(const StyleSizeLength& sizingFunction, float referenceLength) {
    return sizingFunction.isDefined() && sizingFunction.resolve(referenceLength).isDefined();
  }
  
  bool isIntrinsicSizingFunction(const StyleSizeLength& sizingFunction, float referenceLength) {
    return isAutoSizingFunction(sizingFunction, referenceLength);
  }
  
  bool isAutoSizingFunction(const StyleSizeLength& sizingFunction, float referenceLength) {
    return sizingFunction.isAuto() || (sizingFunction.isPercent() && !yoga::isDefined(referenceLength));
  }
  
  bool isFlexibleSizingFunction(const StyleSizeLength& sizingFunction) {
    return sizingFunction.isStretch();
  }

  std::vector<GridTrackSize*> getTracksSpannedByItem(
    const GridItemArea& item,
    std::vector<GridTrackSize>& tracks,
    Dimension dimension) {
    auto start = dimension == Dimension::Width ? item.columnStart : item.rowStart;
    auto end = dimension == Dimension::Width ? item.columnEnd : item.rowEnd;
    std::vector<GridTrackSize*> spannedTracks;
    spannedTracks.reserve(end - start);
    for (size_t i = start; i < end; ++i) {
      spannedTracks.push_back(&tracks[i]);
    }
    return spannedTracks;
  }

  bool includesFlexibleTrack(const std::vector<GridTrackSize*>& tracks) {
    for (auto& track: tracks) {
      if (isFlexibleSizingFunction(track->maxSizingFunction)) {
        return true;
      }
    }
    return false;
  }

  float getTotalBaseSize(Dimension dimension) {
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    auto tracks = dimension == Dimension::Width ? columnTracks : rowTracks;
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

  std::pair<float, float> getContainingBlockSizeForItem(const GridItemArea& item, float effectiveColumnGap, float effectiveRowGap) {
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

  ItemConstraint calculateItemConstraints(const GridItemArea& item, Dimension dimension) {
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
      const GridItemArea& item,
      float containingBlockWidth,
      float containingBlockHeight) {
    auto availableWidth = YGUndefined;
    auto availableHeight = YGUndefined;
    auto widthSizingMode = SizingMode::MaxContent;
    auto heightSizingMode = SizingMode::MaxContent;

    if (yoga::isDefined(containingBlockWidth)) {
      widthSizingMode = SizingMode::FitContent;
      availableWidth = containingBlockWidth;
    }

    if (yoga::isDefined(containingBlockHeight)) {
      heightSizingMode = SizingMode::FitContent;
      availableHeight = containingBlockHeight;
    }

    const auto marginInline = item.node->style().computeMarginForAxis(FlexDirection::Row, containingBlockWidth);
    if (item.node->hasDefiniteLength(Dimension::Width, containingBlockWidth)) {
      widthSizingMode = SizingMode::StretchFit;
      availableWidth = item.node->getResolvedDimension(
        direction,
        Dimension::Width,
        containingBlockWidth,
        containingBlockWidth).unwrap() + marginInline;
    }

    const auto marginBlock = item.node->style().computeMarginForAxis(FlexDirection::Column, containingBlockWidth);
    if (item.node->hasDefiniteLength(Dimension::Height, containingBlockHeight)) {
      heightSizingMode = SizingMode::StretchFit;
      availableHeight = item.node->getResolvedDimension(
        direction,
        Dimension::Height,
        containingBlockHeight,
        containingBlockWidth).unwrap() + marginBlock;
    }

    auto justifySelf = item.node->style().justifySelf();
    if (justifySelf == Justify::Auto) {
      justifySelf = node->style().justifyItems();
    }

    auto alignSelf = item.node->style().alignSelf();
    if (alignSelf == Align::Auto) {
      alignSelf = node->style().alignItems();
    }

    bool hasMarginInlineAuto = item.node->style().flexStartMarginIsAuto(FlexDirection::Row, direction)
      || item.node->style().flexEndMarginIsAuto(FlexDirection::Row, direction);
    bool hasMarginBlockAuto = item.node->style().flexStartMarginIsAuto(FlexDirection::Column, direction)
      || item.node->style().flexEndMarginIsAuto(FlexDirection::Column, direction);

    // For stretch-aligned items with a definite containing block size and no auto margins,
    // treat the item as having a definite size in that axis (it will stretch to fill).
    const auto& itemStyle = item.node->style();

    if (yoga::isDefined(containingBlockWidth) &&
        !item.node->hasDefiniteLength(Dimension::Width, containingBlockWidth) &&
        justifySelf == Justify::Stretch &&
        !hasMarginInlineAuto) {
      widthSizingMode = SizingMode::StretchFit;
      availableWidth = containingBlockWidth;
    }

    if (yoga::isDefined(containingBlockHeight) &&
        !item.node->hasDefiniteLength(Dimension::Height, containingBlockHeight) &&
        alignSelf == Align::Stretch &&
        !hasMarginBlockAuto) {
      heightSizingMode = SizingMode::StretchFit;
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
      if (widthSizingMode == SizingMode::StretchFit &&
          heightSizingMode == SizingMode::StretchFit) {
        if (maxHeight.isDefined()) {
          float constrainedHeight = std::min(availableHeight - marginBlock, maxHeight.unwrap());
          availableHeight = marginBlock + constrainedHeight;
          availableWidth = marginInline + constrainedHeight * aspectRatio;
        } else if (maxWidth.isDefined()) {
          float constrainedWidth = std::min(availableWidth - marginInline, maxWidth.unwrap());
          availableWidth = marginInline + constrainedWidth;
          availableHeight = marginBlock + constrainedWidth / aspectRatio;
        }
      } else if (widthSizingMode == SizingMode::StretchFit &&
                 heightSizingMode != SizingMode::StretchFit) {
        availableHeight = marginBlock + (availableWidth - marginInline) / aspectRatio;
        if (maxHeight.isDefined() && availableHeight - marginBlock > maxHeight.unwrap()) {
          availableHeight = marginBlock + maxHeight.unwrap();
          availableWidth = marginInline + maxHeight.unwrap() * aspectRatio;
        }
        heightSizingMode = SizingMode::StretchFit;
      } else if (heightSizingMode == SizingMode::StretchFit &&
                 widthSizingMode != SizingMode::StretchFit) {
        availableWidth = marginInline + (availableHeight - marginBlock) * aspectRatio;
        if (maxWidth.isDefined() && availableWidth - marginInline > maxWidth.unwrap()) {
          availableWidth = marginInline + maxWidth.unwrap();
          availableHeight = marginBlock + maxWidth.unwrap() / aspectRatio;
        }
        widthSizingMode = SizingMode::StretchFit;
      }
    }

    return ItemConstraint{
      availableWidth,
      availableHeight,
      widthSizingMode,
      heightSizingMode,
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
};

} // namespace facebook::yoga
