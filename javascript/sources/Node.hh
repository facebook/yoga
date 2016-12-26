#pragma once

#include <yoga/Yoga.h>

#include "./Layout.hh"

class Node {

 public:

    Node(void);
    Node(YGNodeRef node);
    Node(Node && other);

    ~Node(void);

 public:

    Node(Node const &) = delete;

    Node const & operator=(Node const &) = delete;

 public:

    void setPositionType(int positionType);
    void setPosition(int edge, double position);

    void setAlignContent(int alignContent);
    void setAlignItems(int alignItems);
    void setAlignSelf(int alignSelf);
    void setFlexDirection(int flexDirection);
    void setFlexWrap(int flexWrap);
    void setJustifyContent(int justifyContent);

    void setMargin(int edge, double margin);

    void setOverflow(int overflow);

    void setFlexBasis(double flexBasis);
    void setFlexGrow(double flexGrow);
    void setFlexShrink(double flexShrink);

    void setWidth(double width);
    void setHeight(double height);

    void setMinWidth(double minWidth);
    void setMinHeight(double minHeight);

    void setMaxWidth(double maxWidth);
    void setMaxHeight(double maxHeight);

    void setBorder(int edge, double border);

    void setPadding(int edge, double padding);

 public:

    int getPositionType(void) const;
    double getPosition(int edge) const;

    int getAlignContent(void) const;
    int getAlignItems(void) const;
    int getAlignSelf(void) const;
    int getFlexDirection(void) const;
    int getFlexWrap(void) const;
    int getJustifyContent(void) const;

    double getMargin(int edge) const;

    int getOverflow(void) const;

    double getFlexBasis(void) const;
    double getFlexGrow(void) const;
    double getFlexShrink(void) const;

    double getWidth(void) const;
    double getHeight(void) const;

    double getMinWidth(void) const;
    double getMinHeight(void) const;

    double getMaxWidth(void) const;
    double getMaxHeight(void) const;

    double getBorder(int edge) const;

    double getPadding(int edge) const;

 public:

    void insertChild(Node const & child, unsigned index) const;
    void removeChild(Node const & child) const;

 public:

    unsigned getChildCount(void) const;
    Node getChild(unsigned index) const;

 public:

    void calculateLayout(double width, double height, int direction = YGDirectionLTR) const;

 public:

    double getComputedLeft(void) const;
    double getComputedRight(void) const;

    double getComputedTop(void) const;
    double getComputedBottom(void) const;

    double getComputedWidth(void) const;
    double getComputedHeight(void) const;

    Layout getComputedLayout(void) const;

 private:

    YGNodeRef m_node;

};
