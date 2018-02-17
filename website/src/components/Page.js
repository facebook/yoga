/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @flow
 * @format
 */

import React from 'react';
import Toolbar from './Toolbar';
import Footer from './Footer';
import './Page.css';
require('prismjs/themes/prism.css');

type Props = {|
  children: any,
  className?: string,
  withSpacing?: boolean,
  shouldShowFooter?: boolean,
|};

export default (props: Props) => (
  <div className={`Page ${props.className || ''}`}>
    <Toolbar />
    <div className={`PageContent ${props.withSpacing ? 'withSpacing' : ''}`}>
      {props.children}
    </div>
    {props.shouldShowFooter && <Footer />}
  </div>
);
