/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include <CSSLayout/CSSLayout.h>
#include <gtest/gtest.h>

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

TEST(CSSLayoutTest, memory_func_default) {
  CSSLayoutSetMemoryFuncs(NULL, NULL, NULL, NULL);
  const CSSNodeRef root = CSSNodeNew();
  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeInsertChild(root, root_child0, 0);
  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, memory_func_test_funcs) {
  CSSLayoutSetMemoryFuncs(&testMalloc, &testCalloc, &testRealloc, &testFree);
  const CSSNodeRef root = CSSNodeNew();
  for (int i = 0; i < 10; i++) {
    const CSSNodeRef child = CSSNodeNew();
    CSSNodeInsertChild(root, child, 0);
  }
  CSSNodeFreeRecursive(root);
  ASSERT_NE(testMallocCount, 0);
  ASSERT_NE(testCallocCount, 0);
  ASSERT_NE(testReallocCount, 0);
  ASSERT_NE(testFreeCount, 0);
  CSSLayoutSetMemoryFuncs(NULL, NULL, NULL, NULL);
}

#if GTEST_HAS_DEATH_TEST
TEST(CSSLayoutTest, memory_func_assert_zero_nodes) {
  const CSSNodeRef root = CSSNodeNew();
  ASSERT_DEATH(CSSLayoutSetMemoryFuncs(&testMalloc, &testCalloc, &testRealloc, &testFree), "Cannot set memory functions: all node must be freed first");
  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, memory_func_assert_all_non_null) {
  ASSERT_DEATH(CSSLayoutSetMemoryFuncs(NULL, &testCalloc, &testRealloc, &testFree), "Cannot set memory functions: functions must be all NULL or Non-NULL");
}
#endif
