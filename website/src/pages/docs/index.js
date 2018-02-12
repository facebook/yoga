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
import Link from 'gatsby-link';
import Page from '../../components/Page';
import Padded from '../../components/Padded';
import {Row, Col} from 'antd';

const CATEGORY_TITLE = {
  'getting-started': 'Getting Started',
  properties: 'Properties',
  examples: 'Examples',
  contributing: 'Contributing',
};

export default ({data}) => (
  <Page withSpacing>
    <Padded>
      <h1>Documentation</h1>
      <p>
        Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam quis
        urna in lacus rutrum vehicula. Curabitur vitae dictum ante, sollicitudin
        sollicitudin tortor. Morbi a vehicula justo. Proin luctus tellus vitae
        nulla bibendum gravida. Duis varius cursus erat ut tempus. Fusce ex
        arcu, accumsan et ultricies at, fermentum sit amet lectus. Donec a neque
        nec leo pharetra fermentum.
      </p>
      <Row>
        {['getting-started', 'properties', 'examples', 'contributing'].map(
          category => (
            <Col md={6} sm={12} xs={24} key={category}>
              <h2>{CATEGORY_TITLE[category]}</h2>
              {data.allMarkdownRemark.edges
                .filter(
                  ({node}) =>
                    node.fileAbsolutePath.indexOf(`/${category}/`) > -1,
                )
                .map(({node}) => (
                  <Link key={node.id} to={node.frontmatter.path}>
                    {node.frontmatter.title}
                  </Link>
                ))}
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
          }
          fileAbsolutePath
        }
      }
    }
  }
`;
