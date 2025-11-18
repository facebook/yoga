/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>
#include <yoga/node/Node.h>
#include <yoga/algorithm/grid/TrackSizing.h>
#include <yoga/algorithm/grid/AutoPlacement.h>
#include <yoga/style/GridTrack.h>
#include <yoga/style/StyleLength.h>

using namespace facebook::yoga;

class TrackSizingTest : public ::testing::Test {
protected:
    Node* testNode;
    LayoutData layoutData;

    void SetUp() override {
        testNode = new Node();
    }

    void TearDown() override {
        delete testNode;
    }
};

TEST_F(TrackSizingTest, initializeTrackSizes_fixed_length_tracks) {
    std::vector<GridTrackSize> columnTracks = {
        GridTrackSize::length(100.0f),
        GridTrackSize::length(150.0f),
        GridTrackSize::length(200.0f)
    };
    std::vector<GridTrackSize> rowTracks = {};
    std::vector<GridItemArea> gridItemAreas = {};

    TrackSizing trackSizing(
        testNode,
        columnTracks,
        rowTracks,
        500.0f,
        300.0f,
        gridItemAreas,
        SizingMode::StretchFit,
        SizingMode::StretchFit,
        Direction::LTR,
        500.0f,
        300.0f,
        layoutData,
        0,
        0
    );

    trackSizing.initializeTrackSizes(Dimension::Width);

    EXPECT_EQ(columnTracks[0].baseSize, 100.0f);
    EXPECT_EQ(columnTracks[0].growthLimit, 100.0f);

    EXPECT_EQ(columnTracks[1].baseSize, 150.0f);
    EXPECT_EQ(columnTracks[1].growthLimit, 150.0f);

    EXPECT_EQ(columnTracks[2].baseSize, 200.0f);
    EXPECT_EQ(columnTracks[2].growthLimit, 200.0f);
}

TEST_F(TrackSizingTest, initializeTrackSizes_auto_tracks) {
    std::vector<GridTrackSize> columnTracks = {
        GridTrackSize::auto_(),
        GridTrackSize::auto_()
    };
    std::vector<GridTrackSize> rowTracks = {};
    std::vector<GridItemArea> gridItemAreas = {};

    TrackSizing trackSizing(
        testNode,
        columnTracks,
        rowTracks,
        500.0f,
        300.0f,
        gridItemAreas,
        SizingMode::StretchFit,
        SizingMode::StretchFit,
        Direction::LTR,
        500.0f,
        300.0f,
        layoutData,
        0,
        0
    );

    trackSizing.initializeTrackSizes(Dimension::Width);

    EXPECT_EQ(columnTracks[0].baseSize, 0.0f);
    EXPECT_EQ(columnTracks[0].growthLimit, INFINITY);

    EXPECT_EQ(columnTracks[1].baseSize, 0.0f);
    EXPECT_EQ(columnTracks[1].growthLimit, INFINITY);
}

TEST_F(TrackSizingTest, initializeTrackSizes_fr_tracks) {
    std::vector<GridTrackSize> columnTracks = {
        GridTrackSize::fr(1.0f),
        GridTrackSize::fr(2.0f)
    };
    std::vector<GridTrackSize> rowTracks = {};
    std::vector<GridItemArea> gridItemAreas = {};

    TrackSizing trackSizing(
        testNode,
        columnTracks,
        rowTracks,
        500.0f,
        300.0f,
        gridItemAreas,
        SizingMode::StretchFit,
        SizingMode::StretchFit,
        Direction::LTR,
        500.0f,
        300.0f,
        layoutData,
        0,
        0
    );

    trackSizing.initializeTrackSizes(Dimension::Width);

    EXPECT_EQ(columnTracks[0].baseSize, 0.0f);
    EXPECT_EQ(columnTracks[0].growthLimit, INFINITY);

    EXPECT_EQ(columnTracks[1].baseSize, 0.0f);
    EXPECT_EQ(columnTracks[1].growthLimit, INFINITY);
}

