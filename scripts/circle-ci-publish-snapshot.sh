#!/usr/bin/env bash
#
# Deploy a SNAPSHOT JAR after every successful Circle CI To Sonatype.
# See https://circleci.com/docs/1.0/environment-variables/
#

set -e

BASEDIR="$(readlink -m "$(dirname "$0")/..")"
IS_SNAPSHOT="$(grep 'VERSION_NAME=[0-9\.]\+-SNAPSHOT' "$BASEDIR/gradle.properties")"

if [ "$TRAVIS_REPO_SLUG" != "facebook/yoga" ]; then
  echo "Skipping repository. Expected project to be 'facebook/yoga', but was '$TRAVIS_REPO_SLUG'."
  exit
elif [ "$TRAVIS_BRANCH" != "master" ]; then
  echo "Skipping build. Expected branch name to be 'master', but was '$TRAVIS_BRANCH'."
  exit
elif [ "$TRAVIS_PULL_REQUEST" != "false" ]; then
  echo "Skipping build. Only considering non-PR builds, but URL was '$TRAVIS_PULL_REQUEST'."
  exit
elif [ "$IS_SNAPSHOT" == "" ]; then
  echo "Skipping build. Given build doesn't appear to be a SNAPSHOT release."
else
  "$BASEDIR/gradlew" uploadArchives
fi
