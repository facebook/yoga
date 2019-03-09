/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */
package com.facebook.yoga;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import static org.junit.Assert.assertEquals;

@RunWith(Parameterized.class)
public class BatchingAPITests {

  @Parameterized.Parameters(name = "{0}")
  public static Iterable<TestParametrization.NodeFactory> nodeFactories() {
    return TestParametrization.nodeFactories();
  }

  @Parameterized.Parameter public TestParametrization.NodeFactory mNodeFactory;

  @Test
  public void testStyleInputLayoutDirection() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.LAYOUT_DIRECTION, YogaDirection.LTR.intValue()};
    root.setStyleInputs(arr, 2);
    root.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
    assertEquals(root.getLayoutDirection(), YogaDirection.LTR);
  }

  @Test
  public void testStyleInputFlexDirection() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.FLEX_DIRECTION, YogaFlexDirection.ROW.intValue()};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getFlexDirection(), YogaFlexDirection.ROW);
  }

  @Test
  public void testStyleInputFlex() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.FLEX, 5f};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getFlex(), 5f, 0.0f);
  }

  @Test
  public void testStyleInputFlexGrow() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.FLEX_GROW, 5f};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getFlexGrow(), 5f, 0.0f);
  }

  @Test
  public void testStyleInputFlexShrink() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.FLEX_SHRINK, 5f};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getFlexShrink(), 5f, 0.0f);
  }

  @Test
  public void testStyleInputFlexBasis() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.FLEX_BASIS, 5f};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getFlexBasis(), new YogaValue(5f, YogaUnit.POINT));
  }

  @Test
  public void testStyleInputFlexBasisPercent() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.FLEX_BASIS_PERCENT, 5f};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getFlexBasis(), new YogaValue(5f, YogaUnit.PERCENT));
  }

  @Test
  public void testStyleInputFlexBasisAuto() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.FLEX_BASIS_AUTO};
    root.setStyleInputs(arr, 1);
    assertEquals(root.getFlexBasis(), YogaValue.AUTO);
  }

  @Test
  public void testStyleInputFlexWrap() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.FLEX_WRAP, YogaWrap.WRAP.intValue()};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getWrap(), YogaWrap.WRAP);
  }

  @Test
  public void testStyleInputWidth() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.WIDTH, 50f};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getWidth(), new YogaValue(50f, YogaUnit.POINT));
  }

  @Test
  public void testStyleInputWidthPercent() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.WIDTH_PERCENT, 5f};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getWidth(), new YogaValue(5f, YogaUnit.PERCENT));
  }

  @Test
  public void testStyleInputWidthAuto() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.WIDTH_AUTO};
    root.setStyleInputs(arr, 1);
    assertEquals(root.getWidth(), YogaValue.AUTO);
  }

  @Test
  public void testStyleInputMinWidth() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.MIN_WIDTH, 50f};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getMinWidth(), new YogaValue(50f, YogaUnit.POINT));
  }

  @Test
  public void testStyleInputMinWidthPercent() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.MIN_WIDTH_PERCENT, 5f};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getMinWidth(), new YogaValue(5f, YogaUnit.PERCENT));
  }

  @Test
  public void testStyleInputMaxWidth() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.MAX_WIDTH, 50f};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getMaxWidth(), new YogaValue(50f, YogaUnit.POINT));
  }

  @Test
  public void testStyleInputMaxWidthPercent() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.MAX_WIDTH_PERCENT, 5f};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getMaxWidth(), new YogaValue(5f, YogaUnit.PERCENT));
  }

  @Test
  public void testStyleInputHeight() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.HEIGHT, 50f};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getHeight(), new YogaValue(50f, YogaUnit.POINT));
  }

  @Test
  public void testStyleInputHeightPercent() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.HEIGHT_PERCENT, 5f};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getHeight(), new YogaValue(5f, YogaUnit.PERCENT));
  }

  @Test
  public void testStyleInputHeightAuto() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.HEIGHT_AUTO};
    root.setStyleInputs(arr, 1);
    assertEquals(root.getHeight(), YogaValue.AUTO);
  }

  @Test
  public void testStyleInputMinHeight() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.MIN_HEIGHT, 50f};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getMinHeight(), new YogaValue(50f, YogaUnit.POINT));
  }

  @Test
  public void testStyleInputMinHeightPercent() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.MIN_HEIGHT_PERCENT, 5f};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getMinHeight(), new YogaValue(5f, YogaUnit.PERCENT));
  }

  @Test
  public void testStyleInputMaxHeight() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.MAX_HEIGHT, 50f};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getMaxHeight(), new YogaValue(50f, YogaUnit.POINT));
  }

  @Test
  public void testStyleInputMaxHeightPercent() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.MAX_HEIGHT_PERCENT, 5f};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getMaxHeight(), new YogaValue(5f, YogaUnit.PERCENT));
  }

  @Test
  public void testStyleInputJustiyContent() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.JUSTIFY_CONTENT, YogaJustify.CENTER.intValue()};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getJustifyContent(), YogaJustify.CENTER);
  }

  @Test
  public void testStyleInputAlignItems() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.ALIGN_ITEMS, YogaAlign.BASELINE.intValue()};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getAlignItems(), YogaAlign.BASELINE);
  }

  @Test
  public void testStyleInputAlignSelf() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.ALIGN_SELF, YogaAlign.BASELINE.intValue()};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getAlignSelf(), YogaAlign.BASELINE);
  }

  @Test
  public void testStyleInputAlignContent() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.ALIGN_CONTENT, YogaAlign.BASELINE.intValue()};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getAlignContent(), YogaAlign.BASELINE);
  }

  @Test
  public void testStyleInputPositionType() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.POSITION_TYPE, YogaPositionType.ABSOLUTE.intValue()};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getPositionType(), YogaPositionType.ABSOLUTE);
  }

  @Test
  public void testStyleInputAspectRatio() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.ASPECT_RATIO, 2f};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getAspectRatio(), 2f, 0.0f);
  }

  @Test
  public void testStyleInputOverflow() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.OVERFLOW, YogaOverflow.HIDDEN.intValue()};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getOverflow(), YogaOverflow.HIDDEN);
  }

  @Test
  public void testStyleInputDisplay() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.DISPLAY, YogaDisplay.NONE.intValue()};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getDisplay(), YogaDisplay.NONE);
  }

  @Test
  public void testStyleInputMargin() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.MARGIN, YogaEdge.LEFT.intValue(), 12f};
    root.setStyleInputs(arr, 3);
    assertEquals(root.getMargin(YogaEdge.LEFT), new YogaValue(12f, YogaUnit.POINT));
  }

  @Test
  public void testStyleInputMarginPercent() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.MARGIN_PERCENT, YogaEdge.LEFT.intValue(), 12f};
    root.setStyleInputs(arr, 3);
    assertEquals(root.getMargin(YogaEdge.LEFT), new YogaValue(12f, YogaUnit.PERCENT));
  }

  @Test
  public void testStyleInputMarginAuto() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.MARGIN_AUTO, YogaEdge.LEFT.intValue()};
    root.setStyleInputs(arr, 2);
    assertEquals(root.getMargin(YogaEdge.LEFT), YogaValue.AUTO);
  }

  @Test
  public void testStyleInputPadding() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.PADDING, YogaEdge.LEFT.intValue(), 12f};
    root.setStyleInputs(arr, 3);
    assertEquals(root.getPadding(YogaEdge.LEFT), new YogaValue(12f, YogaUnit.POINT));
  }

  @Test
  public void testStyleInputPaddingPercent() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.PADDING_PERCENT, YogaEdge.LEFT.intValue(), 12f};
    root.setStyleInputs(arr, 3);
    assertEquals(root.getPadding(YogaEdge.LEFT), new YogaValue(12f, YogaUnit.PERCENT));
  }

  @Test
  public void testStyleInputBorder() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.BORDER, YogaEdge.LEFT.intValue(), 12f};
    root.setStyleInputs(arr, 3);
    assertEquals(root.getBorder(YogaEdge.LEFT), 12f, 0.0f);
  }

  @Test
  public void testStyleInputPosition() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.POSITION, YogaEdge.LEFT.intValue(), 12f};
    root.setStyleInputs(arr, 3);
    assertEquals(root.getPosition(YogaEdge.LEFT), new YogaValue(12f, YogaUnit.POINT));
  }

  @Test
  public void testStyleInputPositionPercent() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.POSITION_PERCENT, YogaEdge.LEFT.intValue(), 12f};
    root.setStyleInputs(arr, 3);
    assertEquals(root.getPosition(YogaEdge.LEFT), new YogaValue(12f, YogaUnit.PERCENT));
  }

  @Test
  public void testStyleInputIsReferenceBaseline() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    float[] arr = new float[]{YogaStyleInputs.IS_REFERENCE_BASELINE, 1f};
    root.setStyleInputs(arr, 2);
    assertEquals(root.isReferenceBaseline(), true);
  }

  @Test
  public void testStyleInputs() {
    YogaConfig config = new YogaConfig();
    final YogaNode root = createNode(config);
    int count = 0;
    float[] arr = new float[100];
    arr[count++] = YogaStyleInputs.FLEX_DIRECTION;
    arr[count++] = YogaFlexDirection.ROW.intValue();

    arr[count++] = YogaStyleInputs.FLEX;
    arr[count++] = 5f;

    arr[count++] = YogaStyleInputs.FLEX_GROW;
    arr[count++] = 5f;

    arr[count++] = YogaStyleInputs.FLEX_SHRINK;
    arr[count++] = 5f;

    arr[count++] = YogaStyleInputs.FLEX_BASIS_AUTO;

    arr[count++] = YogaStyleInputs.FLEX_WRAP;
    arr[count++] = YogaWrap.WRAP.intValue();

    arr[count++] = YogaStyleInputs.WIDTH;
    arr[count++] = 50f;

    arr[count++] = YogaStyleInputs.MIN_WIDTH;
    arr[count++] = 50f;

    arr[count++] = YogaStyleInputs.MAX_WIDTH;
    arr[count++] = 50f;

    arr[count++] = YogaStyleInputs.HEIGHT;
    arr[count++] = 5f;

    arr[count++] = YogaStyleInputs.MIN_HEIGHT;
    arr[count++] = 50f;

    arr[count++] = YogaStyleInputs.MAX_HEIGHT;
    arr[count++] = 50f;

    arr[count++] = YogaStyleInputs.JUSTIFY_CONTENT;
    arr[count++] = YogaJustify.CENTER.intValue();

    arr[count++] = YogaStyleInputs.ALIGN_ITEMS;
    arr[count++] = YogaAlign.BASELINE.intValue();

    arr[count++] = YogaStyleInputs.ALIGN_SELF;
    arr[count++] = YogaAlign.BASELINE.intValue();

    arr[count++] = YogaStyleInputs.ALIGN_CONTENT;
    arr[count++] = YogaAlign.BASELINE.intValue();

    arr[count++] = YogaStyleInputs.POSITION_TYPE;
    arr[count++] = YogaPositionType.ABSOLUTE.intValue();

    arr[count++] = YogaStyleInputs.ASPECT_RATIO;
    arr[count++] = 2f;

    arr[count++] = YogaStyleInputs.OVERFLOW;
    arr[count++] = YogaOverflow.HIDDEN.intValue();

    arr[count++] = YogaStyleInputs.DISPLAY;
    arr[count++] = YogaDisplay.NONE.intValue();

    arr[count++] = YogaStyleInputs.MARGIN_AUTO;
    arr[count++] = YogaEdge.LEFT.intValue();

    arr[count++] = YogaStyleInputs.PADDING;
    arr[count++] = YogaEdge.LEFT.intValue();
    arr[count++] = 12f;

    arr[count++] = YogaStyleInputs.BORDER;
    arr[count++] = YogaEdge.LEFT.intValue();
    arr[count++] = 12f;

    arr[count++] = YogaStyleInputs.POSITION_PERCENT;
    arr[count++] = YogaEdge.LEFT.intValue();
    arr[count++] = 12f;

    arr[count++] = YogaStyleInputs.IS_REFERENCE_BASELINE;
    arr[count++] = 1f;

    root.setStyleInputs(arr, count);

    assertEquals(root.getFlexDirection(), YogaFlexDirection.ROW);
    assertEquals(root.getFlex(), 5f, 0.0f);
    assertEquals(root.getFlexGrow(), 5f, 0.0f);
    assertEquals(root.getFlexShrink(), 5f, 0.0f);
    assertEquals(root.getFlexBasis(), YogaValue.AUTO);
    assertEquals(root.getWrap(), YogaWrap.WRAP);
    assertEquals(root.getWidth(), new YogaValue(50f, YogaUnit.POINT));
    assertEquals(root.getMinWidth(), new YogaValue(50f, YogaUnit.POINT));
    assertEquals(root.getMaxWidth(), new YogaValue(50f, YogaUnit.POINT));
    assertEquals(root.getHeight(), new YogaValue(5f, YogaUnit.POINT));
    assertEquals(root.getMinHeight(), new YogaValue(50f, YogaUnit.POINT));
    assertEquals(root.getMaxHeight(), new YogaValue(50f, YogaUnit.POINT));
    assertEquals(root.getJustifyContent(), YogaJustify.CENTER);
    assertEquals(root.getAlignItems(), YogaAlign.BASELINE);
    assertEquals(root.getAlignSelf(), YogaAlign.BASELINE);
    assertEquals(root.getAlignContent(), YogaAlign.BASELINE);
    assertEquals(root.getPositionType(), YogaPositionType.ABSOLUTE);
    assertEquals(root.getAspectRatio(), 2f, 0.0f);
    assertEquals(root.getOverflow(), YogaOverflow.HIDDEN);
    assertEquals(root.getDisplay(), YogaDisplay.NONE);
    assertEquals(root.getMargin(YogaEdge.LEFT), YogaValue.AUTO);
    assertEquals(root.getPadding(YogaEdge.LEFT), new YogaValue(12f, YogaUnit.POINT));
    assertEquals(root.getBorder(YogaEdge.LEFT), 12f, 0.0f);
    assertEquals(root.getPosition(YogaEdge.LEFT), new YogaValue(12f, YogaUnit.PERCENT));
    assertEquals(root.isReferenceBaseline(), true);
  }

  private YogaNode createNode(YogaConfig config) {
    return mNodeFactory.create(config);
  }
}
