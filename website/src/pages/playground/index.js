/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @flow
 * @format
 */

import React from 'react';
import Page from '../../components/Page';
import Playground from '../../components/Playground/src';
import {Row, Col} from 'antd';
import './index.css';

export default () => (
  <Page title="Playground">
    <Row className="playground-page">
      <Col lg={24} md={0} sm={0} xs={0}>
        <Playground height="100%" selectedNodePath={[]} persist />
      </Col>

      <Col lg={0} xs={24} className="error-container">
        <p className="error-text">
          Sorry! The playground only works on larger displays currently.
        </p>
      </Col>
    </Row>
  </Page>
);
