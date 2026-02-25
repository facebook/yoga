/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <yoga/Yoga.h>

#define NUM_REPETITIONS 1000

#define YGBENCHMARKS(BLOCK)                \
  int main(int argc, char const* argv[]) { \
    (void)argc;                            \
    (void)argv;                            \
    clock_t __start;                       \
    clock_t __endTimes[NUM_REPETITIONS];   \
    {                                      \
      BLOCK                                \
    }                                      \
    return 0;                              \
  }

#define YGBENCHMARK(NAME, BLOCK)                         \
  __start = clock();                                     \
  for (uint32_t __i = 0; __i < NUM_REPETITIONS; __i++) { \
    {BLOCK} __endTimes[__i] = clock();                   \
  }                                                      \
  __printBenchmarkResult(NAME, __start, __endTimes);

static int __compareDoubles(const void* a, const void* b) {
  double arg1 = *(const double*)a;
  double arg2 = *(const double*)b;

  if (arg1 < arg2) {
    return -1;
  }

  if (arg1 > arg2) {
    return 1;
  }

  return 0;
}

static void
__printBenchmarkResult(char* name, clock_t start, const clock_t* endTimes) {
  double timesInMs[NUM_REPETITIONS];
  double mean = 0;
  clock_t lastEnd = start;
  for (uint32_t i = 0; i < NUM_REPETITIONS; i++) {
    timesInMs[i] =
        ((double)(endTimes[i] - lastEnd)) / (double)CLOCKS_PER_SEC * 1000;
    lastEnd = endTimes[i];
    mean += timesInMs[i];
  }
  mean /= NUM_REPETITIONS;

  qsort(timesInMs, NUM_REPETITIONS, sizeof(double), __compareDoubles);
  double median = timesInMs[NUM_REPETITIONS / 2];

  double variance = 0;
  for (uint32_t i = 0; i < NUM_REPETITIONS; i++) {
    variance += pow(timesInMs[i] - mean, 2);
  }
  variance /= NUM_REPETITIONS;
  double stddev = sqrt(variance);

  printf("%s: median: %lf ms, stddev: %lf ms\n", name, median, stddev);
}

static YGSize _measure(
    YGNodeConstRef node,
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode) {
  (void)node;
  return (YGSize){
      .width = widthMode == YGMeasureModeUndefined ? 10 : width,
      .height = heightMode == YGMeasureModeUndefined ? 10 : height,
  };
}

static YGSize _measureFixed(
    YGNodeConstRef node,
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode) {
  (void)node;
  (void)width;
  (void)widthMode;
  (void)height;
  (void)heightMode;
  return (YGSize){
      .width = 50,
      .height = 50,
  };
}

static YGGridTrackListRef createFixed3x100Tracks(void) {
  YGGridTrackListRef tracks = YGGridTrackListCreate();
  YGGridTrackListAddTrack(tracks, YGPoints(100));
  YGGridTrackListAddTrack(tracks, YGPoints(100));
  YGGridTrackListAddTrack(tracks, YGPoints(100));
  return tracks;
}

static YGGridTrackListRef createAuto3Tracks(void) {
  YGGridTrackListRef tracks = YGGridTrackListCreate();
  YGGridTrackListAddTrack(tracks, YGAuto());
  YGGridTrackListAddTrack(tracks, YGAuto());
  YGGridTrackListAddTrack(tracks, YGAuto());
  return tracks;
}

static YGGridTrackListRef createFr3Tracks(void) {
  YGGridTrackListRef tracks = YGGridTrackListCreate();
  YGGridTrackListAddTrack(tracks, YGFr(1));
  YGGridTrackListAddTrack(tracks, YGFr(1));
  YGGridTrackListAddTrack(tracks, YGFr(1));
  return tracks;
}

static YGGridTrackListRef createFr4Tracks(void) {
  YGGridTrackListRef tracks = YGGridTrackListCreate();
  YGGridTrackListAddTrack(tracks, YGFr(1));
  YGGridTrackListAddTrack(tracks, YGFr(1));
  YGGridTrackListAddTrack(tracks, YGFr(1));
  YGGridTrackListAddTrack(tracks, YGFr(1));
  return tracks;
}

