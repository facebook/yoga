---
docid: android
title: Android
layout: docs
permalink: /docs/api/android/
---

To include the java bindings and `.so` libraries, add to your build:
<script src="https://gist.github.com/rspencer01/e3cb51e789147b359d842aac6fa30f9f.js"></script>

There is an easy interface to Yoga called `YogaLayout`.  This is a view group that lays out its children using Yoga.  We recommend looking at the sample app for details on its usage.  However, as an overview you can simply define XML layouts such as
<script src="https://gist.github.com/rspencer01/c1964b98f0c60de7c49683a049ed0640.js"></script>

Note that there are some caveats, such as requiring the custom `YogaLayoutViewFactory` in order to have tags `YogaLayout` instead of `com.facebook.samples.yoga.YogaLayout`.

To include this in your project, add to your build:
<script src="https://gist.github.com/rspencer01/499a9e02185985bf3167f818d9c3398f.js"></script>

## layout\_width and layout\_height

If either are set to an actual size (in px or dp etc) then this is taken as a default for `yoga:height` or `yoga:width`.  Otherwise they are ignored.

## VirtualYogaLayout

Sometimes you will nest `YogaLayout`s within `YogaLayout`s in order to get your layout to be perfect, but some of the `YogaLayout`s are just there to control position: they don't render or anything.  If so, then they are unnecessary (since Yoga stores the view hierarchy itself) and `VirtualYogaLayout` is a ViewGroup that fixes this.  It will never get drawn, but all its children will be placed appropriately.

## RTL locales

RTL locales are supported by default.  That is, unless you explicitly set the `yoga:direction="ltr|rtl|inherit"` attribute on a view, it will obtain the locale direction _at runtime_.  This means that the layout will rearrange properly, even if the locale changes while your app is running!

## Attributes

The list of all attributes can be found in [attrs.xml](https://github.com/facebook/yoga/blob/master/android/sample/res/com/facebook/samples/yoga/res/values/attrs.xml), but logically map from the Yoga properties.

## Auto margins

You can specify `margin_left="auto"` (or `margin_right` etc.) for auto values.  This is in addition to the dimensions you can speicfy, such as `margin_left="20dp"`.

## Invalidation (_temporary_)

If you change any attribute of a view that will change its measure size, you must invalidate it.  Do this by calling `YogaLayout#invalidate(View)` on any `YogaLayout` further up the tree.  Obviously it is most efficient to call it on the view's parent (if it is a `YogaLayout`, but in case this is impractical, you can call it on the root of the tree.

This is a temporary solution.  Ideally, the view should invalidate itself whenever an attribute (text, font etc.) that will alter its size changes.  This will be automatic once we find a good way to hook into the Android invalidation system.
