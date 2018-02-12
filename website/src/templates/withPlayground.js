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
import Playground from '../components/Playground';
import DocsSidebar from '../components/DocsSidebar';
import EditValue from '../components/Playground/EditValue';
import Link from 'gatsby-link';
import {Button, Icon, Row, Col} from 'antd';

export default ({pathContext}) => (
  <Page>
    <Playground
      selectedNodePath={[]}
      showGuides={false}
      renderSidebar={(layout, onChange) => (
        <DocsSidebar>
          <Link to="/docs">
            <Icon type="left-circle-o" /> back to overview
          </Link>
          <div dangerouslySetInnerHTML={{__html: pathContext.html}} />
          {pathContext.frontmatter.editableProperties && (
            <Row type="flex" align="bottom">
              <Col span={12}>
                <h3>Try it out</h3>
              </Col>
              <Col span={12}>
                <Link to="/playground">
                  <Icon type="export" /> Open in playground
                </Link>
              </Col>
            </Row>
          )}
          {(pathContext.frontmatter.editableProperties || []).map(prop => (
            <div key={prop}>
              <h4>{prop}</h4>
              <EditValue
                property={prop}
                value={layout[prop]}
                onChange={e => onChange(prop, e)}
              />
            </div>
          ))}
        </DocsSidebar>
      )}
    />
  </Page>
);
