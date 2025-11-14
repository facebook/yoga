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
#include <set>

namespace facebook::yoga {

enum SpaceDistributionPhase {
  AccommodateMinimumContribution,
  AccommodateMaxContentContribution,
};

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
  void runTrackSizing(Dimension dimension) {
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
    std::map<size_t, std::vector<std::pair<GridItemArea, std::vector<GridTrackSize*>>>> itemsGroupedByIncreasingSpan;
    for (auto& item: gridItemAreas) {
      auto spannedTracks = getTracksSpannedByItem(item, tracks, dimension);
      if (includesFlexibleTrack(spannedTracks)) {
        continue;
      }
      int32_t span = dimension == Dimension::Width ? (item.columnEnd - item.columnStart) : (item.rowEnd - item.rowStart);
      itemsGroupedByIncreasingSpan[span].push_back({item, spannedTracks});
    }

    // auto sizingMode = dimension == Dimension::Width ? widthSizingMode : heightSizingMode;
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    auto sizingMode = dimension == Dimension::Width ? widthSizingMode : heightSizingMode;
    
    // we need to proceed in increasing order of span, keys are automatically sorted in std::map
    for (const auto& [span, itemsWithTracks] : itemsGroupedByIncreasingSpan) {
      for (const auto& [item, spannedTracks] : itemsWithTracks) {
        std::vector<GridTrackSize*> intrinsicMinimumSizingFunctionTracks;
        std::vector<GridTrackSize*> intrinsicMaximumSizingFunctionTracks;
        std::vector<GridTrackSize*> maxContentMaximumSizingFunctionTracks;

        for (auto& track: spannedTracks) {
          if (isIntrinsicSizingFunction(track->minSizingFunction, containerSize)) {
            intrinsicMinimumSizingFunctionTracks.push_back(track);
          }
          
          if (isIntrinsicSizingFunction(track->maxSizingFunction, containerSize)) {
            intrinsicMaximumSizingFunctionTracks.push_back(track);
          } 

          if (isAutoSizingFunction(track->maxSizingFunction, containerSize)) {
            maxContentMaximumSizingFunctionTracks.push_back(track);
          }
        }

        // 1. For intrinsic minimums
        if (intrinsicMinimumSizingFunctionTracks.size() > 0) {
          auto minimumContribution = sizingMode == SizingMode::MaxContent ? getLimitedMinimumContentContribution(item, dimension) : getMinimumContribution(item, dimension);
          distributeSpaceToTracksBaseSize(dimension, intrinsicMinimumSizingFunctionTracks, spannedTracks, minimumContribution, SpaceDistributionPhase::AccommodateMinimumContribution);
        }

        // 2. For content-based minimums
        // Unimplemented
        
        // 3. For max-content minimums        
        // Unimplemented
        
        // 4. If at this point any track’s growth limit is now less than its base size, increase its growth limit to match its base size.
        for (auto& track: spannedTracks) {
          if (track->growthLimit < track->baseSize) {
            track->growthLimit = track->baseSize;
          }
        }

        // 5. For intrinsic maximums
        if (intrinsicMaximumSizingFunctionTracks.size() > 0) {
          auto minimumContentContribution = getMinimumContentContribution(item, dimension);
          distributeSpaceToTracksGrowthLimit(dimension, intrinsicMaximumSizingFunctionTracks, spannedTracks, minimumContentContribution);
        }

        // 6. For max-content maximums
        if (maxContentMaximumSizingFunctionTracks.size() > 0) {
          auto maxContentContribution = getMaxContentContribution(item, dimension);
          distributeSpaceToTracksGrowthLimit(dimension, maxContentMaximumSizingFunctionTracks, spannedTracks, maxContentContribution); 
        }
      }
    }
  };

  void accomodateSpanningItemsCrossingFlexibleTracks(Dimension dimension) {
    auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    auto sizingMode = dimension == Dimension::Width ? widthSizingMode : heightSizingMode;
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;

    std::vector<GridTrackSize*> flexibleTracks;
    for (auto& item: gridItemAreas) {
      auto spannedTracks = getTracksSpannedByItem(item, tracks, dimension);
      for (auto& track: spannedTracks) {
        if (isFlexibleSizingFunction(track->maxSizingFunction)) {
          flexibleTracks.push_back(track);
        }
      }

      std::vector<GridTrackSize*> intrinsicMinimumSizingFunctionTracks;
      for (auto& track : flexibleTracks) {
        if (isIntrinsicSizingFunction(track->minSizingFunction, containerSize)) {
          intrinsicMinimumSizingFunctionTracks.push_back(track);
        }
      }
      // 1. For intrinsic minimums
      if (intrinsicMinimumSizingFunctionTracks.size() > 0) {
        auto minimumContribution = sizingMode == SizingMode::MaxContent ? getLimitedMinimumContentContribution(item, dimension) : getMinimumContribution(item, dimension);
        distributeSpaceToFlexibleTracks(dimension, intrinsicMinimumSizingFunctionTracks, spannedTracks, minimumContribution, SpaceDistributionPhase::AccommodateMinimumContribution);
      }
      // 2, 3, 4, 5, 6 Unimplemented
    }
  };

