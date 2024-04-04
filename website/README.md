# Yoga legacy documentation and playground

This site uses [gatsby.js](https://www.gatsbyjs.org/) as static site generator. Which transforms all markdown and react code to static HTML and JS files.

## Development
```
yarn install
yarn develop
```

### Structure
Documentation pages are generated from the Markdown files in `contents/`. The files are organized in 4 sections/folders (getting-started, properties, examples, contributing) which are dynamically listed on the docs overview page. The Markdown files can have some header files containing metadata.

```
---
path: "docs/flexDirection"
title: "Flex Direction"
hasPlayground: true
editableProperties: ['flexDirection']
---
```

The `path` can be any URL this page should be available at. The `title` is used as the page's HTML-title and when referencing the file from the documentation overview. There are two kinds of templates for a page: with and without playground. `hasPlayground` selects the corresponding template (`src/templates/{with|without}Playground.js`). When using `hasPlayground: true`, `editableProperties` can list all Yoga properties which are editable in the playground.

### Design
We are using [antd](https://ant.design) for various UI elements. See their documentation for the components available. `gatsby-config.js` can be used to overwrite LESS-variables from antd.

For styling react components we create a CSS-file with the same name next to each component and import it in the component. E.g. there is `index.js` and `index.css`. In the react-component we import the stylesheet: `import './index.css'`.

## Build
To generate the static files run:
```
yarn build
```
The output will be in `public/` and can be published on GitHub pages.
