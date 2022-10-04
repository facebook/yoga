/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <nbind/api.h>
#include <nbind/BindDefiner.h>

struct Layout {
  double left;
  double right;

  double top;
  double bottom;

  double width;
  double height;

  void toJS(nbind::cbOutput expose) const {
    expose(left, right, top, bottom, width, height);
  }
};
