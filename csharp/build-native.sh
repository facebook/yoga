#!/bin/sh
# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cd `dirname "$0"`
echo $ANDROID_SDK
BUCK_RELEASE=2018.02.16.01
echo "buck $BUCK_RELEASE"
BUCK=lib/buck-$BUCK_RELEASE/bin/buck
if $BUCK --version >/dev/null 2>&1; then true; else
    echo "Building Buck!"
    BUCK_PATH=buck-$BUCK_RELEASE
    mkdir -p lib
    cd lib
    rm -f $BUCK_PATH.tar.gz
    curl -O -J -L https://github.com/facebook/buck/archive/v$BUCK_RELEASE.tar.gz
    tar xzf $BUCK_PATH.tar.gz
    cd $BUCK_PATH
    ant
    cd ../..
fi

$BUCK build \
    //csharp:yoganet-ios \
    //csharp:yoganet-macosx \
    //csharp:yoganet#android-armv7,shared \
    //csharp:yoganet#android-x86,shared
