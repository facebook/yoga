/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <cstdint>
#include <cstdio>
#include <vector>

#include <yoga/Yoga.h>

#include <yoga/config/Config.h>
#include <yoga/enums/Dimension.h>
#include <yoga/enums/Direction.h>
#include <yoga/enums/Edge.h>
#include <yoga/enums/Errata.h>
#include <yoga/enums/MeasureMode.h>
#include <yoga/enums/NodeType.h>
#include <yoga/enums/PhysicalEdge.h>
#include <yoga/node/LayoutResults.h>
#include <yoga/style/Style.h>

// Tag struct used to form the opaque YGNodeRef for the public C API
struct YGNode {};

namespace facebook::yoga {

class YG_EXPORT Node : public ::YGNode {
 public:
  class LayoutableChildren {
   public:
    using Backtrack = std::vector<std::pair<const Node*, size_t>>;
    struct Iterator {
      using iterator_category = std::input_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = Node*;
      using pointer = Node*;
      using reference = Node*;

      Iterator(const Node* node, size_t childIndex)
          : node_(node), childIndex_(childIndex) {}
      Iterator(const Node* node, size_t childIndex, Backtrack&& backtrack)
          : node_(node),
            childIndex_(childIndex),
            backtrack_(std::move(backtrack)) {}

      Node* operator*() const {
        return node_->getChild(childIndex_);
      }

      Iterator& operator++() {
        next();
        currentNodeIndex_++;
        return *this;
      }

      Iterator operator++(int) {
        Iterator tmp = *this;
        ++(*this);
        return tmp;
      }

      size_t index() const {
        return currentNodeIndex_;
      }

      friend bool operator==(const Iterator& a, const Iterator& b) {
        return a.node_ == b.node_ && a.childIndex_ == b.childIndex_;
      };

      friend bool operator!=(const Iterator& a, const Iterator& b) {
        return a.node_ != b.node_ || a.childIndex_ != b.childIndex_;
      };

     private:
      void next() {
        if (childIndex_ + 1 >= node_->getChildCount()) {
          // if the current node has no more children, try to backtrack and
          // visit its successor
          if (backtrack_.empty()) {
            // if there are no nodes to backtrack to, the last node has been
            // visited
            node_ = nullptr;
            childIndex_ = SIZE_MAX;
          } else {
            // pop and restore the latest backtrack entry
            const auto back = backtrack_.back();
            backtrack_.pop_back();
            node_ = back.first;
            childIndex_ = back.second;

            // go to the next node
            next();
          }
        } else {
          // current node has more children to visit, go to next
          ++childIndex_;
          // skip all display: contents nodes, possibly going deeper into the
          // tree
          skipContentsNodes();
        }
      }

      void skipContentsNodes() {
        // get the node that would be returned from the iterator
        auto currentNode = node_->getChild(childIndex_);
        while (currentNode->style().display() == Display::Contents &&
               currentNode->getChildCount() > 0) {
          // if it has display: contents set, it shouldn't be returned but its
          // children should in its place push the current node and child index
          // so that the current state can be restored when backtracking
          backtrack_.push_back({node_, childIndex_});
          // traverse the child
          node_ = currentNode;
          childIndex_ = 0;

          // repeat until a node without display: contents is found in the
          // subtree or a leaf is reached
          currentNode = currentNode->getChild(childIndex_);
        }

        // if no node without display: contents was found, try to backtrack
        if (currentNode->style().display() == Display::Contents) {
          next();
        }
      }

      const Node* node_;
      size_t childIndex_;
      size_t currentNodeIndex_{0};
      Backtrack backtrack_;

      friend LayoutableChildren;
    };

    LayoutableChildren(const Node* node) : node_(node) {
      static_assert(std::input_iterator<LayoutableChildren::Iterator>);
    }

    Iterator begin() const {
      if (node_->getChildCount() > 0) {
        auto result = Iterator(node_, 0);
        result.skipContentsNodes();
        return result;
      } else {
        return Iterator(nullptr, SIZE_MAX);
      }
    }

    Iterator end() const {
      return Iterator(nullptr, SIZE_MAX);
    }

   private:
    const Node* node_;
  };

  Node();
  explicit Node(const Config* config);

  Node(Node&& node) noexcept;

