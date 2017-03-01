/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#pragma once

#include <nbind/api.h>
#include <nbind/BindDefiner.h>
#include <yoga/Yoga.h>

class Config {
private:
  YGConfigRef m_config;

  Config(void)
  : m_config(YGConfigNew())
  {}

public:

  static Config * create(void)
  {
    return new Config();
  }

  static void destroy(Config * config)
  {
    delete config;
  }

  ~Config(void)
  {
    YGConfigFree(m_config);
  }

  void setExperimentalFeatureEnabled(int feature, bool enabled)
  {
    YGConfigSetExperimentalFeatureEnabled(m_config, static_cast<YGExperimentalFeature>(feature), enabled);
  }

  Config(Config const &) = delete;

  Config const & operator=(Config const &) = delete;
};
