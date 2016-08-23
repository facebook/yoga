/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

package com.facebook.csslayout;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class CSSLayoutFlexBasisTest {

  @Test
  public void testFlexBasis() {
    final CSSNode root = new CSSNode();
    root.setFlexDirection(CSSFlexDirection.ROW);
    root.setStyleWidth(300);
    root.setStyleHeight(100);

    final CSSNode root_child0 = new CSSNode();
    root_child0.setFlexGrow(1);
    root_child0.setFlexBasis(100);
    root_child0.setStyleWidth(200);
    root_child0.setStyleHeight(100);
    root.addChildAt(root_child0, 0);

    final CSSNode root_child1 = new CSSNode();
    root_child1.setFlexGrow(1);
    root_child1.setStyleWidth(100);
    root_child1.setStyleHeight(100);
    root.addChildAt(root_child1, 1);
    root.calculateLayout(new CSSLayoutContext());

    assertEquals(0, root.getLayoutX(), 0.001);
    assertEquals(0, root.getLayoutY(), 0.001);
    assertEquals(300, root.getLayoutWidth(), 0.001);
    assertEquals(100, root.getLayoutHeight(), 0.001);

    assertEquals(0, root_child0.getLayoutX(), 0.001);
    assertEquals(0, root_child0.getLayoutY(), 0.001);
    assertEquals(200, root_child0.getLayoutWidth(), 0.001);
    assertEquals(100, root_child0.getLayoutHeight(), 0.001);

    assertEquals(200, root_child1.getLayoutX(), 0.001);
    assertEquals(0, root_child1.getLayoutY(), 0.001);
    assertEquals(100, root_child1.getLayoutWidth(), 0.001);
    assertEquals(100, root_child1.getLayoutHeight(), 0.001);
  }
}
