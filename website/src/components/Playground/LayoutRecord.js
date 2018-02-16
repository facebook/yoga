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

import {Record, List} from 'immutable';
import type {RecordOf} from 'immutable';
import PositionRecord from './PositionRecord';
import type {PositionRecordT} from './PositionRecord';
import yoga from 'yoga-layout/dist/entry-browser';

import type {
  Yoga$Align,
  Yoga$JustifyContent,
  Yoga$FlexDirection,
  Yoga$FlexWrap,
  Yoga$YogaPositionType,
} from 'yoga-layout';

export type LayoutRecordT = RecordOf<{
  width?: ?number,
  height?: ?number,
  justifyContent?: Yoga$JustifyContent,
  padding: PositionRecordT,
  border: PositionRecordT,
  margin: PositionRecordT,
  position: PositionRecordT,
  positionType: Yoga$YogaPositionType,
  alignItems?: Yoga$Align,
  alignSelf?: Yoga$Align,
  alignContent?: Yoga$Align,
  flexDirection?: Yoga$FlexDirection,
  flexBasis?: number | 'auto',
  flexGrow?: number,
  flexShrink?: number,
  padding?: number,
  flexWrap?: Yoga$FlexWrap,
  aspectRatio?: number,
  children?: List<LayoutRecordT>,
  minWidth?: number,
  maxWidth?: number,
  minHeight?: number,
  maxHeight?: number,
}>;

const r: LayoutRecordT = Record({
  width: 'auto',
  height: 'auto',
  justifyContent: yoga.JUSTIFY_FLEX_START,
  alignItems: yoga.ALIGN_STRETCH,
  alignSelf: yoga.ALIGN_AUTO,
  alignContent: yoga.ALIGN_STRETCH,
  flexDirection: yoga.FLEX_DIRECTION_ROW,
  padding: PositionRecord(),
  margin: PositionRecord(),
  border: PositionRecord(),
  position: PositionRecord(),
  positionType: yoga.POSITION_TYPE_RELATIVE,
  flexWrap: yoga.WRAP_NO_WRAP,
  flexBasis: 'auto',
  flexGrow: 0,
  flexShrink: 1,
  children: List(),
  aspectRatio: 'auto',
  minWidth: NaN,
  maxWidth: NaN,
  minHeight: NaN,
  maxHeight: NaN,
});

export default r;
