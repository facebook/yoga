/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

/**
 * @Generated by gentest/gentest.sh with the following input
 *
<div id="absolute_layout_width_height_start_top" style="width: 100px; height: 100px;">
  <div style="width:10px; height: 10px; position: absolute; start: 10px; top: 10px;"></div>
</div>

<div id="absolute_layout_width_height_end_bottom" style="width: 100px; height: 100px;">
  <div style="width:10px; height: 10px; position: absolute; end: 10px; bottom: 10px;"></div>
</div>

<div id="absolute_layout_start_top_end_bottom" style="width: 100px; height: 100px;">
  <div style="position: absolute; start: 10px; top: 10px; end: 10px; bottom: 10px;"></div>
</div>

<div id="absolute_layout_width_height_start_top_end_bottom" style="width: 100px; height: 100px;">
  <div style="width:10px; height: 10px; position: absolute; start: 10px; top: 10px; end: 10px; bottom: 10px;"></div>
</div>

<div id="do_not_clamp_height_of_absolute_node_to_height_of_its_overflow_hidden_parent" style="height: 50px; width: 50px; overflow: hidden; flex-direction: row;">
  <div style="position: absolute; start: 0; top: 0;">
    <div style="width: 100px; height: 100px;"></div>
  </div>
</div>
 *
 */

