/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <nbind/api.h>
#include <nbind/BindDefiner.h>

struct Size {
  double width;
  double height;

  Size(void) : width(0.0), height(0.0) {}

  Size(double width, double height) : width(width), height(height) {}

  void toJS(nbind::cbOutput expose) const {
    expose(width, height);
  }
};
