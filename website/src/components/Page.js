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

import React from 'react';
import Toolbar from './Toolbar';
import './Page.css';
require('prismjs/themes/prism.css');

type Props = {|
  children: any,
  className?: string,
  withSpacing?: boolean,
|};

export default (props: Props) => (
  <div className={`Page ${props.className || ''}`}>
    <Toolbar/>
    <div className={`PageContent ${props.withSpacing ? 'withSpacing' : ''}`}>
      {props.children}
    </div>
  </div>
);
