/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

module.exports = {
  root: true,
  ignorePatterns: [
    '/website',
    '**/binaries/**',
    '**/build/**',
    '**/generated/**',
  ],
  extends: ['eslint:recommended', 'plugin:prettier/recommended'],
  plugins: ['prettier'],
  rules: {
    'no-unused-vars': ['error', {argsIgnorePattern: '^_'}],
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
  parserOptions: {
    sourceType: 'module',
    ecmaVersion: 'latest',
  },
  overrides: [
    {
      files: ['**/*.ts', '**/*.tsx'],
      extends: ['plugin:@typescript-eslint/recommended'],
      parser: '@typescript-eslint/parser',
      parserOptions: {
        project: true,
      },
      plugins: ['@typescript-eslint'],
      rules: {
        '@typescript-eslint/ban-ts-comment': 'off',
        '@typescript-eslint/no-unused-vars': [
          'error',
          {argsIgnorePattern: '^_'},
        ],
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
      files: ['jest.*', '**/tests/**'],
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
