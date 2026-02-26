/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>
#include <yoga/algorithm/grid/AutoPlacement.h>
#include <yoga/algorithm/grid/GridLayout.h>
#include <yoga/node/Node.h>
#include <yoga/style/GridTrack.h>
#include <yoga/style/StyleLength.h>

using namespace facebook::yoga;

class GridCreateTracksTest : public ::testing::Test {
 protected:
  void SetUp() override {
    gridContainer = new Node();
    gridContainer->style().setDisplay(Display::Grid);
  }

  void TearDown() override {
    delete gridContainer;
  }

  Node* gridContainer{nullptr};

  Node* createGridItem(
      GridLine columnStart = GridLine::auto_(),
      GridLine columnEnd = GridLine::auto_(),
      GridLine rowStart = GridLine::auto_(),
      GridLine rowEnd = GridLine::auto_()) {
    auto item = new Node();
    item->style().setGridColumnStart(columnStart);
    item->style().setGridColumnEnd(columnEnd);
    item->style().setGridRowStart(rowStart);
    item->style().setGridRowEnd(rowEnd);
    gridContainer->insertChild(item, gridContainer->getChildren().size());
    return item;
  }
};

TEST_F(GridCreateTracksTest, only_explicit_tracks) {
  std::vector<GridTrackSize> columns = {
      GridTrackSize::length(100.0f), GridTrackSize::length(150.0f)};
  std::vector<GridTrackSize> rows = {
      GridTrackSize::length(80.0f), GridTrackSize::fr(1.0f)};

  gridContainer->style().setGridTemplateColumns(std::move(columns));
  gridContainer->style().setGridTemplateRows(std::move(rows));

  createGridItem(
      GridLine::fromInteger(1),
      GridLine::fromInteger(2),
      GridLine::fromInteger(1),
      GridLine::fromInteger(2));
  createGridItem(
      GridLine::fromInteger(2),
      GridLine::fromInteger(3),
      GridLine::fromInteger(2),
      GridLine::fromInteger(3));

  auto autoPlacementResult =
      ResolvedAutoPlacement::resolveGridItemPlacements(gridContainer);
  GridTracks tracks = createGridTracks(gridContainer, autoPlacementResult);

  EXPECT_EQ(tracks.columnTracks.size(), 2);
  EXPECT_TRUE(tracks.columnTracks[0].minSizingFunction.isPoints());
  EXPECT_TRUE(tracks.columnTracks[1].minSizingFunction.isPoints());

  EXPECT_EQ(tracks.rowTracks.size(), 2);
  EXPECT_TRUE(tracks.rowTracks[0].minSizingFunction.isPoints());
  EXPECT_TRUE(tracks.rowTracks[1].maxSizingFunction.isStretch());
}

TEST_F(GridCreateTracksTest, implicit_tracks_after_explicit_grid) {
  std::vector<GridTrackSize> columns = {
      GridTrackSize::length(100.0f), GridTrackSize::length(150.0f)};

  gridContainer->style().setGridTemplateColumns(std::move(columns));

  createGridItem(
      GridLine::fromInteger(1),
      GridLine::fromInteger(5),
      GridLine::fromInteger(1),
      GridLine::fromInteger(2));

  auto autoPlacementResult =
      ResolvedAutoPlacement::resolveGridItemPlacements(gridContainer);
  GridTracks tracks = createGridTracks(gridContainer, autoPlacementResult);

  EXPECT_EQ(tracks.columnTracks.size(), 4);

  EXPECT_TRUE(tracks.columnTracks[0].minSizingFunction.isPoints());
  EXPECT_TRUE(tracks.columnTracks[1].minSizingFunction.isPoints());

  EXPECT_TRUE(tracks.columnTracks[2].minSizingFunction.isAuto());
  EXPECT_TRUE(tracks.columnTracks[3].minSizingFunction.isAuto());
}

TEST_F(
    GridCreateTracksTest,
    implicit_tracks_before_explicit_grid_negative_indices) {
  std::vector<GridTrackSize> columns = {
      GridTrackSize::length(20.0f),
      GridTrackSize::length(20.0f),
      GridTrackSize::length(20.0f)};

  gridContainer->style().setGridTemplateColumns(std::move(columns));

  createGridItem(GridLine::fromInteger(-5), GridLine::fromInteger(-4));

  auto autoPlacementResult =
      ResolvedAutoPlacement::resolveGridItemPlacements(gridContainer);
  GridTracks tracks = createGridTracks(gridContainer, autoPlacementResult);

  EXPECT_EQ(tracks.columnTracks.size(), 4);

  EXPECT_TRUE(tracks.columnTracks[0].minSizingFunction.isAuto());
}

