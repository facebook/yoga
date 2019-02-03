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
import Toolbar from './Toolbar';
import Footer from './Footer';
import Helmet from 'react-helmet';
import favicon from '../pages/logos/favicon.png';
import './Page.css';
require('prismjs/themes/prism.css');

type Props = {|
  children: any,
  title?: string,
  className?: string,
  withSpacing?: boolean,
  shouldShowFooter?: boolean,
|};

export default (props: Props) => (
  <div className={`Page ${props.className || ''}`}>
    <Helmet>
      <title>{`Yoga Layout${props.title ? ` | ${props.title}` : ''}`}</title>
      <link rel="shortcut icon" type="image/png" href={favicon} />
    </Helmet>
    <Toolbar />
    <div className={`PageContent ${props.withSpacing ? 'withSpacing' : ''}`}>
      {props.children}
    </div>
    {props.shouldShowFooter && <Footer />}
  </div>
);
