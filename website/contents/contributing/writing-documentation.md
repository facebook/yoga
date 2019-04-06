---
path: "/contributing/writing-documentation"
title: "Writing Documentation"
hasPlayground: false
---

## Writing Documentation

Documentation pages are generated from Markdown files in `contents/`.
The files are organized in 4 sections/folders (getting-started, properties,
examples, contributing) which are dynamically listed on the docs overview page.
The Markdown files should contain a header with metadata.

```markdown
---
path: "docs/flexDirection"
title: "Flex Direction"
hasPlayground: true
initialPlayground: eyJ3aWR0aCI6IjYwMCIsImhlaWdodCI6NTAwLCJjaGlsZHJlbiI6W3t9LHt9LHt9XX0=
---
```

- The `path` indicates the URL path this page will be available at.
- The `title` is used as the page's HTML-title and when referencing
  the file from the documentation overview.
- The `hasPlayground` property indicates whether this documentation
  has an associated playground to test out the documented feature.
- The `initialPlayground` property is only relevant for documentation
  pages with playgrounds and contains the initial playground state.
  This base64 string is a reference to the hash (content after #)
  of a [playground](/playground) url.
 - The `redirect` property allows to redirect to the other page, the path of which is mentioned in the property `path`.


Within the markdown of a documentation page which has an associated
playground you can add controls to let the user play around with the feature
directly from the documenation page.

```markdown
<controls prop="alignContent"></controls>
```

If you would like to redirect to another page (potentially an external link) the header would look something like this.

```markdown
---
path: "/playground?eyJ3aWR0aCI6IjYwMCIsImhlaWdodCI6NTAwLCJjaGlsZHJlbiI6W3t9LHt9LHt9XX0="
title: "Flex Direction"
redirect: true
---

```
