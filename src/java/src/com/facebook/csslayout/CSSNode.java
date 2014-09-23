package com.facebook.csslayout;

import java.util.ArrayList;

/**
 * A CSS Node. It has a style object you can manipulate at {@link #style}. After calling
 * {@link #calculateLayout(float)}, {@link #layout} will be filled with the results of the layout.
 */
public class CSSNode {

  // Only one copy kept around to keep from allocating a bunch of MeasureOutput objects
  // NOT THREAD SAFE! NOT RE-ENTRANT SAFE!
  private static final MeasureOutput MEASURE_OUTPUT = new MeasureOutput();

  public static interface MeasureFunction {

    /**
     * Should measure the given node and put the result in the given MeasureOutput.
     */
    public void measure(CSSNode node, float width, MeasureOutput measureOutput);
  }

  public final CSSStyle style = new CSSStyle();
  public final CSSLayout layout = new CSSLayout();

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
  public void calculateLayout(float maxParentWidth) {
    resetLayoutResultRecursive();
    LayoutEngine.layoutNode(this, maxParentWidth);
  }

  @Override
  public String toString() {
    String layoutString = "layout: {" +
        "x: " + layout.x + ", " +
        "y: " + layout.y + ", " +
        "width: " + layout.width + ", " +
        "height: " + layout.height +
        "}";

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
}
