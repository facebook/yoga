#!/bin/sh
# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

set -e

cd "$( dirname "$0" )"

if [ \! -f yoga.dll ]; then
  echo "Launch win.bat on Windows and copy yoga.dll to here"
  exit 1
fi

function build {
  buck build $1
  echo "$root/`buck targets --show-output $1|tail -1|awk '{print $2}'`"
}

function copy {
  mkdir -p $3
  cp $1 $3/$2
}

rm -rf Yoga yoga.unitypackage

root=`buck root|tail -f`
mac=$(build '//csharp:yoganet#default,shared')
armv7=$(build '//csharp:yoganet#android-armv7,shared')
ios=$(build '//csharp:yoganet-ios')
win=yoga.dll

Unity -quit -batchMode -createProject Yoga

copy $win ${win##*/} Yoga/Assets/Facebook.Yoga/Plugins/x86_64
copy $mac yoga Yoga/Assets/Facebook.Yoga/Plugins/x86_64/yoga.bundle/Contents/MacOS
armv7path=Assets/Plugins/Android/libs/armeabi-v7a
copy $armv7 ${armv7##*/} Yoga/$armv7path
iospath=Assets/Plugins/iOS
copy $ios ${ios##*/} Yoga/$iospath
libs="$armv7path/${armv7##*/} $iospath/${ios##*/}"

scripts=Yoga/Assets/Facebook.Yoga/Scripts/Facebook.Yoga
mkdir -p $scripts
(cd ../Facebook.Yoga; tar cf - *.cs)|tar -C $scripts -xf -

tests=Yoga/Assets/Facebook.Yoga/Editor/Facebook.Yoga.Tests
mkdir -p $tests
(cd ../tests/Facebook.Yoga; tar cf - *.cs)|tar -C $tests -xf -

function onerror {
  local xml=Yoga/EditorTestResults.xml
  if [ -f $xml ]; then cat $xml|grep 'success="False"'; fi
}
trap onerror EXIT
Unity -quit -batchMode -projectPath `pwd`/Yoga -runEditorTests

pkg="`pwd`/yoga.unitypackage"
Unity -quit -batchMode -projectPath `pwd`/Yoga -exportPackage Assets/Facebook.Yoga $libs $pkg

echo "Success: $pkg"
