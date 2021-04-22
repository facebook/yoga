#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#include "../YGEnums.h"
#include "../YGMacros.h"
#include "../YGValue.h"
#include "../Yoga.h"

FOUNDATION_EXPORT double yogaVersionNumber;
FOUNDATION_EXPORT const unsigned char yogaVersionString[];

