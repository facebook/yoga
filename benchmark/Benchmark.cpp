/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <filesystem>
#include <fstream>

#include <benchmark/Benchmark.h>
#include <benchmark/TreeDeserialization.h>
#include <nlohmann/json.hpp>

namespace facebook::yoga {

using namespace nlohmann;
using namespace std::chrono;

constexpr uint32_t kNumRepititions = 1000;
using SteadyClockDurations =
    std::array<steady_clock::duration, kNumRepititions>;

std::shared_ptr<const YGConfig> buildConfigFromJson(const json& j) {
  json jsonConfig = j["config"];
  std::shared_ptr<YGConfig> config(YGConfigNew(), YGConfigFree);
  for (json::iterator it = jsonConfig.begin(); it != jsonConfig.end(); it++) {
    if (it.key() == "use-web-defaults") {
      YGConfigSetUseWebDefaults(config.get(), it.value());
    } else if (it.key() == "point-scale-factor") {
      YGConfigSetPointScaleFactor(config.get(), it.value());
    } else if (it.key() == "errata") {
      YGConfigSetErrata(config.get(), errataFromString(it.value()));
    } else if (it.key() == "experimental-features") {
      // Experimental features is serialized into an array where the values
      // present indicate that that feature is enabled
      for (json::iterator efIt = it.value().begin(); efIt != it.value().end();
           efIt++) {
        YGConfigSetExperimentalFeatureEnabled(
            config.get(), experimentalFeatureFromString(efIt.value()), true);
      }
    }
  }

  return config;
}

std::string edgeStringFromPropertyName(
    std::string key,
    std::string propertyName) {
  return key.substr(propertyName.length() + 1);
}

void setStylesFromJson(const json& j, YGNodeRef node) {
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
}

std::shared_ptr<YGNode> buildNodeFromJson(
    const json& j,
    std::shared_ptr<const YGConfig> config) {
  std::shared_ptr<YGNode> node(YGNodeNewWithConfig(config.get()), YGNodeFree);
  json nodeState = j["node"];

  for (json::iterator it = nodeState.begin(); it != nodeState.end(); it++) {
    if (it.key() == "always-forms-containing-block") {
      YGNodeSetAlwaysFormsContainingBlock(node.get(), it.value());
    }
  }

  return node;
}

YogaNodeAndConfig
buildTreeFromJson(const json& j, YogaNodeAndConfig* parent, size_t index) {
  std::shared_ptr<const YGConfig> config = buildConfigFromJson(j);
  std::shared_ptr<YGNode> node = buildNodeFromJson(j, config);
  YogaNodeAndConfig wrapper{node, config, std::vector<YogaNodeAndConfig>{}};
  if (parent != nullptr) {
    YGNodeInsertChild(parent->node_.get(), node.get(), index);
    parent->children_.push_back(wrapper);
  }

  setStylesFromJson(j, node.get());

  json children = j["children"];
  size_t childIndex = 0;
  for (json child : children) {
    buildTreeFromJson(child, &wrapper, childIndex);
    childIndex++;
  }

  return wrapper;
}

BenchmarkResult generateBenchmark(const std::filesystem::path& capturePath) {
  std::ifstream captureFile(capturePath);
  json capture = json::parse(captureFile);

  auto treeCreationBegin = steady_clock::now();
  YogaNodeAndConfig root = buildTreeFromJson(capture, nullptr, 0 /*index*/);
  auto treeCreationEnd = steady_clock::now();

  json layoutInputs = capture["layout-inputs"];
  float availableWidth = layoutInputs["available-width"];
  float availableHeight = layoutInputs["available-height"];
  YGDirection direction = directionFromString(layoutInputs["owner-direction"]);

  auto layoutBegin = steady_clock::now();
  YGNodeCalculateLayout(
      root.node_.get(), availableWidth, availableHeight, direction);
  auto layoutEnd = steady_clock::now();

  return BenchmarkResult{
      treeCreationEnd - treeCreationBegin, layoutEnd - layoutBegin};
}

static void printBenchmarkResult(
    std::string name,
    SteadyClockDurations& durations) {
  std::array<double, kNumRepititions> timesInMs;
  double mean = 0;
  for (uint32_t i = 0; i < kNumRepititions; i++) {
    auto ms = duration<double, std::milli>(durations[i]).count();
    timesInMs[i] = ms;
    mean += ms;
  }
  mean /= kNumRepititions;

  std::sort(timesInMs.begin(), timesInMs.end());
  double median = timesInMs[kNumRepititions / 2];

  double variance = 0;
  for (uint32_t i = 0; i < kNumRepititions; i++) {
    variance += std::pow(timesInMs[i] - mean, 2);
  }
  variance /= kNumRepititions;
  double stddev = std::sqrt(variance);

  printf("%s: median: %lf ms, stddev: %lf ms\n", name.c_str(), median, stddev);
}

void benchmark(std::filesystem::path& capturesDir) {
  for (auto& capture : std::filesystem::directory_iterator(capturesDir)) {
    if (capture.is_directory() || capture.path().extension() != ".json") {
      continue;
    }

    SteadyClockDurations treeCreationDurations;
    SteadyClockDurations layoutDurations;
    SteadyClockDurations totalDurations;

    for (uint32_t i = 0; i < kNumRepititions; i++) {
      BenchmarkResult result = generateBenchmark(capture.path());
      treeCreationDurations[i] = result.treeCreationDuration;
      layoutDurations[i] = result.layoutDuration;
      totalDurations[i] = result.treeCreationDuration + result.layoutDuration;
    }

    std::string captureName = capture.path().stem().string();
    printBenchmarkResult(captureName + " tree creation", treeCreationDurations);
    printBenchmarkResult(captureName + " layout", layoutDurations);
    printBenchmarkResult(captureName + " total", totalDurations);
  }
}

} // namespace facebook::yoga

int main(int argc, char* argv[]) {
  if (argc == 2) {
    std::filesystem::path capturesDir = argv[argc - 1];
    facebook::yoga::benchmark(capturesDir);
  } else {
    throw std::invalid_argument("Expecting a path as an argument");
    return 1;
  }

  return 0;
}
