#pragma once

#include <nbind/api.h>
#include <nbind/BindDefiner.h>

struct Size
{
    double width;
    double height;

    void toJS(nbind::cbOutput expose) const
    {
        expose(width, height);
    }
};
