---
path: "contributing/writing-documentation"
title: "Writing Documentation"
hasPlayground: false
---

## Writing Documentation

Documentation pages are generated from the Markdown files in `contents/`. The files are organized in 4 sections/folders (getting-started, properties, examples, contributing) which are dynamically listed on the docs overview page. The Markdown files can have some header files containing metadata.

```markdown
---
path: "docs/flexDirection"
title: "Flex Direction"
hasPlayground: true
initialPlayground: eyJ3aWR0aCI6IjYwMCIsImhlaWdodCI6NTAwLCJjaGlsZHJlbiI6W3t9LHt9LHt9XX0=
---
```

The `path` can be any URL this page should be available at. The `title` is used as the page's HTML-title and when referencing the file from the documentation overview. There are two kinds of templates for a page: with and without playground. `hasPlayground` selects the corresponding template (`src/templates/{with|without}Playground.js`). With `hasPlayground: true`, one can add a flex control which can be placed inline with the text in markdown. For example you can do the following,

```markdown
## Align Content

The property defines the distribution of lines along the cross-axis. This only
has effect when items are wrapped to multiple lines (see [flexWrap](flex-wrap)).

<controls prop="alignContent"></controls>

```

There is one more metadata property called `initialPlayground` which allows to provide the custom playground for the documentation. For getting the playground id, create custom yoga layout in [playground](/playground) and copy the string after # from playground URL. For example if playground URL looks like this `https://yogalayout.com/playground#<PLAYGROUND_ID>`, then playground id is the string after `#`. If it isn't the one like in the previous format then actually its default playground, so one can skip this field.



