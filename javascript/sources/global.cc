/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include <yoga/Yoga.h>

#include "./global.hh"

void setExperimentalFeatureEnabled(int feature, bool enabled)
{
    YGSetExperimentalFeatureEnabled(static_cast<YGExperimentalFeature>(feature), enabled);
}

bool isExperimentalFeatureEnabled(int feature)
{
    return YGIsExperimentalFeatureEnabled(static_cast<YGExperimentalFeature>(feature));
}

unsigned getInstanceCount(void)
{
    return YGNodeGetInstanceCount();
}
