/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/util/SingleWriterValueList.h>

#include <numeric>
#include <type_traits>
#include <unordered_set>

namespace facebook {
namespace yoga {

static_assert(
    !std::is_copy_constructible<SingleWriterValueList<int>>::value,
    "SingleWriterValueList must not be copyable");
static_assert(
    !std::is_copy_assignable<SingleWriterValueList<int>>::value,
    "SingleWriterValueList must not be copyable");
static_assert(
    !std::is_copy_constructible<SingleWriterValueList<int>::Borrowed>::value,
    "SingleWriterValueList::Borrowed must not be copyable");
static_assert(
    !std::is_copy_assignable<SingleWriterValueList<int>::Borrowed>::value,
    "SingleWriterValueList::Borrowed must not be copyable");
static_assert(
    std::is_move_constructible<SingleWriterValueList<int>::Borrowed>::value,
    "SingleWriterValueList::Borrowed must be movable");
static_assert(
    std::is_move_assignable<SingleWriterValueList<int>::Borrowed>::value,
    "SingleWriterValueList::Borrowed must be movable");

TEST(SingleWriterValueList, borrowsAreExclusive) {
  SingleWriterValueList<int> x{};

  auto a = x.borrow();
  auto b = x.borrow();

  ASSERT_NE(&a.get(), &b.get());
}

TEST(SingleWriterValueList, borrowsSupportDereference) {
  SingleWriterValueList<int> x{};

  auto a = x.borrow();
  *a = 123;

  ASSERT_EQ(*a, 123);
}

TEST(SingleWriterValueList, borrowsHaveGetMethod) {
  SingleWriterValueList<int> x{};

  auto a = x.borrow();
  a.get() = 123;

  ASSERT_EQ(a.get(), 123);
}

TEST(SingleWriterValueList, exposesBorrowsViaIterator) {
  SingleWriterValueList<int> x{};

  auto a = x.borrow();
  auto b = x.borrow();

  *a = 12;
  *b = 34;

  int sum = 0;
  for (auto& i : x) {
    sum += i;
  }
  ASSERT_EQ(sum, 12 + 34);
}

TEST(SingleWriterValueList, exposesBorrowsViaConstIterator) {
  SingleWriterValueList<int> x{};

  auto a = x.borrow();
  auto b = x.borrow();

  *a = 12;
  *b = 34;

  ASSERT_EQ(std::accumulate(x.cbegin(), x.cend(), 0), 12 + 34);
}

TEST(SingleWriterValueList, doesNotDeallocateReturnedBorrows) {
  SingleWriterValueList<int> x{};

  std::unordered_set<const int*> values;
  {
    auto a = x.borrow();
    auto b = x.borrow();
    values.insert(&a.get());
    values.insert(&b.get());
  }

  auto it = x.begin();

  ASSERT_NE(it, x.end());
  ASSERT_NE(values.find(&*it), values.end());

  ASSERT_NE(++it, x.end());
  ASSERT_NE(values.find(&*it), values.end());
}

TEST(SingleWriterValueList, reusesReturnedBorrows) {
  SingleWriterValueList<int> x{};

  int* firstBorrow;
  {
    auto a = x.borrow();
    firstBorrow = &a.get();
  }

  auto b = x.borrow();

  ASSERT_EQ(&b.get(), firstBorrow);
}

TEST(SingleWriterValueList, keepsValuesAfterReturning) {
  SingleWriterValueList<int> x{};

  {
    auto a = x.borrow();
    *a = 123;
  }

  ASSERT_EQ(*x.begin(), 123);
}

static void addOne(int& v) {
  v += 1;
}

TEST(SingleWriterValueList, allowsCustomReturnPolicy) {
  SingleWriterValueList<int, addOne> x{};

  {
    auto a = x.borrow();
    *a = 123;
  }

  ASSERT_EQ(*x.begin(), 124);
}

TEST(SingleWriterValueList, hasConvenienceResetPolicy) {
  SingleWriterValueList<int, SingleWriterValueList<int>::resetPolicy> x{};

  {
    auto a = x.borrow();
    *a = 123;
  }

  ASSERT_EQ(*x.begin(), 0);
}

} // namespace yoga
} // namespace facebook
