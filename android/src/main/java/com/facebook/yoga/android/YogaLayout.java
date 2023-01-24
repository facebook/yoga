/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.yoga.android;

import android.content.Context;
import android.content.res.Configuration;
import android.content.res.TypedArray;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.os.Build;
import android.util.AttributeSet;
import android.util.SparseArray;
import android.util.TypedValue;
import android.view.View;
import android.view.ViewGroup;
import com.facebook.yoga.YogaAlign;
import com.facebook.yoga.YogaConstants;
import com.facebook.yoga.YogaDirection;
import com.facebook.yoga.YogaDisplay;
import com.facebook.yoga.YogaEdge;
import com.facebook.yoga.YogaFlexDirection;
import com.facebook.yoga.YogaJustify;
import com.facebook.yoga.YogaMeasureFunction;
import com.facebook.yoga.YogaMeasureMode;
import com.facebook.yoga.YogaMeasureOutput;
import com.facebook.yoga.YogaNode;
import com.facebook.yoga.YogaNodeFactory;
import com.facebook.yoga.YogaOverflow;
import com.facebook.yoga.YogaPositionType;
import com.facebook.yoga.YogaWrap;
import java.util.HashMap;
import java.util.Map;

/**
 * A {@code ViewGroup} based on the Yoga layout engine.
 *
 * <p>
 * This class is designed to be as "plug and play" as possible.  That is, you can use it in XML
 * like this (note: to use {@code YogaLayout} you need to use the {@link YogaViewLayoutFactory}):
 * <p>
 * <pre>{@code
 * <YogaLayout
 *     xmlns:android="http://schemas.android.com/apk/res/android"
 *     xmlns:yoga="http://schemas.android.com/apk/com.facebook.yoga.android"
 *     android:layout_width="match_owner"
 *     android:layout_height="match_owner"
 *     yoga:flex_direction="row"
 *     yoga:padding_all="10dp"
 *     >
 *     <TextView
 *         android:layout_width="match_owner"
 *         android:layout_height="match_owner"
 *         android:text="Hello, World!"
 *         yoga:flex="1"
 *         />
 * </YogaLayout>
 * }</pre>
 *
 * Under the hood, all views added to this {@code ViewGroup} are laid out using flexbox rules
 * and the Yoga engine.
 */
public class YogaLayout extends ViewGroup {
  private final Map<View, YogaNode> mYogaNodes;
  private final YogaNode mYogaNode;

  public YogaLayout(Context context) {
    this(context, null, 0);
  }

  public YogaLayout(Context context, AttributeSet attrs) {
    this(context, attrs, 0);
  }

  public YogaLayout(Context context, AttributeSet attrs, int defStyleAttr) {
    super(context, attrs, defStyleAttr);

    mYogaNode = YogaNodeFactory.create();
    mYogaNodes = new HashMap<>();

    mYogaNode.setData(this);
    mYogaNode.setMeasureFunction(new ViewMeasureFunction());

    LayoutParams layoutParams = null;
    if (attrs != null) {
      layoutParams = new LayoutParams(context, attrs);
    } else {
      layoutParams = (LayoutParams) generateDefaultLayoutParams();
    }
    applyLayoutParams(layoutParams, mYogaNode, this);
  }

  public YogaNode getYogaNode() {
    return mYogaNode;
  }

  public YogaNode getYogaNodeForView(View view) {
    return mYogaNodes.get(view);
  }

