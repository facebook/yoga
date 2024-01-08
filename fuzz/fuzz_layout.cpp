#include <fuzzer/FuzzedDataProvider.h>
#include <yoga/Yoga.h>
#include <cstdint>

YGFlexDirection fuzzed_flex_direction(FuzzedDataProvider& fdp) {
  return fdp.PickValueInArray({
      YGFlexDirectionColumn,
      YGFlexDirectionColumnReverse,
      YGFlexDirectionRow,
      YGFlexDirectionRowReverse,
  });
}

void FillFuzzedTree(
    FuzzedDataProvider& fdp,
    const YGConfigRef& config,
    const YGNodeRef& root,
    size_t depth = 0) {
  constexpr size_t kMaxDepth = 20;
  constexpr size_t kMaxChildren = 20;

  if (depth > kMaxDepth) {
    return;
  }

  size_t children = fdp.ConsumeIntegralInRange<size_t>(0, kMaxChildren);
  for (size_t i = 0; i < children; i++) {
    const YGNodeRef child = YGNodeNewWithConfig(config);
    YGNodeStyleSetFlexDirection(root, fuzzed_flex_direction(fdp));
    YGNodeStyleSetWidth(child, fdp.ConsumeFloatingPoint<float>());
    YGNodeStyleSetGap(
        child, YGGutterAll, fdp.ConsumeProbability<float>() * 100);
    YGNodeStyleSetHeight(child, fdp.ConsumeFloatingPoint<float>());
    YGNodeInsertChild(root, child, i);
    FillFuzzedTree(fdp, config, child, depth + 1);
  }
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  const YGConfigRef config = YGConfigNew();
  const YGNodeRef root = YGNodeNewWithConfig(config);
  FillFuzzedTree(fdp, config, root);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  YGNodeFreeRecursive(root);
  YGConfigFree(config);
  return 0;
}
