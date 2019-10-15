/*
 * Copyright (c) Facebook, Inc. and its affiliates.
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
    clock_t __start;                       \
    clock_t __endTimes[NUM_REPETITIONS];   \
    { BLOCK }                              \
    return 0;                              \
  }

#define YGBENCHMARK(NAME, BLOCK)                         \
  __start = clock();                                     \
  for (uint32_t __i = 0; __i < NUM_REPETITIONS; __i++) { \
    {BLOCK} __endTimes[__i] = clock();                   \
  }                                                      \
  __printBenchmarkResult(NAME, __start, __endTimes);

static int __compareDoubles(const void* a, const void* b) {
  double arg1 = *(const double*) a;
  double arg2 = *(const double*) b;

  if (arg1 < arg2) {
    return -1;
  }

  if (arg1 > arg2) {
    return 1;
  }

  return 0;
}

static void __printBenchmarkResult(
    char* name,
    clock_t start,
    clock_t* endTimes) {
  double timesInMs[NUM_REPETITIONS];
  double mean = 0;
  clock_t lastEnd = start;
  for (uint32_t i = 0; i < NUM_REPETITIONS; i++) {
    timesInMs[i] = (endTimes[i] - lastEnd) / (double) CLOCKS_PER_SEC * 1000;
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
    YGNodeRef node,
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode) {
  return (YGSize){
      .width = widthMode == YGMeasureModeUndefined ? 10 : width,
      .height = heightMode == YGMeasureModeUndefined ? 10 : width,
  };
}

YGBENCHMARKS({
  YGBENCHMARK("Stack with flex", {
    const YGNodeRef root = YGNodeNew();
    YGNodeStyleSetWidth(root, 100);
    YGNodeStyleSetHeight(root, 100);

    for (uint32_t i = 0; i < 10; i++) {
      const YGNodeRef child = YGNodeNew();
      YGNodeSetMeasureFunc(child, _measure);
      YGNodeStyleSetFlex(child, 1);
      YGNodeInsertChild(root, child, 0);
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

  YGBENCHMARK("Align stretch in undefined axis", {
    const YGNodeRef root = YGNodeNew();

    for (uint32_t i = 0; i < 10; i++) {
      const YGNodeRef child = YGNodeNew();
      YGNodeStyleSetHeight(child, 20);
      YGNodeSetMeasureFunc(child, _measure);
      YGNodeInsertChild(root, child, 0);
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

  YGBENCHMARK("Nested flex", {
    const YGNodeRef root = YGNodeNew();

    for (uint32_t i = 0; i < 10; i++) {
      const YGNodeRef child = YGNodeNew();
      YGNodeStyleSetFlex(child, 1);
      YGNodeInsertChild(root, child, 0);

      for (uint32_t ii = 0; ii < 10; ii++) {
        const YGNodeRef grandChild = YGNodeNew();
        YGNodeSetMeasureFunc(grandChild, _measure);
        YGNodeStyleSetFlex(grandChild, 1);
        YGNodeInsertChild(child, grandChild, 0);
      }
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });

  YGBENCHMARK("Huge nested layout", {
    const YGNodeRef root = YGNodeNew();

    for (uint32_t i = 0; i < 10; i++) {
      const YGNodeRef child = YGNodeNew();
      YGNodeStyleSetFlexGrow(child, 1);
      YGNodeStyleSetWidth(child, 10);
      YGNodeStyleSetHeight(child, 10);
      YGNodeInsertChild(root, child, 0);

      for (uint32_t ii = 0; ii < 10; ii++) {
        const YGNodeRef grandChild = YGNodeNew();
        YGNodeStyleSetFlexDirection(grandChild, YGFlexDirectionRow);
        YGNodeStyleSetFlexGrow(grandChild, 1);
        YGNodeStyleSetWidth(grandChild, 10);
        YGNodeStyleSetHeight(grandChild, 10);
        YGNodeInsertChild(child, grandChild, 0);

        for (uint32_t iii = 0; iii < 10; iii++) {
          const YGNodeRef grandGrandChild = YGNodeNew();
          YGNodeStyleSetFlexGrow(grandGrandChild, 1);
          YGNodeStyleSetWidth(grandGrandChild, 10);
          YGNodeStyleSetHeight(grandGrandChild, 10);
          YGNodeInsertChild(grandChild, grandGrandChild, 0);

          for (uint32_t iiii = 0; iiii < 10; iiii++) {
            const YGNodeRef grandGrandGrandChild = YGNodeNew();
            YGNodeStyleSetFlexDirection(
                grandGrandGrandChild, YGFlexDirectionRow);
            YGNodeStyleSetFlexGrow(grandGrandGrandChild, 1);
            YGNodeStyleSetWidth(grandGrandGrandChild, 10);
            YGNodeStyleSetHeight(grandGrandGrandChild, 10);
            YGNodeInsertChild(grandGrandChild, grandGrandGrandChild, 0);
          }
        }
      }
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeFreeRecursive(root);
  });
});
