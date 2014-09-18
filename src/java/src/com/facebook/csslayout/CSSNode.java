package com.facebook.csslayout;

import java.util.ArrayList;

/**
 * A CSS Node. It has a style object you can manipulate at {@link #style}. After calling
 * {@link #calculateLayout()}, {@link #layout} will be filled with the results of the layout.
 */
public class CSSNode {

  private static enum LayoutState {
    /**
     * Some property of this node or its children has changes and the current values in
     * {@link #layout} are not valid.
     */
    DIRTY,

    /**
     * This node has a new layout relative to the last time {@link #markLayoutApplied()} was called.
     */
    HAS_NEW_LAYOUT,

    /**
     * {@link #layout} is valid for the node's properties and this layout has been marked as
     * having been applied.
     */
    UP_TO_DATE,
  }

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
  /*package*/ final CachedCSSLayout lastLayout = new CachedCSSLayout();

  // 4 is kinda arbitrary, but the default of 10 seems really high for an average View.
  private final ArrayList<CSSNode> mChildren = new ArrayList<CSSNode>(4);

  private CSSNode mParent;
  private MeasureFunction mMeasureFunction = null;
  private LayoutState mLayoutState = LayoutState.DIRTY;

  public int getChildCount() {
    return mChildren.size();
  }

  public CSSNode getChildAt(int i) {
    return mChildren.get(i);
  }

  public void addChildAt(CSSNode child, int i) {
    if (child.mParent != null) {
      throw new IllegalStateException("Child already has a parent, it must be removed first.");
    }

    mChildren.add(i, child);
    child.mParent = this;
    dirty();
  }

  public void removeChildAt(int i) {
    mChildren.remove(i).mParent = null;
    dirty();
  }

  public CSSNode getParent() {
    return mParent;
  }

