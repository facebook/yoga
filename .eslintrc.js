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
    es2020: true,
  },
  parserOptions: {
    sourceType: 'module',
    ecmaVersion: 'latest',
  },
  overrides: [
    {
      files: ['**/*.ts', '**/*.cts', '**/*.mts'],
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
      files: ['**/tests/**'],
      extends: ['plugin:jest/recommended'],
    },
  ],
};