  /**
   * Adds a child view with the specified layout parameters.
   *
   * In the typical View is added, this constructs a {@code YogaNode} for this child and applies all
   * the {@code yoga:*} attributes.  The Yoga node is added to the Yoga tree and the child is added
   * to this ViewGroup.
   *
   * If the child is a {@link YogaLayout} itself, we do not construct a new Yoga node for that
   * child, but use its root node instead.
   *
   * If the child is a {@link VirtualYogaLayout}, we also use its Yoga node, but we also instruct it
   * to transfer all of its children to this {@link YogaLayout} while preserving the Yoga tree (so
   * that the layout of its children is correct).  The {@link VirtualYogaLayout} is then not added
   * to the View hierarchy.
   *
   * <p><strong>Note:</strong> do not invoke this method from
   * {@code #draw(android.graphics.Canvas)}, {@code onDraw(android.graphics.Canvas)},
   * {@code #dispatchDraw(android.graphics.Canvas)} or any related method.</p>
   *
   * @param child the child view to add
   * @param index the position at which to add the child or -1 to add last
   * @param params the layout parameters to set on the child
   */
  @Override
  public void addView(View child, int index, ViewGroup.LayoutParams params) {
    // Internal nodes (which this is now) cannot have measure functions
    mYogaNode.setMeasureFunction(null);

    if (child instanceof VirtualYogaLayout) {
      ((VirtualYogaLayout) child).transferChildren(this);
      final YogaNode childNode = ((VirtualYogaLayout) child).getYogaNode();

      mYogaNode.addChildAt(childNode, mYogaNode.getChildCount());

      return;
    }

    super.addView(child, index, params);

    // It is possible that addView is being called as part of a transferal of children, in which
    // case we already know about the YogaNode and only need the Android View tree to be aware
    // that we now own this child.  If so, we don't need to do anything further
    if (mYogaNodes.containsKey(child)) {
      return;
    }

    YogaNode childNode;

    if (child instanceof YogaLayout) {
      childNode = ((YogaLayout) child).getYogaNode();
    } else {
      if(mYogaNodes.containsKey(child)) {
        childNode = mYogaNodes.get(child);
      } else {
        childNode = YogaNodeFactory.create();
      }

      childNode.setData(child);
      childNode.setMeasureFunction(new ViewMeasureFunction());
    }

    final LayoutParams lp = (LayoutParams) child.getLayoutParams();
    applyLayoutParams(lp, childNode, child);

    mYogaNodes.put(child, childNode);
    mYogaNode.addChildAt(childNode, mYogaNode.getChildCount());
  }

  /**
   * Adds a view to this {@code ViewGroup} with an already given {@code YogaNode}.  Use
   * this function if you already have a Yoga node (and perhaps tree) associated with the view you
   * are adding, that you would like to preserve.
   *
   * @param child The view to add
   * @param node The Yoga node belonging to the view
   */
  public void addView(View child, YogaNode node) {
    mYogaNodes.put(child, node);
    addView(child);
  }

  @Override
  public void removeView(View view) {
    removeViewFromYogaTree(view, false);
    super.removeView(view);
  }

  @Override
  public void removeViewAt(int index) {
    removeViewFromYogaTree(getChildAt(index), false);
    super.removeViewAt(index);
  }

  @Override
  public void removeViewInLayout(View view) {
    removeViewFromYogaTree(view, true);
    super.removeViewInLayout(view);
  }

  @Override
  public void removeViews(int start, int count) {
    for (int i = start; i < start + count; i++) {
      removeViewFromYogaTree(getChildAt(i), false);
    }
    super.removeViews(start, count);
  }

  @Override
  public void removeViewsInLayout(int start, int count) {
    for (int i = start; i < start + count; i++) {
      removeViewFromYogaTree(getChildAt(i), true);
    }
    super.removeViewsInLayout(start, count);
  }

  @Override
  public void removeAllViews() {
    final int childCount = getChildCount();
    for (int i = 0; i < childCount; i++) {
      removeViewFromYogaTree(getChildAt(i), false);
    }
    super.removeAllViews();
  }

  @Override
  public void removeAllViewsInLayout() {
    final int childCount = getChildCount();
    for (int i = 0; i < childCount; i++) {
      removeViewFromYogaTree(getChildAt(i), true);
    }
    super.removeAllViewsInLayout();
  }

  /**
   * Marks a particular view as "dirty" and to be relaid out.  If the view is not a child of this
   * {@link YogaLayout}, the entire tree is traversed to find it.
   *
   * @param view the view to mark as dirty
   */
  public void invalidate(View view) {
    if (mYogaNodes.containsKey(view)) {
      mYogaNodes.get(view).dirty();
      return;
    }

    final int childCount = mYogaNode.getChildCount();
    for (int i = 0; i < childCount; i++) {
      final YogaNode yogaNode = mYogaNode.getChildAt(i);
      if (yogaNode.getData() instanceof YogaLayout) {
        ((YogaLayout) yogaNode.getData()).invalidate(view);
      }
    }
    invalidate();
  }

  private void removeViewFromYogaTree(View view, boolean inLayout) {
    final YogaNode node = mYogaNodes.get(view);
    if (node == null) {
      return;
    }

    final YogaNode owner = node.getOwner();

    for (int i = 0; i < owner.getChildCount(); i++) {
      if (owner.getChildAt(i).equals(node)) {
        owner.removeChildAt(i);
        break;
      }
    }

    node.setData(null);
    mYogaNodes.remove(view);

    if (inLayout) {
      mYogaNode.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
    }
  }

