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
import * as path from 'path';
import * as process from 'node:process';
import {Builder, logging} from 'selenium-webdriver';
import {Options} from 'selenium-webdriver/chrome.js';
import {stdin, stdout} from 'node:process';
import minimist from 'minimist';
import readline from 'node:readline/promises';
import signedsource from 'signedsource';

function signFile(fileData: string) {
  let signedFile = fileData.replace(
    'MAGIC_PLACEHOLDER',
    signedsource.getSigningToken(),
  );
  signedFile = signedsource.signFile(signedFile);

  return signedFile;
}

process.chdir(path.dirname(process.argv[1]));

const argv = minimist(process.argv.slice(2));
const specificFixture = argv.f || argv.fixture;
const suspend = argv.s || argv.suspend;

let fixtures = await fs.readdir('./fixtures');
try {
  if (specificFixture != undefined) {
    await fs.access(`fixtures/${specificFixture}.html`, fs.constants.F_OK);
    fixtures = [specificFixture + '.html'];
  }
} catch {
  console.log(
    `NOTE: ${specificFixture}.html does not exist. Executing against all fixtures.`,
  );
}

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

for (const fileName of fixtures) {
  const fixture = await fs.readFile('fixtures/' + fileName, 'utf8');
  const fileNameNoExtension = path.parse(fileName).name;
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

  const template = await fs.readFile('test-template.html', 'utf8');
  const f = await fs.open('test.html', 'w');
  await f.write(
    format(template, fileNameNoExtension, ltrFixture, rtlFixture, fixture),
  );
  await f.close();

  await driver.get('file://' + process.cwd() + '/test.html');
  const logs = await driver.manage().logs().get(logging.Type.BROWSER);

    await fs.writeFile(
      `../tests/generated/${fileNameNoExtension}.cpp`,
      signFile(eval(logs[0].message.replace(/^[^"]*/, ''))),
    );

    await fs.writeFile(
      `../java/tests/com/facebook/yoga/${fileNameNoExtension}.java`,
      signFile(
        eval(logs[1].message.replace(/^[^"]*/, '')).replace(
          'YogaTest',
          fileNameNoExtension,
        ),
      ),
    );

    await fs.writeFile(
      `../javascript/tests/generated/${fileNameNoExtension}.test.ts`,
      signFile(
        eval(logs[2].message.replace(/^[^"]*/, '')).replace(
          'YogaTest',
          fileNameNoExtension,
        ),
      ),
    );

  if (suspend) {
    const rl = readline.createInterface({input: stdin, output: stdout});
    await rl.question('');
    rl.close();
  }
}
await fs.unlink('test.html');
await driver.quit();
