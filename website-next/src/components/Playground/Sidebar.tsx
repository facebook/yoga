/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import React, {Component} from 'react';
import styles from './Sidebar.module.css';
import clsx from 'clsx';

type Props = {
  width?: number;
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  children: any;
};

function PlaceholderContent() {
  return (
    <div className={styles.placeholder}>
      <p>Select a node to edit its properties</p>
    </div>
  );
}

export default class Sidebar extends Component<Props> {
  render() {
    return (
      <div
        className={clsx('card', styles.sidebar)}
        style={{width: this.props.width}}>
        {this.props.children || <PlaceholderContent />}
      </div>
    );
  }
}
