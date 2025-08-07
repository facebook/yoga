/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.yoga

public abstract class YogaNode : YogaProps {
  /** The interface the [getData] object can optionally implement. */
  public fun interface Inputs {
    /** Requests the data object to disable mutations of its inputs. */
    public fun freeze(node: YogaNode, parent: YogaNode?)
  }

  public abstract fun reset()

  public abstract fun getChildCount(): Int

  public abstract fun getChildAt(i: Int): YogaNode

  public abstract fun addChildAt(child: YogaNode, i: Int)

  abstract override fun setIsReferenceBaseline(isReferenceBaseline: Boolean)

  public abstract fun isReferenceBaseline(): Boolean

  public abstract fun removeChildAt(i: Int): YogaNode

  /**
   * @returns the [YogaNode] that owns this [YogaNode]. The owner is used to identify the YogaTree
   *   that a [YogaNode] belongs to. This method will return the parent of the [YogaNode] when the
   *   [YogaNode] only belongs to one YogaTree or null when the [YogaNode] is shared between two or
   *   more YogaTrees.
   */
  public abstract fun getOwner(): YogaNode?

  @Deprecated(
      "Use getOwner() instead. This will be removed in the next version. ",
      replaceWith = ReplaceWith("getOwner()"))
  public abstract fun getParent(): YogaNode?

  public abstract fun indexOf(child: YogaNode): Int

  public abstract fun calculateLayout(width: Float, height: Float)

  public abstract fun hasNewLayout(): Boolean

  public abstract fun dirty()

  public abstract fun isDirty(): Boolean

  public abstract fun copyStyle(srcNode: YogaNode)

  public abstract fun markLayoutSeen()

  abstract override fun getStyleDirection(): YogaDirection

  abstract override fun setDirection(direction: YogaDirection)

  abstract override fun getFlexDirection(): YogaFlexDirection

  abstract override fun setFlexDirection(flexDirection: YogaFlexDirection)

  abstract override fun getJustifyContent(): YogaJustify

  abstract override fun setJustifyContent(justifyContent: YogaJustify)

  abstract override fun getAlignItems(): YogaAlign

  abstract override fun setAlignItems(alignItems: YogaAlign)

  abstract override fun getAlignSelf(): YogaAlign

  abstract override fun setAlignSelf(alignSelf: YogaAlign)

  abstract override fun getAlignContent(): YogaAlign

  abstract override fun setAlignContent(alignContent: YogaAlign)

  abstract override fun getPositionType(): YogaPositionType

  abstract override fun setPositionType(positionType: YogaPositionType)

  abstract override fun getBoxSizing(): YogaBoxSizing

  abstract override fun setBoxSizing(boxSizing: YogaBoxSizing)

  public abstract fun getWrap(): YogaWrap

  abstract override fun setWrap(flexWrap: YogaWrap)

  public abstract fun getOverflow(): YogaOverflow

  public abstract fun setOverflow(overflow: YogaOverflow)

  public abstract fun getDisplay(): YogaDisplay

  public abstract fun setDisplay(display: YogaDisplay)

  public abstract fun getFlex(): Float

  abstract override fun setFlex(flex: Float)

  abstract override fun getFlexGrow(): Float

  abstract override fun setFlexGrow(flexGrow: Float)

  abstract override fun getFlexShrink(): Float

  abstract override fun setFlexShrink(flexShrink: Float)

  abstract override fun getFlexBasis(): YogaValue

  abstract override fun setFlexBasis(flexBasis: Float)

  abstract override fun setFlexBasisPercent(percent: Float)

  abstract override fun setFlexBasisAuto()

  abstract override fun setFlexBasisMaxContent()

  abstract override fun setFlexBasisFitContent()

  abstract override fun setFlexBasisStretch()

  abstract override fun getMargin(edge: YogaEdge): YogaValue

  abstract override fun setMargin(edge: YogaEdge, margin: Float)

  abstract override fun setMarginPercent(edge: YogaEdge, percent: Float)

  abstract override fun setMarginAuto(edge: YogaEdge)

