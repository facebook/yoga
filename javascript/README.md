# yoga-layout

This package provides prebuilt WebAssembly bindings for the Yoga layout engine.

See more at https://yogalayout.dev

## Usage

```ts
import { Align, Yoga } from "yoga-layout";

const node = Yoga.Node.create();
node.setAlignContent(Align.Center);
```

Objects created by `Yoga.<>.create()` are not automatically garbage collected
and should be freed once they are no longer in use.

```ts
// Free a config
config.free();

// Free a tree of Nodes
node.freeRecursive();

// Free a single Node
node.free();
```

## Requirements

`yoga-layout` requires a toolchain that supports ES Modules and top-level await.

If top-level-await is not supported, use the `yoga-layout/load` entry point
instead. This requires to load yoga manually:

```ts
import { Align, loadYoga } from "yoga-layout/load";

const node = (await loadYoga).Node.create();
node.setAlignContent(Align.Center);
```

You can also use `yoga-layout/loadSeparate`, which has the exactly same api as
`yoga-layout/load`, if you want the js and wasm in separate files, this can
useful in several scenarios such as avoiding
[unsafe-wasm-eval](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Content-Security-Policy/script-src#unsafe_webassembly_execution).
Do be aware that this option might not work out of the box with any and all
bundlers or frameworks
