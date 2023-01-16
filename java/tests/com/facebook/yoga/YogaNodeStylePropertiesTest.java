/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.yoga;

import static org.junit.Assert.assertEquals;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

@RunWith(Parameterized.class)
public class YogaNodeStylePropertiesTest {

  @Parameterized.Parameters(name = "{0}")
  public static Iterable<TestParametrization.NodeFactory> nodeFactories() {
    return TestParametrization.nodeFactories();
  }

  @Parameterized.Parameter public TestParametrization.NodeFactory mNodeFactory;

  private static final float UNDEFINED = YogaValue.UNDEFINED.value;

  @Test
  public void testDirectionDefault() {
    final YogaNode node = createNode();

    assertEquals(node.getStyleDirection(), YogaDirection.INHERIT);
    assertEquals(node.getLayoutDirection(), YogaDirection.INHERIT);
  }

  @Test
  public void testDirectionAssignment() {
    final YogaNode node = createNode();
    node.setDirection(YogaDirection.LTR);
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(YogaDirection.LTR, node.getStyleDirection());
    assertEquals(YogaDirection.LTR, node.getLayoutDirection());
  }

  @Test
  public void testDirectionAffectsLayout() {
    final YogaNode node =
        style().direction(YogaDirection.RTL).width(200).children(style().widthPercent(40)).node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(120, node.getChildAt(0).getLayoutX(), 0);
  }

  @Test
  public void testFlexDirectionDefault() {
    final YogaNode node = createNode();

    assertEquals(YogaFlexDirection.COLUMN, node.getFlexDirection());
  }

  @Test
  public void testFlexDirectionAssignment() {
    final YogaNode node = style().flexDirection(YogaFlexDirection.COLUMN_REVERSE).node();

    assertEquals(YogaFlexDirection.COLUMN_REVERSE, node.getFlexDirection());
  }

  @Test
  public void testFlexDirectionAffectsLayout() {
    final YogaNode node =
        style()
            .flexDirection(YogaFlexDirection.ROW_REVERSE)
            .width(200)
            .children(style().widthPercent(40))
            .node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(120, node.getChildAt(0).getLayoutX(), 0);
  }

  @Test
  public void testJustifyContentDefault() {
    final YogaNode node = createNode();

    assertEquals(YogaJustify.FLEX_START, node.getJustifyContent());
  }

  @Test
  public void testJustifyContentAssignment() {
    final YogaNode node = createNode();
    node.setJustifyContent(YogaJustify.SPACE_EVENLY);

    assertEquals(YogaJustify.SPACE_EVENLY, node.getJustifyContent());
  }

  @Test
  public void testJustifyContentAffectsLayout() {
    final YogaNode node =
        style()
            .justifyContent(YogaJustify.CENTER)
            .height(200)
            .children(style().heightPercent(40))
            .node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(60, node.getChildAt(0).getLayoutY(), 0);
  }

  @Test
  public void testAlignItemsDefault() {
    final YogaNode node = createNode();

    assertEquals(YogaAlign.STRETCH, node.getAlignItems());
  }

  @Test
  public void testAlignItemsAssignment() {
    final YogaNode node = createNode();
    node.setAlignItems(YogaAlign.SPACE_AROUND);

    assertEquals(YogaAlign.SPACE_AROUND, node.getAlignItems());
  }

  @Test
  public void testAlignItemsAffectsLayout() {
    final YogaNode node =
        style().alignItems(YogaAlign.CENTER).height(200).children(style().widthPercent(40)).node();
    node.calculateLayout(200, UNDEFINED);

    assertEquals(60, node.getChildAt(0).getLayoutX(), 0);
  }

  @Test
  public void testAlignSelfDefault() {
    final YogaNode node = createNode();

    assertEquals(YogaAlign.AUTO, node.getAlignSelf());
  }

  @Test
  public void testAlignSelfAssignment() {
    final YogaNode node = createNode();
    node.setAlignSelf(YogaAlign.FLEX_END);

    assertEquals(YogaAlign.FLEX_END, node.getAlignSelf());
  }

