/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import * as fs from 'node:fs/promises';
import {dirname} from 'path';
import {fileURLToPath} from 'url';
import signedsource from 'signedsource';

const yogaDir = dirname(dirname(fileURLToPath(import.meta.url)));
const cppTestDir = `${yogaDir}/tests/generated`;
const jsTestDir = `${yogaDir}/javascript/tests/generated`;
const javaTestDir = `${yogaDir}/java/tests/com/facebook/yoga`;
const testDirs = [cppTestDir, jsTestDir, javaTestDir];

for (const testDir of testDirs) {
  const tests = await fs.readdir(testDir);

  for (const test of tests) {
    const testData = await fs.readFile(`${testDir}/${test}`, 'utf8');
    try {
      const validSignature = signedsource.verifySignature(testData);
      if (!validSignature) {
        console.error(`Invalid signature for ${test}`);
        process.exitCode = 1;
      }
    } catch (e) {
      // Java test dir does not separate generated tests from non-generated ones
      if (testDir != javaTestDir) {
        console.error(`${test}: ${e}`);
        process.exitCode = 1;
      }
    }
  }
}
