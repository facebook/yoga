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

TEST(CSSLayoutTest, dont_cache_computed_flex_basis_between_layouts) {
  const CSSNodeRef root = CSSNodeNew();

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child0, 10);
  CSSNodeStyleSetFlexBasis(root_child0, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, 100, CSSUndefined, CSSDirectionLTR);
  CSSNodeCalculateLayout(root, 100, 100, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(20, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}
