/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include <yoga/Yoga.h>

#include "./Node.hh"
#include "./Layout.hh"
#include "./Size.hh"
#include "./global.hh"

#define NBIND_DUPLICATE_POINTERS true

#include <nbind/nbind.h>

NBIND_GLOBAL()
{
    function(setExperimentalFeatureEnabled);
    function(isExperimentalFeatureEnabled);
    function(getInstanceCount);
}

NBIND_CLASS(Size)
{
    construct<>();
    construct<double, double>();
}

NBIND_CLASS(Layout)
{
    construct<>();
}

NBIND_CLASS(Node)
{
    method(create);
    method(destroy);

    method(reset);

    method(copyStyle);

    method(setPositionType);
    method(setPosition);

    method(setAlignContent);
    method(setAlignItems);
    method(setAlignSelf);
    method(setFlexDirection);
    method(setFlexWrap);
    method(setJustifyContent);

    method(setMargin);

    method(setOverflow);

    method(setFlex);
    method(setFlexBasis);
    method(setFlexGrow);
    method(setFlexShrink);

    method(setWidth);
    method(setHeight);

    method(setMinWidth);
    method(setMinHeight);

    method(setMaxWidth);
    method(setMaxHeight);

    method(setAspectRatio);

    method(setBorder);

    method(setPadding);

    method(getPositionType);
    method(getPosition);

    method(getAlignContent);
    method(getAlignItems);
    method(getAlignSelf);
    method(getFlexDirection);
    method(getFlexWrap);
    method(getJustifyContent);

    method(getMargin);

    method(getFlexBasis);
    method(getFlexGrow);
    method(getFlexShrink);

    method(getWidth);
    method(getHeight);

    method(getMinWidth);
    method(getMinHeight);

    method(getMaxWidth);
    method(getMaxHeight);

    method(getAspectRatio);

    method(getBorder);

    method(getPadding);

    method(insertChild);
    method(removeChild);

    method(getChildCount);

    method(getParent);
    method(getChild);

    method(setMeasureFunc);
    method(unsetMeasureFunc);

    method(markDirty);
    method(isDirty);

    method(calculateLayout);

    method(getComputedLeft);
    method(getComputedRight);

    method(getComputedTop);
    method(getComputedBottom);

    method(getComputedWidth);
    method(getComputedHeight);

    method(getComputedLayout);
}