  @Test
  public void testAlignSelfAffectsLayout() {
    final YogaNode node =
        style().height(200).children(style().alignSelf(YogaAlign.CENTER).widthPercent(40)).node();
    node.calculateLayout(200, UNDEFINED);

    assertEquals(60, node.getChildAt(0).getLayoutX(), 0);
  }

  @Test
  public void testAlignContentDefault() {
    final YogaNode node = createNode();

    assertEquals(YogaAlign.FLEX_START, node.getAlignContent());
  }

  @Test
  public void testAlignContentAssignment() {
    final YogaNode node = createNode();
    node.setAlignContent(YogaAlign.BASELINE);

    assertEquals(YogaAlign.BASELINE, node.getAlignContent());
  }

  @Test
  public void testAlignContentAffectsLayout() {
    final YogaNode node =
        style()
            .alignContent(YogaAlign.SPACE_AROUND)
            .flexWrap(YogaWrap.WRAP)
            .height(200)
            .width(200)
            .children(
                style().widthPercent(20).heightPercent(60),
                style().widthPercent(20).heightPercent(60))
            .node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(30, node.getChildAt(0).getLayoutX(), 0);
  }

  @Test
  public void testPositionTypeDefault() {
    final YogaNode node = createNode();

    assertEquals(YogaPositionType.STATIC, node.getPositionType());
  }

  @Test
  public void testPositionTypeAssignment() {
    final YogaNode node = createNode();
    node.setPositionType(YogaPositionType.ABSOLUTE);

    assertEquals(YogaPositionType.ABSOLUTE, node.getPositionType());
  }

  @Test
  public void testPositionTypeAffectsLayout() {
    final YogaNode node =
        style()
            .height(200)
            .children(
                style().height(100), style().height(100).positionType(YogaPositionType.ABSOLUTE))
            .node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(0, node.getChildAt(1).getLayoutY(), 0);
  }

  @Test
  public void testWrapAffectsLayout() {
    final YogaNode node =
        style()
            .width(200)
            .height(200)
            .flexWrap(YogaWrap.WRAP_REVERSE)
            .children(style().width(10).heightPercent(60), style().heightPercent(60))
            .node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(190, node.getChildAt(0).getLayoutX(), 0);
  }

  @Test
  public void testOverflowDefault() {
    final YogaNode node = createNode();

    assertEquals(YogaOverflow.VISIBLE, node.getOverflow());
  }

  @Test
  public void testOverflowAssignment() {
    final YogaNode node = createNode();
    node.setOverflow(YogaOverflow.SCROLL);

    assertEquals(YogaOverflow.SCROLL, node.getOverflow());
  }

  // TODO add testOverflowAffectsLayout()

  @Test
  public void testDisplayDefault() {
    final YogaNode node = createNode();

    assertEquals(YogaDisplay.FLEX, node.getDisplay());
  }

  @Test
  public void testDisplayAssignment() {
    final YogaNode node = createNode();
    node.setDisplay(YogaDisplay.NONE);

    assertEquals(YogaDisplay.NONE, node.getDisplay());
  }

  @Test
  public void testDisplayAffectsLayout() {
    final YogaNode node =
        style().children(style().flexGrow(1).display(YogaDisplay.NONE), style().flexGrow(1)).node();
    node.calculateLayout(200, 200);

    assertEquals(200, node.getChildAt(1).getLayoutHeight(), 0);
  }

  @Test
  public void testFlexAffectsLayoutGrowing() {
    final YogaNode node = style().height(200).children(style().height(100).flex(1.25f)).node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(200, node.getChildAt(0).getLayoutHeight(), 0);
  }

  @Test
  public void testFlexAffectsLayoutShrinking() {
    final YogaNode node = style().height(200).children(style().height(300).flex(1.25f)).node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(200, node.getChildAt(0).getLayoutHeight(), 0);
  }

