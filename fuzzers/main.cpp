// Copyright (c) Facebook, Inc. and its affiliates.
//
// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.

#include "yoga.pb.h"
#include "Yoga.h"
#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"

namespace yoga_proto {

void PerformAction(const YGNodeRef& node, const Action& action){
  if (action.has_nodesetisreferencebaseline()){
    YGNodeSetIsReferenceBaseline(node, action.nodesetisreferencebaseline().isreferencebaseline());
  }
  else if (action.has_nodecalculatelayout()){
    YGDirection direction;
    switch (action.nodecalculatelayout().ownerdirection()) {
      case DirectionInherit: direction = YGDirectionInherit; break;
      case DirectionLTR: direction = YGDirectionLTR; break;
      case DirectionRTL: direction = YGDirectionRTL; break;
    }
    YGNodeCalculateLayout(node,
                          action.nodecalculatelayout().availablewidth(),
                          action.nodecalculatelayout().availableheight(),
                          direction);
  }
  else if (action.has_nodemarkdirty()){
    // not security related function
  }
  else if (action.has_nodemarkdirtyandpropogatetodescendants()){
    // not security related function
  }
  else if (action.has_nodeprint()){
    // not security related function
  }
  else if (action.has_nodesethasnewlayout()){
    YGNodeSetHasNewLayout(node, action.nodesethasnewlayout().hasnewlayout());
  }
  else if (action.has_nodestylesetdirection()){
    YGDirection direction;
    switch (action.nodestylesetdirection().direction()) {
      case DirectionInherit: direction = YGDirectionInherit; break;
      case DirectionLTR: direction = YGDirectionLTR; break;
      case DirectionRTL: direction = YGDirectionRTL; break;
    }
    YGNodeStyleSetDirection(node, direction);
  }
  else if (action.has_nodestylesetflexdirection()){
    YGFlexDirection flexdirection;
    switch (action.nodestylesetflexdirection().flexdirection()) {
      case FlexDirectionColumn: flexdirection = YGFlexDirectionColumn; break;
      case FlexDirectionColumnReverse: flexdirection = YGFlexDirectionColumnReverse; break;
      case FlexDirectionRow: flexdirection = YGFlexDirectionRow; break;
      case FlexDirectionRowReverse: flexdirection = YGFlexDirectionRowReverse; break;
    }
    YGNodeStyleSetFlexDirection(node, flexdirection);
  }
  else if (action.has_nodestylesetjustifycontent()){
    YGJustify justify;
    switch (action.nodestylesetjustifycontent().justifycontent()) {
      case JustifyFlexStart: justify = YGJustifyFlexStart; break;
      case JustifyCenter: justify = YGJustifyCenter; break;
      case JustifyFlexEnd: justify = YGJustifyFlexEnd; break;
      case JustifySpaceBetween: justify = YGJustifySpaceBetween; break;
      case JustifySpaceAround: justify = YGJustifySpaceAround; break;
      case JustifySpaceEvenly: justify = YGJustifySpaceEvenly; break;
    }
    YGNodeStyleSetJustifyContent(node, justify);
  }
  else if (action.has_nodestylesetaligncontent()){
    YGAlign align;
    switch (action.nodestylesetaligncontent().aligncontent()) {
      case AlignAuto: align = YGAlignAuto; break;
      case AlignFlexStart: align = YGAlignFlexStart; break;
      case AlignCenter: align = YGAlignCenter; break;
      case AlignFlexEnd: align = YGAlignFlexEnd; break;
      case AlignStretch: align = YGAlignStretch; break;
      case AlignBaseline: align = YGAlignBaseline; break;
      case AlignSpaceBetween: align = YGAlignSpaceBetween; break;
      case AlignSpaceAround: align = YGAlignSpaceAround; break;
    }
    YGNodeStyleSetAlignContent(node, align);
  }
  else if (action.has_nodestylesetalignitems()){
    YGAlign align;
    switch (action.nodestylesetalignitems().alignitems()) {
      case AlignAuto: align = YGAlignAuto; break;
      case AlignFlexStart: align = YGAlignFlexStart; break;
      case AlignCenter: align = YGAlignCenter; break;
      case AlignFlexEnd: align = YGAlignFlexEnd; break;
      case AlignStretch: align = YGAlignStretch; break;
      case AlignBaseline: align = YGAlignBaseline; break;
      case AlignSpaceBetween: align = YGAlignSpaceBetween; break;
      case AlignSpaceAround: align = YGAlignSpaceAround; break;
    }
    YGNodeStyleSetAlignItems(node, align);
  }
  else if (action.has_nodestylesetalignself()){
    YGAlign align;
    switch (action.nodestylesetalignself().alignself()) {
      case AlignAuto: align = YGAlignAuto; break;
      case AlignFlexStart: align = YGAlignFlexStart; break;
      case AlignCenter: align = YGAlignCenter; break;
      case AlignFlexEnd: align = YGAlignFlexEnd; break;
      case AlignStretch: align = YGAlignStretch; break;
      case AlignBaseline: align = YGAlignBaseline; break;
      case AlignSpaceBetween: align = YGAlignSpaceBetween; break;
      case AlignSpaceAround: align = YGAlignSpaceAround; break;
    }
    YGNodeStyleSetAlignSelf(node, align);
  }
  else if (action.has_nodestylesetpositiontype()){
    YGPositionType positiontype;
    switch (action.nodestylesetpositiontype().positiontype()) {
      case PositionTypeStatic: positiontype = YGPositionTypeStatic; break;
      case PositionTypeRelative: positiontype = YGPositionTypeRelative; break;
      case PositionTypeAbsolute: positiontype = YGPositionTypeAbsolute; break;
    }
    YGNodeStyleSetPositionType(node, positiontype);
  }
  else if (action.has_nodestylesetflexwrap()){
    YGWrap wrap;
    switch (action.nodestylesetflexwrap().flexwrap()) {
      case WrapNoWrap: wrap = YGWrapNoWrap; break;
      case WrapWrap: wrap = YGWrapWrap; break;
      case WrapWrapReverse: wrap = YGWrapWrapReverse; break;
    }
    YGNodeStyleSetFlexWrap(node, wrap);
  }
  else if (action.has_nodestylesetoverflow()){
    YGOverflow overflow;
    switch (action.nodestylesetoverflow().overflow()) {
      case OverflowVisible: overflow = YGOverflowVisible; break;
      case OverflowHidden: overflow = YGOverflowHidden; break;
      case OverflowScroll: overflow = YGOverflowScroll; break;
    }
    YGNodeStyleSetOverflow(node, overflow);
  }
  else if (action.has_nodestylesetdisplay()){
    YGDisplay display;
    switch (action.nodestylesetdisplay().display()) {
      case DisplayFlex: display = YGDisplayFlex; break;
      case DisplayNone: display = YGDisplayNone; break;
    }
    YGNodeStyleSetDisplay(node, display);
  }
  else if (action.has_nodestylesetflex()){
    YGNodeStyleSetFlex(node, action.nodestylesetflex().flex());
  }
  else if (action.has_nodestylesetflexgrow()){
    YGNodeStyleSetFlexGrow(node, action.nodestylesetflexgrow().flexgrow());
  }
  else if (action.has_nodestylesetflexshrink()){
    YGNodeStyleSetFlexShrink(node, action.nodestylesetflexshrink().flexshrink());
  }
  else if (action.has_nodestylesetflexbasis()){
    YGNodeStyleSetFlexBasis(node, action.nodestylesetflexbasis().flexbasis());
  }
  else if (action.has_nodestylesetflexbasispercent()){
    YGNodeStyleSetFlexBasisPercent(node, action.nodestylesetflexbasispercent().flexbasis());
  }
  else if (action.has_nodestylesetflexbasisauto()){
    YGNodeStyleSetFlexBasisAuto(node);
  }
  else if (action.has_nodestylesetposition()){
    YGEdge edge;
    switch (action.nodestylesetposition().edge()) {
      case EdgeLeft: edge = YGEdgeLeft; break;
      case EdgeTop: edge = YGEdgeTop; break;
      case EdgeRight: edge = YGEdgeRight; break;
      case EdgeBottom: edge = YGEdgeBottom; break;
      case EdgeStart: edge = YGEdgeStart; break;
      case EdgeEnd: edge = YGEdgeEnd; break;
      case EdgeHorizontal: edge = YGEdgeHorizontal; break;
      case EdgeVertical: edge = YGEdgeVertical; break;
      case EdgeAll: edge = YGEdgeAll; break;
    }
    YGNodeStyleSetPosition(node, edge,action.nodestylesetposition().position());
  }
  else if (action.has_nodestylesetpositionpercent()){
    YGEdge edge;
    switch (action.nodestylesetpositionpercent().edge()) {
      case EdgeLeft: edge = YGEdgeLeft; break;
      case EdgeTop: edge = YGEdgeTop; break;
      case EdgeRight: edge = YGEdgeRight; break;
      case EdgeBottom: edge = YGEdgeBottom; break;
      case EdgeStart: edge = YGEdgeStart; break;
      case EdgeEnd: edge = YGEdgeEnd; break;
      case EdgeHorizontal: edge = YGEdgeHorizontal; break;
      case EdgeVertical: edge = YGEdgeVertical; break;
      case EdgeAll: edge = YGEdgeAll; break;
    }
    YGNodeStyleSetPositionPercent(node, edge,action.nodestylesetpositionpercent().position());
  }
  else if (action.has_nodestylesetmargin()){
    YGEdge edge;
    switch (action.nodestylesetmargin().edge()) {
      case EdgeLeft: edge = YGEdgeLeft; break;
      case EdgeTop: edge = YGEdgeTop; break;
      case EdgeRight: edge = YGEdgeRight; break;
      case EdgeBottom: edge = YGEdgeBottom; break;
      case EdgeStart: edge = YGEdgeStart; break;
      case EdgeEnd: edge = YGEdgeEnd; break;
      case EdgeHorizontal: edge = YGEdgeHorizontal; break;
      case EdgeVertical: edge = YGEdgeVertical; break;
      case EdgeAll: edge = YGEdgeAll; break;
    }
    YGNodeStyleSetMargin(node, edge,action.nodestylesetmargin().margin());
  }
  else if (action.has_nodestylesetmarginpercent()){
    YGEdge edge;
    switch (action.nodestylesetmarginpercent().edge()) {
      case EdgeLeft: edge = YGEdgeLeft; break;
      case EdgeTop: edge = YGEdgeTop; break;
      case EdgeRight: edge = YGEdgeRight; break;
      case EdgeBottom: edge = YGEdgeBottom; break;
      case EdgeStart: edge = YGEdgeStart; break;
      case EdgeEnd: edge = YGEdgeEnd; break;
      case EdgeHorizontal: edge = YGEdgeHorizontal; break;
      case EdgeVertical: edge = YGEdgeVertical; break;
      case EdgeAll: edge = YGEdgeAll; break;
    }
    YGNodeStyleSetMarginPercent(node, edge,action.nodestylesetmarginpercent().margin());
  }
  else if (action.has_nodestylesetmarginauto()){
    YGEdge edge;
    switch (action.nodestylesetmarginauto().edge()) {
      case EdgeLeft: edge = YGEdgeLeft; break;
      case EdgeTop: edge = YGEdgeTop; break;
      case EdgeRight: edge = YGEdgeRight; break;
      case EdgeBottom: edge = YGEdgeBottom; break;
      case EdgeStart: edge = YGEdgeStart; break;
      case EdgeEnd: edge = YGEdgeEnd; break;
      case EdgeHorizontal: edge = YGEdgeHorizontal; break;
      case EdgeVertical: edge = YGEdgeVertical; break;
      case EdgeAll: edge = YGEdgeAll; break;
    }
    YGNodeStyleSetMarginAuto(node, edge);
  }
  else if (action.has_nodestylesetpadding()){
    YGEdge edge;
    switch (action.nodestylesetpadding().edge()) {
      case EdgeLeft: edge = YGEdgeLeft; break;
      case EdgeTop: edge = YGEdgeTop; break;
      case EdgeRight: edge = YGEdgeRight; break;
      case EdgeBottom: edge = YGEdgeBottom; break;
      case EdgeStart: edge = YGEdgeStart; break;
      case EdgeEnd: edge = YGEdgeEnd; break;
      case EdgeHorizontal: edge = YGEdgeHorizontal; break;
      case EdgeVertical: edge = YGEdgeVertical; break;
      case EdgeAll: edge = YGEdgeAll; break;
    }
    YGNodeStyleSetPadding(node, edge,action.nodestylesetpadding().padding());
  }
  else if (action.has_nodestylesetpaddingpercent()){
    YGEdge edge;
    switch (action.nodestylesetpaddingpercent().edge()) {
      case EdgeLeft: edge = YGEdgeLeft; break;
      case EdgeTop: edge = YGEdgeTop; break;
      case EdgeRight: edge = YGEdgeRight; break;
      case EdgeBottom: edge = YGEdgeBottom; break;
      case EdgeStart: edge = YGEdgeStart; break;
      case EdgeEnd: edge = YGEdgeEnd; break;
      case EdgeHorizontal: edge = YGEdgeHorizontal; break;
      case EdgeVertical: edge = YGEdgeVertical; break;
      case EdgeAll: edge = YGEdgeAll; break;
    }
    YGNodeStyleSetPaddingPercent(node, edge,action.nodestylesetpaddingpercent().padding());
  }
  else if (action.has_nodestylesetborder()){
    YGEdge edge;
    switch (action.nodestylesetborder().edge()) {
      case EdgeLeft: edge = YGEdgeLeft; break;
      case EdgeTop: edge = YGEdgeTop; break;
      case EdgeRight: edge = YGEdgeRight; break;
      case EdgeBottom: edge = YGEdgeBottom; break;
      case EdgeStart: edge = YGEdgeStart; break;
      case EdgeEnd: edge = YGEdgeEnd; break;
      case EdgeHorizontal: edge = YGEdgeHorizontal; break;
      case EdgeVertical: edge = YGEdgeVertical; break;
      case EdgeAll: edge = YGEdgeAll; break;
    }
    YGNodeStyleSetBorder(node, edge,action.nodestylesetborder().border());
  }
  else if (action.has_nodestylesetwidth()){
    YGNodeStyleSetWidth(node, action.nodestylesetwidth().width());
  }
  else if (action.has_nodestylesetwidthpercent()){
    YGNodeStyleSetWidthPercent(node, action.nodestylesetwidthpercent().width());
  }
  else if (action.has_nodestylesetwidthauto()){
    YGNodeStyleSetWidthAuto(node);
  }
  else if (action.has_nodestylesetheight()){
    YGNodeStyleSetHeight(node, action.nodestylesetheight().height());
  }
  else if (action.has_nodestylesetheightpercent()){
    YGNodeStyleSetHeightPercent(node, action.nodestylesetheightpercent().height());
  }
  else if (action.has_nodestylesetheightauto()){
    YGNodeStyleSetHeightAuto(node);
  }
  else if (action.has_nodestylesetminwidth()){
    YGNodeStyleSetMinWidth(node, action.nodestylesetminwidth().minwidth());
  }
  else if (action.has_nodestylesetminwidthpercent()){
    YGNodeStyleSetMinWidthPercent(node, action.nodestylesetminwidthpercent().minwidth());
  }
  else if (action.has_nodestylesetminheight()){
    YGNodeStyleSetMinHeight(node, action.nodestylesetminheight().minheight());
  }
  else if (action.has_nodestylesetminheightpercent()){
    YGNodeStyleSetMinHeightPercent(node, action.nodestylesetminheightpercent().minheight());
  }
  else if (action.has_nodestylesetmaxwidth()){
    YGNodeStyleSetMaxWidth(node, action.nodestylesetmaxwidth().maxwidth());
  }
  else if (action.has_nodestylesetmaxwidthpercent()){
    YGNodeStyleSetMaxWidthPercent(node, action.nodestylesetmaxwidthpercent().maxwidth());
  }
  else if (action.has_nodestylesetmaxheight()){
    YGNodeStyleSetMaxHeight(node, action.nodestylesetmaxheight().maxheight());
  }
  else if (action.has_nodestylesetmaxheightpercent()){
    YGNodeStyleSetMaxHeightPercent(node, action.nodestylesetmaxheightpercent().maxheight());
  }
  else if (action.has_nodestylesetaspectratio()){
    YGNodeStyleSetAspectRatio(node, action.nodestylesetaspectratio().aspectratio());
  }

}

void CreateNode(const Node& node, YGNodeRef parent, std::vector<YGNode*> allNodes){
  auto currentNode = YGNodeNew();
  allNodes.emplace_back(currentNode);
  if (parent != nullptr){
    YGNodeInsertChild(parent, currentNode, 0);
  }
  for (int i = 0; i < node.actions_size(); ++i) {
    try {
      PerformAction(currentNode, node.actions(i));
    } catch (std::logic_error&){
      // don't care because it is not security related
    }
  }
  for (int i = 0; i < node.children_size(); ++i) {
    CreateNode(node.children(i), currentNode, allNodes);
  }
}

void Parse(const YogaParseAPI& yoga_parser) {
  // create roots
  std::vector<YGNode*> allNodes;
  for (int i = 0; i < yoga_parser.yoga_roots_size(); ++i) {
    CreateNode(yoga_parser.yoga_roots(i), nullptr, allNodes);
  }
  for (auto node : allNodes) {
    YGNodeCalculateLayout(node, YGUndefined, YGUndefined, YGDirectionLTR);
    YGNodeCalculateLayout(node, YGUndefined, YGUndefined, YGDirectionRTL);
    YGNodeCalculateLayout(node, YGUndefined, YGUndefined, YGDirectionInherit);
  }
  for (auto node : allNodes) {
    YGNodeFree(node);
  }
}
}

DEFINE_PROTO_FUZZER(const yoga_proto::YogaParseAPI &obj) {
  yoga_proto::Parse(obj);
}

