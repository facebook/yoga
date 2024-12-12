/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "TestUtil.h"

#include <yoga/YGEnums.h>
#include <yoga/YGNode.h>
#include <yoga/event/event.h>
#include <yoga/node/Node.h>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

namespace facebook::yoga::test {

int nodeInstanceCount = 0;

namespace {

void yogaEventSubscriber(
    YGNodeConstRef /*node*/,
    Event::Type eventType,
    const Event::Data& /*eventData*/) {
  switch (eventType) {
    case Event::NodeAllocation:
      nodeInstanceCount++;
      break;
    case Event::NodeDeallocation:
      nodeInstanceCount--;
      break;
    default:
      break;
  }
}
} // namespace

void TestUtil::startCountingNodes() {
  nodeInstanceCount = 0;
  Event::subscribe(yogaEventSubscriber);
}

int TestUtil::nodeCount() {
  return nodeInstanceCount;
}

int TestUtil::stopCountingNodes() {
  Event::reset();
  auto prev = nodeInstanceCount;
  nodeInstanceCount = 0;
  return prev;
}

ScopedEventSubscription::ScopedEventSubscription(
    std::function<Event::Subscriber>&& s) {
  Event::subscribe(std::move(s));
}

ScopedEventSubscription::~ScopedEventSubscription() {
  Event::reset();
}

YGSize IntrinsicSizeMeasure(
    YGNodeConstRef node,
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode) {
  std::string_view innerText((char*)YGNodeGetContext(node));
  float heightPerChar = 10;
  float widthPerChar = 10;
  float measuredWidth;
  float measuredHeight;

  if (widthMode == YGMeasureModeExactly) {
    measuredWidth = width;
  } else if (widthMode == YGMeasureModeAtMost) {
    measuredWidth = std::min((float)innerText.size() * widthPerChar, width);
  } else {
    measuredWidth = (float)innerText.size() * widthPerChar;
  }

  if (heightMode == YGMeasureModeExactly) {
    measuredHeight = height;
  } else if (heightMode == YGMeasureModeAtMost) {
    measuredHeight = std::min(
        calculateHeight(
            innerText,
            YGNodeStyleGetFlexDirection(node) == YGFlexDirectionColumn
                ? measuredWidth
                : std::max(
                      longestWordWidth(innerText, widthPerChar), measuredWidth),
            widthPerChar,
            heightPerChar),
        height);
  } else {
    measuredHeight = calculateHeight(
        innerText,
        YGNodeStyleGetFlexDirection(node) == YGFlexDirectionColumn
            ? measuredWidth
            : std::max(
                  longestWordWidth(innerText, widthPerChar), measuredWidth),
        widthPerChar,
        heightPerChar);
  }

  return YGSize{measuredWidth, measuredHeight};
}

float longestWordWidth(std::string_view text, float widthPerChar) {
  int maxLength = 0;
  int currentLength = 0;
  for (auto c : text) {
    if (c == ' ') {
      maxLength = std::max(currentLength, maxLength);
      currentLength = 0;
    } else {
      currentLength++;
    }
  }
  return (float)std::max(currentLength, maxLength) * widthPerChar;
}

float calculateHeight(
    std::string_view text,
    float measuredWidth,
    float widthPerChar,
    float heightPerChar) {
  if ((float)text.size() * widthPerChar <= measuredWidth) {
    return heightPerChar;
  }

  std::vector<std::string> words;
  std::istringstream iss((std::string)text);
  std::string currentWord;
  while (getline(iss, currentWord, ' ')) {
    words.push_back(currentWord);
  }

  float lines = 1;
  float currentLineLength = 0;
  for (const std::string& word : words) {
    float wordWidth = (float)word.length() * widthPerChar;
    if (wordWidth > measuredWidth) {
      if (currentLineLength > 0) {
        lines++;
      }
      lines++;
      currentLineLength = 0;
    } else if (currentLineLength + wordWidth <= measuredWidth) {
      currentLineLength += wordWidth + widthPerChar;
    } else {
      lines++;
      currentLineLength = wordWidth + widthPerChar;
    }
  }
  return (currentLineLength == 0 ? lines - 1 : lines) * heightPerChar;
}

} // namespace facebook::yoga::test