TEST_F(TrackSizingTest, initializeTrackSizes_mixed_tracks) {
    std::vector<GridTrackSize> columnTracks = {
        GridTrackSize::length(100.0f),
        GridTrackSize::auto_(),
        GridTrackSize::fr(1.0f),
        GridTrackSize::length(50.0f)
    };
    std::vector<GridTrackSize> rowTracks = {};
    std::vector<GridItemArea> gridItemAreas = {};

    TrackSizing trackSizing(
        testNode,
        columnTracks,
        rowTracks,
        500.0f,
        300.0f,
        gridItemAreas,
        SizingMode::StretchFit,
        SizingMode::StretchFit,
        Direction::LTR,
        500.0f,
        300.0f,
        layoutData,
        0,
        0
    );

    trackSizing.initializeTrackSizes(Dimension::Width);

    EXPECT_EQ(columnTracks[0].baseSize, 100.0f);
    EXPECT_EQ(columnTracks[0].growthLimit, 100.0f);

    EXPECT_EQ(columnTracks[1].baseSize, 0.0f);
    EXPECT_EQ(columnTracks[1].growthLimit, INFINITY);

    EXPECT_EQ(columnTracks[2].baseSize, 0.0f);
    EXPECT_EQ(columnTracks[2].growthLimit, INFINITY);

    EXPECT_EQ(columnTracks[3].baseSize, 50.0f);
    EXPECT_EQ(columnTracks[3].growthLimit, 50.0f);
}

TEST_F(TrackSizingTest, initializeTrackSizes_minmax_fixed_fixed) {
    std::vector<GridTrackSize> columnTracks = {};
    std::vector<GridTrackSize> rowTracks = {
        GridTrackSize::minmax(StyleSizeLength::points(100.0f), StyleSizeLength::points(200.0f))
    };
    std::vector<GridItemArea> gridItemAreas = {};

    TrackSizing trackSizing(
        testNode,
        columnTracks,
        rowTracks,
        500.0f,
        300.0f,
        gridItemAreas,
        SizingMode::StretchFit,
        SizingMode::StretchFit,
        Direction::LTR,
        500.0f,
        300.0f,
        layoutData,
        0,
        0
    );

    trackSizing.initializeTrackSizes(Dimension::Height);

    EXPECT_EQ(rowTracks[0].baseSize, 100.0f);
    EXPECT_EQ(rowTracks[0].growthLimit, 200.0f);
}

TEST_F(TrackSizingTest, initializeTrackSizes_growthLimit_never_less_than_baseSize) {
    std::vector<GridTrackSize> columnTracks = {
        // Create a minmax where min > max (200 > 50)
        GridTrackSize::minmax(StyleSizeLength::points(200.0f), StyleSizeLength::points(50.0f))
    };
    std::vector<GridTrackSize> rowTracks = {};
    std::vector<GridItemArea> gridItemAreas = {};

    TrackSizing trackSizing(
        testNode,
        columnTracks,
        rowTracks,
        500.0f,
        300.0f,
        gridItemAreas,
        SizingMode::StretchFit,
        SizingMode::StretchFit,
        Direction::LTR,
        500.0f,
        300.0f,
        layoutData,
        0,
        0
    );

    trackSizing.initializeTrackSizes(Dimension::Width);

    EXPECT_EQ(columnTracks[0].baseSize, 200.0f);
    EXPECT_EQ(columnTracks[0].growthLimit, 200.0f);
}

// Percentage sizing functions should be treated as fixed
TEST_F(TrackSizingTest, initializeTrackSizes_percentage_with_defined_container) {
    std::vector<GridTrackSize> columnTracks = {
        GridTrackSize::minmax(StyleSizeLength::percent(50.0f), StyleSizeLength::percent(50.0f))
    };
    std::vector<GridTrackSize> rowTracks = {};
    std::vector<GridItemArea> gridItemAreas = {};

    TrackSizing trackSizing(
        testNode,
        columnTracks,
        rowTracks,
        500.0f,
        300.0f,
        gridItemAreas,
        SizingMode::StretchFit,
        SizingMode::StretchFit,
        Direction::LTR,
        500.0f,
        300.0f,
        layoutData,
        0,
        0
    );

    trackSizing.initializeTrackSizes(Dimension::Width);

    EXPECT_EQ(columnTracks[0].baseSize, 250.0f);
    EXPECT_EQ(columnTracks[0].growthLimit, 250.0f);
}

