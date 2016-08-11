/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define NUM_REPETITIONS 100

#define CSS_BENCHMARKS(BLOCK)                                                                      \
  int main(int argc, char const *argv[]) {                                                         \
    clock_t __start;                                                                               \
    clock_t __end;                                                                                 \
    { BLOCK }                                                                                      \
    return 0;                                                                                      \
  }

#define CSS_BENCHMARK(NAME, BLOCK)                                                                 \
  __start = clock();                                                                               \
  for (uint32_t __i = 0; __i < NUM_REPETITIONS; __i++) {                                           \
    BLOCK                                                                                          \
  }                                                                                                \
  __end = clock();                                                                                 \
  __printBenchmarkResult(NAME, __start, __end);

void __printBenchmarkResult(char *name, clock_t start, clock_t end) {
  float total = (end - start) / (double)CLOCKS_PER_SEC * 1000;
  float mean = total / NUM_REPETITIONS;
  printf("%s: ", name);
  printf("%lf ms", mean);
  printf("\n");
}
