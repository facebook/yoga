/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
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
