/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <yoga/Yoga.h>

#include "./Config.h"

/* static */ Config* Config::create(void) {
  return new Config();
}

/* static */ void Config::destroy(Config* node) {
  delete node;
}

Config::Config(void) : m_config(YGConfigNew()) {}

Config::~Config(void) {
  YGConfigFree(m_config);
}

void Config::setExperimentalFeatureEnabled(int feature, bool enabled) {
  YGConfigSetExperimentalFeatureEnabled(
      m_config, static_cast<YGExperimentalFeature>(feature), enabled);
}

void Config::setPointScaleFactor(float pixelsInPoint) {
  YGConfigSetPointScaleFactor(m_config, pixelsInPoint);
}

void Config::setUseLegacyStretchBehaviour(bool useLegacyStretchBehaviour) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"
  YGConfigSetUseLegacyStretchBehaviour(m_config, useLegacyStretchBehaviour);
#pragma clang diagnostic pop
}

void Config::setErrata(int errata) {
  YGConfigSetErrata(m_config, static_cast<YGErrata>(errata));
}

void Config::setUseWebDefaults(bool useWebDefaults) {
  YGConfigSetUseWebDefaults(m_config, useWebDefaults);
}

bool Config::isExperimentalFeatureEnabled(int feature) const {
  return YGConfigIsExperimentalFeatureEnabled(
      m_config, static_cast<YGExperimentalFeature>(feature));
}

bool Config::useLegacyStretchBehaviour() const {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"
  return YGConfigGetUseLegacyStretchBehaviour(m_config);
#pragma clang diagnostic pop
}

int Config::getErrata() const {
  return static_cast<int>(YGConfigGetErrata(m_config));
}

bool Config::useWebDefaults() const {
  return YGConfigGetUseWebDefaults(m_config);
}