  // Does not expose true value semantics, as children are not cloned eagerly.
  // Should we remove this?
  Node(const Node& node) = default;

  // assignment means potential leaks of existing children, or alternatively
  // freeing unowned memory, double free, or freeing stack memory.
  Node& operator=(const Node&) = delete;

  // Getters
  void* getContext() const {
    return context_;
  }

  bool alwaysFormsContainingBlock() const {
    return alwaysFormsContainingBlock_;
  }

  bool getHasNewLayout() const {
    return hasNewLayout_;
  }

  NodeType getNodeType() const {
    return nodeType_;
  }

  bool hasMeasureFunc() const noexcept {
    return measureFunc_ != nullptr;
  }

  YGSize measure(
      float availableWidth,
      MeasureMode widthMode,
      float availableHeight,
      MeasureMode heightMode);

  bool hasBaselineFunc() const noexcept {
    return baselineFunc_ != nullptr;
  }

  float baseline(float width, float height) const;

  float dimensionWithMargin(FlexDirection axis, float widthSize);

  bool isLayoutDimensionDefined(FlexDirection axis);

  /**
   * Whether the node has a "definite length" along the given axis.
   * https://www.w3.org/TR/css-sizing-3/#definite
   */
  inline bool hasDefiniteLength(Dimension dimension, float ownerSize) {
    auto usedValue = getProcessedDimension(dimension).resolve(ownerSize);
    return usedValue.isDefined() && usedValue.unwrap() >= 0.0f;
  }

  bool hasErrata(Errata errata) const {
    return config_->hasErrata(errata);
  }

  YGDirtiedFunc getDirtiedFunc() const {
    return dirtiedFunc_;
  }

  // For Performance reasons passing as reference.
  Style& style() {
    return style_;
  }

  const Style& style() const {
    return style_;
  }

  // For Performance reasons passing as reference.
  LayoutResults& getLayout() {
    return layout_;
  }

  const LayoutResults& getLayout() const {
    return layout_;
  }

  size_t getLineIndex() const {
    return lineIndex_;
  }

  bool isReferenceBaseline() const {
    return isReferenceBaseline_;
  }

  // returns the Node that owns this Node. An owner is used to identify
  // the YogaTree that a Node belongs to. This method will return the parent
  // of the Node when a Node only belongs to one YogaTree or nullptr when
  // the Node is shared between two or more YogaTrees.
  Node* getOwner() const {
    return owner_;
  }

  const std::vector<Node*>& getChildren() const {
    return children_;
  }

  Node* getChild(size_t index) const {
    return children_.at(index);
  }

  size_t getChildCount() const {
    return children_.size();
  }

  const LayoutableChildren getLayoutChildren() const {
    static_assert(std::input_iterator<LayoutableChildren::Iterator>);
    return LayoutableChildren(this);
  }

  size_t getLayoutChildCount() const {
    if (contentsChildren_ == 0) {
      return children_.size();
    } else {
      size_t count = 0;
      for (auto iter = getLayoutChildren().begin();
           iter != getLayoutChildren().end();
           iter++) {
        count++;
      }
      return count;
    }
  }

  const Config* getConfig() const {
    return config_;
  }

  bool isDirty() const {
    return isDirty_;
  }

  Style::Length getProcessedDimension(Dimension dimension) const {
    return processedDimensions_[static_cast<size_t>(dimension)];
  }

  FloatOptional getResolvedDimension(
      Direction direction,
      Dimension dimension,
      float referenceLength,
      float ownerWidth) const {
    FloatOptional value =
        getProcessedDimension(dimension).resolve(referenceLength);
    if (style_.boxSizing() == BoxSizing::BorderBox) {
      return value;
    }

    FloatOptional dimensionPaddingAndBorder =
        FloatOptional{style_.computePaddingAndBorderForDimension(
            direction, dimension, ownerWidth)};

    return value +
        (dimensionPaddingAndBorder.isDefined() ? dimensionPaddingAndBorder
                                               : FloatOptional{0.0});
  }

  // Setters

  void setContext(void* context) {
    context_ = context;
  }

  void setAlwaysFormsContainingBlock(bool alwaysFormsContainingBlock) {
    alwaysFormsContainingBlock_ = alwaysFormsContainingBlock;
  }

  void setHasNewLayout(bool hasNewLayout) {
    hasNewLayout_ = hasNewLayout;
  }