TEST_F(GridCreateTracksTest, implicit_tracks_before_and_after) {
  std::vector<GridTrackSize> columns = {
      GridTrackSize::length(100.0f), GridTrackSize::fr(1.0f)};

  // creates 3 grid lines 1, 2, 3
  gridContainer->style().setGridTemplateColumns(std::move(columns));
  // -4 index = 0 index. 1 new track before. and 5 index = 1 new track after.
  // total 5 tracks
  createGridItem(GridLine::fromInteger(-4), GridLine::fromInteger(5));

  auto autoPlacementResult =
      ResolvedAutoPlacement::resolveGridItemPlacements(gridContainer);
  GridTracks tracks = createGridTracks(gridContainer, autoPlacementResult);

  EXPECT_EQ(tracks.columnTracks.size(), 5);
  EXPECT_TRUE(tracks.columnTracks[0].minSizingFunction.isAuto());
  EXPECT_TRUE(tracks.columnTracks[1].minSizingFunction.isPoints());
  EXPECT_TRUE(tracks.columnTracks[2].maxSizingFunction.isStretch());
  EXPECT_TRUE(tracks.columnTracks[4].minSizingFunction.isAuto());
  EXPECT_TRUE(tracks.columnTracks[4].minSizingFunction.isAuto());
}

TEST_F(GridCreateTracksTest, no_explicit_tracks_only_implicit) {
  createGridItem();
  createGridItem();
  createGridItem();

  auto autoPlacementResult =
      ResolvedAutoPlacement::resolveGridItemPlacements(gridContainer);
  GridTracks tracks = createGridTracks(gridContainer, autoPlacementResult);

  for (const auto& track : tracks.columnTracks) {
    EXPECT_TRUE(track.minSizingFunction.isAuto());
  }

  for (const auto& track : tracks.rowTracks) {
    EXPECT_TRUE(track.minSizingFunction.isAuto());
  }
}

TEST_F(GridCreateTracksTest, empty_grid_no_items) {
  std::vector<GridTrackSize> columns = {
      GridTrackSize::length(100.0f), GridTrackSize::length(150.0f)};

  gridContainer->style().setGridTemplateColumns(std::move(columns));

  auto autoPlacementResult =
      ResolvedAutoPlacement::resolveGridItemPlacements(gridContainer);
  GridTracks tracks = createGridTracks(gridContainer, autoPlacementResult);
  EXPECT_EQ(tracks.columnTracks.size(), 2);
}

TEST_F(GridCreateTracksTest, large_span_creating_many_implicit_tracks) {
  createGridItem(GridLine::auto_(), GridLine::span(10));

  auto autoPlacementResult =
      ResolvedAutoPlacement::resolveGridItemPlacements(gridContainer);
  GridTracks tracks = createGridTracks(gridContainer, autoPlacementResult);

  EXPECT_EQ(tracks.columnTracks.size(), 10);

  for (const auto& track : tracks.columnTracks) {
    EXPECT_TRUE(track.minSizingFunction.isAuto());
  }
}