// Percentage sizing functions should be treated as auto (intrinsic)
TEST_F(TrackSizingTest, initializeTrackSizes_percentage_with_undefined_container) {
    std::vector<GridTrackSize> columnTracks = {
        GridTrackSize::minmax(StyleSizeLength::percent(50.0f), StyleSizeLength::percent(50.0f))
    };
    std::vector<GridTrackSize> rowTracks = {};
    std::vector<GridItemArea> gridItemAreas = {};

    TrackSizing trackSizing(
        testNode,
        columnTracks,
        rowTracks,
        YGUndefined,
        300.0f,
        gridItemAreas,
        SizingMode::MaxContent,
        SizingMode::StretchFit,
        Direction::LTR,
        YGUndefined,
        300.0f,
        layoutData,
        0,
        0
    );

    trackSizing.initializeTrackSizes(Dimension::Width);

    // Percentage with undefined container should be treated as auto (intrinsic)
    EXPECT_EQ(columnTracks[0].baseSize, 0.0f);
    EXPECT_EQ(columnTracks[0].growthLimit, INFINITY);
}

// ============================================================================
// distributeSpaceToTracksBaseSize Tests
// ============================================================================

// Test basic space distribution to base size
TEST_F(TrackSizingTest, distributeSpaceToTracksBaseSize_basic_distribution) {
    std::vector<GridTrackSize> columnTracks = {
        GridTrackSize::auto_(),  // baseSize: 0, growthLimit: INFINITY
        GridTrackSize::auto_()   // baseSize: 0, growthLimit: INFINITY
    };
    std::vector<GridTrackSize> rowTracks = {};
    std::vector<GridItemArea> gridItemAreas = {
        {0, 2, 0, 1, nullptr}  // Item spanning columns 0-2
    };

    TrackSizing trackSizing(
        testNode,
        columnTracks,
        rowTracks,
        500.0f,
        300.0f,
        gridItemAreas,
        SizingMode::MaxContent,
        SizingMode::StretchFit,
        Direction::LTR,
        500.0f,
        300.0f,
        layoutData,
        0,
        0
    );

    trackSizing.initializeTrackSizes(Dimension::Width);

    // Both tracks have intrinsic min sizing functions
    std::vector<GridTrackSize*> affectedTracks = {&columnTracks[0], &columnTracks[1]};
    std::vector<GridTrackSize*> spannedTracks = {&columnTracks[0], &columnTracks[1]};

    // Distribute 200px across both tracks
    trackSizing.distributeSpaceToTracksBaseSize(
        Dimension::Width,
        affectedTracks,
        spannedTracks,
        200.0f
    );

    // Each track should get 100px
    EXPECT_EQ(columnTracks[0].baseSize, 100.0f);
    EXPECT_EQ(columnTracks[1].baseSize, 100.0f);
}

// Test distribution with growth limits
TEST_F(TrackSizingTest, distributeSpaceToTracksBaseSize_with_growth_limits) {
    std::vector<GridTrackSize> columnTracks = {
        GridTrackSize::minmax(StyleSizeLength::ofAuto(), StyleSizeLength::points(80.0f)),
        GridTrackSize::auto_()
    };
    std::vector<GridTrackSize> rowTracks = {};
    std::vector<GridItemArea> gridItemAreas = {};

    TrackSizing trackSizing(
        testNode,
        columnTracks,
        rowTracks,
        500.0f,
        300.0f,
        gridItemAreas,
        SizingMode::MaxContent,
        SizingMode::StretchFit,
        Direction::LTR,
        500.0f,
        300.0f,
        layoutData,
        0,
        0
    );

    trackSizing.initializeTrackSizes(Dimension::Width);

    std::vector<GridTrackSize*> affectedTracks = {&columnTracks[0], &columnTracks[1]};
    std::vector<GridTrackSize*> spannedTracks = {&columnTracks[0], &columnTracks[1]};

    // Distribute 200px - first track limited to 80px
    trackSizing.distributeSpaceToTracksBaseSize(
        Dimension::Width,
        affectedTracks,
        spannedTracks,
        200.0f
    );

    // First track should be limited to its growth limit (80px)
    // Second track should get the remainder
    EXPECT_EQ(columnTracks[0].baseSize, 80.0f);
    EXPECT_EQ(columnTracks[1].baseSize, 120.0f);
}

