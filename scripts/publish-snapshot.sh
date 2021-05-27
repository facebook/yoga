#!/usr/bin/env bash
#
# Deploy a SNAPSHOT JAR after every successful CI run To Sonatype.

#
#  Copyright (c) Facebook, Inc. and its affiliates.
#
#  This source code is licensed under the MIT license found in the LICENSE
#  file in the root directory of this source tree.
#

set -e

BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." && pwd )"
IS_SNAPSHOT="$(grep 'VERSION_NAME=[0-9\.]\+-SNAPSHOT' "$BASEDIR/gradle.properties")"

if [ "$IS_SNAPSHOT" == "" ]; then
  echo >&2 "Skipping build. Given build doesn't appear to be a SNAPSHOT release."
else
  env TERMINAL=dumb "$BASEDIR/gradlew" publish
fi
