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

std::shared_ptr<YGConfig> buildConfigFromJson(json& j) {
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

void setStylesFromJson(json& j, std::shared_ptr<YGNode> node) {
  json style = j["style"];
  for (const auto& [key, value] : style.items()) {
    if (key == "flex-direction") {
      YGNodeStyleSetFlexDirection(node.get(), flexDirectionFromString(value));
    } else if (key == "justify-content") {
      YGNodeStyleSetJustifyContent(node.get(), justifyContentFromString(value));
    } else if (key == "align-items") {
      YGNodeStyleSetAlignItems(node.get(), alignFromString(value));
    } else if (key == "align-content") {
      YGNodeStyleSetAlignContent(node.get(), alignFromString(value));
    } else if (key == "align-self") {
      YGNodeStyleSetAlignSelf(node.get(), alignFromString(value));
    } else if (key == "flex-wrap") {
      YGNodeStyleSetFlexWrap(node.get(), wrapFromString(value));
    } else if (key == "overflow") {
      YGNodeStyleSetOverflow(node.get(), overflowFromString(value));
    } else if (key == "display") {
      YGNodeStyleSetDisplay(node.get(), displayFromString(value));
    } else if (key == "position-type") {
      YGNodeStyleSetPositionType(node.get(), positionTypeFromString(value));
    } else if (key == "flex-grow") {
      YGNodeStyleSetFlexGrow(node.get(), value);
    } else if (key == "flex-shrink") {
      YGNodeStyleSetFlexShrink(node.get(), value);
    } else if (key == "flex") {
      YGNodeStyleSetFlex(node.get(), value);
    } else if (key == "flex-basis") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitAuto) {
        YGNodeStyleSetFlexBasisAuto(node.get());
      } else if (unit == YGUnitPoint) {
        YGNodeStyleSetFlexBasis(node.get(), value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetFlexBasisPercent(node.get(), value["value"]);
      }
    } else if (key.starts_with("position")) {
      YGEdge edge = edgeFromString(edgeStringFromPropertyName(key, "position"));
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetPosition(node.get(), edge, value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetPositionPercent(node.get(), edge, value["value"]);
      }
    } else if (key.starts_with("padding")) {
      YGEdge edge = edgeFromString(edgeStringFromPropertyName(key, "padding"));
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetPadding(node.get(), edge, value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetPaddingPercent(node.get(), edge, value["value"]);
      }
    } else if (key.starts_with("border")) {
      YGEdge edge = edgeFromString(edgeStringFromPropertyName(key, "border"));
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetBorder(node.get(), edge, value["value"]);
      }
    } else if (key.starts_with("margin")) {
      YGEdge edge = edgeFromString(edgeStringFromPropertyName(key, "margin"));
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetMargin(node.get(), edge, value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetMarginPercent(node.get(), edge, value["value"]);
      } else if (unit == YGUnitAuto) {
        YGNodeStyleSetMarginAuto(node.get(), edge);
      }
    } else if (key == "gap") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetGap(node.get(), YGGutterAll, value["value"]);
      }
    } else if (key == "column-gap") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetGap(node.get(), YGGutterColumn, value["value"]);
      }
    } else if (key == "row-gap") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetGap(node.get(), YGGutterRow, value["value"]);
      }
    } else if (key == "height") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitAuto) {
        YGNodeStyleSetHeightAuto(node.get());
      } else if (unit == YGUnitPoint) {
        YGNodeStyleSetHeight(node.get(), value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetHeightPercent(node.get(), value["value"]);
      }
    } else if (key == "width") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitAuto) {
        YGNodeStyleSetWidthAuto(node.get());
      } else if (unit == YGUnitPoint) {
        YGNodeStyleSetWidth(node.get(), value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetWidthPercent(node.get(), value["value"]);
      }
    } else if (key == "min-height") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetMinHeight(node.get(), value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetMinHeightPercent(node.get(), value["value"]);
      }
    } else if (key == "min-width") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetMinWidth(node.get(), value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetMinWidthPercent(node.get(), value["value"]);
      }
    } else if (key == "max-height") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetMaxHeight(node.get(), value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetMaxHeightPercent(node.get(), value["value"]);
      }
    } else if (key == "max-width") {
      YGUnit unit = unitFromJson(value);
      if (unit == YGUnitPoint) {
        YGNodeStyleSetMaxWidth(node.get(), value["value"]);
      } else if (unit == YGUnitPercent) {
        YGNodeStyleSetMaxWidthPercent(node.get(), value["value"]);
      }
    }
  }
}

YogaNodeAndConfig
buildTreeFromJson(json& j, YogaNodeAndConfig* parent, size_t index) {
  std::shared_ptr<YGConfig> config = buildConfigFromJson(j);
  std::shared_ptr<YGNode> node(YGNodeNewWithConfig(config.get()), YGNodeFree);
  YogaNodeAndConfig wrapper{node, config, std::vector<YogaNodeAndConfig>{}};
  if (parent != nullptr) {
    YGNodeInsertChild(parent->node_.get(), node.get(), index);
    parent->children_.push_back(wrapper);
  }

  setStylesFromJson(j, node);

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

  auto layoutBegin = steady_clock::now();
  YGNodeCalculateLayout(
      root.node_.get(), YGUndefined, YGUndefined, YGDirectionLTR);
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