// Test distribution when space is less than current total
TEST_F(TrackSizingTest, distributeSpaceToTracksBaseSize_no_space_to_distribute) {
    std::vector<GridTrackSize> columnTracks = {
        GridTrackSize::length(100.0f),
        GridTrackSize::length(150.0f)
    };
    std::vector<GridTrackSize> rowTracks = {};
    std::vector<GridItemArea> gridItemAreas = {};

    TrackSizing trackSizing(
        testNode,
        columnTracks,
        rowTracks,
        500.0f,
        300.0f,
        gridItemAreas,
        SizingMode::MaxContent,
        SizingMode::StretchFit,
        Direction::LTR,
        500.0f,
        300.0f,
        layoutData,
        0,
        0
    );

    trackSizing.initializeTrackSizes(Dimension::Width);

    std::vector<GridTrackSize*> affectedTracks = {&columnTracks[0], &columnTracks[1]};
    std::vector<GridTrackSize*> spannedTracks = {&columnTracks[0], &columnTracks[1]};

    // Try to distribute 200px when tracks already total 250px
    trackSizing.distributeSpaceToTracksBaseSize(
        Dimension::Width,
        affectedTracks,
        spannedTracks,
        200.0f
    );

    // Tracks should remain unchanged
    EXPECT_EQ(columnTracks[0].baseSize, 100.0f);
    EXPECT_EQ(columnTracks[1].baseSize, 150.0f);
}

// Test distribution to single track
TEST_F(TrackSizingTest, distributeSpaceToTracksBaseSize_single_track) {
    std::vector<GridTrackSize> columnTracks = {
        GridTrackSize::auto_()
    };
    std::vector<GridTrackSize> rowTracks = {};
    std::vector<GridItemArea> gridItemAreas = {};

    TrackSizing trackSizing(
        testNode,
        columnTracks,
        rowTracks,
        500.0f,
        300.0f,
        gridItemAreas,
        SizingMode::MaxContent,
        SizingMode::StretchFit,
        Direction::LTR,
        500.0f,
        300.0f,
        layoutData,
        0,
        0
    );

    trackSizing.initializeTrackSizes(Dimension::Width);

    std::vector<GridTrackSize*> affectedTracks = {&columnTracks[0]};
    std::vector<GridTrackSize*> spannedTracks = {&columnTracks[0]};

    trackSizing.distributeSpaceToTracksBaseSize(
        Dimension::Width,
        affectedTracks,
        spannedTracks,
        150.0f
    );

    EXPECT_EQ(columnTracks[0].baseSize, 150.0f);
}

// ============================================================================
// distributeSpaceToTracksGrowthLimit Tests
// ============================================================================

// Test basic space distribution to growth limit
TEST_F(TrackSizingTest, distributeSpaceToTracksGrowthLimit_basic_distribution) {
    std::vector<GridTrackSize> columnTracks = {
        GridTrackSize::auto_(),
        GridTrackSize::auto_()
    };
    std::vector<GridTrackSize> rowTracks = {};
    std::vector<GridItemArea> gridItemAreas = {};

    TrackSizing trackSizing(
        testNode,
        columnTracks,
        rowTracks,
        500.0f,
        300.0f,
        gridItemAreas,
        SizingMode::MaxContent,
        SizingMode::StretchFit,
        Direction::LTR,
        500.0f,
        300.0f,
        layoutData,
        0,
        0
    );

    trackSizing.initializeTrackSizes(Dimension::Width);

    // Set up tracks with some base size
    columnTracks[0].baseSize = 50.0f;
    columnTracks[1].baseSize = 50.0f;

    std::vector<GridTrackSize*> affectedTracks = {&columnTracks[0], &columnTracks[1]};
    std::vector<GridTrackSize*> spannedTracks = {&columnTracks[0], &columnTracks[1]};

    // Distribute to growth limit - need to mark tracks as infinitely growable
    columnTracks[0].infinitelyGrowable = true;
    columnTracks[1].infinitelyGrowable = true;

    trackSizing.distributeSpaceToTracksGrowthLimit(
        Dimension::Width,
        affectedTracks,
        spannedTracks,
        300.0f,
        true
    );

    // Each track's growth limit should be set (was INFINITY)
    // Space to distribute = 300 - 100 = 200px, each gets 100px
    EXPECT_EQ(columnTracks[0].growthLimit, 150.0f);  // 50 base + 100
    EXPECT_EQ(columnTracks[1].growthLimit, 150.0f);  // 50 base + 100
}

