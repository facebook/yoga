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

import React, {Component} from 'react';
import Page from '../components/Page';
import Playground from '../components/Playground';
import DocsSidebar from '../components/DocsSidebar';
import EditValue from '../components/Playground/EditValue';
import Link from 'gatsby-link';
import {Button, Icon, Row, Col} from 'antd';
import './index.css';

type Props = {
  pathContext: {
    html: string,
    frontmatter: {},
  },
};
const REGEX = /<controls prop="([A-Za-z]+)"\s?\/>/gi;

export default class withPlayground extends Component<Props> {
  render() {
    return (
      <Page className="doc-block playground">
        <Playground
          selectedNodePath={[]}
          showGuides={false}
          renderSidebar={(layout, onChange) => (
            <DocsSidebar
              layout={layout}
              onChange={onChange}
              markdown={this.props.pathContext.html}
            />
          )}
        />
      </Page>
    );
  }
}
