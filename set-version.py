#!/usr/bin/env python3
# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

import os
import re
import sys

os.chdir(os.path.dirname(__file__))

if len(sys.argv) != 2:
    print("usage: ./set-version <version>", file=sys.stderr)
    sys.exit(1)

version = sys.argv[1]

with open("gradle.properties", "r+") as f:
    new_contents = re.sub(r"VERSION_NAME=.*", f"VERSION_NAME={version}", f.read())
    f.seek(0)
    f.truncate()
    f.write(new_contents)

with open("javascript/package.json", "r+") as f:
    new_contents = re.sub(r'"version": ".*",', f'"version": "{version}",', f.read())
    f.seek(0)
    f.truncate()
    f.write(new_contents)

with open("website-next/package.json", "r+") as f:
    new_contents = re.sub(
        r'"yoga-layout": ".*"', f'"yoga-layout": "{version}"', f.read()
    )
    f.seek(0)
    f.truncate()
    f.write(new_contents)

with open("Yoga.podspec", "r+") as f:
    new_contents = re.sub(
        r"spec\.version = '.*'", f"spec.version = '{version}'", f.read()
    )
    f.seek(0)
    f.truncate()
    f.write(new_contents)
