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

struct Layout
{
    double left;
    double right;

    double top;
    double bottom;

    double width;
    double height;

    void toJS(nbind::cbOutput expose) const
    {
        expose(left, right, top, bottom, width, height);
    }
};
