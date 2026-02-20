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
import {parse, dirname, relative} from 'path';
import * as process from 'node:process';
import {Builder, logging} from 'selenium-webdriver';
import {Options} from 'selenium-webdriver/chrome.js';
import {fileURLToPath} from 'url';
import {stdin, stdout} from 'node:process';
import minimist from 'minimist';
import readline from 'node:readline/promises';
import signedsource from 'signedsource';
import {glob} from 'glob';

function addSignatureToSourceCode(sourceCode: string): string {
  const codeWithToken = sourceCode.replace(
    'MAGIC_PLACEHOLDER',
    signedsource.getSigningToken(),
  );

  return signedsource.signFile(codeWithToken);
}

const argv = minimist(process.argv.slice(2));
const specificFixture = argv.f || argv.fixture;
const suspend = argv.s || argv.suspend;
const headless = argv.h || argv.headless;

const gentestDir = dirname(fileURLToPath(import.meta.url));
const yogaDir = dirname(gentestDir);
const fixturesDir = `${gentestDir}/fixtures`;

let fixtures: string[];
try {
  if (specificFixture != null) {
    const fixturePath = `${fixturesDir}/${specificFixture}.html`;
    await fs.access(fixturePath, fs.constants.F_OK);
    fixtures = [fixturePath];
  } else {
    fixtures = await glob(`${fixturesDir}/**/*.html`);
  }
} catch (e) {
  const errorMessage = e instanceof Error ? e.message : '';
  console.log(
    `Trying to access ${specificFixture}.html threw an exception. Executing against all fixtures. ${errorMessage}`,
  );
  fixtures = await glob(`${fixturesDir}/**/*.html`);
}

const options = new Options();
options.addArguments(
  '--force-device-scale-factor=1',
  '--window-position=0,0',
  '--hide-scrollbars',
);
headless && options.addArguments('--headless');
options.setLoggingPrefs({
  browser: 'ALL',
  performance: 'ALL',
});
const driver = await new Builder()
  .forBrowser('chrome')
  .setChromeOptions(options)
  .build();

for (const fixturePath of fixtures) {
  const fixture = await fs.readFile(fixturePath, 'utf8');
  const relativePath = relative(fixturesDir, fixturePath);
  const fileNameNoExtension = parse(relativePath).name;
  console.log('Generate', fileNameNoExtension);

  // TODO: replace this with something more robust than just blindly replacing
  // start/end in the entire fixture
  const ltrFixture = fixture
    // prevent replacing in grid properties and alignment properties (justify/align-*)
    .replaceAll(
      /(?<!grid-column-)(?<!grid-row-)(?<!justify-self: )(?<!align-self: )(?<!justify-content: )(?<!align-content: )(?<!justify-items: )(?<!align-items: )start/g,
      'left',
    )
    .replaceAll(
      /(?<!grid-column-)(?<!grid-row-)(?<!justify-self: )(?<!align-self: )(?<!justify-content: )(?<!align-content: )(?<!justify-items: )(?<!align-items: )end/g,
      'right',
    )
    .replaceAll('flex-left', 'flex-start')
    .replaceAll('flex-right', 'flex-end');

  const rtlFixture = fixture
    // prevent replacing in grid properties and alignment properties (justify/align-*)
    .replaceAll(
      /(?<!grid-column-)(?<!grid-row-)(?<!justify-self: )(?<!align-self: )(?<!justify-content: )(?<!align-content: )(?<!justify-items: )(?<!align-items: )start/g,
      'right',
    )
    .replaceAll(
      /(?<!grid-column-)(?<!grid-row-)(?<!justify-self: )(?<!align-self: )(?<!justify-content: )(?<!align-content: )(?<!justify-items: )(?<!align-items: )end/g,
      'left',
    )
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

  const testLogs = logs.filter(
    log => !log.message.replace(/^[^"]*/, '').startsWith('"gentest-log:'),
  );

  await fs.writeFile(
    `${yogaDir}/tests/generated/${fileNameNoExtension}.cpp`,
    addSignatureToSourceCode(
      JSON.parse(testLogs[0].message.replace(/^[^"]*/, '')),
    ),
  );

  await fs.writeFile(
    `${yogaDir}/java/tests/generated/com/facebook/yoga/${fileNameNoExtension}.java`,
    addSignatureToSourceCode(
      JSON.parse(testLogs[1].message.replace(/^[^"]*/, '')).replace(
        'YogaTest',
        fileNameNoExtension,
      ),
    ),
  );

  await fs.writeFile(
    `${yogaDir}/javascript/tests/generated/${fileNameNoExtension}.test.ts`,
    addSignatureToSourceCode(
      JSON.parse(testLogs[2].message.replace(/^[^"]*/, '')).replace(
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
await fs.unlink(`${gentestDir}/test.html`);
await driver.quit();
