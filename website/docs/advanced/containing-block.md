---
sidebar_position: 2
---

import Tabs from '@theme/Tabs';
import TabItem from '@theme/TabItem';
import Playground from '@site/src/components/Playground';

# Containing block

Often times certain properties depend on a node beyond the
one it is applied to. An example of this is percentage lengths like `width: 50%` which
will set the width of a node to 50% of some other length. That other length is determined
by the size of the _containing block_. A containing block is not a Yoga-specific
concept and exists in the [web](https://developer.mozilla.org/en-US/docs/Web/CSS/Containing_block),
but since Yoga only implements a subset of web browser capabilities the behavior of
containing blocks is much more streamlined and it is helpful to frame it differently.

### Identifying the containing block of a node

- If the [position type](/docs/styling/position) of a node is static or relative then the containing block
  is always the _content box_ of the parent. This is because in Yoga every node is a
  flex container and therefore establishes a formatting context which would form a
  containing block on the web. The content box is formed by the node without margin, padding, or borders.
- If the [position type](/docs/styling/position) of a node is absolute then the containing block will be
  the _padding box_ (the content box plus padding) of any of:
  - The nearest non-static ancestor.
  - The nearest ancestor which is configured to always form a containing block. This
    is helpful for supporting things outside of Yoga which would form a containing block
    on the web, such as [filters](https://developer.mozilla.org/en-US/docs/Web/CSS/filter)
    or [transforms](https://developer.mozilla.org/en-US/docs/Web/CSS/transform). This
    is done by calling the corresponding API for the language you are working in.
    <Tabs groupId="language">
    <TabItem value="cpp" label="C/C++">
    ```cpp
    YGNodeSetAlwaysFormsContainingBlock(node, true /*alwaysFormsContainingBlock*/);
    ```
    </TabItem>
    <TabItem value="java" label="Java">
    ```java
    node.setAlwaysFormsContainingBlock(true /*alwaysFormsContainingBlock*/);
    ```
    </TabItem>
    <TabItem value="js" label="JavaScript">
    ```typescript
    node.setAlwaysFormsContainingBlock(true /*alwaysFormsContainingBlock*/);
    ```
    </TabItem>
    </Tabs>
  - The root if none of the above apply. Note that this is different from the web
    which has the notion of the _initial containing block_ that depends on the size
    of the viewport.
- If the node in question is the root then there is no containing block, but it will
  use the `availableWidth` and `availableHeight` that is passed in to the call to
  [`CalculateLayout`](/docs/getting-started/laying-out-a-tree).

### What the containing block affects

- Any percentage-based lengths will depend on the size of the containing block.
  Specifically the [height](/docs/styling/width-height), top, and bottom properties will use the height of the
  containing block. The [width](/docs/styling/width-height), left, right, [margin](/docs/styling/margin-padding-border),
  and [padding](/docs/styling/margin-padding-border) will use the width of the containing block.
- Any insets (left, right, top, bottom, etc.) applied to absolute nodes will be
  relative to the corresponding edge of the containing block.

<Playground code={`<Layout config={{useWebDefaults: false}}>
  <Node
    style={{
      width: 200,
      height: 200,
      padding: 10
    }}>
    <Node
      style={{
        height: 100,
        width: 100,
        position: 'static'
      }}>
      <Node
        style={{
          height: 25,
          width: '50%',
          bottom: 10,
          position: 'absolute'
        }}
      />
    </Node>
  </Node>
</Layout>`} />