  public void setMeasureFunction(MeasureFunction measureFunction) {
    dirtyIfDifferent(mMeasureFunction, measureFunction);
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

  /**
   * See {@link LayoutState#DIRTY}.
   */
  /*package*/ boolean isDirty() {
    return mLayoutState == LayoutState.DIRTY;
  }

  /**
   * See {@link LayoutState#HAS_NEW_LAYOUT}.
   */
  public boolean hasNewLayout() {
    return mLayoutState == LayoutState.HAS_NEW_LAYOUT;
  }

  protected void dirty() {
    if (mLayoutState == LayoutState.DIRTY) {
      return;
    } else if (mLayoutState == LayoutState.HAS_NEW_LAYOUT) {
      throw new IllegalStateException(
          "Previous layout was ignored! markLayoutApplied() never called");
    }

    mLayoutState = LayoutState.DIRTY;

    if (mParent != null) {
      mParent.dirty();
    }
  }

  /*package*/ void markHasNewLayout() {
    mLayoutState = LayoutState.HAS_NEW_LAYOUT;
  }

  /**
   * Tells the node that the current values in {@link #layout} have been applied. Subsequent calls
   * to {@link #hasNewLayout()} will return false until this node is laid out with new parameters.
   * You must call this each time the layout is generated if the node has a new layout.
   */
  public void markLayoutApplied() {
    if (!hasNewLayout()) {
      throw new IllegalStateException("Expected node to have a new layout to apply!");
    }

    mLayoutState = LayoutState.UP_TO_DATE;
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

  protected void dirtyIfDifferent(float f1, float f2) {
    if (!FloatUtil.floatsEqual(f1, f2)) {
      dirty();
    }
  }

  private static <T> boolean objectsEqual(T o1, T o2) {
    if (o1 == null) {
      return o2 == null;
    }
    return o1.equals(o2);
  }

  protected <T> void dirtyIfDifferent(T o1, T o2) {
    if (!objectsEqual(o1, o2)) {
      dirty();
    }
  }

  public void setFlexDirection(CSSFlexDirection flexDirection) {
    dirtyIfDifferent(style.flexDirection, flexDirection);
    style.flexDirection = flexDirection;
  }

  public void setJustifyContent(CSSJustify justifyContent) {
    dirtyIfDifferent(style.justifyContent, justifyContent);
    style.justifyContent = justifyContent;
  }

  public void setAlignItems(CSSAlign alignItems) {
    dirtyIfDifferent(style.alignItems, alignItems);
    style.alignItems = alignItems;
  }

  public void setAlignSelf(CSSAlign alignSelf) {
    dirtyIfDifferent(style.alignSelf, alignSelf);
    style.alignSelf = alignSelf;
  }

  public void setPositionType(CSSPositionType positionType) {
    dirtyIfDifferent(style.positionType, positionType);
    style.positionType = positionType;
  }

  public void setFlex(float flex) {
    dirtyIfDifferent(style.flex, flex);
    style.flex = flex;
  }

  public void setMarginTop(float marginTop) {
    dirtyIfDifferent(style.marginTop, marginTop);
    style.marginTop = marginTop;
  }

  public void setMarginBottom(float marginBottom) {
    dirtyIfDifferent(style.marginBottom, marginBottom);
    style.marginBottom = marginBottom;
  }

  public void setMarginLeft(float marginLeft) {
    dirtyIfDifferent(style.marginLeft, marginLeft);
    style.marginLeft = marginLeft;
  }

  public void setMarginRight(float marginRight) {
    dirtyIfDifferent(style.marginRight, marginRight);
    style.marginRight = marginRight;
  }

  public void setPaddingTop(float paddingTop) {
    dirtyIfDifferent(style.paddingTop, paddingTop);
    style.paddingTop = paddingTop;
  }

  public void setPaddingBottom(float paddingBottom) {
    dirtyIfDifferent(style.paddingBottom, paddingBottom);
    style.paddingBottom = paddingBottom;
  }

  public void setPaddingLeft(float paddingLeft) {
    dirtyIfDifferent(style.paddingLeft, paddingLeft);
    style.paddingLeft = paddingLeft;
  }

  public void setPaddingRight(float paddingRight) {
    dirtyIfDifferent(style.paddingRight, paddingRight);
    style.paddingRight = paddingRight;
  }

  public void setPositionTop(float positionTop) {
    dirtyIfDifferent(style.positionTop, positionTop);
    style.positionTop = positionTop;
  }

  public void setPositionBottom(float positionBottom) {
    dirtyIfDifferent(style.positionBottom, positionBottom);
    style.positionBottom = positionBottom;
  }

  public void setPositionLeft(float positionLeft) {
    dirtyIfDifferent(style.positionLeft, positionLeft);
    style.positionLeft = positionLeft;
  }

  public void setPositionRight(float positionRight) {
    dirtyIfDifferent(style.positionRight, positionRight);
    style.positionRight = positionRight;
  }

  public void setBorderTop(float borderTop) {
    dirtyIfDifferent(style.borderTop, borderTop);
    style.borderTop = borderTop;
  }

  public void setBorderBottom(float borderBottom) {
    dirtyIfDifferent(style.borderBottom, borderBottom);
    style.borderBottom = borderBottom;
  }

  public void setBorderLeft(float borderLeft) {
    dirtyIfDifferent(style.borderLeft, borderLeft);
    style.borderLeft = borderLeft;
  }

  public void setBorderRight(float borderRight) {
    dirtyIfDifferent(style.borderRight, borderRight);
    style.borderRight = borderRight;
  }

  public void setStyleWidth(float width) {
    dirtyIfDifferent(style.width, width);
    style.width = width;
  }

  public void setStyleHeight(float height) {
    dirtyIfDifferent(style.height, height);
    style.height = height;
  }

  public float getLayoutX() {
    return layout.x;
  }

  public float getLayoutY() {
    return layout.y;
  }

  public float getLayoutWidth() {
    return layout.width;
  }

  public float getLayoutHeight() {
    return layout.height;
  }
}
