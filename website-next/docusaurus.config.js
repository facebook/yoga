/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// @ts-check

import {themes as prismThemes} from 'prism-react-renderer';

/** @type {import('@docusaurus/types').Config} */
export default {
  title: 'Yoga',
  tagline:
    'Build flexible layouts on any platform with a highly optimized open source layout engine designed with speed, size, and ease of use in mind.',
  favicon: 'img/favicon.png',

  url: 'https:/yogalayout.dev',
  baseUrl: '/',

  organizationName: 'facebook',
  projectName: 'yoga',

  onBrokenLinks: 'throw',
  onBrokenMarkdownLinks: 'warn',

  i18n: {
    defaultLocale: 'en',
    locales: ['en'],
  },

  presets: [
    [
      'classic',
      /** @type {import('@docusaurus/preset-classic').Options} */
      ({
        docs: {
          sidebarPath: require.resolve('./sidebars.cjs'),
          editUrl: 'https://github.com/facebook/yoga/tree/main/website',
        },
        blog: {
          showReadingTime: true,
          editUrl: 'https://github.com/facebook/yoga/tree/main/website',
        },
        theme: {
          customCss: require.resolve('./src/css/custom.css'),
        },
      }),
    ],
  ],

  themeConfig:
    /** @type {import('@docusaurus/preset-classic').ThemeConfig} */
    ({
      navbar: {
        title: 'Yoga',
        logo: {
          alt: 'Yoga Logo',
          src: 'img/logo.svg',
        },
        items: [
          {
            type: 'docSidebar',
            sidebarId: 'docsSidebar',
            position: 'left',
            label: 'Documentation',
          },
          {to: '/playground', label: 'Playground', position: 'left'},
          {to: '/blog', label: 'Blog', position: 'left'},
          {
            href: 'https://github.com/facebook/yoga',
            label: 'GitHub',
            position: 'right',
          },
        ],
      },
      footer: {
        style: 'dark',
        logo: {
          alt: 'Meta Open Source',
          src: 'img/meta_oss.svg',
          href: 'https://opensource.fb.com',
          width: 300,
          height: 64,
        },
        links: [
          {
            title: 'Docs',
            items: [
              {
                label: 'Tutorial',
                to: '/docs/intro',
              },
            ],
          },
          {
            title: 'Community',
            items: [
              {
                label: 'Stack Overflow',
                href: 'https://stackoverflow.com/questions/tagged/yoga',
              },
              {
                label: 'Twitter',
                href: 'https://twitter.com/yogalayout',
              },
            ],
          },
          {
            title: 'More',
            items: [
              {
                label: 'Blog',
                to: '/blog',
              },
              {
                label: 'GitHub',
                href: 'https://github.com/facebook/yoga',
              },
            ],
          },
        ],
        copyright: `Copyright © ${new Date().getFullYear()} Meta Platforms, Inc.`,
      },
      prism: {
        theme: prismThemes.github,
        darkTheme: prismThemes.oneDark,
        additionalLanguages: ['gradle', 'java', 'json', 'json5', 'ruby'],
      },
      colorMode: {
        defaultMode: 'dark',
        respectPrefersColorScheme: true,
      },
    }),
};
