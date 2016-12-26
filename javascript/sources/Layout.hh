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
