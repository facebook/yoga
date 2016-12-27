#pragma once

#include <nbind/api.h>
#include <nbind/BindDefiner.h>

struct Size
{
    double width;
    double height;

    Size(void)
    : width(0.0)
    , height(0.0)
    {
    }

    Size(double width, double height)
    : width(width)
    , height(height)
    {
    }

    void toJS(nbind::cbOutput expose) const
    {
        expose(width, height);
    }
};
