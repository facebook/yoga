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
import Page from '../../components/Page';
import Playground from '../../components/Playground';
import {Row, Col} from 'antd';
import './index.css';

export default () => (
  <Page>
	<Row className="playground-page">
      <Col lg={24} md={0} sm={0} xs={0}>
	    <Playground height="100%" selectedNodePath={[]} persist />
	  </Col>

  	  <Col lg={0} xs={24} className="error-container">
	    <p className="error-text">Sorry! The playground only works on larger displays currently.</p>
	  </Col>
	</Row>
  </Page>
);
