/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include <CSSLayout/Yoga.h>
#include <gtest/gtest.h>

extern int32_t gNodeInstanceCount;

static int testMallocCount;
static int testCallocCount;
static int testReallocCount;
static int testFreeCount;

static void *testMalloc(size_t size) {
  testMallocCount++;
  return malloc(size);
}

static void *testCalloc(size_t count, size_t size) {
  testCallocCount++;
  return calloc(count, size);
}

static void *testRealloc(void *ptr, size_t size) {
  testReallocCount++;
  return realloc(ptr, size);
}

static void testFree(void *ptr) {
  testFreeCount++;
  free(ptr);
}

TEST(YogaTest, memory_func_default) {
  gNodeInstanceCount = 0; // Reset YGNode instance count for memory func test
  YGSetMemoryFuncs(NULL, NULL, NULL, NULL);
  const YGNodeRef root = YGNodeNew();
  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeInsertChild(root, root_child0, 0);
  YGNodeFreeRecursive(root);
}

TEST(YogaTest, memory_func_test_funcs) {
  gNodeInstanceCount = 0; // Reset YGNode instance count for memory func test
  YGSetMemoryFuncs(&testMalloc, &testCalloc, &testRealloc, &testFree);
  const YGNodeRef root = YGNodeNew();
  for (int i = 0; i < 10; i++) {
    const YGNodeRef child = YGNodeNew();
    YGNodeInsertChild(root, child, 0);
  }
  YGNodeFreeRecursive(root);
  ASSERT_NE(testMallocCount, 0);
  ASSERT_NE(testCallocCount, 0);
  ASSERT_NE(testReallocCount, 0);
  ASSERT_NE(testFreeCount, 0);
  YGSetMemoryFuncs(NULL, NULL, NULL, NULL);
}

#if GTEST_HAS_DEATH_TEST
TEST(YogaTest, memory_func_assert_zero_nodes) {
  gNodeInstanceCount = 0; // Reset YGNode instance count for memory func test
  const YGNodeRef root = YGNodeNew();
  ASSERT_DEATH(YGSetMemoryFuncs(&testMalloc, &testCalloc, &testRealloc, &testFree), "Cannot set memory functions: all node must be freed first");
  YGNodeFreeRecursive(root);
}

TEST(YogaTest, memory_func_assert_all_non_null) {
  gNodeInstanceCount = 0; // Reset YGNode instance count for memory func test
  ASSERT_DEATH(YGSetMemoryFuncs(NULL, &testCalloc, &testRealloc, &testFree), "Cannot set memory functions: functions must be all NULL or Non-NULL");
}
#endif
