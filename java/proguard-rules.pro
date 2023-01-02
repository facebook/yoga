# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

-keep,allowobfuscation @interface com.facebook.yoga.annotations.DoNotStrip
-keep,allowobfuscation @interface com.facebook.yoga.annotations.DoNotStripAny

# Do not strip any method/class that is annotated with @DoNotStrip
-keep @com.facebook.yoga.annotations.DoNotStrip class *
-keepclassmembers class * {
    @com.facebook.yoga.annotations.DoNotStrip *;
}
