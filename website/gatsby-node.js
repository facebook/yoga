/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @flow
 * @format
 */

const path = require('path');

exports.createPages = ({boundActionCreators, graphql}) => {
  const {createPage} = boundActionCreators;
  const withPlayground = path.resolve(`src/templates/withPlayground.js`);
  const withoutPlayground = path.resolve(`src/templates/withoutPlayground.js`);

  return graphql(`
    {
      allMarkdownRemark {
        edges {
          node {
            frontmatter {
              path
              title
              hasPlayground
              initialPlayground
              redirect
            }
            html
          }
        }
      }
    }
  `).then(result => {
    if (result.errors) {
      return Promise.reject(result.errors);
    }

    result.data.allMarkdownRemark.edges.forEach(({node}) => {
      if (!node.frontmatter.redirect) {
        createPage({
          path: node.frontmatter.path,
          component: node.frontmatter.hasPlayground
            ? withPlayground
            : withoutPlayground,
          context: node,
        });
      }
    });
  });
};
