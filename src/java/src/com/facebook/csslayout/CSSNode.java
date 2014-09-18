package com.facebook.csslayout;

import java.util.ArrayList;

/**
 * A CSS Node. It has a style object you can manipulate at {@link #style}. After calling
 * {@link #calculateLayout()}, {@link #layout} will be filled with the results of the layout.
 */
public class CSSNode {

  // Only one copy kept around to keep from allocating a bunch of MeasureOutput objects
  // NOT THREAD SAFE! NOT RE-ENTRANT SAFE!
  private static final MeasureOutput MEASURE_OUTPUT = new MeasureOutput();

  public static interface MeasureFunction {

    /**
     * Should measure the given node and put the result in the given MeasureOutput.
     *
     * NB: measure is NOT guaranteed to be threadsafe/re-entrant safe!
     */
    public void measure(CSSNode node, float width, MeasureOutput measureOutput);
  }

  // VisibleForTesting
  /*package*/ final CSSStyle style = new CSSStyle();
  /*package*/ final CSSLayout layout = new CSSLayout();

  // 4 is kinda arbitrary, but the default of 10 seems really high for an average View.
  private final ArrayList<CSSNode> mChildren = new ArrayList<CSSNode>(4);

  private MeasureFunction mMeasureFunction = null;

  public int getChildCount() {
    return mChildren.size();
  }

  public CSSNode getChildAt(int i) {
    return mChildren.get(i);
  }

  public void addChildAt(CSSNode child, int i) {
    mChildren.add(i, child);
  }

  public void setMeasureFunction(MeasureFunction measureFunction) {
    mMeasureFunction = measureFunction;
  }

  public boolean isMeasureDefined() {
    return mMeasureFunction != null;
  }

  /*package*/ MeasureOutput measure(float width) {
    if (!isMeasureDefined()) {
      throw new RuntimeException("Measure function isn't defined!");
    }
    MEASURE_OUTPUT.height = CSSConstants.UNDEFINED;
    MEASURE_OUTPUT.width = CSSConstants.UNDEFINED;
    mMeasureFunction.measure(this, width, MEASURE_OUTPUT);
    return MEASURE_OUTPUT;
  }

  /**
   * Performs the actual layout and saves the results in {@link #layout}
   */
  public void calculateLayout() {
    resetLayoutResultRecursive();
    LayoutEngine.layoutNode(this, CSSConstants.UNDEFINED);
  }

  @Override
  public String toString() {
    String layoutString = layout.toString();

    if (getChildCount() == 0) {
      return layoutString;
    }

    layoutString += ", children: [\n";

    for (int i = 0; i < getChildCount(); i++) {
      String childString = getChildAt(i).toString();
      childString = childString.replaceAll("\n", "\n\t");
      layoutString += "\t" + childString + "\n";
    }

    layoutString += "]";

    return layoutString;
  }

  private void resetLayoutResultRecursive() {
    layout.resetResult();
    for (int i = 0; i < getChildCount(); i++) {
      getChildAt(i).resetLayoutResultRecursive();
    }
  }

  public void setFlexDirection(CSSFlexDirection flexDirection) {
    style.flexDirection = flexDirection;
  }

  public void setJustifyContent(CSSJustify justifyContent) {
    style.justifyContent = justifyContent;
  }

  public void setAlignItems(CSSAlign alignItems) {
    style.alignItems = alignItems;
  }

  public void setAlignSelf(CSSAlign alignSelf) {
    style.alignSelf = alignSelf;
  }

  public void setPositionType(CSSPositionType positionType) {
    style.positionType = positionType;
  }

  public void setFlex(float flex) {
    style.flex = flex;
  }

  public void setMarginTop(float marginTop) {
    style.marginTop = marginTop;
  }

  public void setMarginBottom(float marginBottom) {
    style.marginBottom = marginBottom;
  }

  public void setMarginLeft(float marginLeft) {
    style.marginLeft = marginLeft;
  }

  public void setMarginRight(float marginRight) {
    style.marginRight = marginRight;
  }

  public void setPaddingTop(float paddingTop) {
    style.paddingTop = paddingTop;
  }

  public void setPaddingBottom(float paddingBottom) {
    style.paddingBottom = paddingBottom;
  }

  public void setPaddingLeft(float paddingLeft) {
    style.paddingLeft = paddingLeft;
  }

  public void setPaddingRight(float paddingRight) {
    style.paddingRight = paddingRight;
  }

  public void setPositionTop(float positionTop) {
    style.positionTop = positionTop;
  }

  public void setPositionBottom(float positionBottom) {
    style.positionBottom = positionBottom;
  }

  public void setPositionLeft(float positionLeft) {
    style.positionLeft = positionLeft;
  }

  public void setPositionRight(float positionRight) {
    style.positionRight = positionRight;
  }

  public void setBorderTop(float borderTop) {
    style.borderTop = borderTop;
  }

  public void setBorderBottom(float borderBottom) {
    style.borderBottom = borderBottom;
  }

  public void setBorderLeft(float borderLeft) {
    style.borderLeft = borderLeft;
  }

  public void setBorderRight(float borderRight) {
    style.borderRight = borderRight;
  }

  public void setStyleWidth(float width) {
    style.width = width;
  }

  public void setStyleHeight(float height) {
    style.height = height;
  }

  public float getLayoutX() {
    return layout.x;
  }

  public float getLayoutY() {
    return layout.y;
  }

  public float getLayoutWidth() {
    return layout.x;
  }

  public float getLayoutHeight() {
    return layout.x;
  }
}
