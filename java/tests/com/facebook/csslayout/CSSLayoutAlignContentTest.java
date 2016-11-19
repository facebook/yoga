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
<div id="align_content_flex_start" style="width: 100px; height: 100px; flex-wrap: wrap; flex-direction: column; align-content: flex-start;">
  <div style="width: 50px; height: 10px;"></div>
  <div style="width: 50px; height: 10px;"></div>
  <div style="width: 50px; height: 10px;"></div>
  <div style="width: 50px; height: 10px;"></div>
  <div style="width: 50px; height: 10px;"></div>
</div>

<div id="align_content_flex_end" style="width: 100px; height: 100px; flex-wrap: wrap; flex-direction: column; align-content: flex-end;">
  <div style="width: 50px; height: 10px;"></div>
  <div style="width: 50px; height: 10px;"></div>
  <div style="width: 50px; height: 10px;"></div>
  <div style="width: 50px; height: 10px;"></div>
  <div style="width: 50px; height: 10px;"></div>
</div>

<div id="align_content_center" style="width: 100px; height: 100px; flex-wrap: wrap; flex-direction: column; align-content: center;">
  <div style="width: 50px; height: 10px;"></div>
  <div style="width: 50px; height: 10px;"></div>
  <div style="width: 50px; height: 10px;"></div>
  <div style="width: 50px; height: 10px;"></div>
  <div style="width: 50px; height: 10px;"></div>
</div>

<div id="align_content_stretch" style="width: 100px; height: 100px; flex-wrap: wrap; flex-direction: column; align-content: stretch;">
  <div style="width: 50px;"></div>
  <div style="width: 50px;"></div>
  <div style="width: 50px;"></div>
  <div style="width: 50px;"></div>
  <div style="width: 50px;"></div>
</div>
 *
 */