// Test that non-infinitely-growable tracks don't grow
TEST_F(TrackSizingTest, distributeSpaceToTracksGrowthLimit_not_infinitely_growable) {
    std::vector<GridTrackSize> columnTracks = {
        GridTrackSize::minmax(StyleSizeLength::ofAuto(), StyleSizeLength::points(100.0f)),
        GridTrackSize::auto_()
    };
    std::vector<GridTrackSize> rowTracks = {};
    std::vector<GridItemArea> gridItemAreas = {};

    TrackSizing trackSizing(
        testNode,
        columnTracks,
        rowTracks,
        500.0f,
        300.0f,
        gridItemAreas,
        SizingMode::MaxContent,
        SizingMode::StretchFit,
        Direction::LTR,
        500.0f,
        300.0f,
        layoutData,
        0,
        0
    );

    trackSizing.initializeTrackSizes(Dimension::Width);

    columnTracks[0].baseSize = 50.0f;
    columnTracks[1].baseSize = 50.0f;

    std::vector<GridTrackSize*> affectedTracks = {&columnTracks[0], &columnTracks[1]};
    std::vector<GridTrackSize*> spannedTracks = {&columnTracks[0], &columnTracks[1]};

    // Only second track is infinitely growable
    columnTracks[0].infinitelyGrowable = false;
    columnTracks[1].infinitelyGrowable = true;

    trackSizing.distributeSpaceToTracksGrowthLimit(
        Dimension::Width,
        affectedTracks,
        spannedTracks,
        300.0f,
        true
    );

    // First track shouldn't grow (not infinitely growable)
    EXPECT_EQ(columnTracks[0].growthLimit, 100.0f);
    // Second track gets all the space
    // totalSpannedTracksSize = 150 (track0: growthLimit 100, track1: baseSize 50)
    // spaceToDistribute = 300 - 150 = 150
    // track1 gets all 150px: growthLimit = baseSize + increase = 50 + 150 = 200
    EXPECT_EQ(columnTracks[1].growthLimit, 200.0f);  // 50 base + 150
}

// ============================================================================
// distributeSpaceToFlexibleTracks Tests
// ============================================================================

// Test basic fr distribution with sum of flex factors >= 1
TEST_F(TrackSizingTest, distributeSpaceToFlexibleTracks_sum_gte_1) {
    std::vector<GridTrackSize> columnTracks = {
        GridTrackSize::fr(1.0f),  // 1fr
        GridTrackSize::fr(2.0f)   // 2fr
    };
    std::vector<GridTrackSize> rowTracks = {};
    std::vector<GridItemArea> gridItemAreas = {};

    TrackSizing trackSizing(
        testNode,
        columnTracks,
        rowTracks,
        500.0f,
        300.0f,
        gridItemAreas,
        SizingMode::MaxContent,
        SizingMode::StretchFit,
        Direction::LTR,
        500.0f,
        300.0f,
        layoutData,
        0,
        0
    );

    trackSizing.initializeTrackSizes(Dimension::Width);

    std::vector<GridTrackSize*> affectedTracks = {&columnTracks[0], &columnTracks[1]};
    std::vector<GridTrackSize*> spannedTracks = {&columnTracks[0], &columnTracks[1]};

    // Distribute 300px with flex factors 1fr and 2fr (sum = 3fr)
    trackSizing.distributeSpaceToFlexibleTracks(
        Dimension::Width,
        affectedTracks,
        spannedTracks,
        300.0f
    );

    // First track: 300 * (1/3) = 100px
    // Second track: 300 * (2/3) = 200px
    EXPECT_FLOAT_EQ(columnTracks[0].baseSize, 100.0f);
    EXPECT_FLOAT_EQ(columnTracks[1].baseSize, 200.0f);
}

