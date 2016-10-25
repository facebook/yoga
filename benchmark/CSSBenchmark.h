/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#pragma once

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_REPETITIONS 1000

#define CSS_BENCHMARKS(BLOCK)              \
  int main(int argc, char const *argv[]) { \
    clock_t __start;                       \
    clock_t __endTimes[NUM_REPETITIONS];   \
    { BLOCK }                              \
    return 0;                              \
  }

#define CSS_BENCHMARK(NAME, BLOCK)                       \
  __start = clock();                                     \
  for (uint32_t __i = 0; __i < NUM_REPETITIONS; __i++) { \
    { BLOCK }                                            \
    __endTimes[__i] = clock();                           \
  }                                                      \
  __printBenchmarkResult(NAME, __start, __endTimes);

int __compareDoubles(const void *a, const void *b) {
  double arg1 = *(const double *) a;
  double arg2 = *(const double *) b;

  if (arg1 < arg2) {
    return -1;
  }

  if (arg1 > arg2) {
    return 1;
  }

  return 0;
}

void __printBenchmarkResult(char *name, clock_t start, clock_t *endTimes) {
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
