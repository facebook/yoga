/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import React, {Component} from 'react';
import Yoga from 'yoga-layout/sync';
import {Radio, Menu, Dropdown, Button, Icon} from 'antd';
import './YogaEnumSelect.css';
const RadioButton = Radio.Button;
const RadioGroup = Radio.Group;

const PROPERTY_LOOKUP = {
  flexDirection: 'FLEX_DIRECTION',
  direction: 'DIRECTION',
  justifyContent: 'JUSTIFY',
  alignSelf: 'ALIGN',
  alignContent: 'ALIGN',
  alignItems: 'ALIGN',
  positionType: 'POSITION_TYPE',
  flexWrap: 'WRAP',
};

type Property = keyof typeof PROPERTY_LOOKUP;

type Props = {
  property: Property;
  disabled?: boolean;
  value: string | number;
  onChange: (property: Property, value: number) => void;
};

export default class YogaEnumSelect extends Component<Props> {
  static availableProperties = Object.keys(PROPERTY_LOOKUP);

  values: Array<{key: string; value: number}>;

  constructor(props: Props) {
    super(props);

    const property = PROPERTY_LOOKUP[props.property];

    this.values = Object.keys(Yoga)
      .map(key => ({key, value: Yoga[key]}))
      .filter(
        ({key}) => key.startsWith(property) && key !== `${property}_COUNT`,
      );
  }

  handleMenuClick = ({key}: {key: string}) => {
    this.props.onChange(this.props.property, Yoga[key]);
  };

  getTitle = (property: string, key: string): string => {
    const replacer = new RegExp(`^${property}_`);
    return key.replace(replacer, '').replace('_', ' ').toLowerCase();
  };

  render() {
    const property = PROPERTY_LOOKUP[this.props.property];
    const selected = this.values.find(({value}) => value === this.props.value);

    return this.values.length > 3 ? (
      <div className="YogaEnumSelect">
        {/*@ts-ignore*/}
        <Dropdown
          trigger={['click']}
          disabled={this.props.disabled}
          overlay={
            // @ts-ignore
            <Menu onClick={this.handleMenuClick}>
              {this.values.map(({key, value}) => (
                // @ts-ignore
                <Menu.Item key={key} value={value}>
                  {this.getTitle(property, key)}
                </Menu.Item>
              ))}
            </Menu>
          }>
          <Button>
            {selected ? this.getTitle(property, selected.key) : ''}
            {/*@ts-ignore*/}
            <Icon type="down" />
          </Button>
        </Dropdown>
      </div>
    ) : (
      <RadioGroup
        {...this.props}
        onChange={e => this.props.onChange(this.props.property, e.target.value)}
        defaultValue="a"
        className="YogaEnumSelect">
        {this.values.map(({key, value}) => (
          <RadioButton key={key} value={value}>
            {this.getTitle(property, key)}
          </RadioButton>
        ))}
      </RadioGroup>
    );
  }
}
