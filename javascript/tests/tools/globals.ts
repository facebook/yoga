/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

declare global {
  // eslint-disable-next-line no-var
  var YGBENCHMARK: (title: string, fn: () => void) => void;
}

if (globalThis.YGBENCHMARK === undefined) {
  throw new Error('Expected "YGBENCHMARK" global to be set');
}

const benchmark = globalThis.YGBENCHMARK;

export {benchmark as YGBENCHMARK};
