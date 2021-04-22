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

#include "../UIView+Yoga.h"
#include "../YGLayout.h"

FOUNDATION_EXPORT double YogaKitVersionNumber;
FOUNDATION_EXPORT const unsigned char YogaKitVersionString[];

