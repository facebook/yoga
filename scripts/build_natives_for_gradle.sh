#!/bin/bash

set -e
BASEDIR=$(dirname $0)

DESTINATIONS=(
  "build/buck-out/jniLibs/x86"
  "build/buck-out/jniLibs/x86_64"
  "build/buck-out/jniLibs/armeabi-v7a"
  "build/buck-out/jniLibs/arm64-v8a"
)

BUCK_TARGETS=(
  "android-x86"
  "android-x86_64"
  "android-armv7"
  "android-arm64"
)

for (( i=0; i<4; i++ ));
do
  mkdir -p "${DESTINATIONS[i]}"
done

# There must be a better way to get gnustl_shared than building the android target.
# But for now, we include that target simply for that shared library...
echo "Build libgnustl_shared.so"
buck build //android/sample:sample

cp "$BASEDIR/../buck-out/gen/android/sample/sample#X86,android-strip,libgnustl_shared.so/libgnustl_shared.so" "${DESTINATIONS[0]}"
cp "$BASEDIR/../buck-out/gen/android/sample/sample#X86_64,android-strip,libgnustl_shared.so/libgnustl_shared.so" "${DESTINATIONS[1]}"
cp "$BASEDIR/../buck-out/gen/android/sample/sample#ARMV7,android-strip,libgnustl_shared.so/libgnustl_shared.so" "${DESTINATIONS[2]}"
cp "$BASEDIR/../buck-out/gen/android/sample/sample#ARM64,android-strip,libgnustl_shared.so/libgnustl_shared.so" "${DESTINATIONS[3]}"

# This is to clean up after the mess above.  Yes, it is required.
buck clean
rm -r "$BASEDIR/../buck-out"

for (( i=0; i<4; i++ ));
do
  echo "Build ${BUCK_TARGETS[i]}"
  buck build "//java:jni#${BUCK_TARGETS[i]},shared"
  cp "$BASEDIR/../buck-out/gen/java/jni#${BUCK_TARGETS[i]},shared/libyoga.so" "${DESTINATIONS[i]}"
  cp "$BASEDIR/../buck-out/gen/yoga#${BUCK_TARGETS[i]},shared/libyogacore.so" "${DESTINATIONS[i]}"
  cp "$BASEDIR/../buck-out/gen/lib/fb/fbjni#${BUCK_TARGETS[i]},shared/liblib_fb_fbjni.so" "${DESTINATIONS[i]}"
done