  void setNodeType(NodeType nodeType) {
    nodeType_ = nodeType;
  }

  void setMeasureFunc(YGMeasureFunc measureFunc);

  void setBaselineFunc(YGBaselineFunc baseLineFunc) {
    baselineFunc_ = baseLineFunc;
  }

  void setDirtiedFunc(YGDirtiedFunc dirtiedFunc) {
    dirtiedFunc_ = dirtiedFunc;
  }

  void setStyle(const Style& style) {
    style_ = style;
  }

  void setLayout(const LayoutResults& layout) {
    layout_ = layout;
  }

  void setLineIndex(size_t lineIndex) {
    lineIndex_ = lineIndex;
  }

  void setIsReferenceBaseline(bool isReferenceBaseline) {
    isReferenceBaseline_ = isReferenceBaseline;
  }

  void setOwner(Node* owner) {
    owner_ = owner;
  }

  void setChildren(const std::vector<Node*>& children) {
    children_ = children;
  }

  // TODO: rvalue override for setChildren

  void setConfig(Config* config);

  void setDirty(bool isDirty);
  void setLayoutLastOwnerDirection(Direction direction);
  void setLayoutComputedFlexBasis(FloatOptional computedFlexBasis);
  void setLayoutComputedFlexBasisGeneration(
      uint32_t computedFlexBasisGeneration);
  void setLayoutMeasuredDimension(float measuredDimension, Dimension dimension);
  void setLayoutHadOverflow(bool hadOverflow);
  void setLayoutDimension(float LengthValue, Dimension dimension);
  void setLayoutDirection(Direction direction);
  void setLayoutMargin(float margin, PhysicalEdge edge);
  void setLayoutBorder(float border, PhysicalEdge edge);
  void setLayoutPadding(float padding, PhysicalEdge edge);
  void setLayoutPosition(float position, PhysicalEdge edge);
  void setPosition(Direction direction, float ownerWidth, float ownerHeight);

  // Other methods
  Style::Length processFlexBasis() const;
  FloatOptional resolveFlexBasis(
      Direction direction,
      FlexDirection flexDirection,
      float referenceLength,
      float ownerWidth) const;
  void processDimensions();
  Direction resolveDirection(Direction ownerDirection);
  void clearChildren();
  /// Replaces the occurrences of oldChild with newChild
  void replaceChild(Node* oldChild, Node* newChild);
  void replaceChild(Node* child, size_t index);
  void insertChild(Node* child, size_t index);
  /// Removes the first occurrence of child
  bool removeChild(Node* child);
  void removeChild(size_t index);

  void cloneChildrenIfNeeded();
  void markDirtyAndPropagate();
  float resolveFlexGrow() const;
  float resolveFlexShrink() const;
  bool isNodeFlexible();
  void reset();

 private:
  // Used to allow resetting the node
  Node& operator=(Node&&) noexcept = default;

  float relativePosition(
      FlexDirection axis,
      Direction direction,
      float axisSize) const;

  void useWebDefaults() {
    style_.setFlexDirection(FlexDirection::Row);
    style_.setAlignContent(Align::Stretch);
  }

  bool hasNewLayout_ : 1 = true;
  bool isReferenceBaseline_ : 1 = false;
  bool isDirty_ : 1 = true;
  bool alwaysFormsContainingBlock_ : 1 = false;
  NodeType nodeType_ : bitCount<NodeType>() = NodeType::Default;
  void* context_ = nullptr;
  YGMeasureFunc measureFunc_ = nullptr;
  YGBaselineFunc baselineFunc_ = nullptr;
  YGDirtiedFunc dirtiedFunc_ = nullptr;
  Style style_;
  LayoutResults layout_;
  size_t lineIndex_ = 0;
  size_t contentsChildren_ = 0;
  Node* owner_ = nullptr;
  std::vector<Node*> children_;
  const Config* config_;
  std::array<Style::Length, 2> processedDimensions_{
      {StyleLength::undefined(), StyleLength::undefined()}};
};

inline Node* resolveRef(const YGNodeRef ref) {
  return static_cast<Node*>(ref);
}

inline const Node* resolveRef(const YGNodeConstRef ref) {
  return static_cast<const Node*>(ref);
}

} // namespace facebook::yoga