  abstract override fun getPadding(edge: YogaEdge): YogaValue

  abstract override fun setPadding(edge: YogaEdge, padding: Float)

  abstract override fun setPaddingPercent(edge: YogaEdge, percent: Float)

  abstract override fun getBorder(edge: YogaEdge): Float

  abstract override fun setBorder(edge: YogaEdge, border: Float)

  abstract override fun getPosition(edge: YogaEdge): YogaValue

  abstract override fun setPosition(edge: YogaEdge, position: Float)

  abstract override fun setPositionPercent(edge: YogaEdge, percent: Float)

  public abstract fun setPositionAuto(edge: YogaEdge)

  abstract override fun getWidth(): YogaValue

  abstract override fun setWidth(width: Float)

  abstract override fun setWidthPercent(percent: Float)

  abstract override fun setWidthAuto()

  abstract override fun setWidthMaxContent()

  abstract override fun setWidthFitContent()

  abstract override fun setWidthStretch()

  abstract override fun getHeight(): YogaValue

  abstract override fun setHeight(height: Float)

  abstract override fun setHeightPercent(percent: Float)

  abstract override fun setHeightAuto()

  abstract override fun setHeightMaxContent()

  abstract override fun setHeightFitContent()

  abstract override fun setHeightStretch()

  abstract override fun getMinWidth(): YogaValue

  abstract override fun setMinWidth(minWidth: Float)

  abstract override fun setMinWidthPercent(percent: Float)

  abstract override fun setMinWidthMaxContent()

  abstract override fun setMinWidthFitContent()

  abstract override fun setMinWidthStretch()

  abstract override fun getMinHeight(): YogaValue

  abstract override fun setMinHeight(minHeight: Float)

  abstract override fun setMinHeightPercent(percent: Float)

  abstract override fun setMinHeightMaxContent()

  abstract override fun setMinHeightFitContent()

  abstract override fun setMinHeightStretch()

  abstract override fun getMaxWidth(): YogaValue

  abstract override fun setMaxWidth(maxWidth: Float)

  abstract override fun setMaxWidthPercent(percent: Float)

  abstract override fun setMaxWidthMaxContent()

  abstract override fun setMaxWidthFitContent()

  abstract override fun setMaxWidthStretch()

  abstract override fun getMaxHeight(): YogaValue

  abstract override fun setMaxHeight(maxheight: Float)

  abstract override fun setMaxHeightPercent(percent: Float)

  abstract override fun setMaxHeightMaxContent()

  abstract override fun setMaxHeightFitContent()

  abstract override fun setMaxHeightStretch()

  abstract override fun getAspectRatio(): Float

  abstract override fun setAspectRatio(aspectRatio: Float)

  public abstract fun getGap(gutter: YogaGutter): YogaValue

  public abstract fun setGap(gutter: YogaGutter, gapLength: Float)

  public abstract fun setGapPercent(gutter: YogaGutter, gapLength: Float)

  public abstract fun getLayoutX(): Float

  public abstract fun getLayoutY(): Float

  public abstract fun getLayoutWidth(): Float

  public abstract fun getLayoutHeight(): Float

  public abstract fun getLayoutMargin(edge: YogaEdge): Float

  public abstract fun getLayoutPadding(edge: YogaEdge): Float

  public abstract fun getLayoutBorder(edge: YogaEdge): Float

  public abstract fun getLayoutDirection(): YogaDirection

  abstract override fun setMeasureFunction(measureFunction: YogaMeasureFunction)

  abstract override fun setBaselineFunction(baselineFunction: YogaBaselineFunction)

  public abstract fun isMeasureDefined(): Boolean

  public abstract fun isBaselineDefined(): Boolean

  public abstract fun setData(data: Any)

  public abstract fun getData(): Any?

  public abstract fun cloneWithoutChildren(): YogaNode

  public abstract fun cloneWithChildren(): YogaNode

  public abstract fun setAlwaysFormsContainingBlock(alwaysFormsContainingBlock: Boolean)
}
