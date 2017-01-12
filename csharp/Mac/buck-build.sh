#!/bin/sh
if buck --version >/dev/null 2>&1; then true; else
  echo "SKIP: Need to install buck https://buckbuild.com/setup/getting_started.html"
  exit 0
fi
buck build $1
