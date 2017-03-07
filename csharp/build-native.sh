#!/bin/sh
echo $ANDROID_SDK
if buck --version >/dev/null 2>&1; then true; else
    echo "Building Buck!"
    mkdir lib
    cd lib
    git clone https://github.com/facebook/buck.git --depth 1
    cd buck
    ant
    cd ..
    cd ..
fi
buck build //:yoga
buck build //csharp:yoganet-ios
buck build //csharp:yoganet-macosx
buck build //csharp:yoganet#android-x86,shared
buck build //csharp:yoganet#android-armv7,shared