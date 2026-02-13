/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <yoga/Yoga.h>
#include <yoga/debug/AssertFatal.h>
#include <yoga/debug/Log.h>

using namespace facebook;
using namespace facebook::yoga;

YGConfigRef YGConfigNew(void) {
  return new yoga::Config(getDefaultLogger());
}

void YGConfigFree(const YGConfigRef config) {
  delete resolveRef(config);
}

YGConfigConstRef YGConfigGetDefault() {
  return &yoga::Config::getDefault();
}

void YGConfigSetUseWebDefaults(const YGConfigRef config, const bool enabled) {
  resolveRef(config)->setUseWebDefaults(enabled);
}

bool YGConfigGetUseWebDefaults(const YGConfigConstRef config) {
  return resolveRef(config)->useWebDefaults();
}

void YGConfigSetPointScaleFactor(
    const YGConfigRef config,
    const float pixelsInPoint) {
  yoga::assertFatalWithConfig(
      resolveRef(config),
      pixelsInPoint >= 0.0f,
      "Scale factor should not be less than zero");

  resolveRef(config)->setPointScaleFactor(pixelsInPoint);
}

float YGConfigGetPointScaleFactor(const YGConfigConstRef config) {
  return resolveRef(config)->getPointScaleFactor();
}

void YGConfigSetViewportWidth(
    const YGConfigRef config,
    const float viewportWidth) {
  yoga::assertFatalWithConfig(
      resolveRef(config),
      viewportWidth >= 0.0f,
      "Viewport width should not be less than zero");

  resolveRef(config)->setViewportWidth(viewportWidth);
}

float YGConfigGetViewportWidth(const YGConfigConstRef config) {
  return resolveRef(config)->getViewportWidth();
}

void YGConfigSetViewportHeight(
    const YGConfigRef config,
    const float viewportHeight) {
  yoga::assertFatalWithConfig(
      resolveRef(config),
      viewportHeight >= 0.0f,
      "Viewport height should not be less than zero");

  resolveRef(config)->setViewportHeight(viewportHeight);
}

float YGConfigGetViewportHeight(const YGConfigConstRef config) {
  return resolveRef(config)->getViewportHeight();
}

void YGConfigSetErrata(YGConfigRef config, YGErrata errata) {
  resolveRef(config)->setErrata(scopedEnum(errata));
}

YGErrata YGConfigGetErrata(YGConfigConstRef config) {
  return unscopedEnum(resolveRef(config)->getErrata());
}

void YGConfigSetLogger(const YGConfigRef config, YGLogger logger) {
  if (logger != nullptr) {
    resolveRef(config)->setLogger(logger);
  } else {
    resolveRef(config)->setLogger(getDefaultLogger());
  }
}

void YGConfigSetContext(const YGConfigRef config, void* context) {
  resolveRef(config)->setContext(context);
}

void* YGConfigGetContext(const YGConfigConstRef config) {
  return resolveRef(config)->getContext();
}

void YGConfigSetExperimentalFeatureEnabled(
    const YGConfigRef config,
    const YGExperimentalFeature feature,
    const bool enabled) {
  resolveRef(config)->setExperimentalFeatureEnabled(
      scopedEnum(feature), enabled);
}

bool YGConfigIsExperimentalFeatureEnabled(
    const YGConfigConstRef config,
    const YGExperimentalFeature feature) {
  return resolveRef(config)->isExperimentalFeatureEnabled(scopedEnum(feature));
}

void YGConfigSetCloneNodeFunc(
    const YGConfigRef config,
    const YGCloneNodeFunc callback) {
  resolveRef(config)->setCloneNodeCallback(callback);
}
