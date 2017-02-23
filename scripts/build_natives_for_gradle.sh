#!/bin/bash

buck build //android:android

X86_DEST=build/buck-out/jniLibs/x86
ARMV7_DEST=build/buck-out/jniLibs/armabi-v7a

mkdir -p $X86_DEST
mkdir -p $ARMV7_DEST

cp ../buck-out/gen/java/jni#android-armv7,shared/libyoga.so $ARMV7_DEST
cp ../buck-out/gen/java/jni#android-x86,shared/libyoga.so $X86_DEST 

cp ../buck-out/gen/yoga#android-armv7,shared/libyogacore.so $ARMV7_DEST
cp ../buck-out/gen/yoga#android-x86,shared/libyogacore.so $X86_DEST

