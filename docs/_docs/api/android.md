---
docid: android
title: Android
layout: docs
permalink: /docs/api/android/
---

There is an easy interface to Yoga called `YogaLayout`.  This is a view group that lays out its children using Yoga.  We recommend looking at the sample app for details on its usage.  However, as an overview you can simply define XML layouts such as

<script src="https://gist.github.com/rspencer01/c1964b98f0c60de7c49683a049ed0640.js"></script>

Note that there are some caveats, such as requiring the custom `YogaLayoutViewFactory` in order to have tags `YogaLayout` instead of `com.facebook.samples.yoga.YogaLayout`.

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
