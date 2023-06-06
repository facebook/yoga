/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

import type {Yoga} from 'yoga-layout';

declare global {
  // eslint-disable-next-line no-var
  var Yoga: Yoga | undefined;
  // eslint-disable-next-line no-var
  var YGBENCHMARK: (title: string, fn: () => void) => void;
}

if (globalThis.Yoga === undefined) {
  throw new Error('Expected "Yoga" global to be set');
}
if (globalThis.YGBENCHMARK === undefined) {
  throw new Error('Expected "YGBENCHMARK" global to be set');
}

const yoga = globalThis.Yoga;
const benchmark = globalThis.YGBENCHMARK;

export {yoga as Yoga, benchmark as YGBENCHMARK};
