#!/bin/sh
# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

if mcs --version >/dev/null 2>&1 && mono --version >/dev/null 2>&1; then true; else
  echo "ERROR: Need to install Mono (brew install mono, or http://www.mono-project.com/download/)"
  exit 1
fi

cd "$( dirname "$0" )"

NUNIT=NUnit-2.6.4/bin
if [ -d $NUNIT \
    -a -f $NUNIT/nunit-console.exe \
    -a -f $NUNIT/lib/nunit-console-runner.dll \
    -a -f $NUNIT/lib/nunit.core.dll \
    -a -f $NUNIT/lib/nunit.core.interfaces.dll \
    -a -f $NUNIT/lib/nunit.util.dll ]; then true; else
  curl -L -O https://github.com/nunit/nunitv2/releases/download/2.6.4/NUnit-2.6.4.zip
  unzip -qq NUnit-2.6.4.zip
  rm NUnit-2.6.4.zip
fi

TARGET=//csharp:yoganet#default,shared
buck build $TARGET
ROOT=`buck root|tail -1`
DYLIB=`buck targets --show-output $TARGET|tail -1|awk '{print $2}'`
cp $ROOT/$DYLIB .

mcs -debug -d:YOGA_ENABLE_GC_TEST -t:library -r:$NUNIT/nunit.framework.dll -out:YogaTest.dll *.cs ../../../csharp/Facebook.Yoga/*cs
MONO_PATH=$NUNIT mono --arch=64 --debug $NUNIT/nunit-console.exe YogaTest.dll
