/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifdef DEBUG

#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>
#include <yoga/Yoga.h>
#include <yoga/benchmark/Benchmark.h>
#include <yoga/debug/NodeToString.h>
#include <yoga/enums/PrintOptions.h>

namespace facebook::yoga {

using namespace nlohmann;

std::string parentPath() {
  std::filesystem::path currentPath = __FILE__;
  return currentPath.parent_path().string();
}

std::filesystem::path capturePath(std::string captureName) {
  return parentPath() + "/captures/" + captureName + ".json";
}

void captureTree(const Node* node, std::string captureName) {
  std::string str;
  nodeToString(str, node, PrintOptions::Style | PrintOptions::Children);
  std::ofstream captureFile(capturePath(captureName));
  captureFile << str;
  captureFile.close();
}

std::string invalidArgumentMessage(std::string arg, std::string enumName) {
  return arg + " does not represent any " + enumName + " values";
}

YGFlexDirection flexDirectionFromString(std::string str) {
  if (str == "row") {
    return YGFlexDirectionRow;
  } else if (str == "row-reverse") {
    return YGFlexDirectionRowReverse;
  } else if (str == "column") {
    return YGFlexDirectionColumn;
  } else if (str == "column-reverse") {
    return YGFlexDirectionColumnReverse;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(str, "YGFlexDirection"));
  }
}

YGJustify justifyContentFromString(std::string str) {
  if (str == "flex-start") {
    return YGJustifyFlexStart;
  } else if (str == "center") {
    return YGJustifyCenter;
  } else if (str == "flex-end") {
    return YGJustifyFlexEnd;
  } else if (str == "space-between") {
    return YGJustifySpaceBetween;
  } else if (str == "space-around") {
    return YGJustifySpaceAround;
  } else if (str == "space-evenly") {
    return YGJustifySpaceEvenly;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(str, "YGJustify"));
  }
}

YGAlign alignFromString(std::string str) {
  if (str == "auto") {
    return YGAlignAuto;
  } else if (str == "flex-start") {
    return YGAlignFlexStart;
  } else if (str == "center") {
    return YGAlignCenter;
  } else if (str == "flex-end") {
    return YGAlignFlexEnd;
  } else if (str == "stretch") {
    return YGAlignStretch;
  } else if (str == "baseline") {
    return YGAlignBaseline;
  } else if (str == "space-between") {
    return YGAlignSpaceBetween;
  } else if (str == "space-around") {
    return YGAlignSpaceAround;
  } else if (str == "space-evenly") {
    return YGAlignSpaceEvenly;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(str, "YGAlign"));
  }
}

YGWrap wrapFromString(std::string str) {
  if (str == "no-wrap") {
    return YGWrapNoWrap;
  } else if (str == "wrap") {
    return YGWrapWrap;
  } else if (str == "wrap-reverse") {
    return YGWrapWrapReverse;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(str, "YGAlign"));
  }
}

YGOverflow overflowFromString(std::string str) {
  if (str == "visible") {
    return YGOverflowVisible;
  } else if (str == "hidden") {
    return YGOverflowHidden;
  } else if (str == "scroll") {
    return YGOverflowScroll;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(str, "YGAlign"));
  }
}

YGDisplay displayFromString(std::string str) {
  if (str == "flex") {
    return YGDisplayFlex;
  } else if (str == "none") {
    return YGDisplayNone;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(str, "YGAlign"));
  }
}

YGPositionType positionTypeFromString(std::string str) {
  if (str == "static") {
    return YGPositionTypeStatic;
  } else if (str == "relative") {
    return YGPositionTypeRelative;
  } else if (str == "absolute") {
    return YGPositionTypeAbsolute;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(str, "YGAlign"));
  }
}

bool isAuto(json& j) {
  return j.is_string() && j == "auto";
}