  @Test
  public void testFlexGrowDefault() {
    final YogaNode node = createNode();

    assertEquals(0, node.getFlexGrow(), 0);
  }

  @Test
  public void testFlexGrowAssignment() {
    final YogaNode node = createNode();
    node.setFlexGrow(2.5f);

    assertEquals(2.5f, node.getFlexGrow(), 0);
  }

  @Test
  public void testFlexGrowAffectsLayout() {
    final YogaNode node =
        style().height(200).children(style().height(50).flexGrow(1), style().height(50)).node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(150, node.getChildAt(0).getLayoutHeight(), 0);
  }

  @Test
  public void testFlexShrinkDefault() {
    final YogaNode node = createNode();

    assertEquals(0, node.getFlexShrink(), 0);
  }

  @Test
  public void testFlexShrinkAssignment() {
    final YogaNode node = createNode();
    node.setFlexShrink(2.5f);

    assertEquals(2.5f, node.getFlexShrink(), 0);
  }

  @Test
  public void testFlexShrinkAffectsLayout() {
    final YogaNode node =
        style().height(200).children(style().height(150).flexShrink(1), style().height(150)).node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(50, node.getChildAt(0).getLayoutHeight(), 0);
  }

  @Test
  public void testFlexBasisDefault() {
    final YogaNode node = createNode();

    assertEquals(YogaValue.AUTO, node.getFlexBasis());
  }

  @Test
  public void testFlexBasisAssignment() {
    final YogaNode node = createNode();
    node.setFlexBasis(50);
    assertEquals(new YogaValue(50, YogaUnit.POINT), node.getFlexBasis());

    node.setFlexBasisPercent(20);
    assertEquals(new YogaValue(20, YogaUnit.PERCENT), node.getFlexBasis());

    node.setFlexBasisAuto();
    assertEquals(YogaValue.AUTO, node.getFlexBasis());
  }

  @Test
  public void testFlexBasisAffectsLayout() {
    final YogaNode node =
        style()
            .height(200)
            .children(style().flexBasis(150).flexShrink(1), style().flexBasis(150).flexShrink(1))
            .node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(100, node.getChildAt(0).getLayoutHeight(), 0);
  }

  @Test
  public void testFlexBasisPercentAffectsLayout() {
    final YogaNode node =
        style()
            .height(200)
            .children(style().flexBasisPercent(60), style().flexBasisPercent(40))
            .node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(80, node.getChildAt(1).getLayoutHeight(), 0);
  }

  @Test
  public void testMarginDefault() {
    final YogaNode node = createNode();
    for (YogaEdge edge : YogaEdge.values()) {
      assertEquals(YogaValue.UNDEFINED, node.getMargin(edge));
    }
  }

  @Test
  public void testMarginAssignment() {
    final YogaNode node = createNode();
    for (YogaEdge edge : YogaEdge.values()) {
      node.setMargin(edge, 25);
      assertEquals(new YogaValue(25, YogaUnit.POINT), node.getMargin(edge));

      node.setMarginPercent(edge, 5);
      assertEquals(new YogaValue(5, YogaUnit.PERCENT), node.getMargin(edge));

      node.setMarginAuto(edge);
      assertEquals(YogaValue.AUTO, node.getMargin(edge));
    }
  }

  @Test
  public void testNegativeMarginAssignment() {
    final YogaNode node = createNode();
    for (YogaEdge edge : YogaEdge.values()) {
      node.setMargin(edge, -25);
      assertEquals(new YogaValue(-25, YogaUnit.POINT), node.getMargin(edge));

      node.setMarginPercent(edge, -5);
      assertEquals(new YogaValue(-5, YogaUnit.PERCENT), node.getMargin(edge));

      node.setMarginAuto(edge);
      assertEquals(YogaValue.AUTO, node.getMargin(edge));
    }
  }

  @Test
  public void testMarginPointAffectsLayout() {
    final YogaNode node = style().margin(YogaEdge.TOP, 42).node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(42, node.getLayoutY(), 0);
  }

