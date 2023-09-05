/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import React, {Component} from 'react';
import PositionRecord from './PositionRecord';
import type {PositionRecordType} from './PositionRecord';
import './PositionGuide.css';

type Props = {
  inset?: boolean;
  reverse?: boolean;
  position: PositionRecordType;
  offset: PositionRecordType;
  color: string;
};

export default class PositionGuide extends Component<Props> {
  static defaultProps = {
    offset: PositionRecord({}),
  };

  render() {
    const {position, offset, inset, color, reverse} = this.props;
    let {top, left, right, bottom} = position;
    let {top: oTop, left: oLeft, right: oRight, bottom: oBottom} = offset;

    if (
      typeof top !== 'number' ||
      typeof left !== 'number' ||
      typeof right !== 'number' ||
      typeof bottom !== 'number' ||
      typeof oTop !== 'number' ||
      typeof oLeft !== 'number' ||
      typeof oRight !== 'number' ||
      typeof oBottom !== 'number'
    ) {
      return null;
    }
    if (reverse) {
      let temp1 = left;
      left = right;
      right = temp1;
      temp1 = oLeft;
      oLeft = oRight;
      oRight = temp1;
    }

    if (!top) {
      top = 0;
    }
    if (!left) {
      left = 0;
    }
    if (!right) {
      right = 0;
    }
    if (!bottom) {
      bottom = 0;
    }
    if (!oTop) {
      oTop = 0;
    }
    if (!oLeft) {
      oLeft = 0;
    }
    if (!oRight) {
      oRight = 0;
    }
    if (!oBottom) {
      oBottom = 0;
    }

    if (!inset) {
      if (typeof top === 'number' && typeof bottom === 'number') {
        if (top < 0) {
          bottom -= top;
          top = 0;
        }
        if (bottom < 0) {
          top -= bottom;
          bottom = 0;
        }
      }
      if (left < 0) {
        right -= left;
        left = 0;
      }
      if (right < 0) {
        left -= right;
        right = 0;
      }
    }

    return [
      top !== 0 ? (
        <div
          key="top"
          className="PositionGuide"
          style={{
            backgroundColor: color,
            height: top,
            top: inset ? oTop : -top - oTop,
            left: inset ? left + oLeft : -left - oLeft,
            right: inset ? right + oRight : -right - oRight,
          }}>
          {top}
        </div>
      ) : null,
      left !== 0 ? (
        <div
          key="left"
          className="PositionGuide"
          style={{
            backgroundColor: color,
            width: left,
            top: inset ? oTop : -oTop,
            bottom: inset ? oBottom : -oBottom,
            left: inset ? oLeft : -left - oLeft,
          }}>
          {left}
        </div>
      ) : null,
      right !== 0 ? (
        <div
          key="right"
          className="PositionGuide"
          style={{
            backgroundColor: color,
            width: right,
            top: inset ? oTop : -oTop,
            bottom: inset ? oBottom : -oBottom,
            right: inset ? oRight : -right - oRight,
          }}>
          {right}
        </div>
      ) : null,
      bottom !== 0 ? (
        <div
          key="bottom"
          className="PositionGuide"
          style={{
            backgroundColor: color,
            height: bottom,
            bottom: inset ? oBottom : -bottom - oBottom,
            left: inset ? left + oLeft : -left - oLeft,
            right: inset ? right + oRight : -right - oRight,
          }}>
          {bottom}
        </div>
      ) : null,
    ];
  }
}
