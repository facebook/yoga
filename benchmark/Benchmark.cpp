/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <fstream>

#include <benchmark/Benchmark.h>
#include <nlohmann/json.hpp>
#include <yoga/Yoga.h>

namespace facebook::yoga {

using namespace nlohmann;

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
    std::string key,
    std::string propertyName) {
  return key.substr(propertyName.length() + 1);
}

YGNodeRef buildTreeFromJson(json& j, YGNodeRef parent, size_t index) {
  const YGNodeRef node = YGNodeNew();
  if (parent != nullptr) {
    YGNodeInsertChild(parent, node, index);
  }

  json style = j["style"];
  for (const auto& [key, value] : style.items()) {
    if (key == "flex-direction") {
      YGNodeStyleSetFlexDirection(node, flexDirectionFromString(value));
    } else if (key == "justify-content") {
      YGNodeStyleSetJustifyContent(node, justifyContentFromString(value));
    } else if (key == "align-items") {
      YGNodeStyleSetAlignItems(node, alignFromString(value));
    } else if (key == "align-content") {
      YGNodeStyleSetAlignContent(node, alignFromString(value));
    } else if (key == "align-self") {
      YGNodeStyleSetAlignSelf(node, alignFromString(value));
    } else if (key == "flex-wrap") {
      YGNodeStyleSetFlexWrap(node, wrapFromString(value));
    } else if (key == "overflow") {
      YGNodeStyleSetOverflow(node, overflowFromString(value));
    } else if (key == "display") {
      YGNodeStyleSetDisplay(node, displayFromString(value));
    } else if (key == "position-type") {
      YGNodeStyleSetPositionType(node, positionTypeFromString(value));
    } else if (key == "flex-grow") {
      YGNodeStyleSetFlexGrow(node, value);
    } else if (key == "flex-shrink") {
      YGNodeStyleSetFlexShrink(node, value);
    } else if (key == "flex") {
      YGNodeStyleSetFlex(node, value);
    } else if (key == "flex-basis") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitAuto) {
        YGNodeStyleSetFlexBasisAuto(node);
      } else if (unit == YGUnitPoint) {
        YGNodeStyleSetFlexBasis(node, value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetFlexBasisPercent(node, value["value"]);
      }
    } else if (key.starts_with("position")) {
      YGEdge edge = edgeFromString(edgeStringFromPropertyName(key, "position"));
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetPosition(node, edge, value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetPositionPercent(node, edge, value["value"]);
      }
    } else if (key.starts_with("padding")) {
      YGEdge edge = edgeFromString(edgeStringFromPropertyName(key, "padding"));
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetPadding(node, edge, value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetPaddingPercent(node, edge, value["value"]);
      }
    } else if (key.starts_with("border")) {
      YGEdge edge = edgeFromString(edgeStringFromPropertyName(key, "border"));
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetBorder(node, edge, value["value"]);
      }
    } else if (key.starts_with("margin")) {
      YGEdge edge = edgeFromString(edgeStringFromPropertyName(key, "margin"));
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetMargin(node, edge, value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetMarginPercent(node, edge, value["value"]);
      } else if (unit == YGUnitAuto) {
        YGNodeStyleSetMarginAuto(node, edge);
      }
    } else if (key == "gap") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetGap(node, YGGutterAll, value["value"]);
      }
    } else if (key == "column-gap") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetGap(node, YGGutterColumn, value["value"]);
      }
    } else if (key == "row-gap") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetGap(node, YGGutterRow, value["value"]);
      }
    } else if (key == "height") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitAuto) {
        YGNodeStyleSetHeightAuto(node);
      } else if (unit == YGUnitPoint) {
        YGNodeStyleSetHeight(node, value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetHeightPercent(node, value["value"]);
      }
    } else if (key == "width") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitAuto) {
        YGNodeStyleSetWidthAuto(node);
      } else if (unit == YGUnitPoint) {
        YGNodeStyleSetWidth(node, value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetWidthPercent(node, value["value"]);
      }
    } else if (key == "min-height") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetMinHeight(node, value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetMinHeightPercent(node, value["value"]);
      }
    } else if (key == "min-width") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetMinWidth(node, value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetMinWidthPercent(node, value["value"]);
      }
    } else if (key == "max-height") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetMaxHeight(node, value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetMaxHeightPercent(node, value["value"]);
      }
    } else if (key == "max-width") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetMaxWidth(node, value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetMaxWidthPercent(node, value["value"]);
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

void generateBenchmark(const std::filesystem::path& capturePath) {
  std::ifstream captureFile(capturePath);
  json capture = json::parse(captureFile);

  YGNodeRef root = buildTreeFromJson(capture, nullptr, 0 /*index*/);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  YGNodeFreeRecursive(root);
}

} // namespace facebook::yoga

int main() {
  return 0;
}
