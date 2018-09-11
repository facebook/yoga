/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @flow
 * @format
 */

import React from 'react';
import './Padded.css';

type Props = {
  children: any,
  className?: string,
};

export default (props: Props) => (
  <div className={`Padded ${props.className || ''}`}>{props.children}</div>
);
