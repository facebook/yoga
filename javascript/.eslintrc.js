/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

const path = require('path');

module.exports = {
  root: true,
  ignorePatterns: ['binaries/**', 'build/**', 'dist/**', 'tests/generated/**'],
  extends: ['eslint:recommended', 'plugin:prettier/recommended'],
  plugins: ['prettier'],
  rules: {
    'no-var': 'error',
    'prefer-arrow-callback': 'error',
    'prefer-const': 'error',
    'prefer-object-spread': 'error',
    'prefer-spread': 'error',
    'require-await': 'error',
  },
  env: {
    commonjs: true,
    es2018: true,
  },
  overrides: [
    {
      files: ['**/*.js'],
      parser: '@babel/eslint-parser',
      parserOptions: {
        babelOptions: {
          configFile: path.join(__dirname, '.babelrc.js'),
        },
      },
    },
    {
      files: ['**/*.ts'],
      extends: ['plugin:@typescript-eslint/recommended'],
      parser: '@typescript-eslint/parser',
      parserOptions: {
        project: path.join(__dirname, 'tsconfig.json'),
      },
      plugins: ['@typescript-eslint'],
      rules: {
        '@typescript-eslint/no-var-requires': 'off',
      },
    },
    {
      files: ['**/.eslintrc.js', '**/just.config.js'],
      env: {
        node: true,
      },
    },
    {
      files: ['jest.*', 'tests/**'],
      env: {
        node: true,
      },
      extends: ['plugin:jest/recommended'],
      globals: {
        getMeasureCounter: 'writable',
        getMeasureCounterMax: 'writable',
        getMeasureCounterMin: 'writable',
        Yoga: 'writable',
        YGBENCHMARK: 'writable',
      },
    },
  ],
};