static YGGridTrackListRef createFr5Tracks(void) {
  YGGridTrackListRef tracks = YGGridTrackListCreate();
  YGGridTrackListAddTrack(tracks, YGFr(1));
  YGGridTrackListAddTrack(tracks, YGFr(1));
  YGGridTrackListAddTrack(tracks, YGFr(1));
  YGGridTrackListAddTrack(tracks, YGFr(1));
  YGGridTrackListAddTrack(tracks, YGFr(1));
  return tracks;
}

static YGGridTrackListRef createFr2Tracks(void) {
  YGGridTrackListRef tracks = YGGridTrackListCreate();
  YGGridTrackListAddTrack(tracks, YGFr(1));
  YGGridTrackListAddTrack(tracks, YGFr(1));
  return tracks;
}

static YGGridTrackListRef createFixed3x80Tracks(void) {
  YGGridTrackListRef tracks = YGGridTrackListCreate();
  YGGridTrackListAddTrack(tracks, YGPoints(80));
  YGGridTrackListAddTrack(tracks, YGPoints(80));
  YGGridTrackListAddTrack(tracks, YGPoints(80));
  return tracks;
}

static YGGridTrackListRef createAuto4Tracks(void) {
  YGGridTrackListRef tracks = YGGridTrackListCreate();
  YGGridTrackListAddTrack(tracks, YGAuto());
  YGGridTrackListAddTrack(tracks, YGAuto());
  YGGridTrackListAddTrack(tracks, YGAuto());
  YGGridTrackListAddTrack(tracks, YGAuto());
  return tracks;
}

static YGGridTrackListRef createAuto2Tracks(void) {
  YGGridTrackListRef tracks = YGGridTrackListCreate();
  YGGridTrackListAddTrack(tracks, YGAuto());
  YGGridTrackListAddTrack(tracks, YGAuto());
  return tracks;
}

static YGGridTrackListRef createPercent3Tracks(void) {
  YGGridTrackListRef tracks = YGGridTrackListCreate();
  YGGridTrackListAddTrack(tracks, YGPercent(25));
  YGGridTrackListAddTrack(tracks, YGPercent(50));
  YGGridTrackListAddTrack(tracks, YGPercent(25));
  return tracks;
}

static YGGridTrackListRef createPercent3RowTracks(void) {
  YGGridTrackListRef tracks = YGGridTrackListCreate();
  YGGridTrackListAddTrack(tracks, YGPercent(33.33f));
  YGGridTrackListAddTrack(tracks, YGPercent(33.33f));
  YGGridTrackListAddTrack(tracks, YGPercent(33.33f));
  return tracks;
}

static YGGridTrackListRef createMixedColumnTracks(void) {
  YGGridTrackListRef tracks = YGGridTrackListCreate();
  YGGridTrackListAddTrack(tracks, YGPoints(200));
  YGGridTrackListAddTrack(tracks, YGFr(1));
  YGGridTrackListAddTrack(tracks, YGPoints(200));
  return tracks;
}

static YGGridTrackListRef createMixedRowTracks(void) {
  YGGridTrackListRef tracks = YGGridTrackListCreate();
  YGGridTrackListAddTrack(tracks, YGPoints(60));
  YGGridTrackListAddTrack(tracks, YGFr(1));
  YGGridTrackListAddTrack(tracks, YGPoints(40));
  return tracks;
}

static YGGridTrackListRef createMinmaxColumnTracks(void) {
  YGGridTrackListRef tracks = YGGridTrackListCreate();
  YGGridTrackListAddTrack(tracks, YGMinMax(YGPoints(100), YGFr(1)));
  YGGridTrackListAddTrack(tracks, YGMinMax(YGPoints(100), YGFr(1)));
  YGGridTrackListAddTrack(tracks, YGMinMax(YGPoints(100), YGFr(1)));
  return tracks;
}

