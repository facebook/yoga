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
import './YogaPositionEditor.css';

type Property = 'position' | 'margin' | 'padding' | 'border';

type Props = {
  value: PositionRecordType;
  property: Property;
  disabled?: boolean;
  onChange: (property: Property, value: PositionRecordType) => void;
};

export default class YogaPositionEditor extends Component<Props> {
  static availableProperties = ['position', 'margin', 'padding', 'border'];

  static defaultProps = {
    value: PositionRecord(),
  };

  render() {
    const {onChange, value, property, disabled} = this.props;
    return (
      <div className="YogaPositionEditor">
        <input
          type="text"
          value={Number.isNaN(value.top) ? '' : value.top}
          disabled={disabled}
          onChange={e => onChange(property, value.set('top', e.target.value))}
        />
        <div className="YogaPositionEditorRow">
          <input
            type="text"
            value={Number.isNaN(value.left) ? '' : value.left}
            disabled={disabled}
            onChange={e =>
              onChange(property, value.set('left', e.target.value))
            }
          />
          {property.toUpperCase()}
          <input
            type="text"
            value={Number.isNaN(value.right) ? '' : value.right}
            disabled={disabled}
            onChange={e =>
              onChange(property, value.set('right', e.target.value))
            }
          />
        </div>
        <input
          type="text"
          value={Number.isNaN(value.bottom) ? '' : value.bottom}
          disabled={disabled}
          onChange={e =>
            onChange(property, value.set('bottom', e.target.value))
          }
        />
      </div>
    );
  }
}