  private void applyLayoutRecursive(YogaNode node, float xOffset, float yOffset) {
    View view = (View) node.getData();

    if (view != null && view != this) {
      if (view.getVisibility() == GONE) {
        return;
      }
      int left = Math.round(xOffset + node.getLayoutX());
      int top = Math.round(yOffset + node.getLayoutY());
      view.measure(
          View.MeasureSpec.makeMeasureSpec(
              Math.round(node.getLayoutWidth()),
              View.MeasureSpec.EXACTLY),
          View.MeasureSpec.makeMeasureSpec(
              Math.round(node.getLayoutHeight()),
              View.MeasureSpec.EXACTLY));
      view.layout(left, top, left + view.getMeasuredWidth(), top + view.getMeasuredHeight());
    }

    final int childrenCount = node.getChildCount();
    for (int i = 0; i < childrenCount; i++) {
      if (this.equals(view)) {
        applyLayoutRecursive(node.getChildAt(i), xOffset, yOffset);
      } else if (view instanceof YogaLayout) {
        continue;
      } else {
        applyLayoutRecursive(
            node.getChildAt(i),
            xOffset + node.getLayoutX(),
            yOffset + node.getLayoutY());
      }
    }
  }

  @Override
  protected void onLayout(boolean changed, int l, int t, int r, int b) {
    // Either we are a root of a tree, or this function is called by our owner's onLayout, in which
    // case our r-l and b-t are the size of our node.
    if (!(getParent() instanceof YogaLayout)) {
        createLayout(
            MeasureSpec.makeMeasureSpec(r - l, MeasureSpec.EXACTLY),
            MeasureSpec.makeMeasureSpec(b - t, MeasureSpec.EXACTLY));
    }

    applyLayoutRecursive(mYogaNode, 0, 0);
  }

  /**
   * This function is mostly unneeded, because Yoga is doing the measuring.  Hence we only need to
   * return accurate results if we are the root.
   *
   * @param widthMeasureSpec the suggested specification for the width
   * @param heightMeasureSpec the suggested specification for the height
   */
  @Override
  protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
    if (!(getParent() instanceof YogaLayout)) {
      createLayout(widthMeasureSpec, heightMeasureSpec);
    }

