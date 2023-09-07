/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <cstdint>
#include <stdio.h>
#include <vector>

#include <yoga/config/Config.h>
#include <yoga/node/LayoutResults.h>
#include <yoga/style/CompactValue.h>
#include <yoga/style/Style.h>

// Tag struct used to form the opaque YGNodeRef for the public C API
struct YGNode {};

namespace facebook::yoga {

#pragma pack(push)
#pragma pack(1)
struct NodeFlags {
  bool hasNewLayout : 1;
  bool isReferenceBaseline : 1;
  bool isDirty : 1;
  uint32_t nodeType : 1;
  bool measureUsesContext : 1;
  bool baselineUsesContext : 1;
  bool printUsesContext : 1;
};
#pragma pack(pop)

class YOGA_EXPORT Node : public ::YGNode {
public:
  using MeasureWithContextFn =
      YGSize (*)(YGNode*, float, YGMeasureMode, float, YGMeasureMode, void*);
  using BaselineWithContextFn = float (*)(YGNode*, float, float, void*);
  using PrintWithContextFn = void (*)(YGNode*, void*);

private:
  void* context_ = nullptr;
  NodeFlags flags_ = {};
  union {
    YGMeasureFunc noContext;
    MeasureWithContextFn withContext;
  } measure_ = {nullptr};
  union {
    YGBaselineFunc noContext;
    BaselineWithContextFn withContext;
  } baseline_ = {nullptr};
  union {
    YGPrintFunc noContext;
    PrintWithContextFn withContext;
  } print_ = {nullptr};
  YGDirtiedFunc dirtied_ = nullptr;
  Style style_ = {};
  LayoutResults layout_ = {};
  uint32_t lineIndex_ = 0;
  Node* owner_ = nullptr;
  std::vector<Node*> children_ = {};
  Config* config_;
  std::array<YGValue, 2> resolvedDimensions_ = {
      {YGValueUndefined, YGValueUndefined}};

  FloatOptional relativePosition(
      const YGFlexDirection axis,
      const float axisSize) const;

  void setMeasureFunc(decltype(measure_));
  void setBaselineFunc(decltype(baseline_));

  void useWebDefaults() {
    style_.flexDirection() = YGFlexDirectionRow;
    style_.alignContent() = YGAlignStretch;
  }

  // DANGER DANGER DANGER!
  // If the node assigned to has children, we'd either have to deallocate
  // them (potentially incorrect) or ignore them (danger of leaks). Only ever
  // use this after checking that there are no children.
  // DO NOT CHANGE THE VISIBILITY OF THIS METHOD!
  Node& operator=(Node&&) = default;

public:
  Node() : Node{static_cast<Config*>(YGConfigGetDefault())} {
    flags_.hasNewLayout = true;
  }
  explicit Node(Config* config);
  ~Node() = default; // cleanup of owner/children relationships in YGNodeFree

  Node(Node&&);

  // Does not expose true value semantics, as children are not cloned eagerly.
  // Should we remove this?
  Node(const Node& node) = default;

  // assignment means potential leaks of existing children, or alternatively
  // freeing unowned memory, double free, or freeing stack memory.
  Node& operator=(const Node&) = delete;

  // Getters
  void* getContext() const { return context_; }

  void print(void*);

  bool getHasNewLayout() const { return flags_.hasNewLayout; }

  YGNodeType getNodeType() const {
    return static_cast<YGNodeType>(flags_.nodeType);
  }

  bool hasMeasureFunc() const noexcept { return measure_.noContext != nullptr; }

  YGSize measure(float, YGMeasureMode, float, YGMeasureMode, void*);

  bool hasBaselineFunc() const noexcept {
    return baseline_.noContext != nullptr;
  }

  float baseline(float width, float height, void* layoutContext) const;

  bool hasErrata(YGErrata errata) const { return config_->hasErrata(errata); }

  YGDirtiedFunc getDirtied() const { return dirtied_; }