  @Test
  public void testMarginPercentAffectsLayout() {
    final YogaNode node =
        style().height(200).children(style().flexGrow(1).marginPercent(YogaEdge.TOP, 20)).node();
    node.calculateLayout(200, 200);

    assertEquals(40, node.getChildAt(0).getLayoutY(), 0);
  }

  @Test
  public void testMarginAutoAffectsLayout() {
    final YogaNode node =
        style()
            .width(200)
            .flexDirection(YogaFlexDirection.ROW)
            .children(style().marginAuto(YogaEdge.LEFT).marginAuto(YogaEdge.RIGHT).width(100))
            .node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(50, node.getChildAt(0).getLayoutX(), 0);
  }

  @Test
  public void testPaddingDefault() {
    final YogaNode node = createNode();
    for (YogaEdge edge : YogaEdge.values()) {
      assertEquals(YogaValue.UNDEFINED, node.getPadding(edge));
    }
  }

  @Test
  public void testPaddingAssignment() {
    final YogaNode node = createNode();
    for (YogaEdge edge : YogaEdge.values()) {
      node.setPadding(edge, 25);
      assertEquals(new YogaValue(25, YogaUnit.POINT), node.getPadding(edge));

      node.setPaddingPercent(edge, 5);
      assertEquals(new YogaValue(5, YogaUnit.PERCENT), node.getPadding(edge));
    }
  }

  @Test
  public void testPaddingPointAffectsLayout() {
    final YogaNode node = style().padding(YogaEdge.TOP, 42).children(style()).node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(42, node.getChildAt(0).getLayoutY(), 0);
  }

  @Test
  public void testPaddingPercentAffectsLayout() {
    final YogaNode node =
        style().height(200).paddingPercent(YogaEdge.TOP, 20).children(style().flexGrow(1)).node();
    node.calculateLayout(200, 200);

    assertEquals(40, node.getChildAt(0).getLayoutY(), 0);
  }

  @Test
  public void testBorderDefault() {
    final YogaNode node = createNode();
    for (YogaEdge edge : YogaEdge.values()) {
      assertEquals(UNDEFINED, node.getBorder(edge), 0);
    }
  }

  @Test
  public void testBorderAssignment() {
    final YogaNode node = createNode();
    for (YogaEdge edge : YogaEdge.values()) {
      node.setBorder(edge, 2.5f);
      assertEquals(2.5f, node.getBorder(edge), 0);
    }
  }

  @Test
  public void testBorderAffectsLayout() {
    final YogaNode node = style().border(YogaEdge.TOP, 42).children(style()).node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(42, node.getChildAt(0).getLayoutY(), 0);
  }

  @Test
  public void testPositionDefault() {
    final YogaNode node = createNode();
    for (YogaEdge edge : YogaEdge.values()) {
      assertEquals(YogaValue.UNDEFINED, node.getPosition(edge));
    }
  }

  @Test
  public void testPositionAssignment() {
    final YogaNode node = createNode();
    for (YogaEdge edge : YogaEdge.values()) {
      node.setPosition(edge, 25);
      assertEquals(new YogaValue(25, YogaUnit.POINT), node.getPosition(edge));

      node.setPositionPercent(edge, 5);
      assertEquals(new YogaValue(5, YogaUnit.PERCENT), node.getPosition(edge));
    }
  }

  @Test
  public void testPositionAffectsLayout() {
    final YogaNode node =
        style()
            .height(100)
            .children(
                style()
                    .positionType(YogaPositionType.ABSOLUTE)
                    .position(YogaEdge.TOP, 11)
                    .position(YogaEdge.BOTTOM, 22))
            .node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(67, node.getChildAt(0).getLayoutHeight(), 0);
  }

  @Test
  public void testPositionPercentAffectsLayout() {
    final YogaNode node =
        style()
            .width(100)
            .children(
                style()
                    .positionType(YogaPositionType.ABSOLUTE)
                    .positionPercent(YogaEdge.LEFT, 11)
                    .positionPercent(YogaEdge.RIGHT, 22))
            .node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(67, node.getChildAt(0).getLayoutWidth(), 0);
  }

