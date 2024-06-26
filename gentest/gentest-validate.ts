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
import {glob} from 'glob';

const yogaRootDir = dirname(dirname(fileURLToPath(import.meta.url)));

const filesToValidate = await glob(
  [
    'tests/generated/**/*.{h,cpp}',
    'javascript/tests/generated/**/*.test.ts',
    'java/tests/generated/com/facebook/yoga/**/*.java',
  ],
  {
    cwd: yogaRootDir,
  },
);

console.log(`Found ${filesToValidate.length} files to validate`);

for (const file of filesToValidate) {
  const content = await fs.readFile(`${yogaRootDir}/${file}`, 'utf8');
  if (signedsource.isSigned(content)) {
    console.log(`Checking ${file}`);
    const validSignature = signedsource.verifySignature(content);
    if (!validSignature) {
      console.error(`Invalid signature "${file}"`);
      process.exitCode = 1;
    }
  } else {
    console.log(`Skipped ${file}`);
  }
}