  // https://www.w3.org/TR/css-grid-1/#extra-space
  // Handles for distributing space to track's base size
  void distributeSpaceToTracksBaseSize(
    Dimension dimension, 
    std::vector<GridTrackSize*>& affectedTracks, 
    const std::vector<GridTrackSize*>& spannedTracks, 
    float sizeContribution, 
    SpaceDistributionPhase sizeContributionPhase) {
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
  
    // 1. Set planned increase to 0 for all affected tracks
    std::map<GridTrackSize*, float> plannedIncrease;
    std::map<GridTrackSize*, float> itemIncurredIncrease;
    for (auto& track: affectedTracks) {
      plannedIncrease[track] = 0.0f;
      itemIncurredIncrease[track] = 0.0f;
    }

    // 2.1 Find the space to distribute
    float totalSpannedTracksSize = 0.0f;
    for (auto& track: spannedTracks) {
      totalSpannedTracksSize += track->baseSize;
    }
    float spaceToDistribute = std::max(0.0f, sizeContribution - totalSpannedTracksSize);
    std::set<GridTrackSize*> frozenTracks;
    
    // 2.2. Distribute space up to limits
    while (frozenTracks.size() < affectedTracks.size() && spaceToDistribute > 0.0f && !yoga::inexactEquals(spaceToDistribute, 0.0f)) {
      auto unfrozenTrackCount = affectedTracks.size() - frozenTracks.size();
      auto distributionPerTrack = spaceToDistribute / unfrozenTrackCount;

      for (auto& track: affectedTracks) {
        if (frozenTracks.contains(track)) {
          continue;
        }
        auto limit = track->growthLimit;
        if (track->maxSizingFunction.resolve(containerSize).isDefined()) {
          limit = std::min(limit, track->maxSizingFunction.resolve(containerSize).unwrap());
        }
        if (track->baseSize + distributionPerTrack + itemIncurredIncrease[track] > limit) {
          frozenTracks.insert(track);
          auto increase = limit - track->baseSize - itemIncurredIncrease[track];
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
      if (sizeContributionPhase == SpaceDistributionPhase::AccommodateMinimumContribution) {
        for (auto& track: affectedTracks) {
          if (isIntrinsicSizingFunction(track->maxSizingFunction, containerSize)) {
            tracksToGrowBeyondLimits.push_back(track);
          }
        }

        if (tracksToGrowBeyondLimits.size() == 0) {
          tracksToGrowBeyondLimits = affectedTracks;
        }
      } else if (sizeContributionPhase == SpaceDistributionPhase::AccommodateMaxContentContribution) {
        for (auto& track: affectedTracks) {
          if (track->maxSizingFunction.isMaxContent() || isAutoSizingFunction(track->maxSizingFunction, containerSize)) {
            tracksToGrowBeyondLimits.push_back(track);
          }
        }
        if (tracksToGrowBeyondLimits.size() == 0) {
          tracksToGrowBeyondLimits = affectedTracks;
        }
      }

      frozenTracks.clear();
      while (spaceToDistribute > 0.0f && !yoga::inexactEquals(spaceToDistribute, 0.0f) && tracksToGrowBeyondLimits.size() > 0) {
        auto unfrozenTrackCount = tracksToGrowBeyondLimits.size() - frozenTracks.size();
        auto distributionPerTrack = spaceToDistribute / unfrozenTrackCount;
        for (auto& track: tracksToGrowBeyondLimits) {
          if (frozenTracks.contains(track)) {
            continue;
          }
          itemIncurredIncrease[track] += distributionPerTrack;
          spaceToDistribute -= distributionPerTrack;
        }
      }
    }

    // 2.5. For each affected track, if the track’s item-incurred increase is larger than the track’s planned increase set the track’s planned increase to that value.
    for (auto& track: affectedTracks) {
      if (itemIncurredIncrease[track] > plannedIncrease[track]) {
        plannedIncrease[track] = itemIncurredIncrease[track];
      }
    }

    // 3. Update the tracks' affected sizes
    for (auto& track: affectedTracks) {
      track->baseSize += plannedIncrease[track];
    }
  }

  void distributeSpaceToTracksGrowthLimit(
    Dimension dimension, 
    std::vector<GridTrackSize*>& affectedTracks, 
    const std::vector<GridTrackSize*>& spannedTracks, 
    float sizeContribution
  ) {
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    
    // 1. Set planned increase to 0 for all affected tracks
    std::map<GridTrackSize*, float> plannedIncrease;
    std::map<GridTrackSize*, float> itemIncurredIncrease;
    for (auto& track: affectedTracks) {
      plannedIncrease[track] = 0.0f;
      itemIncurredIncrease[track] = 0.0f;
    }

    // 2.1 Find the space to distribute
    float totalSpannedTracksSize = 0.0f;
    for (auto& track: spannedTracks) {
      totalSpannedTracksSize += track->growthLimit == INFINITY ? track->baseSize : track->growthLimit;
    }
    float spaceToDistribute = std::max(0.0f, sizeContribution - totalSpannedTracksSize);
    std::set<GridTrackSize*> frozenTracks;

    // Freeze tracks that are not infinitely growable before distribution
    // Per spec: "If the affected size was a growth limit and the track is not marked infinitely growable,
    // then each item-incurred increase will be zero."

    // 2.2. Distribute space up to limits
    while (frozenTracks.size() < affectedTracks.size() && spaceToDistribute > 0.0f && !yoga::inexactEquals(spaceToDistribute, 0.0f)) {
      auto unfrozenTrackCount = affectedTracks.size() - frozenTracks.size();
      auto distributionPerTrack = spaceToDistribute / unfrozenTrackCount;

      for (auto& track: affectedTracks) {
        if (frozenTracks.find(track) != frozenTracks.end()) {
          continue;
        }
        auto limit = INFINITY;
        if (track->growthLimit != INFINITY && !track->infinitelyGrowable) {
          limit = track->growthLimit;
        } else if (track->maxSizingFunction.isFitContent() && track->maxSizingFunction.resolve(containerSize).isDefined()) {
          limit = track->maxSizingFunction.resolve(containerSize).unwrap();
        }

        // If the affected size was a growth limit and the track is not marked infinitely growable, then each item-incurred increase will be zero.
        if (!track->infinitelyGrowable) {
          frozenTracks.insert(track);
          continue;
        }

        if (track->growthLimit + distributionPerTrack + itemIncurredIncrease[track] > limit) {
          frozenTracks.insert(track);
          auto increase = limit - track->growthLimit - itemIncurredIncrease[track];
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
        frozenTracks.clear();
        while (spaceToDistribute > 0.0f && !yoga::inexactEquals(spaceToDistribute, 0.0f) && tracksToGrowBeyondLimits.size() > 0) {
          // TODO: handle fit-content check here
          auto unfrozenTrackCount = tracksToGrowBeyondLimits.size() - frozenTracks.size();
          auto distributionPerTrack = spaceToDistribute / unfrozenTrackCount;
          for (auto& track: tracksToGrowBeyondLimits) {
            if (frozenTracks.find(track) != frozenTracks.end()) {
              continue;
            }
            itemIncurredIncrease[track] += distributionPerTrack;
            spaceToDistribute -= distributionPerTrack;
          }
        }
      }

    // 2.5. For each affected track, if the track’s item-incurred increase is larger than the track’s planned increase set the track’s planned increase to that value.
    for (auto& track: affectedTracks) {
      if (itemIncurredIncrease[track] > plannedIncrease[track]) {
        plannedIncrease[track] = itemIncurredIncrease[track];
      }
    }

    // 3. Update the tracks' affected sizes
    for (auto& track: affectedTracks) {
      if (track->growthLimit == INFINITY) {
        track->growthLimit = track->baseSize + plannedIncrease[track];
        track->infinitelyGrowable = true;
      } else {
        track->growthLimit += plannedIncrease[track];
      }
    }
  }

  void distributeSpaceToFlexibleTracks(
    Dimension dimension, 
    std::vector<GridTrackSize*>& affectedTracks, 
    const std::vector<GridTrackSize*>& spannedTracks, 
    float sizeContribution, 
    SpaceDistributionPhase sizeContributionPhase
  ) {
    float totalSpannedTracksSize = 0.0f;
    for (auto& track: spannedTracks) {
      totalSpannedTracksSize += track->baseSize;
    }

    float sumOfFlexFactors = 0.0f;
    for (auto& track: affectedTracks) {
      sumOfFlexFactors += track->maxSizingFunction.value().unwrap();
    }
    float spaceToDistribute = std::max(0.0f, sizeContribution - totalSpannedTracksSize);

    if (sumOfFlexFactors >= 1.0f) {
      for (auto& track: affectedTracks) {
        auto flexFactor = track->maxSizingFunction.value().unwrap();
        auto spaceForTrack = spaceToDistribute * flexFactor / sumOfFlexFactors;
        track->baseSize += spaceForTrack;
      }
    } 
    else if (sumOfFlexFactors > 0.0f && !yoga::inexactEquals(sumOfFlexFactors, 0.0f)) {
      auto proportionalSpace = spaceToDistribute * sumOfFlexFactors;
      for (auto& track: affectedTracks) {
        auto flexFactor = track->maxSizingFunction.value().unwrap();
        auto spaceForTrack = proportionalSpace * flexFactor / sumOfFlexFactors;
        track->baseSize += spaceForTrack;
      }

      auto remainingSpace = spaceToDistribute - proportionalSpace;
      auto spaceForTrack = remainingSpace / affectedTracks.size();
      for (auto& track: affectedTracks) {
        track->baseSize += spaceForTrack;
      }
    }
  };

  void maximizeTrackSizes(Dimension dimension) {
    auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    auto sizingMode = dimension == Dimension::Width ? widthSizingMode : heightSizingMode;

    // Gap percentages should resolve against the grid container's content-box
    // Use containerInnerWidth/Height which is the determined container size
    auto distributeToTracks = [&](float targetAvailableSize) {
      auto totalBaseSize = getTotalBaseSize(dimension);
      auto freeSpace = 0.0f;
      // For the purpose of this step: if sizing the grid container under a max-content constraint, the free space is infinite; 
      // if sizing under a min-content constraint, the free space is zero.
      if (sizingMode == SizingMode::MaxContent) {
        freeSpace = INFINITY;
      } else if (yoga::isDefined(targetAvailableSize)) {
        // Equal to the available grid space minus the sum of the base sizes of all the grid tracks, floored at zero.
        freeSpace = std::max(0.0f, targetAvailableSize - totalBaseSize);
      } else {
        // If available grid space is indefinite, the free space is indefinite as well.
        freeSpace = INFINITY;
      }
      
      // If the free space is positive, distribute it equally to the base sizes of all tracks, 
      // freezing tracks as they reach their growth limits (and continuing to grow the unfrozen tracks as needed).
      if (freeSpace > 0.0f && !yoga::inexactEquals(freeSpace, 0.0f)) {
        std::set<GridTrackSize*> frozenTracks;
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
            if (track.growthLimit != INFINITY && track.baseSize + distributionPerTrack > track.growthLimit) {
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
    };
    
    // Save original base sizes before maximization
    std::vector<float> originalBaseSizes;
    for (auto& track : tracks) {
      originalBaseSizes.push_back(track.baseSize);
    }
    
    // First attempt with the originally available size
    distributeToTracks(containerSize);
    
    // Check if this would cause the grid to be larger than the grid container's inner size as limited by its max-width/height
    auto totalGridSize = getTotalBaseSize(dimension);
    
    // Get the max constraint for this dimension
    const float paddingAndBorder = dimension == Dimension::Width
        ? paddingAndBorderForAxis(node, FlexDirection::Row, direction, ownerWidth)
        : paddingAndBorderForAxis(node, FlexDirection::Column, direction, ownerWidth);

    auto maxContainerOuter = node->style().resolvedMaxDimension(
        direction,
        dimension,
        dimension == Dimension::Width ? ownerWidth : ownerHeight,
        ownerWidth);

    auto maxContainerSize = maxContainerOuter.isDefined()
        ? maxContainerOuter.unwrap() - paddingAndBorder
        : YGUndefined;
    if (yoga::isDefined(maxContainerSize)) {
      if (totalGridSize > maxContainerSize) {
        // Redo this step, treating the available grid space as equal to the grid container's inner size when it's sized to its max-width/height
        // Reset base sizes to their values before this maximize step
        for (size_t i = 0; i < tracks.size(); i++) {
          tracks[i].baseSize = originalBaseSizes[i];
        }
        
        distributeToTracks(maxContainerSize);
      }
    }
  }

  void expandFlexibleTracks(Dimension dimension) {
    auto& gridTracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    auto sizingMode = dimension == Dimension::Width ? widthSizingMode : heightSizingMode;
    auto gap = node->style().computeGapForDimension(dimension, containerSize);

    // Convert gridTracks to pointers for the algorithm
    std::vector<GridTrackSize*> trackPointers;
    for (auto& track : gridTracks) {
      trackPointers.push_back(&track);
    }

    std::function<float(const std::vector<GridTrackSize*>&, float, std::set<GridTrackSize*>)> findFrSize;
    findFrSize = [&](const std::vector<GridTrackSize*>& tracks, float spaceToFill, std::set<GridTrackSize*> inflexibleTracks) -> float {
      auto leftoverSpace = spaceToFill;
      auto flexFactorSum = 0.0f;
      std::vector<GridTrackSize*> flexibleTracks;

      for (size_t i = 0; i < tracks.size(); i++) {
        auto& track = tracks[i];
        if (i < tracks.size() - 1) {
          leftoverSpace -= gap;
        }
        if (!isFlexibleSizingFunction(track->maxSizingFunction) || inflexibleTracks.find(track) != inflexibleTracks.end()) {
          // Let leftover space be the space to fill minus the base sizes of the non-flexible grid tracks.
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
      // If the product of the hypothetical fr size and a flexible track's flex factor is less than the track's base size
      std::set<GridTrackSize*> _inflexibleTracks;
      for (auto& track : flexibleTracks) {
        if (track->maxSizingFunction.isStretch() && track->maxSizingFunction.value().isDefined()) {
          float flexFactor = track->maxSizingFunction.value().unwrap();
          if (hypotheticalFrSize * flexFactor < track->baseSize) {
            _inflexibleTracks.insert(track);
          }
        }
      }
      
      // restart this algorithm treating all such tracks as inflexible.
      if (_inflexibleTracks.size() > 0) {
        return findFrSize(tracks, spaceToFill, _inflexibleTracks);
      }

      return hypotheticalFrSize;
    };

    // Calculate total base size
    float totalBaseSize = getTotalBaseSize(dimension);
    

    float usedFlexFraction = 0.0f;
    float freeSpace = 0.0f;

    if (sizingMode == SizingMode::MaxContent) {
      freeSpace = YGUndefined;
    } else if (yoga::isDefined(containerSize)) {
      freeSpace = std::max(0.0f, containerSize - totalBaseSize);
    }

    // If the free space is zero or if sizing the grid container under a min-content constraint:
    if (yoga::inexactEquals(freeSpace, 0.0f)) {
      usedFlexFraction = 0.0f;
    } 
    // Otherwise, if the free space is a definite length:
    // The used flex fraction is the result of finding the size of an fr using all of the grid tracks and a space to fill of the available grid space.
    else if (freeSpace != YGUndefined) {
      usedFlexFraction = findFrSize(trackPointers, containerSize, std::set<GridTrackSize*>());
    } 
    // Otherwise, if the free space is an indefinite length:
    // The used flex fraction is the maximum of:
    // For each flexible track, if the flexible track's flex factor is greater than one, the result of dividing the track's base size by its flex factor; otherwise, the track's base size.
    // For each grid item that crosses a flexible track, the result of finding the size of an fr using all the grid tracks that the item crosses and a space to fill of the item’s max-content contribution.
    else {
      for (auto& track : gridTracks) {
        if (isFlexibleSizingFunction(track.maxSizingFunction) && track.maxSizingFunction.isStretch() && track.maxSizingFunction.value().isDefined()) {
          float flexFactor = track.maxSizingFunction.value().unwrap();
          if (flexFactor > 1.0f) {
            usedFlexFraction = std::max(usedFlexFraction, track.baseSize / flexFactor);
          } else {
            usedFlexFraction = std::max(usedFlexFraction, track.baseSize);
          }
        }
      }
      for (auto& item : gridItemAreas) {
          auto spannedTracks = getTracksSpannedByItem(item, gridTracks, dimension);
          if (!includesFlexibleTrack(spannedTracks)) {
            continue;
          }
          std::vector<GridTrackSize*> spannedTrackPointers;
          for (auto& track : spannedTracks) {
            spannedTrackPointers.push_back(track);
          }
          auto itemMaxContentContribution = getMaxContentContribution(item, dimension);
          usedFlexFraction = std::max(usedFlexFraction, findFrSize(spannedTrackPointers, itemMaxContentContribution, std::set<GridTrackSize*>()));
        }
      }

    // If using this flex fraction would cause the grid to be smaller than the grid container's min-width/height 
    // (or larger than the grid container's max-width/height), then redo this step, treating the free space as definite 
    // and the available grid space as equal to the grid container's inner size when it's sized to its min-width/height (max-width/height).
    
    // Calculate what the grid size would be with this flex fraction
    float newTotalSize = 0.0f;
    for (size_t i = 0; i < gridTracks.size(); i++) {
      auto& track = gridTracks[i];
      if (isFlexibleSizingFunction(track.maxSizingFunction) && track.maxSizingFunction.isStretch() && track.maxSizingFunction.value().isDefined()) {
        float flexFactor = track.maxSizingFunction.value().unwrap();
        newTotalSize += std::max(track.baseSize, usedFlexFraction * flexFactor);
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
        usedFlexFraction = findFrSize(trackPointers, minContainerSize, std::set<GridTrackSize*>());
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
        usedFlexFraction = findFrSize(trackPointers, maxContainerSize, std::set<GridTrackSize*>());
      }
    }
    
    // For each flexible track, if the product of the used flex fraction and the track's flex factor is greater than the track's base size, 
    // set its base size to that product.
    for (auto& track : gridTracks) {
      if (isFlexibleSizingFunction(track.maxSizingFunction) && track.maxSizingFunction.isStretch() && track.maxSizingFunction.value().isDefined()) {
        float flexFactor = track.maxSizingFunction.value().unwrap();
        float newSize = usedFlexFraction * flexFactor;
        if (newSize > track.baseSize) {
          track.baseSize = newSize;
        }
      }
    }
  };

  void stretchAutoTracks(Dimension dimension) {
    auto& gridTracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    auto sizingMode = dimension == Dimension::Width ? widthSizingMode : heightSizingMode;

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

      auto totalBaseSize = getTotalBaseSize(dimension);

      auto freeSpace = 0.0f;
      if (sizingMode == SizingMode::MaxContent) {
        freeSpace = YGUndefined;
      } else if (yoga::isDefined(containerSize)) {
        freeSpace = std::max(0.0f, containerSize - totalBaseSize);
      } else {
        freeSpace = YGUndefined;
      }

      if (freeSpace == YGUndefined) {
        // If the free space is indefinite, but the grid container has a definite min-width/height, use that size to calculate the free space for this step instead.
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
          freeSpace = std::max(0.0f, minContainerSize - totalBaseSize);
        }
      }

      if (freeSpace > 0.0f && !yoga::inexactEquals(freeSpace, 0.0f)) {
        // Divide free space equally among auto tracks only
        auto freeSpacePerAutoTrack = freeSpace / autoTracks.size();
        for (auto& track : autoTracks) {
          track->baseSize += freeSpacePerAutoTrack;
        }
      }
    }
  };

  float getMinimumContentContribution(const GridItemArea& item, Dimension dimension) {
    // Min-content contribution is the item's min-content size plus margins
    // Per CSS Grid spec: "the smallest size the item could take while still fitting around its contents"
    auto [containingBlockWidth, containingBlockHeight] = getContainingBlockSizeForItem(item);
    auto containingBlockSize = dimension == Dimension::Width ? containingBlockWidth : containingBlockHeight;

    float minContentSize;

    if (item.node->hasDefiniteLength(dimension, containingBlockSize)) {
      minContentSize = item.node->getResolvedDimension(
          direction,
          dimension,
          containingBlockSize,
          containingBlockSize
      ).unwrap();
    } else {
      // For auto-sized items, measure the min-content size by laying out the item
      // This varies from spec as Yoga does not support min-content (this should mostly affect Text nodes)
      // TODO: verify if there is any better approach
      minContentSize = contentSizeSuggestion(item, dimension, containingBlockWidth, containingBlockHeight);
    }

    auto marginForAxis = item.node->style().computeMarginForAxis(
        dimension == Dimension::Width ? FlexDirection::Row : FlexDirection::Column,
        containingBlockSize);

    return minContentSize + marginForAxis;
  };

  float getMaxContentContribution(const GridItemArea& item, Dimension dimension) {
    auto [containingBlockWidth, containingBlockHeight] = getContainingBlockSizeForItem(item);

    Direction direction = node->getLayout().direction();

    bool isWidthDefined = item.node->hasDefiniteLength(Dimension::Width, containingBlockWidth);
    bool isHeightDefined = item.node->hasDefiniteLength(Dimension::Height, containingBlockHeight);

    float childWidth = YGUndefined;
    float childHeight = YGUndefined;
    SizingMode childWidthSizingMode = SizingMode::MaxContent;
    SizingMode childHeightSizingMode = SizingMode::MaxContent;

    // If width is definite, use it + margins (like CalculateLayout.cpp)
    if (isWidthDefined) {
        childWidth = item.node->getResolvedDimension(
            direction, Dimension::Width, containingBlockWidth, containingBlockWidth
        ).unwrap() + item.node->style().computeMarginForAxis(FlexDirection::Row, containingBlockWidth);
        childWidthSizingMode = SizingMode::StretchFit;
    }

    // If height is definite, use it + margins (like CalculateLayout.cpp)
    if (isHeightDefined) {
        childHeight = item.node->getResolvedDimension(
            direction, Dimension::Height, containingBlockHeight, containingBlockWidth
        ).unwrap() + item.node->style().computeMarginForAxis(FlexDirection::Column, containingBlockWidth);
        childHeightSizingMode = SizingMode::StretchFit;
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
        false,
        LayoutPassReason::kMeasureChild,
        layoutMarkerData,
        depth + 1,
        generationCount);

    return item.node->getLayout().measuredDimension(dimension);
  };

  float autoMinimumSize(const GridItemArea& item, Dimension dimension) {
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
      return contentBasedMinimumSize(item, dimension);
    }

    return 0.0f;
  }

  float contentBasedMinimumSize(const GridItemArea& item, Dimension dimension) {
    float result = 0.0f;
    auto [containingBlockWidth, containingBlockHeight] = getContainingBlockSizeForItem(item);
    auto containingBlockSize = dimension == Dimension::Width ? containingBlockWidth : containingBlockHeight;
    auto aspectRatio = item.node->style().aspectRatio();
    Dimension orthogonalDimension = dimension == Dimension::Width ? Dimension::Height : Dimension::Width;
    auto orthogonalContainingBlockSize = orthogonalDimension == Dimension::Width ? containingBlockWidth : containingBlockHeight;

    // For border-box model, definite sizes already include padding and border
    if (item.node->hasDefiniteLength(dimension, containingBlockSize)) {
      result = item.node->getResolvedDimension(
          direction,
          dimension,
          containingBlockSize,
          containingBlockSize
      ).unwrap();
    } 
    else if (aspectRatio.isDefined() && item.node->hasDefiniteLength(orthogonalDimension, orthogonalContainingBlockSize)) {
      auto suggestedSize = transferredSizeSuggestion(item, dimension, containingBlockWidth, containingBlockHeight);
      if (suggestedSize.isDefined()) {
        result = suggestedSize.unwrap();
      }
    } else {
      // Content size suggestion: min-content clamped by opposite-axis min/max through aspect ratio
      result = contentSizeSuggestion(item, dimension, containingBlockWidth, containingBlockHeight);
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

  float contentSizeSuggestion(const GridItemArea& item, Dimension dimension, float containingBlockWidth, float containingBlockHeight) {
    // Content size suggestion:
    // The content size suggestion is the min-content size in the relevant axis,
    // clamped, if it has a preferred aspect ratio, by any definite opposite-axis
    // minimum and maximum sizes converted through the aspect ratio.

    // Measure the item with min-content constraint (MaxContent sizing mode in Yoga)
    auto marginRow = item.node->style().computeMarginForAxis(FlexDirection::Row, containingBlockWidth);
    auto marginColumn = item.node->style().computeMarginForAxis(FlexDirection::Column, containingBlockWidth);

    // Start with MaxContent (min-content in CSS) for both dimensions
    float childWidth = YGUndefined;
    float childHeight = YGUndefined;
    SizingMode childWidthSizingMode = SizingMode::MaxContent;
    SizingMode childHeightSizingMode = SizingMode::MaxContent;

    // If width is definite, use it + margins with StretchFit (like CalculateLayout.cpp:138-144)
    // We add margins because calculateLayoutInternal needs total space including margins,
    // and will return measuredDimension (content box) which excludes margins
    bool isWidthDefined = item.node->hasDefiniteLength(Dimension::Width, containingBlockWidth);
    if (isWidthDefined) {
      childWidth = item.node->getResolvedDimension(
          direction, Dimension::Width, containingBlockWidth, containingBlockWidth).unwrap() + marginRow;
      childWidthSizingMode = SizingMode::StretchFit;
    }

    // If height is definite, use it + margins with StretchFit (like CalculateLayout.cpp:146-154)
    bool isHeightDefined = item.node->hasDefiniteLength(Dimension::Height, containingBlockHeight);
    if (isHeightDefined) {
      childHeight = item.node->getResolvedDimension(
          direction, Dimension::Height, containingBlockHeight, containingBlockWidth).unwrap() + marginColumn;
      childHeightSizingMode = SizingMode::StretchFit;
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
        false,
        LayoutPassReason::kMeasureChild,
        layoutMarkerData,
        depth + 1,
        generationCount);

    float minContentSize = item.node->getLayout().measuredDimension(dimension);

    // Clamp by opposite-axis min/max sizes converted through aspect ratio
    auto aspectRatio = item.node->style().aspectRatio();
    if (aspectRatio.isDefined()) {
      Dimension orthogonalDimension = dimension == Dimension::Width ? Dimension::Height : Dimension::Width;
      auto orthogonalContainingBlockSize = orthogonalDimension == Dimension::Width ? containingBlockWidth : containingBlockHeight;

      // Clamp by opposite-axis minimum size (converted through aspect ratio)
      auto orthogonalMinSize = item.node->style().minDimension(orthogonalDimension);
      if (orthogonalMinSize.isDefined()) {
        auto resolvedOrthogonalMinSize = orthogonalMinSize.resolve(orthogonalContainingBlockSize);
        if (resolvedOrthogonalMinSize.isDefined()) {
          float convertedMinSize;
          if (dimension == Dimension::Width) {
            // width = height * aspectRatio
            convertedMinSize = resolvedOrthogonalMinSize.unwrap() * aspectRatio.unwrap();
          } else {
            // height = width / aspectRatio
            convertedMinSize = resolvedOrthogonalMinSize.unwrap() / aspectRatio.unwrap();
          }
          minContentSize = std::max(minContentSize, convertedMinSize);
        }
      }

      // Clamp by opposite-axis maximum size (converted through aspect ratio)
      auto orthogonalMaxSize = item.node->style().maxDimension(orthogonalDimension);
      if (orthogonalMaxSize.isDefined()) {
        auto resolvedOrthogonalMaxSize = orthogonalMaxSize.resolve(orthogonalContainingBlockSize);
        if (resolvedOrthogonalMaxSize.isDefined()) {
          float convertedMaxSize;
          if (dimension == Dimension::Width) {
            // width = height * aspectRatio
            convertedMaxSize = resolvedOrthogonalMaxSize.unwrap() * aspectRatio.unwrap();
          } else {
            // height = width / aspectRatio
            convertedMaxSize = resolvedOrthogonalMaxSize.unwrap() / aspectRatio.unwrap();
          }
          minContentSize = std::min(minContentSize, convertedMaxSize);
        }
      }
    }

    return minContentSize;
  }
  
  // https://www.w3.org/TR/css-grid-1/#minimum-contribution
  float getMinimumContribution(const GridItemArea& item, Dimension dimension) {
    auto preferredSize = item.node->style().dimension(dimension);
    if (preferredSize.isAuto() || preferredSize.isPercent()) {
      auto [containingBlockWidth, containingBlockHeight] = getContainingBlockSizeForItem(item);
      auto containingBlockSize = dimension == Dimension::Width ? containingBlockWidth : containingBlockHeight;
      
      auto minSize = item.node->style().minDimension(dimension);
      // CSS spec has initial min-width size to auto, but yoga keeps it undefined.
      if (minSize.isAuto() || !minSize.isDefined()) {
        auto newMinimumSize = autoMinimumSize(item, dimension);
        auto marginForAxis = item.node->style().computeMarginForAxis(
          dimension == Dimension::Width ? FlexDirection::Row : FlexDirection::Column,
          containingBlockSize);
        return newMinimumSize + marginForAxis;
      } else {
        auto resolvedMinSize = minSize.resolve(containingBlockSize);
        auto marginForAxis = item.node->style().computeMarginForAxis(
          dimension == Dimension::Width ? FlexDirection::Row : FlexDirection::Column,
          containingBlockSize);
        return resolvedMinSize.unwrap() + marginForAxis;
      }
    } else {
      return getMinimumContentContribution(item, dimension);
    }
  }

  FloatOptional transferredSizeSuggestion(const GridItemArea& item, Dimension dimension, float containingBlockWidth, float containingBlockHeight) {
    // Transferred size suggestion:
    // If the item has a preferred aspect ratio and its preferred size in the opposite axis is definite,
    // then the transferred size suggestion is that size (clamped by the opposite-axis minimum and maximum
    // sizes if they are definite), converted through the aspect ratio.
    auto aspectRatio = item.node->style().aspectRatio();
    if (!aspectRatio.isDefined()) {
      return yoga::FloatOptional();
    }

    Dimension orthogonalDimension = dimension == Dimension::Width ? Dimension::Height : Dimension::Width;
    auto orthogonalContainingBlockSize = orthogonalDimension == Dimension::Width ? containingBlockWidth : containingBlockHeight;
    auto containingBlockSize = dimension == Dimension::Width ? containingBlockWidth : containingBlockHeight;

    // Check if the item has a definite preferred size in the opposite axis
    if (!item.node->hasDefiniteLength(orthogonalDimension, orthogonalContainingBlockSize)) {
      return yoga::FloatOptional();
    }

    // Get the definite preferred size in the opposite axis
    auto orthogonalSize = item.node->style().dimension(orthogonalDimension);
    float resolvedOrthogonalSize = orthogonalSize.resolve(orthogonalContainingBlockSize).unwrap();

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
      // Resolve indefinite percentages against zero
      auto resolvedPreferredSize = preferredSize.resolve(containingBlockSize);
      if (resolvedPreferredSize.isDefined()) {
        result = std::min(result, resolvedPreferredSize.unwrap());
      }
    }

    // Cap by definite maximum size in the relevant axis
    auto maxSize = item.node->style().maxDimension(dimension);
    if (maxSize.isDefined()) {
      // Resolve indefinite percentages against zero
      auto resolvedMaxSize = maxSize.resolve(containingBlockSize);
      if (resolvedMaxSize.isDefined()) {
        result = std::min(result, resolvedMaxSize.unwrap());
      }
    }

    return yoga::FloatOptional(result);
  }

  // https://www.w3.org/TR/css-grid-1/#limited-contribution
  float getLimitedMinimumContentContribution(const GridItemArea& item, Dimension dimension) {
    auto [upperLimit, onlySpansFixedMaxTracks] = getUpperLimitForItem(item, dimension);
    auto minContentContribution = getMinimumContentContribution(item, dimension);
    auto minimumContribution = getMinimumContribution(item, dimension);
    
    if (onlySpansFixedMaxTracks && upperLimit > 0) {
      auto limitedContribution = std::min(minContentContribution, upperLimit);
      return std::max(limitedContribution, minimumContribution);
    }
    
    return std::max(minContentContribution, minimumContribution);
  }

  std::pair<float, bool> getUpperLimitForItem(const GridItemArea& item, Dimension dimension) {
    float upperLimit = 0.0f;
    bool onlySpansFixedMaxTracks = true;
    auto& tracks = dimension == Dimension::Width ? columnTracks : rowTracks;
    auto containerSize = dimension == Dimension::Width ? containerInnerWidth : containerInnerHeight;
    
    size_t startIndex = dimension == Dimension::Width ? item.columnStart : item.rowStart;
    size_t endIndex = dimension == Dimension::Width ? item.columnEnd : item.rowEnd;
    
    for (size_t trackIndex = startIndex; trackIndex < endIndex; trackIndex++) {
      auto& track = tracks[trackIndex];
      if (isFixedSizingFunction(track.maxSizingFunction, containerSize)) {
        auto resolved = track.maxSizingFunction.resolve(containerSize);
        if (resolved.isDefined()) {
          upperLimit += resolved.unwrap();
        }
      } else {
        onlySpansFixedMaxTracks = false;
      }
    }
    
    return std::make_pair(upperLimit, onlySpansFixedMaxTracks);
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
    std::vector<GridTrackSize*> spannedTracks;
    auto start = dimension == Dimension::Width ? item.columnStart : item.rowStart;
    auto end = dimension == Dimension::Width ? item.columnEnd : item.rowEnd;
    for (int i = start; i < end; ++i) {
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

  std::pair<float, float> getContainingBlockSizeForItem(const GridItemArea& item) {
    float containingBlockWidth = 0.0f;
    float containingBlockHeight = 0.0f;
    auto columnGap = node->style().computeGapForDimension(Dimension::Width, containerInnerWidth);
    auto rowGap = node->style().computeGapForDimension(Dimension::Height, containerInnerHeight);
    
    // Calculate width: sum of spanned column tracks + gaps
    for (int i = item.columnStart; i < item.columnEnd && i < (int)columnTracks.size(); i++) {
      containingBlockWidth += columnTracks[i].baseSize;
      // Add column gap if not the last spanned track
      if (i < item.columnEnd - 1) {
        containingBlockWidth += columnGap;
      }
    }
    
    // Calculate height: sum of spanned row tracks + gaps
    for (int i = item.rowStart; i < item.rowEnd && i < (int)rowTracks.size(); i++) {
      containingBlockHeight += rowTracks[i].baseSize;
      // Add row gap if not the last spanned track
      if (i < item.rowEnd - 1) {
        containingBlockHeight += rowGap;
      }
    }
    
    return std::make_pair(containingBlockWidth, containingBlockHeight);
  }
};

} // namespace facebook::yoga