  @Test
  public void testWidthDefault() {
    final YogaNode node = createNode();

    assertEquals(YogaValue.AUTO, node.getWidth());
  }

  @Test
  public void testWidthAssignment() {
    final YogaNode node = createNode();
    node.setWidth(123);
    assertEquals(new YogaValue(123, YogaUnit.POINT), node.getWidth());

    node.setWidthPercent(45);
    assertEquals(new YogaValue(45, YogaUnit.PERCENT), node.getWidth());
  }

  @Test
  public void testWidthAffectsLayout() {
    final YogaNode node = style().width(123).node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(123, node.getLayoutWidth(), 0);
  }

  @Test
  public void testWidthPercentAffectsLayout() {
    final YogaNode node = style().widthPercent(75).node();
    node.calculateLayout(200, UNDEFINED);

    assertEquals(150, node.getLayoutWidth(), 0);
  }

  // TODO: testWidthAutoAffectsLayout

  @Test
  public void testHeightDefault() {
    final YogaNode node = createNode();

    assertEquals(YogaValue.AUTO, node.getHeight());
  }

  @Test
  public void testHeightAssignment() {
    final YogaNode node = createNode();
    node.setHeight(123);
    assertEquals(new YogaValue(123, YogaUnit.POINT), node.getHeight());

    node.setHeightPercent(45);
    assertEquals(new YogaValue(45, YogaUnit.PERCENT), node.getHeight());
  }

  @Test
  public void testHeightAffectsLayout() {
    final YogaNode node = style().height(123).node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(123, node.getLayoutHeight(), 0);
  }

  @Test
  public void testHeightPercentAffectsLayout() {
    final YogaNode node = style().heightPercent(75).node();
    node.calculateLayout(UNDEFINED, 200);

    assertEquals(150, node.getLayoutHeight(), 0);
  }

  // TODO: testHeightAutoAffectsLayout

  @Test
  public void testMinWidthDefault() {
    final YogaNode node = createNode();

    assertEquals(YogaValue.UNDEFINED, node.getMinWidth());
  }

  @Test
  public void testMinWidthAssignment() {
    final YogaNode node = createNode();
    node.setMinWidth(123);
    assertEquals(new YogaValue(123, YogaUnit.POINT), node.getMinWidth());

    node.setMinWidthPercent(45);
    assertEquals(new YogaValue(45, YogaUnit.PERCENT), node.getMinWidth());
  }

  @Test
  public void testMinWidthAffectsLayout() {
    final YogaNode node = style().minWidth(123).node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(123, node.getLayoutWidth(), 0);
  }

  @Test
  public void testMinWidthPercentAffectsLayout() {
    final YogaNode node = style().minWidthPercent(120).node();
    node.calculateLayout(200, UNDEFINED);

    assertEquals(240, node.getLayoutWidth(), 0);
  }

  @Test
  public void testMinHeightDefault() {
    final YogaNode node = createNode();

    assertEquals(YogaValue.UNDEFINED, node.getMinHeight());
  }

  @Test
  public void testMinHeightAssignment() {
    final YogaNode node = createNode();
    node.setMinHeight(123);
    assertEquals(new YogaValue(123, YogaUnit.POINT), node.getMinHeight());

    node.setMinHeightPercent(45);
    assertEquals(new YogaValue(45, YogaUnit.PERCENT), node.getMinHeight());
  }

  @Test
  public void testMinHeightAffectsLayout() {
    final YogaNode node = style().minHeight(123).node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(123, node.getLayoutHeight(), 0);
  }

  @Test
  public void testMinHeightPercentAffectsLayout() {
    final YogaNode node = style().minHeightPercent(120).node();
    node.calculateLayout(UNDEFINED, 200);

    assertEquals(240, node.getLayoutHeight(), 0);
  }

  @Test
  public void testMaxWidthDefault() {
    final YogaNode node = createNode();

    assertEquals(YogaValue.UNDEFINED, node.getMaxWidth());
  }

