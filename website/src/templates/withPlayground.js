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
import './index.css';

export default ({pathContext}) => (
  <Page className="doc-block">
    <Playground
      selectedNodePath={[]}
      showGuides={false}
      renderSidebar={(layout, onChange) => (
        <DocsSidebar>
          <div className="markdown" dangerouslySetInnerHTML={{__html: pathContext.html}} />
          
          {(pathContext.frontmatter.editableProperties || []).map(prop => (
            <div key={prop} className="prop">
              <h4>{prop}</h4>
              <EditValue
                property={prop}
                value={layout[prop]}
                onChange={e => onChange(prop, e)}
              />
            </div>
          ))}
          
          <Link to="/docs" className="overview">
            BACK TO OVERVIEW
          </Link>
        </DocsSidebar>
      )}
    />
  </Page>
);
