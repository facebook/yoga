#!/bin/bash

buck build //android:android

X86_DEST=build/buck-out/jniLibs/x86
ARMV7_DEST=build/buck-out/jniLibs/armeabi-v7a

mkdir -p $X86_DEST
mkdir -p $ARMV7_DEST

cp ../buck-out/gen/java/jni#ARMV7,android-armv7,android-strip,libyoga.so,shared/libyoga.so $ARMV7_DEST
cp ../buck-out/gen/java/jni#X86,android-strip,android-x86,libyoga.so,shared/libyoga.so $X86_DEST

cp ../buck-out/gen/yoga#ARMV7,android-armv7,android-strip,libyogacore.so,shared/libyogacore.so $ARMV7_DEST
cp ../buck-out/gen/yoga#X86,android-strip,android-x86,libyogacore.so,shared/libyogacore.so $X86_DEST

cp ../buck-out/gen/lib/fb/fbjni#ARMV7,android-armv7,android-strip,liblib_fb_fbjni.so,shared/liblib_fb_fbjni.so $ARMV7_DEST
cp ../buck-out/gen/lib/fb/fbjni#X86,android-strip,android-x86,liblib_fb_fbjni.so,shared/liblib_fb_fbjni.so $X86_DEST

cp ../buck-out/gen/android/android#ARMV7,android-strip,libgnustl_shared.so/libgnustl_shared.so $ARMV7_DEST
cp ../buck-out/gen/android/android#X86,android-strip,libgnustl_shared.so/libgnustl_shared.so $X86_DEST
