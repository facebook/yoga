/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

(function() {
  const node0 = _YGNodeNew();
  const node1 = _YGNodeNew();
  ASSERT_FALSE(_YGNodeIsDirty(node0));

  _YGNodeCopyStyle(node0, node1);
  ASSERT_FALSE(_YGNodeIsDirty(node0));

  _YGNodeFree(node0);
  _YGNodeFree(node1);
})();

(function() {
  const node0 = _YGNodeNew();
  ASSERT_FALSE(_YGNodeIsDirty(node0));
  ASSERT_EQ(_YGFlexDirectionColumn, _YGNodeStyleGetFlexDirection(node0));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetMaxHeight(node0)));

  const node1 = _YGNodeNew();
  _YGNodeStyleSetFlexDirection(node1, _YGFlexDirectionRow);
  _YGNodeStyleSetMaxHeight(node1, 10);

  _YGNodeCopyStyle(node0, node1);
  ASSERT_TRUE(_YGNodeIsDirty(node0));
  ASSERT_EQ(_YGFlexDirectionRow, _YGNodeStyleGetFlexDirection(node0));
  ASSERT_FLOAT_EQ(10, _YGNodeStyleGetMaxHeight(node0));

  _YGNodeFree(node0);
  _YGNodeFree(node1);
})();

(function() {
  const node0 = _YGNodeNew();
  _YGNodeStyleSetFlexDirection(node0, _YGFlexDirectionRow);
  _YGNodeStyleSetMaxHeight(node0, 10);
  _YGNodeCalculateLayout(node0, _YGUndefined, _YGUndefined, _YGDirectionLTR);
  ASSERT_FALSE(_YGNodeIsDirty(node0));

  const node1 = _YGNodeNew();
  _YGNodeStyleSetFlexDirection(node1, _YGFlexDirectionRow);
  _YGNodeStyleSetMaxHeight(node1, 10);

  _YGNodeCopyStyle(node0, node1);
  ASSERT_FALSE(_YGNodeIsDirty(node0));

  _YGNodeFree(node0);
  _YGNodeFree(node1);
})();
