/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import {
  argv,
  cleanTask,
  eslintTask,
  logger,
  jestTask,
  option,
  parallel,
  series,
  spawn,
  task,
  tscTask,
} from 'just-scripts';

import {readFile, writeFile} from 'fs/promises';

import glob from 'glob';
import path from 'path';
import which from 'which';

const node = process.execPath;

option('fix');

task('clean', cleanTask({paths: ['build', 'dist']}));

function defineFlavor(flavor: string, env: NodeJS.ProcessEnv) {
  task(`cmake-build:${flavor}`, cmakeBuildTask({targets: [flavor]}));
  task(
    `jest:${flavor}`,
    jestTask({config: path.join(__dirname, 'jest.config.ts'), env}),
  );
  task(
    `test:${flavor}`,
    series(emcmakeGenerateTask(), `cmake-build:${flavor}`, `jest:${flavor}`),
  );
}

defineFlavor('asmjs-async-node', {WASM: '0', SYNC: '0'});
defineFlavor('asmjs-sync-node', {WASM: '0', SYNC: '1'});
defineFlavor('asmjs-async-web', {WASM: '0', SYNC: '0'});
defineFlavor('asmjs-sync-web', {WASM: '0', SYNC: '1'});
defineFlavor('wasm-async-node', {WASM: '1', SYNC: '0'});
defineFlavor('wasm-sync-node', {WASM: '1', SYNC: '1'});
defineFlavor('wasm-async-web', {WASM: '1', SYNC: '0'});
defineFlavor('wasm-sync-web', {WASM: '1', SYNC: '1'});

task('build', series(emcmakeGenerateTask(), cmakeBuildTask()));

task(
  'test',
  series(
    emcmakeGenerateTask(),
    series('cmake-build:asmjs-async-node', 'jest:asmjs-async-node'),
    series('cmake-build:asmjs-sync-node', 'jest:asmjs-sync-node'),
    series('cmake-build:wasm-async-node', 'jest:wasm-async-node'),
    series('cmake-build:wasm-sync-node', 'jest:wasm-sync-node'),
  ),
);

task(
  'benchmark',
  series(
    emcmakeGenerateTask(),
    cmakeBuildTask({targets: ['asmjs-sync-node', 'wasm-sync-node']}),
    runBenchTask(),
  ),
);

task(
  'lint',
  parallel(
    tscTask({noEmit: true}),
    series(eslintTask({fix: argv().fix}), clangFormatTask({fix: argv().fix})),
  ),
);

task('prepack-package-json', async () => {
  const packageJsonPath = path.join(__dirname, 'package.json');
  const packageJsonContents = await readFile(packageJsonPath);
  const packageJson = JSON.parse(packageJsonContents.toString('utf-8'));

  recursiveReplace(packageJson, /(.\/src\/.*)\.ts/, '$1.js');
  await writeFile(packageJsonPath, JSON.stringify(packageJson, null, 2));
});

task(
  'prepack',
  series(
    parallel('build', tscTask({emitDeclarationOnly: true})),
    babelTransformTask({dir: 'src'}),
    'prepack-package-json',
  ),
);

function recursiveReplace(
  obj: Record<string, unknown>,
  pattern: RegExp,
  replacement: string,
) {
  for (const [key, value] of Object.entries(obj)) {
    if (typeof value === 'string') {
      obj[key] = value.replace(pattern, replacement);
    } else if (typeof value === 'object' && value != null) {
      recursiveReplace(value as Record<string, unknown>, pattern, replacement);
    }
  }
}

function babelTransformTask(opts: {dir: string}) {
  return () => {
    const args = [
      opts.dir,
      '--source-maps',
      '--out-dir',
      opts.dir,
      '--extensions',
      '.js,.ts',
    ];
    logger.info(`Transforming "${path.resolve(opts.dir)}"`);

    return spawn(node, [require.resolve('@babel/cli/bin/babel'), ...args], {
      cwd: __dirname,
    });
  };
}

function runBenchTask() {
  return () => {
    const files = glob.sync('./tests/Benchmarks/**/*');

    const args = [
      '--extensions',
      '.js,.ts',
      '--config-file',
      path.join(__dirname, '.babelrc.js'),
      '--',
      './tests/bin/run-bench.ts',
      ...files,
    ];
    logger.info(['babel-node', ...args].join(' '));

    return spawn(
      node,
      [require.resolve('@babel/node/bin/babel-node'), ...args],
      {
        stdio: 'inherit',
      },
    );
  };
}

function emcmakeGenerateTask() {
  return () => {
    const emcmake = which.sync('emcmake');
    const ninja = which.sync('ninja', {nothrow: true});
    const args = [
      'cmake',
      '-S',
      '.',
      '-B',
      'build',
      ...(ninja ? ['-G', 'Ninja'] : []),
    ];
    logger.info(['emcmake', ...args].join(' '));

    return spawn(emcmake, args, {stdio: 'inherit'});
  };
}

function cmakeBuildTask(opts?: {targets?: ReadonlyArray<string>}) {
  return () => {
    const cmake = which.sync('cmake');
    const args = [
      '--build',
      'build',
      ...(opts?.targets ? ['--target', ...opts.targets] : []),
    ];
    logger.info(['cmake', ...args].join(' '));

    return spawn(cmake, args, {stdio: 'inherit'});
  };
}

function clangFormatTask(opts?: {fix?: boolean}) {
  return () => {
    const args = [
      ...(opts?.fix ? ['-i'] : ['--dry-run', '--Werror']),
      ...glob.sync('**/*.{h,hh,hpp,c,cpp,cc,m,mm}'),
    ];
    logger.info(['clang-format', ...args].join(' '));

    return spawn(node, [require.resolve('clang-format'), ...args], {
      stdio: 'inherit',
    });
  };
}