    setMeasuredDimension(
        Math.round(mYogaNode.getLayoutWidth()),
        Math.round(mYogaNode.getLayoutHeight()));
  }

  private void createLayout(int widthMeasureSpec, int heightMeasureSpec) {
    final int widthSize = MeasureSpec.getSize(widthMeasureSpec);
    final int heightSize = MeasureSpec.getSize(heightMeasureSpec);
    final int widthMode = MeasureSpec.getMode(widthMeasureSpec);
    final int heightMode = MeasureSpec.getMode(heightMeasureSpec);

    if (heightMode == MeasureSpec.EXACTLY) {
      mYogaNode.setHeight(heightSize);
    }
    if (widthMode == MeasureSpec.EXACTLY) {
      mYogaNode.setWidth(widthSize);
    }
    if (heightMode == MeasureSpec.AT_MOST) {
      mYogaNode.setMaxHeight(heightSize);
    }
    if (widthMode == MeasureSpec.AT_MOST) {
      mYogaNode.setMaxWidth(widthSize);
    }
    mYogaNode.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
  }

  /**
   * Applies the layout parameters to the YogaNode.  That is, this function is a translator from
   * {@code yoga:X="Y"} to {@code yogaNode.setX(Y);}, with some reasonable defaults.
   *
   * <p>
   * If the SDK version is high enough, and the {@code yoga:direction} is not set on
   * the component, the direction (LTR or RTL) is set according to the locale.
   *
   * <p>
   * The attributes {@code padding_top}, {@code padding_right} etc. default to those of the view's
   * drawable background, if it has one.
   *
   * @param layoutParameters The source set of params
   * @param node The destination node
   */
  protected static void applyLayoutParams(LayoutParams layoutParameters, YogaNode node, View view) {
    // JELLY_BEAN_MR1 (17) is the first version supporting getLayoutDirection()
    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR1) {
      Configuration configuration = view.getResources().getConfiguration();
      if (configuration.getLayoutDirection() == LAYOUT_DIRECTION_RTL) {
        node.setDirection(YogaDirection.RTL);
      }
    }

    Drawable background = view.getBackground();
    if (background != null) {
      final Rect backgroundPadding = new Rect();
      if (background.getPadding(backgroundPadding)) {
        node.setPadding(YogaEdge.LEFT, backgroundPadding.left);
        node.setPadding(YogaEdge.TOP, backgroundPadding.top);
        node.setPadding(YogaEdge.RIGHT, backgroundPadding.right);
        node.setPadding(YogaEdge.BOTTOM, backgroundPadding.bottom);
      }
    }

    for (int i = 0; i < layoutParameters.numericAttributes.size(); i++) {
      final int attribute = layoutParameters.numericAttributes.keyAt(i);
      final float value = layoutParameters.numericAttributes.valueAt(i);

      if (attribute == R.styleable.yoga_yg_alignContent) {
        node.setAlignContent(YogaAlign.fromInt(Math.round(value)));
      } else if (attribute == R.styleable.yoga_yg_alignItems) {
        node.setAlignItems(YogaAlign.fromInt(Math.round(value)));
      } else if (attribute == R.styleable.yoga_yg_alignSelf) {
        node.setAlignSelf(YogaAlign.fromInt(Math.round(value)));
      } else if (attribute == R.styleable.yoga_yg_aspectRatio) {
        node.setAspectRatio(value);
      } else if (attribute == R.styleable.yoga_yg_borderLeft) {
        node.setBorder(YogaEdge.LEFT, value);
      } else if (attribute == R.styleable.yoga_yg_borderTop) {
        node.setBorder(YogaEdge.TOP, value);
      } else if (attribute == R.styleable.yoga_yg_borderRight) {
        node.setBorder(YogaEdge.RIGHT, value);
      } else if (attribute == R.styleable.yoga_yg_borderBottom) {
        node.setBorder(YogaEdge.BOTTOM, value);
      } else if (attribute == R.styleable.yoga_yg_borderStart) {
        node.setBorder(YogaEdge.START, value);
      } else if (attribute == R.styleable.yoga_yg_borderEnd) {
        node.setBorder(YogaEdge.END, value);
      } else if (attribute == R.styleable.yoga_yg_borderHorizontal) {
        node.setBorder(YogaEdge.HORIZONTAL, value);
      } else if (attribute == R.styleable.yoga_yg_borderVertical) {
        node.setBorder(YogaEdge.VERTICAL, value);
      } else if (attribute == R.styleable.yoga_yg_borderAll) {
        node.setBorder(YogaEdge.ALL, value);
      } else if (attribute == R.styleable.yoga_yg_direction) {
        node.setDirection(YogaDirection.fromInt(Math.round(value)));
      } else if (attribute == R.styleable.yoga_yg_display) {
        node.setDisplay(YogaDisplay.fromInt(Math.round(value)));
      } else if (attribute == R.styleable.yoga_yg_flex) {
        node.setFlex(value);
      } else if (attribute == R.styleable.yoga_yg_flexBasis) {
        node.setFlexBasis(value);
      } else if (attribute == R.styleable.yoga_yg_flexDirection) {
        node.setFlexDirection(YogaFlexDirection.fromInt(Math.round(value)));
      } else if (attribute == R.styleable.yoga_yg_flexGrow) {
        node.setFlexGrow(value);
      } else if (attribute == R.styleable.yoga_yg_flexShrink) {
        node.setFlexShrink(value);
      } else if (attribute == R.styleable.yoga_yg_height) {
        node.setHeight(value);
      } else if (attribute == R.styleable.yoga_yg_marginLeft) {
        node.setMargin(YogaEdge.LEFT, value);
      } else if (attribute == R.styleable.yoga_yg_justifyContent) {
        node.setJustifyContent(YogaJustify.fromInt(Math.round(value)));
      } else if (attribute == R.styleable.yoga_yg_marginTop) {
        node.setMargin(YogaEdge.TOP, value);
      } else if (attribute == R.styleable.yoga_yg_marginRight) {
        node.setMargin(YogaEdge.RIGHT, value);
      } else if (attribute == R.styleable.yoga_yg_marginBottom) {
        node.setMargin(YogaEdge.BOTTOM, value);
      } else if (attribute == R.styleable.yoga_yg_marginStart) {
        node.setMargin(YogaEdge.START, value);
      } else if (attribute == R.styleable.yoga_yg_marginEnd) {
        node.setMargin(YogaEdge.END, value);
      } else if (attribute == R.styleable.yoga_yg_marginHorizontal) {
        node.setMargin(YogaEdge.HORIZONTAL, value);
      } else if (attribute == R.styleable.yoga_yg_marginVertical) {
        node.setMargin(YogaEdge.VERTICAL, value);
      } else if (attribute == R.styleable.yoga_yg_marginAll) {
        node.setMargin(YogaEdge.ALL, value);
      } else if (attribute == R.styleable.yoga_yg_maxHeight) {
        node.setMaxHeight(value);
      } else if (attribute == R.styleable.yoga_yg_maxWidth) {
        node.setMaxWidth(value);
      } else if (attribute == R.styleable.yoga_yg_minHeight) {
        node.setMinHeight(value);
      } else if (attribute == R.styleable.yoga_yg_minWidth) {
        node.setMinWidth(value);
      } else if (attribute == R.styleable.yoga_yg_overflow) {
        node.setOverflow(YogaOverflow.fromInt(Math.round(value)));
      } else if (attribute == R.styleable.yoga_yg_paddingLeft) {
        node.setPadding(YogaEdge.LEFT, value);
      } else if (attribute == R.styleable.yoga_yg_paddingTop) {
        node.setPadding(YogaEdge.TOP, value);
      } else if (attribute == R.styleable.yoga_yg_paddingRight) {
        node.setPadding(YogaEdge.RIGHT, value);
      } else if (attribute == R.styleable.yoga_yg_paddingBottom) {
        node.setPadding(YogaEdge.BOTTOM, value);
      } else if (attribute == R.styleable.yoga_yg_paddingStart) {
        node.setPadding(YogaEdge.START, value);
      } else if (attribute == R.styleable.yoga_yg_paddingEnd) {
        node.setPadding(YogaEdge.END, value);
      } else if (attribute == R.styleable.yoga_yg_paddingHorizontal) {
        node.setPadding(YogaEdge.HORIZONTAL, value);
      } else if (attribute == R.styleable.yoga_yg_paddingVertical) {
        node.setPadding(YogaEdge.VERTICAL, value);
      } else if (attribute == R.styleable.yoga_yg_paddingAll) {
        node.setPadding(YogaEdge.ALL, value);
      } else if (attribute == R.styleable.yoga_yg_positionLeft) {
        node.setPosition(YogaEdge.LEFT, value);
      } else if (attribute == R.styleable.yoga_yg_positionTop) {
        node.setPosition(YogaEdge.TOP, value);
      } else if (attribute == R.styleable.yoga_yg_positionRight) {
        node.setPosition(YogaEdge.RIGHT, value);
      } else if (attribute == R.styleable.yoga_yg_positionBottom) {
        node.setPosition(YogaEdge.BOTTOM, value);
      } else if (attribute == R.styleable.yoga_yg_positionStart) {
        node.setPosition(YogaEdge.START, value);
      } else if (attribute == R.styleable.yoga_yg_positionEnd) {
        node.setPosition(YogaEdge.END, value);
      } else if (attribute == R.styleable.yoga_yg_positionHorizontal) {
        node.setPosition(YogaEdge.HORIZONTAL, value);
      } else if (attribute == R.styleable.yoga_yg_positionVertical) {
        node.setPosition(YogaEdge.VERTICAL, value);
      } else if (attribute == R.styleable.yoga_yg_positionAll) {
        node.setPosition(YogaEdge.ALL, value);
      } else if (attribute == R.styleable.yoga_yg_positionType) {
        node.setPositionType(YogaPositionType.fromInt(Math.round(value)));
      } else if (attribute == R.styleable.yoga_yg_width) {
        node.setWidth(value);
      } else if (attribute == R.styleable.yoga_yg_wrap) {
        node.setWrap(YogaWrap.fromInt(Math.round(value)));
      }
    }

    for (int i = 0; i < layoutParameters.stringAttributes.size(); i++) {
      final int attribute = layoutParameters.stringAttributes.keyAt(i);
      final String value = layoutParameters.stringAttributes.valueAt(i);

      if (value.equals("auto")) {
        if (attribute == R.styleable.yoga_yg_marginLeft) {
          node.setMarginAuto(YogaEdge.LEFT);
        } else if (attribute == R.styleable.yoga_yg_marginTop) {
          node.setMarginAuto(YogaEdge.TOP);
        } else if (attribute == R.styleable.yoga_yg_marginRight) {
          node.setMarginAuto(YogaEdge.RIGHT);
        } else if (attribute == R.styleable.yoga_yg_marginBottom) {
          node.setMarginAuto(YogaEdge.BOTTOM);
        } else if (attribute == R.styleable.yoga_yg_marginStart) {
          node.setMarginAuto(YogaEdge.START);
        } else if (attribute == R.styleable.yoga_yg_marginEnd) {
          node.setMarginAuto(YogaEdge.END);
        } else if (attribute == R.styleable.yoga_yg_marginHorizontal) {
          node.setMarginAuto(YogaEdge.HORIZONTAL);
        } else if (attribute == R.styleable.yoga_yg_marginVertical) {
          node.setMarginAuto(YogaEdge.VERTICAL);
        } else if (attribute == R.styleable.yoga_yg_marginAll) {
          node.setMarginAuto(YogaEdge.ALL);
        }
      }

      if (value.endsWith("%")) {
        final float numericValue = Float.parseFloat(value.substring(0, value.length()-1));

        if (attribute == R.styleable.yoga_yg_flexBasis) {
          node.setFlexBasisPercent(numericValue);
        } else if (attribute == R.styleable.yoga_yg_height) {
          node.setHeightPercent(numericValue);
        } else if (attribute == R.styleable.yoga_yg_marginLeft) {
          node.setMarginPercent(YogaEdge.LEFT, numericValue);
        } else if (attribute == R.styleable.yoga_yg_marginTop) {
          node.setMarginPercent(YogaEdge.TOP, numericValue);
        } else if (attribute == R.styleable.yoga_yg_marginRight) {
          node.setMarginPercent(YogaEdge.RIGHT, numericValue);
        } else if (attribute == R.styleable.yoga_yg_marginBottom) {
          node.setMarginPercent(YogaEdge.BOTTOM, numericValue);
        } else if (attribute == R.styleable.yoga_yg_marginStart) {
          node.setMarginPercent(YogaEdge.START, numericValue);
        } else if (attribute == R.styleable.yoga_yg_marginEnd) {
          node.setMarginPercent(YogaEdge.END, numericValue);
        } else if (attribute == R.styleable.yoga_yg_marginHorizontal) {
          node.setMarginPercent(YogaEdge.HORIZONTAL, numericValue);
        } else if (attribute == R.styleable.yoga_yg_marginVertical) {
          node.setMarginPercent(YogaEdge.VERTICAL, numericValue);
        } else if (attribute == R.styleable.yoga_yg_marginAll) {
          node.setMarginPercent(YogaEdge.ALL, numericValue);
        } else if (attribute == R.styleable.yoga_yg_maxHeight) {
          node.setMaxHeightPercent(numericValue);
        } else if (attribute == R.styleable.yoga_yg_maxWidth) {
          node.setMaxWidthPercent(numericValue);
        } else if (attribute == R.styleable.yoga_yg_minHeight) {
          node.setMinHeightPercent(numericValue);
        } else if (attribute == R.styleable.yoga_yg_minWidth) {
          node.setMinWidthPercent(numericValue);
        } else if (attribute == R.styleable.yoga_yg_paddingLeft) {
          node.setPaddingPercent(YogaEdge.LEFT, numericValue);
        } else if (attribute == R.styleable.yoga_yg_paddingTop) {
          node.setPaddingPercent(YogaEdge.TOP, numericValue);
        } else if (attribute == R.styleable.yoga_yg_paddingRight) {
          node.setPaddingPercent(YogaEdge.RIGHT, numericValue);
        } else if (attribute == R.styleable.yoga_yg_paddingBottom) {
          node.setPaddingPercent(YogaEdge.BOTTOM, numericValue);
        } else if (attribute == R.styleable.yoga_yg_paddingStart) {
          node.setPaddingPercent(YogaEdge.START, numericValue);
        } else if (attribute == R.styleable.yoga_yg_paddingEnd) {
          node.setPaddingPercent(YogaEdge.END, numericValue);
        } else if (attribute == R.styleable.yoga_yg_paddingHorizontal) {
          node.setPaddingPercent(YogaEdge.HORIZONTAL, numericValue);
        } else if (attribute == R.styleable.yoga_yg_paddingVertical) {
          node.setPaddingPercent(YogaEdge.VERTICAL, numericValue);
        } else if (attribute == R.styleable.yoga_yg_paddingAll) {
          node.setPaddingPercent(YogaEdge.ALL, numericValue);
        } else if (attribute == R.styleable.yoga_yg_positionLeft) {
          node.setPositionPercent(YogaEdge.LEFT, numericValue);
        } else if (attribute == R.styleable.yoga_yg_positionTop) {
          node.setPositionPercent(YogaEdge.TOP, numericValue);
        } else if (attribute == R.styleable.yoga_yg_positionRight) {
          node.setPositionPercent(YogaEdge.RIGHT, numericValue);
        } else if (attribute == R.styleable.yoga_yg_positionBottom) {
          node.setPositionPercent(YogaEdge.BOTTOM, numericValue);
        } else if (attribute == R.styleable.yoga_yg_positionStart) {
          node.setPositionPercent(YogaEdge.START, numericValue);
        } else if (attribute == R.styleable.yoga_yg_positionEnd) {
          node.setPositionPercent(YogaEdge.END, numericValue);
        } else if (attribute == R.styleable.yoga_yg_positionHorizontal) {
          node.setPositionPercent(YogaEdge.HORIZONTAL, numericValue);
        } else if (attribute == R.styleable.yoga_yg_positionVertical) {
          node.setPositionPercent(YogaEdge.VERTICAL, numericValue);
        } else if (attribute == R.styleable.yoga_yg_positionAll) {
          node.setPositionPercent(YogaEdge.ALL, numericValue);
        } else if (attribute == R.styleable.yoga_yg_width) {
          node.setWidthPercent(numericValue);
        }
      }
    }
  }

  @Override
  public ViewGroup.LayoutParams generateLayoutParams(AttributeSet attrs) {
    return new YogaLayout.LayoutParams(getContext(), attrs);
  }

  @Override
  protected ViewGroup.LayoutParams generateDefaultLayoutParams() {
    return new YogaLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                                       ViewGroup.LayoutParams.MATCH_PARENT);
  }

  @Override
  protected ViewGroup.LayoutParams generateLayoutParams(ViewGroup.LayoutParams p) {
    return new YogaLayout.LayoutParams(p);
  }

  @Override
  protected boolean checkLayoutParams(ViewGroup.LayoutParams p) {
    return p instanceof LayoutParams;
  }

  /**
   * {@code YogaLayout.LayoutParams} are used by views to tell {@link YogaLayout} how they want to
   * be laid out.  More precisely, the specify the yoga parameters of the view.
   *
   * <p>
   * This is actually mostly a wrapper around a {@code SparseArray} that holds a mapping between
   * styleable id's ({@code R.styleable.yoga_yg_*}) and the float of their values.  In cases where
   * the value is an enum or an integer, they should first be cast to int (with rounding) before
   * using.
   */
  public static class LayoutParams extends ViewGroup.LayoutParams {

    /**
     * A mapping from attribute keys ({@code R.styleable.yoga_yg_*}) to the float of their values.
     * For attributes like position_percent_left (float), this is the native type.  For attributes
     * like align_self (enums), the integer enum value is cast (rounding is used on the other side
     * to prevent precision errors).  Dimension attributes are stored as float pixels.
     */
    SparseArray<Float> numericAttributes;

    /**
     * A mapping from attribute keys ({@code R.styleable.yoga_yg_*}) with string values to those
     * strings.  This is used for values such as "auto".
     */
    SparseArray<String> stringAttributes;

    /**
     * Constructs a set of layout params from a source set.  In the case that the source set is
     * actually a {@link YogaLayout.LayoutParams}, we can copy all the yoga attributes.  Otherwise
     * we start with a blank slate.
     *
     * @param source The layout params to copy from
     */
    public LayoutParams(ViewGroup.LayoutParams source) {
      super(source);
      if (source instanceof LayoutParams) {
        numericAttributes = ((LayoutParams) source).numericAttributes.clone();
        stringAttributes = ((LayoutParams) source).stringAttributes.clone();
      } else {
        numericAttributes = new SparseArray<>();
        stringAttributes = new SparseArray<>();

        // Negative values include MATCH_PARENT and WRAP_CONTENT
        if (source.width >= 0) {
          numericAttributes.put(R.styleable.yoga_yg_width, (float) width);
        }
        if (source.height >= 0) {
          numericAttributes.put(R.styleable.yoga_yg_height, (float) height);
        }
      }
    }

    /**
     * Constructs a set of layout params, given width and height specs.  In this case, we can set
     * the {@code yoga:width} and {@code yoga:height} if we are given them explicitly.  If other
     * options (such as {@code match_owner} or {@code wrap_content} are given, then the owner
     * LayoutParams will store them, and we deal with them during layout. (see
     * {@link YogaLayout#createLayout})
     *
     * @param width the requested width, either a pixel size, {@code WRAP_CONTENT} or
     *        {@code MATCH_PARENT}.
     * @param height the requested height, either a pixel size, {@code WRAP_CONTENT} or
     *        {@code MATCH_PARENT}.
     */
    public LayoutParams(int width, int height) {
      super(width, height);
      numericAttributes = new SparseArray<>();
      stringAttributes = new SparseArray<>();
      // Negative values include MATCH_PARENT and WRAP_CONTENT
      if (width >= 0) {
        numericAttributes.put(R.styleable.yoga_yg_width, (float) width);
      }
      if (height >= 0) {
        numericAttributes.put(R.styleable.yoga_yg_height, (float) height);
      }
    }

    /**
     * Constructs a set of layout params, given attributes.  Grabs all the {@code yoga:*}
     * defined in {@code ALL_YOGA_ATTRIBUTES} and collects the ones that are set in {@code attrs}.
     *
     * @param context the application environment
     * @param attrs the set of attributes from which to extract the yoga specific attributes
     */
    public LayoutParams(Context context, AttributeSet attrs) {
      super(context, attrs);
      numericAttributes = new SparseArray<>();
      stringAttributes = new SparseArray<>();
      final TypedArray a = context.obtainStyledAttributes(attrs, R.styleable.yoga);

      // Negative values include MATCH_PARENT and WRAP_CONTENT
      if (width >= 0) {
        numericAttributes.put(R.styleable.yoga_yg_width, (float) width);
      }
      if (height >= 0) {
        numericAttributes.put(R.styleable.yoga_yg_height, (float) height);
      }

      final int attributeCount = a.getIndexCount();
      for (int i = 0; i < attributeCount; i++) {
        final int attribute = a.getIndex(i);
        final TypedValue val = new TypedValue();
        a.getValue(attribute, val);

        if (val.type == TypedValue.TYPE_DIMENSION) {
          numericAttributes.put(
              attribute,
              (float) a.getDimensionPixelSize(attribute, 0));
        } else if (val.type == TypedValue.TYPE_STRING) {
          stringAttributes.put(attribute, a.getString(attribute));
        } else {
          numericAttributes.put(attribute, a.getFloat(attribute, 0));
        }
      }
      a.recycle();
    }
  }

  /**
   * Wrapper around measure function for yoga leaves.
   */
  public static class ViewMeasureFunction implements YogaMeasureFunction {

    /**
     * A function to measure leaves of the Yoga tree.  Yoga needs some way to know how large
     * elements want to be.  This function passes that question directly through to the relevant
     * {@code View}'s measure function.
     *
     * @param node The yoga node to measure
     * @param width The suggested width from the owner
     * @param widthMode The type of suggestion for the width
     * @param height The suggested height from the owner
     * @param heightMode The type of suggestion for the height
     * @return A measurement output ({@code YogaMeasureOutput}) for the node
     */
    public long measure(
        YogaNode node,
        float width,
        YogaMeasureMode widthMode,
        float height,
        YogaMeasureMode heightMode) {
      final View view = (View) node.getData();
      if (view == null || view instanceof YogaLayout) {
        return YogaMeasureOutput.make(0, 0);
      }

      final int widthMeasureSpec = MeasureSpec.makeMeasureSpec(
          (int) width,
          viewMeasureSpecFromYogaMeasureMode(widthMode));
      final int heightMeasureSpec = MeasureSpec.makeMeasureSpec(
          (int) height,
          viewMeasureSpecFromYogaMeasureMode(heightMode));

      view.measure(widthMeasureSpec, heightMeasureSpec);

      return YogaMeasureOutput.make(view.getMeasuredWidth(), view.getMeasuredHeight());
    }

    private int viewMeasureSpecFromYogaMeasureMode(YogaMeasureMode mode) {
      if (mode == YogaMeasureMode.AT_MOST) {
        return MeasureSpec.AT_MOST;
      } else if (mode == YogaMeasureMode.EXACTLY) {
        return MeasureSpec.EXACTLY;
      } else {
        return MeasureSpec.UNSPECIFIED;
      }
    }
  }
}