package com.facebook.csslayout;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class CSSLayoutAbsolutePositionTest {
  @Test
  public void test_absolute_layout_width_height_start_top() {
    final CSSNode root = new CSSNode();
    root.setStyleWidth(100);
    root.setStyleHeight(100);

    final CSSNode root_child0 = new CSSNode();
    root_child0.setPositionType(CSSPositionType.ABSOLUTE);
    root_child0.setPosition(Spacing.START, 10);
    root_child0.setPosition(Spacing.TOP, 10);
    root_child0.setStyleWidth(10);
    root_child0.setStyleHeight(10);
    root.addChildAt(root_child0, 0);
    root.setDirection(CSSDirection.LTR);
    root.calculateLayout(null);

    assertEquals(0, root.getLayoutX(), 0.0f);
    assertEquals(0, root.getLayoutY(), 0.0f);
    assertEquals(100, root.getLayoutWidth(), 0.0f);
    assertEquals(100, root.getLayoutHeight(), 0.0f);

    assertEquals(10, root_child0.getLayoutX(), 0.0f);
    assertEquals(10, root_child0.getLayoutY(), 0.0f);
    assertEquals(10, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child0.getLayoutHeight(), 0.0f);

    root.setDirection(CSSDirection.RTL);
    root.calculateLayout(null);

    assertEquals(0, root.getLayoutX(), 0.0f);
    assertEquals(0, root.getLayoutY(), 0.0f);
    assertEquals(100, root.getLayoutWidth(), 0.0f);
    assertEquals(100, root.getLayoutHeight(), 0.0f);

    assertEquals(80, root_child0.getLayoutX(), 0.0f);
    assertEquals(10, root_child0.getLayoutY(), 0.0f);
    assertEquals(10, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child0.getLayoutHeight(), 0.0f);
  }

  @Test
  public void test_absolute_layout_width_height_end_bottom() {
    final CSSNode root = new CSSNode();
    root.setStyleWidth(100);
    root.setStyleHeight(100);

    final CSSNode root_child0 = new CSSNode();
    root_child0.setPositionType(CSSPositionType.ABSOLUTE);
    root_child0.setPosition(Spacing.END, 10);
    root_child0.setPosition(Spacing.BOTTOM, 10);
    root_child0.setStyleWidth(10);
    root_child0.setStyleHeight(10);
    root.addChildAt(root_child0, 0);
    root.setDirection(CSSDirection.LTR);
    root.calculateLayout(null);

    assertEquals(0, root.getLayoutX(), 0.0f);
    assertEquals(0, root.getLayoutY(), 0.0f);
    assertEquals(100, root.getLayoutWidth(), 0.0f);
    assertEquals(100, root.getLayoutHeight(), 0.0f);

    assertEquals(80, root_child0.getLayoutX(), 0.0f);
    assertEquals(80, root_child0.getLayoutY(), 0.0f);
    assertEquals(10, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child0.getLayoutHeight(), 0.0f);

    root.setDirection(CSSDirection.RTL);
    root.calculateLayout(null);

    assertEquals(0, root.getLayoutX(), 0.0f);
    assertEquals(0, root.getLayoutY(), 0.0f);
    assertEquals(100, root.getLayoutWidth(), 0.0f);
    assertEquals(100, root.getLayoutHeight(), 0.0f);

    assertEquals(10, root_child0.getLayoutX(), 0.0f);
    assertEquals(80, root_child0.getLayoutY(), 0.0f);
    assertEquals(10, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child0.getLayoutHeight(), 0.0f);
  }

  @Test
  public void test_absolute_layout_start_top_end_bottom() {
    final CSSNode root = new CSSNode();
    root.setStyleWidth(100);
    root.setStyleHeight(100);

    final CSSNode root_child0 = new CSSNode();
    root_child0.setPositionType(CSSPositionType.ABSOLUTE);
    root_child0.setPosition(Spacing.START, 10);
    root_child0.setPosition(Spacing.TOP, 10);
    root_child0.setPosition(Spacing.END, 10);
    root_child0.setPosition(Spacing.BOTTOM, 10);
    root.addChildAt(root_child0, 0);
    root.setDirection(CSSDirection.LTR);
    root.calculateLayout(null);

    assertEquals(0, root.getLayoutX(), 0.0f);
    assertEquals(0, root.getLayoutY(), 0.0f);
    assertEquals(100, root.getLayoutWidth(), 0.0f);
    assertEquals(100, root.getLayoutHeight(), 0.0f);

    assertEquals(10, root_child0.getLayoutX(), 0.0f);
    assertEquals(10, root_child0.getLayoutY(), 0.0f);
    assertEquals(80, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(80, root_child0.getLayoutHeight(), 0.0f);

    root.setDirection(CSSDirection.RTL);
    root.calculateLayout(null);

    assertEquals(0, root.getLayoutX(), 0.0f);
    assertEquals(0, root.getLayoutY(), 0.0f);
    assertEquals(100, root.getLayoutWidth(), 0.0f);
    assertEquals(100, root.getLayoutHeight(), 0.0f);

    assertEquals(10, root_child0.getLayoutX(), 0.0f);
    assertEquals(10, root_child0.getLayoutY(), 0.0f);
    assertEquals(80, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(80, root_child0.getLayoutHeight(), 0.0f);
  }

  @Test
  public void test_absolute_layout_width_height_start_top_end_bottom() {
    final CSSNode root = new CSSNode();
    root.setStyleWidth(100);
    root.setStyleHeight(100);

    final CSSNode root_child0 = new CSSNode();
    root_child0.setPositionType(CSSPositionType.ABSOLUTE);
    root_child0.setPosition(Spacing.START, 10);
    root_child0.setPosition(Spacing.TOP, 10);
    root_child0.setPosition(Spacing.END, 10);
    root_child0.setPosition(Spacing.BOTTOM, 10);
    root_child0.setStyleWidth(10);
    root_child0.setStyleHeight(10);
    root.addChildAt(root_child0, 0);
    root.setDirection(CSSDirection.LTR);
    root.calculateLayout(null);

    assertEquals(0, root.getLayoutX(), 0.0f);
    assertEquals(0, root.getLayoutY(), 0.0f);
    assertEquals(100, root.getLayoutWidth(), 0.0f);
    assertEquals(100, root.getLayoutHeight(), 0.0f);

    assertEquals(10, root_child0.getLayoutX(), 0.0f);
    assertEquals(10, root_child0.getLayoutY(), 0.0f);
    assertEquals(10, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child0.getLayoutHeight(), 0.0f);

    root.setDirection(CSSDirection.RTL);
    root.calculateLayout(null);

    assertEquals(0, root.getLayoutX(), 0.0f);
    assertEquals(0, root.getLayoutY(), 0.0f);
    assertEquals(100, root.getLayoutWidth(), 0.0f);
    assertEquals(100, root.getLayoutHeight(), 0.0f);

    assertEquals(80, root_child0.getLayoutX(), 0.0f);
    assertEquals(10, root_child0.getLayoutY(), 0.0f);
    assertEquals(10, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child0.getLayoutHeight(), 0.0f);
  }

  @Test
  public void test_do_not_clamp_height_of_absolute_node_to_height_of_its_overflow_hidden_parent() {
    final CSSNode root = new CSSNode();
    root.setFlexDirection(CSSFlexDirection.ROW);
    root.setOverflow(CSSOverflow.HIDDEN);
    root.setStyleWidth(50);
    root.setStyleHeight(50);

    final CSSNode root_child0 = new CSSNode();
    root_child0.setPositionType(CSSPositionType.ABSOLUTE);
    root.addChildAt(root_child0, 0);

    final CSSNode root_child0_child0 = new CSSNode();
    root_child0_child0.setStyleWidth(100);
    root_child0_child0.setStyleHeight(100);
    root_child0.addChildAt(root_child0_child0, 0);
    root.setDirection(CSSDirection.LTR);
    root.calculateLayout(null);

    assertEquals(0, root.getLayoutX(), 0.0f);
    assertEquals(0, root.getLayoutY(), 0.0f);
    assertEquals(50, root.getLayoutWidth(), 0.0f);
    assertEquals(50, root.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child0.getLayoutX(), 0.0f);
    assertEquals(0, root_child0.getLayoutY(), 0.0f);
    assertEquals(100, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(100, root_child0.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child0_child0.getLayoutX(), 0.0f);
    assertEquals(0, root_child0_child0.getLayoutY(), 0.0f);
    assertEquals(100, root_child0_child0.getLayoutWidth(), 0.0f);
    assertEquals(100, root_child0_child0.getLayoutHeight(), 0.0f);

    root.setDirection(CSSDirection.RTL);
    root.calculateLayout(null);

    assertEquals(0, root.getLayoutX(), 0.0f);
    assertEquals(0, root.getLayoutY(), 0.0f);
    assertEquals(50, root.getLayoutWidth(), 0.0f);
    assertEquals(50, root.getLayoutHeight(), 0.0f);

    assertEquals(-50, root_child0.getLayoutX(), 0.0f);
    assertEquals(0, root_child0.getLayoutY(), 0.0f);
    assertEquals(100, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(100, root_child0.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child0_child0.getLayoutX(), 0.0f);
    assertEquals(0, root_child0_child0.getLayoutY(), 0.0f);
    assertEquals(100, root_child0_child0.getLayoutWidth(), 0.0f);
    assertEquals(100, root_child0_child0.getLayoutHeight(), 0.0f);
  }

}
