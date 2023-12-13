/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import * as fs from 'node:fs/promises';
import {format} from 'node:util';
import {parse, dirname} from 'path';
import * as process from 'node:process';
import {Builder, logging} from 'selenium-webdriver';
import {Options} from 'selenium-webdriver/chrome.js';
import {fileURLToPath} from 'url';

const options = new Options();
options.addArguments(
  '--force-device-scale-factor=1',
  '--window-position=0,0',
  '--hide-scrollbars',
);
options.setLoggingPrefs({
  browser: 'ALL',
  performance: 'ALL',
});
const driver = await new Builder()
  .forBrowser('chrome')
  .setChromeOptions(options)
  .build();

const gentestDir = dirname(fileURLToPath(import.meta.url));
const yogaDir = dirname(gentestDir);

const fixtures = await fs.readdir(`${gentestDir}/fixtures`);
for (const fileName of fixtures) {
  const fixture = await fs.readFile(
    `${gentestDir}/fixtures/${fileName}`,
    'utf8',
  );
  const fileNameNoExtension = parse(fileName).name;
  console.log('Generate', fileNameNoExtension);

  // TODO: replace this with something more robust than just blindly replacing
  // start/end in the entire fixture
  const ltrFixture = fixture
    .replaceAll('start', 'left')
    .replaceAll('end', 'right')
    .replaceAll('flex-left', 'flex-start')
    .replaceAll('flex-right', 'flex-end');

  const rtlFixture = fixture
    .replaceAll('start', 'right')
    .replaceAll('end', 'left')
    .replaceAll('flex-right', 'flex-start')
    .replaceAll('flex-left', 'flex-end');

  const template = await fs.readFile(
    `${gentestDir}/test-template.html`,
    'utf8',
  );
  const f = await fs.open(`${gentestDir}/test.html`, 'w');
  await f.write(
    format(template, fileNameNoExtension, ltrFixture, rtlFixture, fixture),
  );
  await f.close();

  await driver.get('file://' + process.cwd() + '/test.html');
  const logs = await driver.manage().logs().get(logging.Type.BROWSER);

  await fs.writeFile(
    `${yogaDir}/tests/generated/${fileNameNoExtension}.cpp`,
    JSON.parse(logs[0].message.replace(/^[^"]*/, '')),
  );

  await fs.writeFile(
    `${yogaDir}/java/tests/com/facebook/yoga/${fileNameNoExtension}.java`,
    JSON.parse(logs[1].message.replace(/^[^"]*/, '')).replace(
      'YogaTest',
      fileNameNoExtension,
    ),
  );

  await fs.writeFile(
    `${yogaDir}/javascript/tests/generated/${fileNameNoExtension}.test.ts`,
    JSON.parse(logs[2].message.replace(/^[^"]*/, '')).replace(
      'YogaTest',
      fileNameNoExtension,
    ),
  );
}
await fs.unlink(`${gentestDir}/test.html`);
await driver.quit();
