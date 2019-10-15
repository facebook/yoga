/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <nbind/api.h>
#include <nbind/BindDefiner.h>
#include <yoga/Yoga.h>

class Config {

  friend class Node;

public:
  static Config* create(void);

  static void destroy(Config* config);

private:
  Config(void);

public:
  ~Config(void);

public: // Prevent accidental copy
  Config(Config const&) = delete;

  Config const& operator=(Config const&) = delete;

public: // Setters
  void setExperimentalFeatureEnabled(int feature, bool enabled);
  void setPointScaleFactor(float pixelsInPoint);

public: // Getters
  bool isExperimentalFeatureEnabled(int feature) const;

private:
  YGConfigRef m_config;
};