  // For Performance reasons passing as reference.
  Style& getStyle() { return style_; }

  const Style& getStyle() const { return style_; }

  // For Performance reasons passing as reference.
  LayoutResults& getLayout() { return layout_; }

  const LayoutResults& getLayout() const { return layout_; }

  uint32_t getLineIndex() const { return lineIndex_; }

  bool isReferenceBaseline() { return flags_.isReferenceBaseline; }

  // returns the Node that owns this Node. An owner is used to identify
  // the YogaTree that a Node belongs to. This method will return the parent
  // of the Node when a Node only belongs to one YogaTree or nullptr when
  // the Node is shared between two or more YogaTrees.
  Node* getOwner() const { return owner_; }

  // Deprecated, use getOwner() instead.
  Node* getParent() const { return getOwner(); }

  const std::vector<Node*>& getChildren() const { return children_; }

  // Applies a callback to all children, after cloning them if they are not
  // owned.
  template <typename T>
  void iterChildrenAfterCloningIfNeeded(T callback, void* cloneContext) {
    int i = 0;
    for (Node*& child : children_) {
      if (child->getOwner() != this) {
        child = static_cast<Node*>(
            config_->cloneNode(child, this, i, cloneContext));
        child->setOwner(this);
      }
      i += 1;

      callback(child, cloneContext);
    }
  }

  Node* getChild(size_t index) const { return children_.at(index); }

  size_t getChildCount() const { return children_.size(); }

  Config* getConfig() const { return config_; }

  bool isDirty() const { return flags_.isDirty; }

  std::array<YGValue, 2> getResolvedDimensions() const {
    return resolvedDimensions_;
  }

  YGValue getResolvedDimension(YGDimension dimension) const {
    return resolvedDimensions_[static_cast<size_t>(dimension)];
  }

  static CompactValue computeEdgeValueForColumn(
      const Style::Edges& edges,
      YGEdge edge,
      CompactValue defaultValue);

  static CompactValue computeEdgeValueForRow(
      const Style::Edges& edges,
      YGEdge rowEdge,
      YGEdge edge,
      CompactValue defaultValue);

  static CompactValue computeRowGap(
      const Style::Gutters& gutters,
      CompactValue defaultValue);

  static CompactValue computeColumnGap(
      const Style::Gutters& gutters,
      CompactValue defaultValue);

  // Methods related to positions, margin, padding and border
  FloatOptional getLeadingPosition(
      const YGFlexDirection axis,
      const float axisSize) const;
  bool isLeadingPositionDefined(const YGFlexDirection axis) const;
  bool isTrailingPosDefined(const YGFlexDirection axis) const;
  FloatOptional getTrailingPosition(
      const YGFlexDirection axis,
      const float axisSize) const;
  FloatOptional getLeadingMargin(
      const YGFlexDirection axis,
      const float widthSize) const;
  FloatOptional getTrailingMargin(
      const YGFlexDirection axis,
      const float widthSize) const;
  float getLeadingBorder(const YGFlexDirection flexDirection) const;
  float getTrailingBorder(const YGFlexDirection flexDirection) const;
  FloatOptional getLeadingPadding(
      const YGFlexDirection axis,
      const float widthSize) const;
  FloatOptional getTrailingPadding(
      const YGFlexDirection axis,
      const float widthSize) const;
  FloatOptional getLeadingPaddingAndBorder(
      const YGFlexDirection axis,
      const float widthSize) const;
  FloatOptional getTrailingPaddingAndBorder(
      const YGFlexDirection axis,
      const float widthSize) const;
  FloatOptional getMarginForAxis(
      const YGFlexDirection axis,
      const float widthSize) const;
  FloatOptional getGapForAxis(const YGFlexDirection axis, const float widthSize)
      const;
  // Setters

  void setContext(void* context) { context_ = context; }

