/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <yoga/YGMacros.h>

YG_EXTERN_C_BEGIN

/**
 * Structure used to represent a calc() expression with mixed units.
 */
typedef struct YGCalc {
  float px;
  float percent;
  float vw;
  float vh;
} YGCalc;

YG_EXTERN_C_END
