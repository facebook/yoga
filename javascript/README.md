# yoga-layout

This package provides prebuilt JavaScript bindings for the Yoga layout engine. Both WebAssembly and asm.js variants are packaged, with the optimal loaded based on platform.

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

Objects created by `Yoga.<>.create()` are not automatically garbage collected and should be freed once they are no longer in use.

```ts
// Free a config
config.free();

// Free a tree of Nodes
node.freeRecursive();

// Free a single Node
node.free();
```

## Selecting WebAssembly or asm.js

For better performance and smaller packages, WebAssembly is preferred to asm.js where available. `yoga-layout` tries to provide the right default using [export maps](https://webpack.js.org/guides/package-exports/#conditional-syntax) so that platforms which can take advantage of WebAssembly use it by default.

A specific entrypoint may be specified on platforms which do not understand export conditions.

```ts
import { loadYoga } from "yoga-layout/dist/entrypoint/wasm-async";
```


## Contributing

### Requirements

1. Emscripten SDK
1. CMake >= 3.13
1. (Optional) ninja, for faster builds

### Building

```bash
git clone https://github.com/facebook/yoga.git
cd yoga/javascript
yarn install
yarn build
```

### Testing

```bash
# Build and test all entrypoints
yarn test

# Build and test a specific entrypoint
yarn test:asmjs-sync
```
