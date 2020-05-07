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

if [ "$GITHUB_REPOSITORY" != "facebook/yoga" ]; then
  echo >&2 "Skipping repository. Expected project to be 'facebook/yoga', but was '$GITHUB_REPOSITORY'."
  exit
elif [ "$GITHUB_REF" != "refs/heads/master" ]; then
  echo >&2 "Skipping build. Expected ref name to be 'refs/heads/master', but was '$GITHUB_REF'."
  exit
elif [ "$GITHUB_EVENT_NAME" != "push" ]; then
  echo >&2 "Skipping build. Only considering push builds, but event was '$GITHUB_EVENT_NAME'."
  exit
elif [ "$IS_SNAPSHOT" == "" ]; then
  echo >&2 "Skipping build. Given build doesn't appear to be a SNAPSHOT release."
else
  env TERMINAL=dumb "$BASEDIR/gradlew" uploadArchives
fi
