#pragma once

#include <yoga/Yoga.h>

struct Value
{
    static Value fromYGValue(YGValue const & ygValue)
    {
        return Value(static_cast<int>(ygValue.unit), ygValue.value);
    }

    int unit;
    double value;

    Value(void)
    : unit(YGUnitUndefined)
    , value(0.0)
    {
    }

    Value(int unit, double value)
    : unit(unit)
    , value(value)
    {
    }

    void toJS(nbind::cbOutput expose) const
    {
        expose(unit, value);
    }
};