  @Test
  public void testMaxWidthAssignment() {
    final YogaNode node = createNode();
    node.setMaxWidth(123);
    assertEquals(new YogaValue(123, YogaUnit.POINT), node.getMaxWidth());

    node.setMaxWidthPercent(45);
    assertEquals(new YogaValue(45, YogaUnit.PERCENT), node.getMaxWidth());
  }

  @Test
  public void testMaxWidthAffectsLayout() {
    final YogaNode node = style().width(200).children(style().maxWidth(123)).node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(123, node.getChildAt(0).getLayoutWidth(), 0);
  }

  @Test
  public void testMaxWidthPercentAffectsLayout() {
    final YogaNode node = style().width(200).children(style().maxWidthPercent(80)).node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(160, node.getChildAt(0).getLayoutWidth(), 0);
  }

  @Test
  public void testMaxHeightDefault() {
    final YogaNode node = createNode();

    assertEquals(YogaValue.UNDEFINED, node.getMaxHeight());
  }

  @Test
  public void testMaxHeightAssignment() {
    final YogaNode node = createNode();
    node.setMaxHeight(123);
    assertEquals(new YogaValue(123, YogaUnit.POINT), node.getMaxHeight());

    node.setMaxHeightPercent(45);
    assertEquals(new YogaValue(45, YogaUnit.PERCENT), node.getMaxHeight());
  }

  @Test
  public void testMaxHeightAffectsLayout() {
    final YogaNode node =
        style()
            .height(200)
            .flexDirection(YogaFlexDirection.ROW)
            .children(style().maxHeight(123))
            .node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(123, node.getChildAt(0).getLayoutHeight(), 0);
  }

  @Test
  public void testMaxHeightPercentAffectsLayout() {
    final YogaNode node =
        style()
            .flexDirection(YogaFlexDirection.ROW)
            .height(200)
            .children(style().maxHeightPercent(80))
            .node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(160, node.getChildAt(0).getLayoutHeight(), 0);
  }

  @Test
  public void testAspectRatioDefault() {
    final YogaNode node = createNode();

    assertEquals(UNDEFINED, node.getAspectRatio(), 0);
  }

  @Test
  public void testAspectRatioAssignment() {
    final YogaNode node = createNode();
    node.setAspectRatio(2.75f);

    assertEquals(2.75f, node.getAspectRatio(), 0);
  }

  @Test
  public void aspectRatioAffectsLayoutWithGivenWidth() {
    final YogaNode node = style().children(style().width(300).aspectRatio(1.5f)).node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(200, node.getChildAt(0).getLayoutHeight(), 0);
  }

  @Test
  public void aspectRatioAffectsLayoutWithGivenHeight() {
    final YogaNode node = style().children(style().height(300).aspectRatio(1.5f)).node();
    node.calculateLayout(UNDEFINED, UNDEFINED);

    assertEquals(450, node.getChildAt(0).getLayoutWidth(), 0);
  }

  private YogaNode createNode() {
    return mNodeFactory.create();
  }

  private StyledNode style() {
    return new StyledNode(mNodeFactory);
  }

  private static class StyledNode {

    private YogaNode mNode;

    public StyledNode(TestParametrization.NodeFactory nodeFactory) {
      mNode = nodeFactory.create();
    }

    YogaNode node() {
      return mNode;
    }

    StyledNode children(StyledNode... children) {
      for (int i = mNode.getChildCount(); --i >= 0; ) {
        mNode.removeChildAt(i);
      }
      for (int i = 0; i < children.length; i++) {
        mNode.addChildAt(children[i].node(), i);
      }
      return this;
    }

    StyledNode direction(YogaDirection direction) {
      mNode.setDirection(direction);
      return this;
    }

    StyledNode width(float width) {
      mNode.setWidth(width);
      return this;
    }

    StyledNode widthPercent(float width) {
      mNode.setWidthPercent(width);
      return this;
    }

