#pragma once

#include <memory>

#include <nbind/api.h>
#include <nbind/BindDefiner.h>
#include <yoga/Yoga.h>

#include "./Layout.hh"
#include "./Size.hh"

class Node {

 public:

    Node(void);
    Node(Node && other);

    ~Node(void);

 public: // Prevent accidental copy

    Node(Node const &) = delete;

    Node const & operator=(Node const &) = delete;

public: // Style setters

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

 public: // Style getters

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

 public: // Tree hierarchy mutators

    void insertChild(Node const & child, unsigned index);
    void removeChild(Node const & child);

 public: // Tree hierarchy inspectors

    unsigned getChildCount(void) const;

    Node * getChild(unsigned index) const;

 public: // Measure func mutators

    void setMeasureFunc(nbind::cbFunction & measureFunc);
    void unsetMeasureFunc(void);

 public: // Measure func inspectors

    Size callMeasureFunc(double width, int widthMode, double height, int heightMode) const;

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

 private:

    YGNodeRef m_node;

    std::unique_ptr<nbind::cbFunction> m_measureFunc;

};