package com.facebook.csslayout;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class CSSLayoutAlignContentTest {
  @Test
  public void test_align_content_flex_start() {
    final CSSNode root = new CSSNode();
    root.setWrap(CSSWrap.WRAP);
    root.setStyleWidth(100);
    root.setStyleHeight(100);

    final CSSNode root_child0 = new CSSNode();
    root_child0.setStyleWidth(50);
    root_child0.setStyleHeight(10);
    root.addChildAt(root_child0, 0);

    final CSSNode root_child1 = new CSSNode();
    root_child1.setStyleWidth(50);
    root_child1.setStyleHeight(10);
    root.addChildAt(root_child1, 1);

    final CSSNode root_child2 = new CSSNode();
    root_child2.setStyleWidth(50);
    root_child2.setStyleHeight(10);
    root.addChildAt(root_child2, 2);

    final CSSNode root_child3 = new CSSNode();
    root_child3.setStyleWidth(50);
    root_child3.setStyleHeight(10);
    root.addChildAt(root_child3, 3);

    final CSSNode root_child4 = new CSSNode();
    root_child4.setStyleWidth(50);
    root_child4.setStyleHeight(10);
    root.addChildAt(root_child4, 4);
    root.setDirection(CSSDirection.LTR);
    root.calculateLayout(null);

    assertEquals(0, root.getLayoutX(), 0.0f);
    assertEquals(0, root.getLayoutY(), 0.0f);
    assertEquals(100, root.getLayoutWidth(), 0.0f);
    assertEquals(100, root.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child0.getLayoutX(), 0.0f);
    assertEquals(0, root_child0.getLayoutY(), 0.0f);
    assertEquals(50, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child0.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child1.getLayoutX(), 0.0f);
    assertEquals(10, root_child1.getLayoutY(), 0.0f);
    assertEquals(50, root_child1.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child1.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child2.getLayoutX(), 0.0f);
    assertEquals(20, root_child2.getLayoutY(), 0.0f);
    assertEquals(50, root_child2.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child2.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child3.getLayoutX(), 0.0f);
    assertEquals(30, root_child3.getLayoutY(), 0.0f);
    assertEquals(50, root_child3.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child3.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child4.getLayoutX(), 0.0f);
    assertEquals(40, root_child4.getLayoutY(), 0.0f);
    assertEquals(50, root_child4.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child4.getLayoutHeight(), 0.0f);

    root.setDirection(CSSDirection.RTL);
    root.calculateLayout(null);

    assertEquals(0, root.getLayoutX(), 0.0f);
    assertEquals(0, root.getLayoutY(), 0.0f);
    assertEquals(100, root.getLayoutWidth(), 0.0f);
    assertEquals(100, root.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child0.getLayoutX(), 0.0f);
    assertEquals(0, root_child0.getLayoutY(), 0.0f);
    assertEquals(50, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child0.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child1.getLayoutX(), 0.0f);
    assertEquals(10, root_child1.getLayoutY(), 0.0f);
    assertEquals(50, root_child1.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child1.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child2.getLayoutX(), 0.0f);
    assertEquals(20, root_child2.getLayoutY(), 0.0f);
    assertEquals(50, root_child2.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child2.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child3.getLayoutX(), 0.0f);
    assertEquals(30, root_child3.getLayoutY(), 0.0f);
    assertEquals(50, root_child3.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child3.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child4.getLayoutX(), 0.0f);
    assertEquals(40, root_child4.getLayoutY(), 0.0f);
    assertEquals(50, root_child4.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child4.getLayoutHeight(), 0.0f);
  }

  @Test
  public void test_align_content_flex_end() {
    final CSSNode root = new CSSNode();
    root.setAlignContent(CSSAlign.FLEX_END);
    root.setWrap(CSSWrap.WRAP);
    root.setStyleWidth(100);
    root.setStyleHeight(100);

    final CSSNode root_child0 = new CSSNode();
    root_child0.setStyleWidth(50);
    root_child0.setStyleHeight(10);
    root.addChildAt(root_child0, 0);

    final CSSNode root_child1 = new CSSNode();
    root_child1.setStyleWidth(50);
    root_child1.setStyleHeight(10);
    root.addChildAt(root_child1, 1);

    final CSSNode root_child2 = new CSSNode();
    root_child2.setStyleWidth(50);
    root_child2.setStyleHeight(10);
    root.addChildAt(root_child2, 2);

    final CSSNode root_child3 = new CSSNode();
    root_child3.setStyleWidth(50);
    root_child3.setStyleHeight(10);
    root.addChildAt(root_child3, 3);

    final CSSNode root_child4 = new CSSNode();
    root_child4.setStyleWidth(50);
    root_child4.setStyleHeight(10);
    root.addChildAt(root_child4, 4);
    root.setDirection(CSSDirection.LTR);
    root.calculateLayout(null);

    assertEquals(0, root.getLayoutX(), 0.0f);
    assertEquals(0, root.getLayoutY(), 0.0f);
    assertEquals(100, root.getLayoutWidth(), 0.0f);
    assertEquals(100, root.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child0.getLayoutX(), 0.0f);
    assertEquals(0, root_child0.getLayoutY(), 0.0f);
    assertEquals(50, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child0.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child1.getLayoutX(), 0.0f);
    assertEquals(10, root_child1.getLayoutY(), 0.0f);
    assertEquals(50, root_child1.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child1.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child2.getLayoutX(), 0.0f);
    assertEquals(20, root_child2.getLayoutY(), 0.0f);
    assertEquals(50, root_child2.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child2.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child3.getLayoutX(), 0.0f);
    assertEquals(30, root_child3.getLayoutY(), 0.0f);
    assertEquals(50, root_child3.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child3.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child4.getLayoutX(), 0.0f);
    assertEquals(40, root_child4.getLayoutY(), 0.0f);
    assertEquals(50, root_child4.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child4.getLayoutHeight(), 0.0f);

    root.setDirection(CSSDirection.RTL);
    root.calculateLayout(null);

    assertEquals(0, root.getLayoutX(), 0.0f);
    assertEquals(0, root.getLayoutY(), 0.0f);
    assertEquals(100, root.getLayoutWidth(), 0.0f);
    assertEquals(100, root.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child0.getLayoutX(), 0.0f);
    assertEquals(0, root_child0.getLayoutY(), 0.0f);
    assertEquals(50, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child0.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child1.getLayoutX(), 0.0f);
    assertEquals(10, root_child1.getLayoutY(), 0.0f);
    assertEquals(50, root_child1.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child1.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child2.getLayoutX(), 0.0f);
    assertEquals(20, root_child2.getLayoutY(), 0.0f);
    assertEquals(50, root_child2.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child2.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child3.getLayoutX(), 0.0f);
    assertEquals(30, root_child3.getLayoutY(), 0.0f);
    assertEquals(50, root_child3.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child3.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child4.getLayoutX(), 0.0f);
    assertEquals(40, root_child4.getLayoutY(), 0.0f);
    assertEquals(50, root_child4.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child4.getLayoutHeight(), 0.0f);
  }

  @Test
  public void test_align_content_center() {
    final CSSNode root = new CSSNode();
    root.setAlignContent(CSSAlign.CENTER);
    root.setWrap(CSSWrap.WRAP);
    root.setStyleWidth(100);
    root.setStyleHeight(100);

    final CSSNode root_child0 = new CSSNode();
    root_child0.setStyleWidth(50);
    root_child0.setStyleHeight(10);
    root.addChildAt(root_child0, 0);

    final CSSNode root_child1 = new CSSNode();
    root_child1.setStyleWidth(50);
    root_child1.setStyleHeight(10);
    root.addChildAt(root_child1, 1);

    final CSSNode root_child2 = new CSSNode();
    root_child2.setStyleWidth(50);
    root_child2.setStyleHeight(10);
    root.addChildAt(root_child2, 2);

    final CSSNode root_child3 = new CSSNode();
    root_child3.setStyleWidth(50);
    root_child3.setStyleHeight(10);
    root.addChildAt(root_child3, 3);

    final CSSNode root_child4 = new CSSNode();
    root_child4.setStyleWidth(50);
    root_child4.setStyleHeight(10);
    root.addChildAt(root_child4, 4);
    root.setDirection(CSSDirection.LTR);
    root.calculateLayout(null);

    assertEquals(0, root.getLayoutX(), 0.0f);
    assertEquals(0, root.getLayoutY(), 0.0f);
    assertEquals(100, root.getLayoutWidth(), 0.0f);
    assertEquals(100, root.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child0.getLayoutX(), 0.0f);
    assertEquals(0, root_child0.getLayoutY(), 0.0f);
    assertEquals(50, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child0.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child1.getLayoutX(), 0.0f);
    assertEquals(10, root_child1.getLayoutY(), 0.0f);
    assertEquals(50, root_child1.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child1.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child2.getLayoutX(), 0.0f);
    assertEquals(20, root_child2.getLayoutY(), 0.0f);
    assertEquals(50, root_child2.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child2.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child3.getLayoutX(), 0.0f);
    assertEquals(30, root_child3.getLayoutY(), 0.0f);
    assertEquals(50, root_child3.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child3.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child4.getLayoutX(), 0.0f);
    assertEquals(40, root_child4.getLayoutY(), 0.0f);
    assertEquals(50, root_child4.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child4.getLayoutHeight(), 0.0f);

    root.setDirection(CSSDirection.RTL);
    root.calculateLayout(null);

    assertEquals(0, root.getLayoutX(), 0.0f);
    assertEquals(0, root.getLayoutY(), 0.0f);
    assertEquals(100, root.getLayoutWidth(), 0.0f);
    assertEquals(100, root.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child0.getLayoutX(), 0.0f);
    assertEquals(0, root_child0.getLayoutY(), 0.0f);
    assertEquals(50, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child0.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child1.getLayoutX(), 0.0f);
    assertEquals(10, root_child1.getLayoutY(), 0.0f);
    assertEquals(50, root_child1.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child1.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child2.getLayoutX(), 0.0f);
    assertEquals(20, root_child2.getLayoutY(), 0.0f);
    assertEquals(50, root_child2.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child2.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child3.getLayoutX(), 0.0f);
    assertEquals(30, root_child3.getLayoutY(), 0.0f);
    assertEquals(50, root_child3.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child3.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child4.getLayoutX(), 0.0f);
    assertEquals(40, root_child4.getLayoutY(), 0.0f);
    assertEquals(50, root_child4.getLayoutWidth(), 0.0f);
    assertEquals(10, root_child4.getLayoutHeight(), 0.0f);
  }

  @Test
  public void test_align_content_stretch() {
    final CSSNode root = new CSSNode();
    root.setAlignContent(CSSAlign.STRETCH);
    root.setWrap(CSSWrap.WRAP);
    root.setStyleWidth(100);
    root.setStyleHeight(100);

    final CSSNode root_child0 = new CSSNode();
    root_child0.setStyleWidth(50);
    root.addChildAt(root_child0, 0);

    final CSSNode root_child1 = new CSSNode();
    root_child1.setStyleWidth(50);
    root.addChildAt(root_child1, 1);

    final CSSNode root_child2 = new CSSNode();
    root_child2.setStyleWidth(50);
    root.addChildAt(root_child2, 2);

    final CSSNode root_child3 = new CSSNode();
    root_child3.setStyleWidth(50);
    root.addChildAt(root_child3, 3);

    final CSSNode root_child4 = new CSSNode();
    root_child4.setStyleWidth(50);
    root.addChildAt(root_child4, 4);
    root.setDirection(CSSDirection.LTR);
    root.calculateLayout(null);

    assertEquals(0, root.getLayoutX(), 0.0f);
    assertEquals(0, root.getLayoutY(), 0.0f);
    assertEquals(100, root.getLayoutWidth(), 0.0f);
    assertEquals(100, root.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child0.getLayoutX(), 0.0f);
    assertEquals(0, root_child0.getLayoutY(), 0.0f);
    assertEquals(50, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(0, root_child0.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child1.getLayoutX(), 0.0f);
    assertEquals(0, root_child1.getLayoutY(), 0.0f);
    assertEquals(50, root_child1.getLayoutWidth(), 0.0f);
    assertEquals(0, root_child1.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child2.getLayoutX(), 0.0f);
    assertEquals(0, root_child2.getLayoutY(), 0.0f);
    assertEquals(50, root_child2.getLayoutWidth(), 0.0f);
    assertEquals(0, root_child2.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child3.getLayoutX(), 0.0f);
    assertEquals(0, root_child3.getLayoutY(), 0.0f);
    assertEquals(50, root_child3.getLayoutWidth(), 0.0f);
    assertEquals(0, root_child3.getLayoutHeight(), 0.0f);

    assertEquals(0, root_child4.getLayoutX(), 0.0f);
    assertEquals(0, root_child4.getLayoutY(), 0.0f);
    assertEquals(50, root_child4.getLayoutWidth(), 0.0f);
    assertEquals(0, root_child4.getLayoutHeight(), 0.0f);

    root.setDirection(CSSDirection.RTL);
    root.calculateLayout(null);

    assertEquals(0, root.getLayoutX(), 0.0f);
    assertEquals(0, root.getLayoutY(), 0.0f);
    assertEquals(100, root.getLayoutWidth(), 0.0f);
    assertEquals(100, root.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child0.getLayoutX(), 0.0f);
    assertEquals(0, root_child0.getLayoutY(), 0.0f);
    assertEquals(50, root_child0.getLayoutWidth(), 0.0f);
    assertEquals(0, root_child0.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child1.getLayoutX(), 0.0f);
    assertEquals(0, root_child1.getLayoutY(), 0.0f);
    assertEquals(50, root_child1.getLayoutWidth(), 0.0f);
    assertEquals(0, root_child1.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child2.getLayoutX(), 0.0f);
    assertEquals(0, root_child2.getLayoutY(), 0.0f);
    assertEquals(50, root_child2.getLayoutWidth(), 0.0f);
    assertEquals(0, root_child2.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child3.getLayoutX(), 0.0f);
    assertEquals(0, root_child3.getLayoutY(), 0.0f);
    assertEquals(50, root_child3.getLayoutWidth(), 0.0f);
    assertEquals(0, root_child3.getLayoutHeight(), 0.0f);

    assertEquals(50, root_child4.getLayoutX(), 0.0f);
    assertEquals(0, root_child4.getLayoutY(), 0.0f);
    assertEquals(50, root_child4.getLayoutWidth(), 0.0f);
    assertEquals(0, root_child4.getLayoutHeight(), 0.0f);
  }

}