  void setPrintFunc(YGPrintFunc printFunc) {
    print_.noContext = printFunc;
    flags_.printUsesContext = false;
  }
  void setPrintFunc(PrintWithContextFn printFunc) {
    print_.withContext = printFunc;
    flags_.printUsesContext = true;
  }
  void setPrintFunc(std::nullptr_t) { setPrintFunc(YGPrintFunc{nullptr}); }

  void setHasNewLayout(bool hasNewLayout) {
    flags_.hasNewLayout = hasNewLayout;
  }

  void setNodeType(YGNodeType nodeType) {
    flags_.nodeType = static_cast<uint32_t>(nodeType) & 0x01;
  }

  void setMeasureFunc(YGMeasureFunc measureFunc);
  void setMeasureFunc(MeasureWithContextFn);
  void setMeasureFunc(std::nullptr_t) {
    return setMeasureFunc(YGMeasureFunc{nullptr});
  }

  void setBaselineFunc(YGBaselineFunc baseLineFunc) {
    flags_.baselineUsesContext = false;
    baseline_.noContext = baseLineFunc;
  }
  void setBaselineFunc(BaselineWithContextFn baseLineFunc) {
    flags_.baselineUsesContext = true;
    baseline_.withContext = baseLineFunc;
  }
  void setBaselineFunc(std::nullptr_t) {
    return setBaselineFunc(YGBaselineFunc{nullptr});
  }

  void setDirtiedFunc(YGDirtiedFunc dirtiedFunc) { dirtied_ = dirtiedFunc; }

  void setStyle(const Style& style) { style_ = style; }

  void setLayout(const LayoutResults& layout) { layout_ = layout; }

  void setLineIndex(uint32_t lineIndex) { lineIndex_ = lineIndex; }

  void setIsReferenceBaseline(bool isReferenceBaseline) {
    flags_.isReferenceBaseline = isReferenceBaseline;
  }

  void setOwner(Node* owner) { owner_ = owner; }

  void setChildren(const std::vector<Node*>& children) { children_ = children; }

  // TODO: rvalue override for setChildren

  void setConfig(Config* config);

  void setDirty(bool isDirty);
  void setLayoutLastOwnerDirection(YGDirection direction);
  void setLayoutComputedFlexBasis(const FloatOptional computedFlexBasis);
  void setLayoutComputedFlexBasisGeneration(
      uint32_t computedFlexBasisGeneration);
  void setLayoutMeasuredDimension(
      float measuredDimension,
      YGDimension dimension);
  void setLayoutHadOverflow(bool hadOverflow);
  void setLayoutDimension(float dimensionValue, YGDimension dimension);
  void setLayoutDirection(YGDirection direction);
  void setLayoutMargin(float margin, YGEdge edge);
  void setLayoutBorder(float border, YGEdge edge);
  void setLayoutPadding(float padding, YGEdge edge);
  void setLayoutPosition(float position, YGEdge edge);
  void setPosition(
      const YGDirection direction,
      const float mainSize,
      const float crossSize,
      const float ownerWidth);
  void markDirtyAndPropagateDownwards();

  // Other methods
  YGValue marginLeadingValue(const YGFlexDirection axis) const;
  YGValue marginTrailingValue(const YGFlexDirection axis) const;
  YGValue resolveFlexBasisPtr() const;
  void resolveDimension();
  YGDirection resolveDirection(const YGDirection ownerDirection);
  void clearChildren();
  /// Replaces the occurrences of oldChild with newChild
  void replaceChild(Node* oldChild, Node* newChild);
  void replaceChild(Node* child, size_t index);
  void insertChild(Node* child, size_t index);
  /// Removes the first occurrence of child
  bool removeChild(Node* child);
  void removeChild(size_t index);

  void cloneChildrenIfNeeded(void*);
  void markDirtyAndPropagate();
  float resolveFlexGrow() const;
  float resolveFlexShrink() const;
  bool isNodeFlexible();
  void reset();
};

} // namespace facebook::yoga
