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
import Link from 'gatsby-link';
import Page from '../../components/Page';
import Padded from '../../components/Padded';
import {Row, Col} from 'antd';
import './index.css';

const CATEGORY_TITLE = {
  'getting-started': 'Getting Started',
  properties: 'Properties',
  examples: 'Examples',
  contributing: 'Contributing',
};

export default ({data}) => (
  <Page className="docs-landing" shouldShowFooter title="Documentation">
    <Padded>
      <Row className="heading">
        <Col xl={16} lg={16} md={24} sm={24} xs={24}>
          <h1>Documentation</h1>
          <p>
            Welcome to Yoga's documentation page. Below you will find helpful
            documentation covering all the features of the library. Each page
            comes with an interactive playground for you to explore that
            feature. The examples section showcases some of the most common
            layouts and how to build them. This is a community project and
            contributions within documentation, code, and tests are more than
            welcome. The contributing section below covers how to get started.
          </p>
        </Col>
      </Row>
      <Row>
        {['getting-started', 'properties', 'examples', 'contributing'].map(
          category => (
            <Col lg={6} md={12} xs={24} key={category} className="category">
              <h2>{CATEGORY_TITLE[category]}</h2>
              {data.allMarkdownRemark.edges
                .filter(
                  ({node}) =>
                    node.fileAbsolutePath.indexOf(`/${category}/`) > -1,
                )
                .map(({node}) =>
                  node.frontmatter.redirect ? (
                    <a key={node.id} href={node.frontmatter.path}>
                      {node.frontmatter.title}
                    </a>
                  ) : (
                    <Link key={node.id} to={node.frontmatter.path}>
                      {node.frontmatter.title}
                    </Link>
                  ),
                )}
            </Col>
          ),
        )}
      </Row>
    </Padded>
  </Page>
);

export const query = graphql`
  query IndexQuery {
    allMarkdownRemark {
      edges {
        node {
          id
          frontmatter {
            title
            path
            redirect
          }
          fileAbsolutePath
        }
      }
    }
  }
`;
