# yoga-layout

This package provides JavaScript bindings for the Yoga layout engine as either WebAssembly (for browsers, Node) or asm.js (other clients or clients unable to read package export maps).

## Usage

The default entrypoint provides an asynchronous loader function to return a Yoga instance.

```ts
import { loadYoga, ALIGN_CENTER } from "yoga-layout";

const Yoga = await loadYoga();

const node = Yoga.Node.create();
node.setAlignContent(ALIGN_CENTER);
```

An alternative synchronous API is provided for compatibility, but requires using asm.js in browsers instead of WebAssembly, leading to worse performance and larger assets.

```ts
import Yoga, { ALIGN_CENTER } from "yoga-layout/sync";

const node = Yoga.Node.create();
node.setAlignContent(ALIGN_CENTER);
```
