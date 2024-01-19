/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <fuzzer/FuzzedDataProvider.h>
#include <yoga/Yoga.h>
#include <cstdint>

YGFlexDirection fuzzedFlexDirection(FuzzedDataProvider& fdp) {
  return fdp.PickValueInArray({
      YGFlexDirectionColumn,
      YGFlexDirectionColumnReverse,
      YGFlexDirectionRow,
      YGFlexDirectionRowReverse,
  });
}

void fillFuzzedTree(
    FuzzedDataProvider& fdp,
    YGConfigConstRef config,
    YGNodeRef root,
    size_t depth = 0) {
  constexpr size_t kMaxDepth = 20;
  constexpr size_t kMaxChildren = 20;

  if (depth > kMaxDepth) {
    return;
  }

  size_t children = fdp.ConsumeIntegralInRange<size_t>(0, kMaxChildren);
  for (size_t i = 0; i < children; i++) {
    YGNodeRef child = YGNodeNewWithConfig(config);
    YGNodeStyleSetFlexDirection(root, fuzzedFlexDirection(fdp));
    YGNodeStyleSetWidth(child, fdp.ConsumeFloatingPoint<float>());
    YGNodeStyleSetGap(
        child, YGGutterAll, fdp.ConsumeProbability<float>() * 100);
    YGNodeStyleSetHeight(child, fdp.ConsumeFloatingPoint<float>());
    YGNodeInsertChild(root, child, i);
    fillFuzzedTree(fdp, config, child, depth + 1);
  }
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  YGConfigRef config = YGConfigNew();
  YGNodeRef root = YGNodeNewWithConfig(config);
  fillFuzzedTree(fdp, config, root);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  YGNodeFreeRecursive(root);
  YGConfigFree(config);
  return 0;
}
