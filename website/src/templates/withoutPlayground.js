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
import Page from '../components/Page';
import Padded from '../components/Padded';
import {Row, Col} from 'antd';
import Link from 'gatsby-link';
import './index.css';

export default ({pathContext}) => {
  return (
    <Page
      className="doc-block no-playground"
      shouldShowFooter
      title={pathContext.frontmatter.title}>
      <Padded>
        <Row>
          <Col xl={16} lg={16} md={24} sm={24} xs={24}>
            <div
              className="markdown"
              dangerouslySetInnerHTML={{__html: pathContext.html}}
            />
          </Col>
        </Row>
        <Link to="/docs" className="overview">
          BACK TO OVERVIEW
        </Link>
      </Padded>
    </Page>
  );
};
