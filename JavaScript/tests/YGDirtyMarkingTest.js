/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetWidth(root_child0, 50);
  _YGNodeStyleSetHeight(root_child0, 20);
  _YGNodeInsertChild(root, root_child0, 0);

  const root_child1 = _YGNodeNew();
  _YGNodeStyleSetWidth(root_child1, 50);
  _YGNodeStyleSetHeight(root_child1, 20);
  _YGNodeInsertChild(root, root_child1, 1);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  _YGNodeStyleSetWidth(root_child0, 20);

  EXPECT_TRUE(_YGNodeIsDirty(root_child0));
  EXPECT_FALSE(_YGNodeIsDirty(root_child1));
  EXPECT_TRUE(_YGNodeIsDirty(root));

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  EXPECT_FALSE(_YGNodeIsDirty(root_child0));
  EXPECT_FALSE(_YGNodeIsDirty(root_child1));
  EXPECT_FALSE(_YGNodeIsDirty(root));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetWidth(root_child0, 50);
  _YGNodeStyleSetHeight(root_child0, 20);
  _YGNodeInsertChild(root, root_child0, 0);

  const root_child1 = _YGNodeNew();
  _YGNodeStyleSetWidth(root_child1, 50);
  _YGNodeStyleSetHeight(root_child1, 20);
  _YGNodeInsertChild(root, root_child1, 1);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  _YGNodeStyleSetWidth(root_child0, 50);

  EXPECT_FALSE(_YGNodeIsDirty(root_child0));
  EXPECT_FALSE(_YGNodeIsDirty(root_child1));
  EXPECT_FALSE(_YGNodeIsDirty(root));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 50);
  _YGNodeStyleSetHeight(root, 50);

  const child0 = _YGNodeNew();
  _YGNodeStyleSetWidth(child0, 50);
  _YGNodeStyleSetHeight(child0, 25);
  _YGNodeInsertChild(root, child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  const child1 = _YGNodeNew();
  _YGNodeRemoveChild(root, child1);
  EXPECT_FALSE(_YGNodeIsDirty(root));
  _YGNodeFree(child1);

  _YGNodeRemoveChild(root, child0);
  EXPECT_TRUE(_YGNodeIsDirty(root));
  _YGNodeFree(child0);

  _YGNodeFreeRecursive(root);
})();
