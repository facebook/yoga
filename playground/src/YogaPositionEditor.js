// @flow
import React, {Component} from 'react';
import {Input} from 'antd';
import PositionRecord from './PositionRecord';
import type {PositionRecordT} from './PositionRecord';
import './YogaPositionEditor.css';

type Props = {
  value: PositionRecordT,
  property: string,
  onChange: (value: PositionRecordT) => void,
};

export default class YogaPositionEditor extends Component<Props> {
  static defaultProps = {
    value: PositionRecord(),
  };

  render() {
    const {onChange, value, property} = this.props;
    return (
      <div className="YogaPositionEditor">
        <Input
          type="text"
          value={value.top}
          onChange={e => onChange(value.set('top', e.target.value))}
        />
        <div className="YogaPositionEditorRow">
          <Input
            type="text"
            value={value.left}
            onChange={e => onChange(value.set('left', e.target.value))}
          />
          {property}
          <Input
            type="text"
            value={value.right}
            onChange={e => onChange(value.set('right', e.target.value))}
          />
        </div>
        <Input
          type="text"
          value={value.bottom}
          onChange={e => onChange(value.set('bottom', e.target.value))}
        />
      </div>
    );
  }
}