static YGGridTrackListRef createMinmaxRowTracks(void) {
  YGGridTrackListRef tracks = YGGridTrackListCreate();
  YGGridTrackListAddTrack(tracks, YGMinMax(YGPoints(50), YGAuto()));
  YGGridTrackListAddTrack(tracks, YGMinMax(YGPoints(50), YGAuto()));
  YGGridTrackListAddTrack(tracks, YGMinMax(YGPoints(50), YGAuto()));
  return tracks;
}

static YGGridTrackListRef createMixed20ColumnTracks(void) {
  YGGridTrackListRef tracks = YGGridTrackListCreate();
  for (int i = 0; i < 5; i++) {
    YGGridTrackListAddTrack(tracks, YGPoints(100));
    YGGridTrackListAddTrack(tracks, YGFr(1));
    YGGridTrackListAddTrack(tracks, YGAuto());
    YGGridTrackListAddTrack(tracks, YGMinMax(YGPoints(50), YGFr(1)));
  }
  return tracks;
}

static YGGridTrackListRef createMixed50RowTracks(void) {
  YGGridTrackListRef tracks = YGGridTrackListCreate();
  for (int i = 0; i < 10; i++) {
    YGGridTrackListAddTrack(tracks, YGPoints(40));
    YGGridTrackListAddTrack(tracks, YGFr(1));
    YGGridTrackListAddTrack(tracks, YGAuto());
    YGGridTrackListAddTrack(tracks, YGMinMax(YGPoints(30), YGAuto()));
    YGGridTrackListAddTrack(tracks, YGFr(2));
  }
  return tracks;
}

