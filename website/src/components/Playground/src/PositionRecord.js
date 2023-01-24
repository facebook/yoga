/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @flow
 * @format
 */

import {Record} from 'immutable';
import type {RecordOf} from 'immutable';

export type PositionRecordT = RecordOf<{
  top: string | number,
  right: string | number,
  bottom: string | number,
  left: string | number,
}>;

const r: PositionRecordT = Record({
  top: 0,
  right: 0,
  bottom: 0,
  left: 0,
});

export default r;
