/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

const {
  argv,
  cleanTask,
  logger,
  jestTask,
  option,
  parallel,
  series,
  spawn,
  task,
  tscTask,
} = require('just-scripts');

const {readFile, writeFile} = require('fs/promises');

const chalk = require('chalk');
const glob = require('glob');
const path = require('path');
const which = require('which');

const node = process.execPath;

option('fix');

task('clean', cleanTask({paths: ['build', 'dist']}));

function defineFlavor(flavor, env) {
  task(`cmake-build:${flavor}`, cmakeBuildTask({targets: [flavor]}));
  task(
    `jest:${flavor}`,
    jestTask({
      config: path.join(__dirname, 'jest.config.js'),
      nodeArgs: ['--experimental-vm-modules'],
      env,
    }),
  );
  task(
    `test:${flavor}`,
    series(emcmakeGenerateTask(), `cmake-build:${flavor}`, `jest:${flavor}`),
  );
}

defineFlavor('web');

task('build', series(emcmakeGenerateTask(), cmakeBuildTask()));

task('test', series(emcmakeGenerateTask(), 'cmake-build:web', 'jest:web'));

task(
  'benchmark',
  series(
    emcmakeGenerateTask(),
    cmakeBuildTask({targets: ['web']}),
    runBenchTask(),
  ),
);

task('clang-format', clangFormatTask({fix: argv().fix}));

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

function recursiveReplace(obj, pattern, replacement) {
  for (const [key, value] of Object.entries(obj)) {
    if (typeof value === 'string') {
      obj[key] = value.replace(pattern, replacement);
    } else if (typeof value === 'object' && value != null) {
      recursiveReplace(value, pattern, replacement);
    }
  }
}

function babelTransformTask(opts) {
  return () => {
    const args = [
      opts.dir,
      '--source-maps',
      '--out-dir',
      opts.dir,
      '--extensions',
      '.js,.cjs,.mjs,.ts,.cts,.mts',
    ];
    logger.info(`Transforming "${path.resolve(opts.dir)}"`);

    return spawn(node, [require.resolve('@babel/cli/bin/babel'), ...args], {
      cwd: __dirname,
      env: {
        // Trigger distribution-specific Babel transforms
        NODE_ENV: 'dist',
      },
    });
  };
}

function runBenchTask() {
  return () => {
    const files = glob.sync('./tests/Benchmarks/**/*');

    const args = [
      '--loader=babel-register-esm',
      './tests/bin/run-bench.ts',
      ...files,
    ];
    logger.info(['node', ...args].join(' '));

    return spawn(node, args, {
      stdio: 'inherit',
    });
  };
}

function findExecutable(name, failureMessage) {
  const exec = which.sync(name, {nothrow: true});
  if (exec) {
    return exec;
  }

  logger.error(chalk.bold.red(failureMessage));
  process.exit(1);
}

function tryFindExecutable(name, failureMessage) {
  const exec = which.sync(name, {nothrow: true});
  if (exec) {
    return exec;
  }

  logger.warn(chalk.bold.yellow(failureMessage));
  return exec;
}

function emcmakeGenerateTask() {
  return () => {
    const ninja = tryFindExecutable(
      'ninja',
      'Warning: Install Ninja (e.g. "brew install ninja") for faster builds',
    );
    const emcmake = findExecutable(
      'emcmake',
      'Error: Please install the emscripten SDK: https://emscripten.org/docs/getting_started/',
    );

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

function cmakeBuildTask(opts) {
  return () => {
    const cmake = findExecutable(
      'cmake',
      'Error: Please install CMake (e.g. "brew install cmake")',
    );
    const args = [
      '--build',
      'build',
      ...(opts?.targets ? ['--target', ...opts.targets] : []),
    ];
    logger.info(['cmake', ...args].join(' '));

    return spawn(cmake, args, {stdio: 'inherit'});
  };
}

function clangFormatTask(opts) {
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
