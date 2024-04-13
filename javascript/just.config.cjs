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
  series,
  spawn,
  task,
  tscTask,
  copyTask,
} = require('just-scripts');

const {existsSync} = require('fs');
const {readFile, writeFile, rm} = require('fs/promises');

const glob = require('glob');
const path = require('path');
const which = require('which');

const node = process.execPath;

option('fix');

task('clean', cleanTask({paths: ['.emsdk', 'binaries', 'build']}));

task(
  'build',
  series(installEmsdkTask(), emcmakeGenerateTask(), cmakeBuildTask()),
);

task(
  'test',
  series(
    'build',
    jestTask({
      config: path.join(__dirname, 'jest.config.js'),
      nodeArgs: ['--experimental-vm-modules'],
    }),
  ),
);

task('benchmark', series('build', runBenchTask()));

task('clang-format', clangFormatTask({fix: argv().fix}));

task('prepack-package-json', async () => {
  const packageJsonPath = path.join(__dirname, 'package.json');
  const packageJsonContents = await readFile(packageJsonPath);
  const packageJson = JSON.parse(packageJsonContents.toString('utf-8'));

  packageJson.main = packageJson.main.replace(
    /^.\/src\/(.*)\.ts/,
    './dist/src/$1.js',
  );
  packageJson.types = packageJson.main.replace(/(.*)\.js/, '$1.d.ts');

  recursiveReplace(
    packageJson.exports,
    /^.\/src\/(.*)\.ts/,
    './dist/src/$1.js',
  );

  await writeFile(packageJsonPath, JSON.stringify(packageJson, null, 2));
});

task(
  'prepack',
  series(
    'build',
    copyTask({paths: ['binaries'], dest: 'dist/binaries'}),
    tscTask({
      emitDeclarationOnly: true,
      rootDir: '.',
      declarationDir: 'dist',
    }),
    babelTransformTask({src: 'src', dst: 'dist/src'}),
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
      opts.src,
      '--source-maps',
      '--out-dir',
      opts.dst,
      '--extensions',
      '.js,.cjs,.mjs,.ts,.cts,.mts',
    ];
    logger.info(`Transforming "${path.resolve(opts.src)}"`);

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

const emsdkVersion = '3.1.28';
const emsdkPath = path.join(__dirname, '.emsdk');
const emsdkBin = path.join(
  emsdkPath,
  process.platform === 'win32' ? 'emsdk.bat' : 'emsdk',
);
const emcmakeBin = path.join(
  emsdkPath,
  'upstream',
  'emscripten',
  process.platform === 'win32' ? 'emcmake.bat' : 'emcmake',
);

function installEmsdkTask() {
  return async () => {
    if (await isEmsdkReadyAndActivated()) {
      logger.verbose(
        `emsdk ${emsdkVersion} is already installed and activated`,
      );
      return false;
    }

    logger.info(`installing emsdk ${emsdkVersion} to ${emsdkPath}`);
    await rm(emsdkPath, {recursive: true, force: true});

    await spawn(
      'git',
      ['clone', 'https://github.com/emscripten-core/emsdk.git', emsdkPath],
      {stdio: 'inherit'},
    );

    await spawn(emsdkBin, ['install', emsdkVersion], {stdio: 'inherit'});

    await spawn(emsdkBin, ['activate', emsdkVersion], {
      stdio: logger.enableVerbose ? 'inherit' : 'ignore',
    });
  };
}

async function isEmsdkReadyAndActivated() {
  if (!existsSync(emcmakeBin)) {
    return false;
  }

  try {
    const emsdkReleases = JSON.parse(
      await readFile(path.join(emsdkPath, 'emscripten-releases-tags.json')),
    ).releases;

    const versionHash = emsdkReleases[emsdkVersion];
    if (!versionHash) {
      return false;
    }

    const activatedVersion = await readFile(
      path.join(emsdkPath, 'upstream', '.emsdk_version'),
    );

    return activatedVersion.toString().includes(versionHash);
  } catch {
    // Something is wrong. Pave and redo.
    return false;
  }
}

function emcmakeGenerateTask() {
  return () => {
    logger.verbose(`emcmake path: ${emcmakeBin}`);

    const args = [
      'cmake',
      '-S',
      '.',
      '-B',
      'build',
      ...(process.platform === 'win32' ? [] : ['-G', 'Ninja']),
    ];
    logger.info(['emcmake', ...args].join(' '));

    return spawn(emcmakeBin, args, {
      stdio: logger.enableVerbose ? 'inherit' : 'ignore',
    });
  };
}

function cmakeBuildTask(opts) {
  return () => {
    const cmake = which.sync('cmake');
    logger.verbose(`cmake path: ${cmake}`);

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
