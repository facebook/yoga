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
import Footer from './Footer';
import './Page.css';

type Props = {|
  children: any,
  title?: string,
  className?: string,
|};

export default (props: Props) => (
  <div className={`Page ${props.className || ''}`}>
    {/* <Head>
      <link
        rel="stylesheet"
        href="//cdnjs.cloudflare.com/ajax/libs/antd/3.2.0/antd.min.css"
      />
      <link href="//fonts.googleapis.com/css?family=Barlow" rel="stylesheet" />
      <title>Yoga Layout{props.title ? ` | ${props.title}` : ''}</title>
    </Head> */}
    <Toolbar />
    <div className="PageContent">{props.children}</div>
    <Footer />
  </div>
);
