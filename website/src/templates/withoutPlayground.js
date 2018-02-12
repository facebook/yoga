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
import Page from '../components/Page';
import Padded from '../components/Padded';
import {Icon} from 'antd';
import Link from 'gatsby-link';

export default ({pathContext}) => {
  return (
    <Page withSpacing>
      <Padded>
        <Link to="/docs">
          <Icon type="left-circle-o" /> back to overview
        </Link>
        <div dangerouslySetInnerHTML={{__html: pathContext.html}} />
      </Padded>
    </Page>
  );
};
