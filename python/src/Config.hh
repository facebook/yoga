/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <memory>
#include <yoga/Yoga.h>

class Config : public std::enable_shared_from_this<Config> {

  friend class Node;

public:
  Config(void);
  ~Config(void);

public: // Prevent accidental copy
  Config(Config const&) = delete;

  Config const& operator=(Config const&) = delete;

public: // Setters
  void setExperimentalFeatureEnabled(int feature, bool enabled);
  void setPointScaleFactor(float pixelsInPoint);
  void setUseLegacyStretchBehaviour(bool useLegacyStretchBehaviour);
  void setUseWebDefaults(bool useWebDefaults);

public: // Getters
  bool isExperimentalFeatureEnabled(int feature) const;
  bool useLegacyStretchBehaviour();
  bool useWebDefaults();

private:
  YGConfigRef m_config;
};
