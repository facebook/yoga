#include <gtest/gtest.h>
#include <yoga/YGNode.h>
#include <iostream>

void CalculateLayout(const YGNodeRef node) {
  void CalculateLayout(const YGNodeRef node) const {
    float parentBaseline = 0;

    for (const YGNodeRef child : node->children) {
      float childBaseline = child->fontSize * child->lineHeight / 2;

      parentBaseline = std::max(parentBaseline, childBaseline);
    }

    for (const YGNodeRef child : node->children) {
      child->layout.top = parentBaseline - child->layout.height / 2;
    }
  }
}
