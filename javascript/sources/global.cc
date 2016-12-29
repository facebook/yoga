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
