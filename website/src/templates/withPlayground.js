/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @flow
 * @format
 */

import React, {Component} from 'react';
import Page from '../components/Page';
import Playground from '../components/Playground/src';
import DocsSidebar from '../components/DocsSidebar';
import EditValue from '../components/Playground/src/EditValue';
import Link from 'gatsby-link';
import {Button, Icon, Row, Col} from 'antd';
import './index.css';
import atob from 'atob';

type Props = {
  pathContext: {
    html: string,
    frontmatter: {
      initialPlayground?: string,
    },
  },
};
const REGEX = /<controls prop="([A-Za-z]+)"\s?\/>/gi;

export default class withPlayground extends Component<Props> {
  render() {
    let layoutDefinition;
    if (this.props.pathContext.frontmatter.initialPlayground) {
      layoutDefinition = JSON.parse(
        atob(this.props.pathContext.frontmatter.initialPlayground),
      );
    }
    return (
      <Page
        className="doc-block playground"
        title={this.props.pathContext.frontmatter.title}>
        <Playground
          layoutDefinition={layoutDefinition}
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