TEST_F(GridCreateTracksTest, grid_auto_columns_pattern_repeats_backward) {
  std::vector<GridTrackSize> columns = {
      GridTrackSize::length(100.0f), GridTrackSize::length(150.0f)};
  gridContainer->style().setGridTemplateColumns(std::move(columns));

  std::vector<GridTrackSize> autoColumns = {
      GridTrackSize::length(50.0f),
      GridTrackSize::fr(1.0f),
      GridTrackSize::length(75.0f)};
  gridContainer->style().setGridAutoColumns(std::move(autoColumns));

  createGridItem(GridLine::fromInteger(-8), GridLine::fromInteger(-7));
  createGridItem(GridLine::fromInteger(3), GridLine::fromInteger(6));

  auto autoPlacementResult =
      ResolvedAutoPlacement::resolveGridItemPlacements(gridContainer);
  GridTracks tracks = createGridTracks(gridContainer, autoPlacementResult);

  // 5 negative implicit + 2 explicit + 3 positive implicit = 10 tracks
  EXPECT_EQ(tracks.columnTracks.size(), 10);

  // Implicit tracks before explicit grid
  EXPECT_TRUE(tracks.columnTracks[4].minSizingFunction.isPoints());
  EXPECT_EQ(
      tracks.columnTracks[4].minSizingFunction.resolve(0.0f).unwrap(), 75.0f);
  EXPECT_TRUE(tracks.columnTracks[3].maxSizingFunction.isStretch());
  EXPECT_TRUE(tracks.columnTracks[2].minSizingFunction.isPoints());
  EXPECT_EQ(
      tracks.columnTracks[2].minSizingFunction.resolve(0.0f).unwrap(), 50.0f);
  EXPECT_TRUE(tracks.columnTracks[1].minSizingFunction.isPoints());
  EXPECT_EQ(
      tracks.columnTracks[1].minSizingFunction.resolve(0.0f).unwrap(), 75.0f);
  EXPECT_TRUE(tracks.columnTracks[0].maxSizingFunction.isStretch());

  // Explicit grid
  EXPECT_TRUE(tracks.columnTracks[5].minSizingFunction.isPoints());
  EXPECT_EQ(
      tracks.columnTracks[5].minSizingFunction.resolve(0.0f).unwrap(), 100.0f);
  EXPECT_TRUE(tracks.columnTracks[6].minSizingFunction.isPoints());
  EXPECT_EQ(
      tracks.columnTracks[6].minSizingFunction.resolve(0.0f).unwrap(), 150.0f);

  // Implicit tracks after explicit grid
  EXPECT_TRUE(tracks.columnTracks[7].minSizingFunction.isPoints());
  EXPECT_EQ(
      tracks.columnTracks[7].minSizingFunction.resolve(0.0f).unwrap(), 50.0f);
  EXPECT_TRUE(tracks.columnTracks[8].maxSizingFunction.isStretch());
  EXPECT_TRUE(tracks.columnTracks[9].minSizingFunction.isPoints());
  EXPECT_EQ(
      tracks.columnTracks[9].minSizingFunction.resolve(0.0f).unwrap(), 75.0f);
}

TEST_F(GridCreateTracksTest, grid_auto_rows_pattern_repeats_both_directions) {
  std::vector<GridTrackSize> rows = {GridTrackSize::length(200.0f)};
  gridContainer->style().setGridTemplateRows(std::move(rows));

  std::vector<GridTrackSize> autoRows = {
      GridTrackSize::length(60.0f), GridTrackSize::length(80.0f)};
  gridContainer->style().setGridAutoRows(std::move(autoRows));

  createGridItem(
      GridLine::auto_(),
      GridLine::auto_(),
      GridLine::fromInteger(-4),
      GridLine::fromInteger(-2));

  createGridItem(
      GridLine::auto_(),
      GridLine::auto_(),
      GridLine::fromInteger(3),
      GridLine::fromInteger(5));

  auto autoPlacementResult =
      ResolvedAutoPlacement::resolveGridItemPlacements(gridContainer);
  GridTracks tracks = createGridTracks(gridContainer, autoPlacementResult);

  // 2 implicit before + 1 explicit + 3 implicit after = 7 tracks
  EXPECT_EQ(tracks.rowTracks.size(), 6);

  // Implicit tracks before explicit grid
  EXPECT_TRUE(tracks.rowTracks[1].minSizingFunction.isPoints());
  EXPECT_EQ(
      tracks.rowTracks[1].minSizingFunction.resolve(0.0f).unwrap(), 80.0f);
  EXPECT_TRUE(tracks.rowTracks[0].minSizingFunction.isPoints());
  EXPECT_EQ(
      tracks.rowTracks[0].minSizingFunction.resolve(0.0f).unwrap(), 60.0f);

  // Explicit grid
  EXPECT_EQ(
      tracks.rowTracks[2].minSizingFunction.resolve(0.0f).unwrap(), 200.0f);

  // Implicit tracks after explicit grid
  EXPECT_TRUE(tracks.rowTracks[3].minSizingFunction.isPoints());
  EXPECT_EQ(
      tracks.rowTracks[3].minSizingFunction.resolve(0.0f).unwrap(), 60.0f);
  EXPECT_TRUE(tracks.rowTracks[4].minSizingFunction.isPoints());
  EXPECT_EQ(
      tracks.rowTracks[4].minSizingFunction.resolve(0.0f).unwrap(), 80.0f);
  EXPECT_TRUE(tracks.rowTracks[5].minSizingFunction.isPoints());
  EXPECT_EQ(
      tracks.rowTracks[5].minSizingFunction.resolve(0.0f).unwrap(), 60.0f);
}