// Test fr distribution with sum of flex factors < 1
TEST_F(TrackSizingTest, distributeSpaceToFlexibleTracks_sum_lt_1) {
    std::vector<GridTrackSize> columnTracks = {
        GridTrackSize::fr(0.3f),
        GridTrackSize::fr(0.2f)
    };
    std::vector<GridTrackSize> rowTracks = {};
    std::vector<GridItemArea> gridItemAreas = {};

    TrackSizing trackSizing(
        testNode,
        columnTracks,
        rowTracks,
        500.0f,
        300.0f,
        gridItemAreas,
        SizingMode::MaxContent,
        SizingMode::StretchFit,
        Direction::LTR,
        500.0f,
        300.0f,
        layoutData,
        0,
        0
    );

    trackSizing.initializeTrackSizes(Dimension::Width);

    std::vector<GridTrackSize*> affectedTracks = {&columnTracks[0], &columnTracks[1]};
    std::vector<GridTrackSize*> spannedTracks = {&columnTracks[0], &columnTracks[1]};

    // Distribute 300px with flex factors 0.3fr and 0.2fr (sum = 0.5fr)
    trackSizing.distributeSpaceToFlexibleTracks(
        Dimension::Width,
        affectedTracks,
        spannedTracks,
        300.0f
    );

    // Proportional space = 300 * 0.5 = 150px
    // First track: 150 * (0.3/0.5) = 90px
    // Second track: 150 * (0.2/0.5) = 60px
    // Remaining 150px distributed equally: 75px each
    EXPECT_FLOAT_EQ(columnTracks[0].baseSize, 165.0f);  // 90 + 75
    EXPECT_FLOAT_EQ(columnTracks[1].baseSize, 135.0f);  // 60 + 75
}

// Test fr distribution with existing base sizes
TEST_F(TrackSizingTest, distributeSpaceToFlexibleTracks_with_existing_base) {
    std::vector<GridTrackSize> columnTracks = {
        GridTrackSize::fr(1.0f),
        GridTrackSize::fr(1.0f)
    };
    std::vector<GridTrackSize> rowTracks = {};
    std::vector<GridItemArea> gridItemAreas = {};

    TrackSizing trackSizing(
        testNode,
        columnTracks,
        rowTracks,
        500.0f,
        300.0f,
        gridItemAreas,
        SizingMode::MaxContent,
        SizingMode::StretchFit,
        Direction::LTR,
        500.0f,
        300.0f,
        layoutData,
        0,
        0
    );

    trackSizing.initializeTrackSizes(Dimension::Width);

    // Set existing base sizes
    columnTracks[0].baseSize = 50.0f;
    columnTracks[1].baseSize = 50.0f;

    std::vector<GridTrackSize*> affectedTracks = {&columnTracks[0], &columnTracks[1]};
    std::vector<GridTrackSize*> spannedTracks = {&columnTracks[0], &columnTracks[1]};

    // Distribute 300px total, already have 100px
    trackSizing.distributeSpaceToFlexibleTracks(
        Dimension::Width,
        affectedTracks,
        spannedTracks,
        300.0f
    );

    // Space to distribute = 300 - 100 = 200px
    // Each track gets 100px added to existing 50px
    EXPECT_FLOAT_EQ(columnTracks[0].baseSize, 150.0f);
    EXPECT_FLOAT_EQ(columnTracks[1].baseSize, 150.0f);
}

// Test fr distribution with single track
TEST_F(TrackSizingTest, distributeSpaceToFlexibleTracks_single_track) {
    std::vector<GridTrackSize> columnTracks = {
        GridTrackSize::fr(1.0f)
    };
    std::vector<GridTrackSize> rowTracks = {};
    std::vector<GridItemArea> gridItemAreas = {};

    TrackSizing trackSizing(
        testNode,
        columnTracks,
        rowTracks,
        500.0f,
        300.0f,
        gridItemAreas,
        SizingMode::MaxContent,
        SizingMode::StretchFit,
        Direction::LTR,
        500.0f,
        300.0f,
        layoutData,
        0,
        0
    );

    trackSizing.initializeTrackSizes(Dimension::Width);

    std::vector<GridTrackSize*> affectedTracks = {&columnTracks[0]};
    std::vector<GridTrackSize*> spannedTracks = {&columnTracks[0]};

    trackSizing.distributeSpaceToFlexibleTracks(
        Dimension::Width,
        affectedTracks,
        spannedTracks,
        250.0f
    );

    EXPECT_FLOAT_EQ(columnTracks[0].baseSize, 250.0f);
}