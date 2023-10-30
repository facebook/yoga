/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import React, {Component} from 'react';
import clsx from 'clsx';
import Yoga from 'yoga-layout';

import styles from './YogaEnumSelect.module.css';

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
      <select className={styles.select} name={this.props.property}>
        {this.values.map(({key, value}) => (
          <option key={key} value={value}>
            {selected ? this.getTitle(property, key) : ''}
          </option>
        ))}
      </select>
    ) : (
      <div className={clsx('button-group', styles.buttonGroup)}>
        {this.values.map(({key, value}) => (
          <button
            className={clsx(
              'button',
              'button--sm',
              'button--outline',
              'button--secondary',
              value === this.props.value && 'button--active',
              styles.button,
            )}
            onClick={() => this.props.onChange(this.props.property, value)}>
            {this.getTitle(property, key)}
          </button>
        ))}
      </div>
    );
  }
}