    StyledNode flexDirection(YogaFlexDirection direction) {
      mNode.setFlexDirection(direction);
      return this;
    }

    StyledNode justifyContent(YogaJustify justify) {
      mNode.setJustifyContent(justify);
      return this;
    }

    StyledNode height(float height) {
      mNode.setHeight(height);
      return this;
    }

    StyledNode heightPercent(float height) {
      mNode.setHeightPercent(height);
      return this;
    }

    StyledNode alignItems(YogaAlign align) {
      mNode.setAlignItems(align);
      return this;
    }

    StyledNode alignSelf(YogaAlign align) {
      mNode.setAlignSelf(align);
      return this;
    }

    StyledNode alignContent(YogaAlign align) {
      mNode.setAlignContent(align);
      return this;
    }

    StyledNode flexWrap(YogaWrap wrap) {
      mNode.setWrap(wrap);
      return this;
    }

    StyledNode positionType(YogaPositionType positionType) {
      mNode.setPositionType(positionType);
      return this;
    }

    StyledNode overflow(YogaOverflow overflow) {
      mNode.setOverflow(overflow);
      return this;
    }

    StyledNode flexShrink(float flexShrink) {
      mNode.setFlexShrink(flexShrink);
      return this;
    }

    StyledNode display(YogaDisplay display) {
      mNode.setDisplay(display);
      return this;
    }

    StyledNode flexGrow(float flexGrow) {
      mNode.setFlexGrow(flexGrow);
      return this;
    }

    StyledNode flex(float flex) {
      mNode.setFlex(flex);
      return this;
    }

    StyledNode flexBasis(float flexBasis) {
      mNode.setFlexBasis(flexBasis);
      return this;
    }

    StyledNode flexBasisPercent(float flexBasis) {
      mNode.setFlexBasisPercent(flexBasis);
      return this;
    }

    StyledNode margin(YogaEdge edge, float margin) {
      mNode.setMargin(edge, margin);
      return this;
    }

    StyledNode marginPercent(YogaEdge edge, float margin) {
      mNode.setMarginPercent(edge, margin);
      return this;
    }

    StyledNode marginAuto(YogaEdge edge) {
      mNode.setMarginAuto(edge);
      return this;
    }

    StyledNode padding(YogaEdge edge, float padding) {
      mNode.setPadding(edge, padding);
      return this;
    }

    StyledNode paddingPercent(YogaEdge edge, float padding) {
      mNode.setPaddingPercent(edge, padding);
      return this;
    }

    StyledNode border(YogaEdge edge, float border) {
      mNode.setBorder(edge, border);
      return this;
    }

    StyledNode position(YogaEdge edge, float position) {
      mNode.setPosition(edge, position);
      return this;
    }

    StyledNode positionPercent(YogaEdge edge, float position) {
      mNode.setPositionPercent(edge, position);
      return this;
    }

    StyledNode minWidth(float minWidth) {
      mNode.setMinWidth(minWidth);
      return this;
    }

    StyledNode minWidthPercent(float minWidth) {
      mNode.setMinWidthPercent(minWidth);
      return this;
    }

    StyledNode minHeight(float minHeight) {
      mNode.setMinHeight(minHeight);
      return this;
    }

    StyledNode minHeightPercent(float minHeight) {
      mNode.setMinHeightPercent(minHeight);
      return this;
    }

    StyledNode maxWidth(float maxWidth) {
      mNode.setMaxWidth(maxWidth);
      return this;
    }

    StyledNode maxWidthPercent(float maxWidth) {
      mNode.setMaxWidthPercent(maxWidth);
      return this;
    }

    StyledNode maxHeight(float maxHeight) {
      mNode.setMaxHeight(maxHeight);
      return this;
    }

    StyledNode maxHeightPercent(float maxHeight) {
      mNode.setMaxHeightPercent(maxHeight);
      return this;
    }

    StyledNode aspectRatio(float aspectRatio) {
      mNode.setAspectRatio(aspectRatio);
      return this;
    }
  }
}