YGBENCHMARKS({
  // Scenario 1: Basic fixed-size grid
  YGBENCHMARK("Grid 3x3 fixed tracks", {
    YGNodeRef root = YGNodeNew();
    YGNodeStyleSetDisplay(root, YGDisplayGrid);
    YGNodeStyleSetWidth(root, 300);
    YGNodeStyleSetHeight(root, 300);
    YGNodeStyleSetGridTemplateColumns(root, createFixed3x100Tracks());
    YGNodeStyleSetGridTemplateRows(root, createFixed3x100Tracks());

    for (uint32_t i = 0; i < 9; i++) {
      YGNodeRef child = YGNodeNew();
      YGNodeInsertChild(root, child, i);
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

  // Scenario 2: Grid with auto-sized items
  YGBENCHMARK("Grid 3x3 auto tracks", {
    YGNodeRef root = YGNodeNew();
    YGNodeStyleSetDisplay(root, YGDisplayGrid);
    YGNodeStyleSetGridTemplateColumns(root, createAuto3Tracks());
    YGNodeStyleSetGridTemplateRows(root, createAuto3Tracks());

    for (uint32_t i = 0; i < 9; i++) {
      YGNodeRef child = YGNodeNew();
      YGNodeSetMeasureFunc(child, _measureFixed);
      YGNodeInsertChild(root, child, i);
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

  // Scenario 3: Grid with fr units
  YGBENCHMARK("Grid 3x3 fr tracks", {
    YGNodeRef root = YGNodeNew();
    YGNodeStyleSetDisplay(root, YGDisplayGrid);
    YGNodeStyleSetWidth(root, 300);
    YGNodeStyleSetHeight(root, 300);
    YGNodeStyleSetGridTemplateColumns(root, createFr3Tracks());
    YGNodeStyleSetGridTemplateRows(root, createFr3Tracks());

    for (uint32_t i = 0; i < 9; i++) {
      YGNodeRef child = YGNodeNew();
      YGNodeInsertChild(root, child, i);
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

  // Scenario 4: Grid with gaps
  YGBENCHMARK("Grid 4x4 with gaps", {
    YGNodeRef root = YGNodeNew();
    YGNodeStyleSetDisplay(root, YGDisplayGrid);
    YGNodeStyleSetWidth(root, 400);
    YGNodeStyleSetHeight(root, 400);
    YGNodeStyleSetGap(root, YGGutterAll, 10);
    YGNodeStyleSetGridTemplateColumns(root, createFr4Tracks());
    YGNodeStyleSetGridTemplateRows(root, createFr4Tracks());

    for (uint32_t i = 0; i < 16; i++) {
      YGNodeRef child = YGNodeNew();
      YGNodeInsertChild(root, child, i);
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

  // Scenario 5: Mixed fixed and flexible tracks
  YGBENCHMARK("Grid mixed tracks (fixed + fr)", {
    YGNodeRef root = YGNodeNew();
    YGNodeStyleSetDisplay(root, YGDisplayGrid);
    YGNodeStyleSetWidth(root, 800);
    YGNodeStyleSetHeight(root, 600);
    YGNodeStyleSetGridTemplateColumns(root, createMixedColumnTracks());
    YGNodeStyleSetGridTemplateRows(root, createMixedRowTracks());

    for (uint32_t i = 0; i < 9; i++) {
      YGNodeRef child = YGNodeNew();
      YGNodeInsertChild(root, child, i);
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

  // Scenario 6: Grid with spanning items
  YGBENCHMARK("Grid with spanning items", {
    YGNodeRef root = YGNodeNew();
    YGNodeStyleSetDisplay(root, YGDisplayGrid);
    YGNodeStyleSetWidth(root, 400);
    YGNodeStyleSetHeight(root, 400);
    YGNodeStyleSetGap(root, YGGutterAll, 8);
    YGNodeStyleSetGridTemplateColumns(root, createFr4Tracks());
    YGNodeStyleSetGridTemplateRows(root, createFr4Tracks());

    YGNodeRef child1 = YGNodeNew();
    YGNodeStyleSetGridColumnStart(child1, 1);
    YGNodeStyleSetGridColumnEndSpan(child1, 2);
    YGNodeInsertChild(root, child1, 0);

    YGNodeRef child2 = YGNodeNew();
    YGNodeStyleSetGridRowStart(child2, 1);
    YGNodeStyleSetGridRowEndSpan(child2, 2);
    YGNodeInsertChild(root, child2, 1);

    YGNodeRef child3 = YGNodeNew();
    YGNodeStyleSetGridColumnStart(child3, 3);
    YGNodeStyleSetGridColumnEndSpan(child3, 2);
    YGNodeStyleSetGridRowStart(child3, 3);
    YGNodeStyleSetGridRowEndSpan(child3, 2);
    YGNodeInsertChild(root, child3, 2);

    for (uint32_t i = 0; i < 8; i++) {
      YGNodeRef child = YGNodeNew();
      YGNodeInsertChild(root, child, 3 + i);
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

  // Scenario 7: Auto-placement
  YGBENCHMARK("Grid auto-placement 5x5", {
    YGNodeRef root = YGNodeNew();
    YGNodeStyleSetDisplay(root, YGDisplayGrid);
    YGNodeStyleSetWidth(root, 500);
    YGNodeStyleSetHeight(root, 500);
    YGNodeStyleSetGridTemplateColumns(root, createFr5Tracks());
    YGNodeStyleSetGridTemplateRows(root, createFr5Tracks());

    for (uint32_t i = 0; i < 25; i++) {
      YGNodeRef child = YGNodeNew();
      YGNodeInsertChild(root, child, i);
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

  // Scenario 8: Nested grids
  YGBENCHMARK("Nested grids 3x3 with 2x2 children", {
    YGNodeRef root = YGNodeNew();
    YGNodeStyleSetDisplay(root, YGDisplayGrid);
    YGNodeStyleSetWidth(root, 600);
    YGNodeStyleSetHeight(root, 600);
    YGNodeStyleSetGap(root, YGGutterAll, 10);
    YGNodeStyleSetGridTemplateColumns(root, createFr3Tracks());
    YGNodeStyleSetGridTemplateRows(root, createFr3Tracks());

    for (uint32_t i = 0; i < 9; i++) {
      YGNodeRef child = YGNodeNew();
      YGNodeStyleSetDisplay(child, YGDisplayGrid);
      YGNodeStyleSetGap(child, YGGutterAll, 4);
      YGNodeStyleSetGridTemplateColumns(child, createFr2Tracks());
      YGNodeStyleSetGridTemplateRows(child, createFr2Tracks());
      YGNodeInsertChild(root, child, i);

      for (uint32_t j = 0; j < 4; j++) {
        YGNodeRef grandChild = YGNodeNew();
        YGNodeInsertChild(child, grandChild, j);
      }
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

  // Scenario 9: Grid with alignment
  YGBENCHMARK("Grid with alignment", {
    YGNodeRef root = YGNodeNew();
    YGNodeStyleSetDisplay(root, YGDisplayGrid);
    YGNodeStyleSetWidth(root, 400);
    YGNodeStyleSetHeight(root, 400);
    YGNodeStyleSetJustifyContent(root, YGJustifyCenter);
    YGNodeStyleSetAlignContent(root, YGAlignCenter);
    YGNodeStyleSetGap(root, YGGutterAll, 10);
    YGNodeStyleSetGridTemplateColumns(root, createFixed3x80Tracks());
    YGNodeStyleSetGridTemplateRows(root, createFixed3x80Tracks());

    for (uint32_t i = 0; i < 9; i++) {
      YGNodeRef child = YGNodeNew();
      YGNodeStyleSetAlignSelf(child, YGAlignCenter);
      YGNodeStyleSetWidth(child, 60);
      YGNodeStyleSetHeight(child, 60);
      YGNodeInsertChild(root, child, i);
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

  // Scenario 10: Grid with intrinsic sizing and measure functions
  YGBENCHMARK("Grid auto tracks with measure", {
    YGNodeRef root = YGNodeNew();
    YGNodeStyleSetDisplay(root, YGDisplayGrid);
    YGNodeStyleSetWidth(root, 400);
    YGNodeStyleSetGridTemplateColumns(root, createAuto4Tracks());
    YGNodeStyleSetGridTemplateRows(root, createAuto4Tracks());

    for (uint32_t i = 0; i < 16; i++) {
      YGNodeRef child = YGNodeNew();
      YGNodeSetMeasureFunc(child, _measure);
      YGNodeInsertChild(root, child, i);
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

  // Scenario 11: minmax tracks
  YGBENCHMARK("Grid minmax tracks", {
    YGNodeRef root = YGNodeNew();
    YGNodeStyleSetDisplay(root, YGDisplayGrid);
    YGNodeStyleSetWidth(root, 600);
    YGNodeStyleSetHeight(root, 400);
    YGNodeStyleSetGap(root, YGGutterAll, 10);
    YGNodeStyleSetGridTemplateColumns(root, createMinmaxColumnTracks());
    YGNodeStyleSetGridTemplateRows(root, createMinmaxRowTracks());

    for (uint32_t i = 0; i < 9; i++) {
      YGNodeRef child = YGNodeNew();
      YGNodeSetMeasureFunc(child, _measureFixed);
      YGNodeInsertChild(root, child, i);
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

  // Scenario 12: Indefinite container size
  YGBENCHMARK("Grid indefinite container", {
    YGNodeRef root = YGNodeNew();
    YGNodeStyleSetDisplay(root, YGDisplayGrid);
    YGNodeStyleSetGridTemplateColumns(root, createAuto3Tracks());
    YGNodeStyleSetGridTemplateRows(root, createAuto2Tracks());

    for (uint32_t i = 0; i < 6; i++) {
      YGNodeRef child = YGNodeNew();
      YGNodeStyleSetWidth(child, 80);
      YGNodeStyleSetHeight(child, 60);
      YGNodeInsertChild(root, child, i);
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

  // Scenario 13: Grid with percentage tracks
  YGBENCHMARK("Grid percentage tracks", {
    YGNodeRef root = YGNodeNew();
    YGNodeStyleSetDisplay(root, YGDisplayGrid);
    YGNodeStyleSetWidth(root, 400);
    YGNodeStyleSetHeight(root, 300);
    YGNodeStyleSetGridTemplateColumns(root, createPercent3Tracks());
    YGNodeStyleSetGridTemplateRows(root, createPercent3RowTracks());

    for (uint32_t i = 0; i < 9; i++) {
      YGNodeRef child = YGNodeNew();
      YGNodeInsertChild(root, child, i);
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

  // Scenario 14: Stress test - 1000 items with mixed tracks and spanning
  YGBENCHMARK("Stress test 1000 items mixed", {
    YGNodeRef root = YGNodeNew();
    YGNodeStyleSetDisplay(root, YGDisplayGrid);
    YGNodeStyleSetWidth(root, 2000);
    YGNodeStyleSetHeight(root, 5000);
    YGNodeStyleSetGap(root, YGGutterColumn, 8);
    YGNodeStyleSetGap(root, YGGutterRow, 4);
    YGNodeStyleSetGridTemplateColumns(root, createMixed20ColumnTracks());
    YGNodeStyleSetGridTemplateRows(root, createMixed50RowTracks());

    uint32_t childIndex = 0;

    for (uint32_t row = 1; row <= 50; row++) {
      for (uint32_t col = 1; col <= 20; col++) {
        YGNodeRef child = YGNodeNew();

        if (childIndex % 30 == 0 && col <= 17) {
          YGNodeStyleSetGridColumnStart(child, (int)col);
          YGNodeStyleSetGridColumnEndSpan(child, 3);
          YGNodeStyleSetGridRowStart(child, (int)row);
        } else if (childIndex % 40 == 0 && col <= 16) {
          YGNodeStyleSetGridColumnStart(child, (int)col);
          YGNodeStyleSetGridColumnEndSpan(child, 4);
          YGNodeStyleSetGridRowStart(child, (int)row);
        } else if (childIndex % 50 == 0 && row <= 48) {
          YGNodeStyleSetGridColumnStart(child, (int)col);
          YGNodeStyleSetGridRowStart(child, (int)row);
          YGNodeStyleSetGridRowEndSpan(child, 2);
        } else if (childIndex % 70 == 0 && row <= 47) {
          YGNodeStyleSetGridColumnStart(child, (int)col);
          YGNodeStyleSetGridRowStart(child, (int)row);
          YGNodeStyleSetGridRowEndSpan(child, 3);
        } else if (childIndex % 100 == 0 && col <= 18 && row <= 48) {
          YGNodeStyleSetGridColumnStart(child, (int)col);
          YGNodeStyleSetGridColumnEndSpan(child, 2);
          YGNodeStyleSetGridRowStart(child, (int)row);
          YGNodeStyleSetGridRowEndSpan(child, 2);
        } else if (childIndex % 150 == 0 && col <= 17 && row <= 48) {
          YGNodeStyleSetGridColumnStart(child, (int)col);
          YGNodeStyleSetGridColumnEndSpan(child, 3);
          YGNodeStyleSetGridRowStart(child, (int)row);
          YGNodeStyleSetGridRowEndSpan(child, 2);
        } else if (childIndex % 200 == 0 && col <= 18 && row <= 47) {
          YGNodeStyleSetGridColumnStart(child, (int)col);
          YGNodeStyleSetGridColumnEndSpan(child, 2);
          YGNodeStyleSetGridRowStart(child, (int)row);
          YGNodeStyleSetGridRowEndSpan(child, 3);
        } else if (childIndex % 300 == 0 && col <= 16 && row <= 47) {
          YGNodeStyleSetGridColumnStart(child, (int)col);
          YGNodeStyleSetGridColumnEndSpan(child, 4);
          YGNodeStyleSetGridRowStart(child, (int)row);
          YGNodeStyleSetGridRowEndSpan(child, 3);
        } else if (childIndex % 500 == 0 && col <= 15 && row <= 46) {
          YGNodeStyleSetGridColumnStart(child, (int)col);
          YGNodeStyleSetGridColumnEndSpan(child, 5);
          YGNodeStyleSetGridRowStart(child, (int)row);
          YGNodeStyleSetGridRowEndSpan(child, 4);
        }

        YGNodeInsertChild(root, child, childIndex);
        childIndex++;

        if (childIndex >= 1000)
          break;
      }
      if (childIndex >= 1000)
        break;
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });
});