YGUnit unitFromJson(json& j) {
  if (isAuto(j)) {
    return YGUnitAuto;
  }

  std::string unit = j["unit"];
  if (unit == "px") {
    return YGUnitPoint;
  } else if (unit == "\%") {
    return YGUnitPercent;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(unit, "YGUnit"));
  }
}

YGEdge edgeFromString(std::string str) {
  if (str == "left") {
    return YGEdgeLeft;
  } else if (str == "top") {
    return YGEdgeTop;
  } else if (str == "right") {
    return YGEdgeRight;
  } else if (str == "bottom") {
    return YGEdgeBottom;
  } else if (str == "start") {
    return YGEdgeStart;
  } else if (str == "end") {
    return YGEdgeEnd;
  } else if (str == "horizontal") {
    return YGEdgeHorizontal;
  } else if (str == "vertical") {
    return YGEdgeVertical;
  } else if (str == "all") {
    return YGEdgeAll;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(str, "YGEdge"));
  }
}

std::string edgeStringFromPropertyName(
    json::iterator it,
    std::string propertyName) {
  return it.key().substr(propertyName.length() + 1);
}

YGNodeRef buildTreeFromJson(json& j, YGNodeRef parent, size_t index) {
  const YGNodeRef node = YGNodeNew();
  if (parent != nullptr) {
    YGNodeInsertChild(parent, node, index);
  }

  json style = j["style"];
  for (json::iterator it = style.begin(); it != style.end(); it++) {
    if (it.key() == "flex-direction") {
      YGNodeStyleSetFlexDirection(node, flexDirectionFromString(it.value()));
    } else if (it.key() == "justify-content") {
      YGNodeStyleSetJustifyContent(node, justifyContentFromString(it.value()));
    } else if (it.key() == "align-items") {
      YGNodeStyleSetAlignItems(node, alignFromString(it.value()));
    } else if (it.key() == "align-content") {
      YGNodeStyleSetAlignContent(node, alignFromString(it.value()));
    } else if (it.key() == "align-self") {
      YGNodeStyleSetAlignSelf(node, alignFromString(it.value()));
    } else if (it.key() == "flex-wrap") {
      YGNodeStyleSetFlexWrap(node, wrapFromString(it.value()));
    } else if (it.key() == "overflow") {
      YGNodeStyleSetOverflow(node, overflowFromString(it.value()));
    } else if (it.key() == "display") {
      YGNodeStyleSetDisplay(node, displayFromString(it.value()));
    } else if (it.key() == "position-type") {
      YGNodeStyleSetPositionType(node, positionTypeFromString(it.value()));
    } else if (it.key() == "flex-grow") {
      YGNodeStyleSetFlexGrow(node, it.value());
    } else if (it.key() == "flex-shrink") {
      YGNodeStyleSetFlexShrink(node, it.value());
    } else if (it.key() == "flex") {
      YGNodeStyleSetFlex(node, it.value());
    } else if (it.key() == "flex-basis") {
      YGUnit unit = unitFromJson(it.value());
      if (unit == YGUnitAuto) {
        YGNodeStyleSetFlexBasisAuto(node);
      } else if (unit == YGUnitPoint) {
        YGNodeStyleSetFlexBasis(node, it.value()["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetFlexBasisPercent(node, it.value()["value"]);
      }
    } else if (it.key().starts_with("position")) {
      YGEdge edge = edgeFromString(edgeStringFromPropertyName(it, "position"));
      YGUnit unit = unitFromJson(it.value());
      if (unit == YGUnitPoint) {
        YGNodeStyleSetPosition(node, edge, it.value()["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetPositionPercent(node, edge, it.value()["value"]);
      }
    } else if (it.key().starts_with("padding")) {
      YGEdge edge = edgeFromString(edgeStringFromPropertyName(it, "padding"));
      YGUnit unit = unitFromJson(it.value());
      if (unit == YGUnitPoint) {
        YGNodeStyleSetPadding(node, edge, it.value()["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetPaddingPercent(node, edge, it.value()["value"]);
      }
    } else if (it.key().starts_with("border")) {
      YGEdge edge = edgeFromString(edgeStringFromPropertyName(it, "border"));
      YGUnit unit = unitFromJson(it.value());
      if (unit == YGUnitPoint) {
        YGNodeStyleSetBorder(node, edge, it.value()["value"]);
      }
    } else if (it.key().starts_with("margin")) {
      YGEdge edge = edgeFromString(edgeStringFromPropertyName(it, "margin"));
      YGUnit unit = unitFromJson(it.value());
      if (unit == YGUnitPoint) {
        YGNodeStyleSetMargin(node, edge, it.value()["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetMarginPercent(node, edge, it.value()["value"]);
      } else if (unit == YGUnitAuto) {
        YGNodeStyleSetMarginAuto(node, edge);
      }
    } else if (it.key() == "gap") {
      YGUnit unit = unitFromJson(it.value());
      if (unit == YGUnitPoint) {
        YGNodeStyleSetGap(node, YGGutterAll, it.value()["value"]);
      }
    } else if (it.key() == "column-gap") {
      YGUnit unit = unitFromJson(it.value());
      if (unit == YGUnitPoint) {
        YGNodeStyleSetGap(node, YGGutterColumn, it.value()["value"]);
      }
    } else if (it.key() == "row-gap") {
      YGUnit unit = unitFromJson(it.value());
      if (unit == YGUnitPoint) {
        YGNodeStyleSetGap(node, YGGutterRow, it.value()["value"]);
      }
    } else if (it.key() == "height") {
      YGUnit unit = unitFromJson(it.value());
      if (unit == YGUnitAuto) {
        YGNodeStyleSetHeightAuto(node);
      } else if (unit == YGUnitPoint) {
        YGNodeStyleSetHeight(node, it.value()["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetHeightPercent(node, it.value()["value"]);
      }
    } else if (it.key() == "width") {
      YGUnit unit = unitFromJson(it.value());
      if (unit == YGUnitAuto) {
        YGNodeStyleSetWidthAuto(node);
      } else if (unit == YGUnitPoint) {
        YGNodeStyleSetWidth(node, it.value()["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetWidthPercent(node, it.value()["value"]);
      }
    } else if (it.key() == "min-height") {
      YGUnit unit = unitFromJson(it.value());
      if (unit == YGUnitPoint) {
        YGNodeStyleSetMinHeight(node, it.value()["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetMinHeightPercent(node, it.value()["value"]);
      }
    } else if (it.key() == "min-width") {
      YGUnit unit = unitFromJson(it.value());
      if (unit == YGUnitPoint) {
        YGNodeStyleSetMinWidth(node, it.value()["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetMinWidthPercent(node, it.value()["value"]);
      }
    } else if (it.key() == "max-height") {
      YGUnit unit = unitFromJson(it.value());
      if (unit == YGUnitPoint) {
        YGNodeStyleSetMaxHeight(node, it.value()["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetMaxHeightPercent(node, it.value()["value"]);
      }
    } else if (it.key() == "max-width") {
      YGUnit unit = unitFromJson(it.value());
      if (unit == YGUnitPoint) {
        YGNodeStyleSetMaxWidth(node, it.value()["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetMaxWidthPercent(node, it.value()["value"]);
      }
    }
  }

  json children = j["children"];
  size_t childIndex = 0;
  for (json child : children) {
    buildTreeFromJson(child, node, childIndex);
    childIndex++;
  }

  return node;
}

void generateBenchmark(std::string captureName) {
  std::ifstream captureFile(capturePath(captureName));
  json capture = json::parse(captureFile);

  YGNodeRef root = buildTreeFromJson(capture, nullptr, 0 /*index*/);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  YGNodeFreeRecursive(root);
}

} // namespace facebook::yoga
#endif
