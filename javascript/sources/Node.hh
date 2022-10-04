/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <memory>

#include <nbind/api.h>
#include <nbind/BindDefiner.h>
#include <yoga/Yoga.h>

#include "./Layout.hh"
#include "./Size.hh"
#include "./Value.hh"
#include "./Config.hh"

class Node {

public:
  static Node* createDefault(void);
  static Node* createWithConfig(Config* config);

  static void destroy(Node* node);

public:
  static Node* fromYGNode(YGNodeRef nodeRef);

private:
  Node(Config* config);

public:
  ~Node(void);

public: // Prevent accidental copy
  Node(Node const&) = delete;

  Node const& operator=(Node const&) = delete;

public:
  void reset(void);

public: // Style setters
  void copyStyle(Node const& other);

  void setPositionType(int positionType);
  void setPosition(int edge, double position);
  void setPositionPercent(int edge, double position);

  void setAlignContent(int alignContent);
  void setAlignItems(int alignItems);
  void setAlignSelf(int alignSelf);
  void setFlexDirection(int flexDirection);
  void setFlexWrap(int flexWrap);
  void setJustifyContent(int justifyContent);

  void setMargin(int edge, double margin);
  void setMarginPercent(int edge, double margin);
  void setMarginAuto(int edge);

  void setOverflow(int overflow);
  void setDisplay(int display);

  void setFlex(double flex);
  void setFlexBasis(double flexBasis);
  void setFlexBasisPercent(double flexBasis);
  void setFlexBasisAuto();
  void setFlexGrow(double flexGrow);
  void setFlexShrink(double flexShrink);

  void setWidth(double width);
  void setWidthPercent(double width);
  void setWidthAuto();
  void setHeight(double height);
  void setHeightPercent(double height);
  void setHeightAuto();

  void setMinWidth(double minWidth);
  void setMinWidthPercent(double minWidth);
  void setMinHeight(double minHeight);
  void setMinHeightPercent(double minHeight);

  void setMaxWidth(double maxWidth);
  void setMaxWidthPercent(double maxWidth);
  void setMaxHeight(double maxHeight);
  void setMaxHeightPercent(double maxHeight);

  void setAspectRatio(double aspectRatio);

  void setBorder(int edge, double border);

  void setPadding(int edge, double padding);
  void setPaddingPercent(int edge, double padding);

public: // Style getters
  int getPositionType(void) const;
  Value getPosition(int edge) const;

  int getAlignContent(void) const;
  int getAlignItems(void) const;
  int getAlignSelf(void) const;
  int getFlexDirection(void) const;
  int getFlexWrap(void) const;
  int getJustifyContent(void) const;

  Value getMargin(int edge) const;

  int getOverflow(void) const;
  int getDisplay(void) const;

  Value getFlexBasis(void) const;
  double getFlexGrow(void) const;
  double getFlexShrink(void) const;

  Value getWidth(void) const;
  Value getHeight(void) const;

  Value getMinWidth(void) const;
  Value getMinHeight(void) const;

  Value getMaxWidth(void) const;
  Value getMaxHeight(void) const;

  double getAspectRatio(void) const;

  double getBorder(int edge) const;

  Value getPadding(int edge) const;

public: // Tree hierarchy mutators
  void insertChild(Node* child, unsigned index);
  void removeChild(Node* child);

public: // Tree hierarchy inspectors
  unsigned getChildCount(void) const;

  // The following functions cannot be const because they could discard const
  // qualifiers (ex: constNode->getChild(0)->getParent() wouldn't be const)

  Node* getParent(void);
  Node* getChild(unsigned index);

public: // Measure func mutators
  void setMeasureFunc(nbind::cbFunction& measureFunc);
  void unsetMeasureFunc(void);

public: // Measure func inspectors
  Size callMeasureFunc(
      double width,
      int widthMode,
      double height,
      int heightMode) const;

public: // Dirtied func mutators
  void setDirtiedFunc(nbind::cbFunction& dirtiedFunc);
  void unsetDirtiedFunc(void);

public: // Dirtied func inspectors
  void callDirtiedFunc(void) const;

public: // Dirtiness accessors
  void markDirty(void);
  bool isDirty(void) const;

public: // Layout mutators
  void calculateLayout(double width, double height, int direction);

public: // Layout inspectors
  double getComputedLeft(void) const;
  double getComputedRight(void) const;

  double getComputedTop(void) const;
  double getComputedBottom(void) const;

  double getComputedWidth(void) const;
  double getComputedHeight(void) const;

  Layout getComputedLayout(void) const;

  double getComputedMargin(int edge) const;
  double getComputedBorder(int edge) const;
  double getComputedPadding(int edge) const;

public:
  void setIsReferenceBaseline(bool isReferenceBaseline);
  bool isReferenceBaseline();

  YGNodeRef m_node;

  std::unique_ptr<nbind::cbFunction> m_measureFunc;
  std::unique_ptr<nbind::cbFunction> m_dirtiedFunc;
};
