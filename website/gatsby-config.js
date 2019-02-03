/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @flow
 * @format
 */

module.exports = {
  siteMetadata: {
    title: 'Yoga Layout',
  },
  plugins: [
    // using latest react version
    'gatsby-plugin-react-next',
    // setting head data like title from within components
    'gatsby-plugin-react-helmet',
    {
      resolve: `gatsby-plugin-less`,
      options: {
        theme: {
          'primary-color': '#6BCEBB',
        },
      },
    },
    // plugin for importing antd components
    {
      resolve: 'gatsby-plugin-antd',
      options: {
        style: true,
      },
    },
    // reading files from the file-system (used for markdown files)
    {
      resolve: `gatsby-source-filesystem`,
      options: {
        path: `${__dirname}/contents`,
        name: 'markdown-pages',
      },
    },
    // parse markdown files, used for content files
    {
      resolve: `gatsby-transformer-remark`,
      options: {
        // code-highlighting in markdown files
        plugins: [
          {
            resolve: `gatsby-remark-prismjs`,
            options: {
              classPrefix: 'language-',
            },
          },
        ],
      },
    },
    {
      resolve: `gatsby-plugin-google-analytics`,
      options: {
        trackingId: 'UA-44373548-24',
        head: false,
        anonymize: true,
      },
    },
  ],
};
