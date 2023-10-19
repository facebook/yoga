# yoga-layout

This package provides prebuilt WebAssembly bindings for the Yoga layout engine.

## Usage

```ts
import {Yoga, Align} from 'yoga-layout';

const node = Yoga.Node.create();
node.setAlignContent(Align.Center);
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

## Using TypeScript

This package provides out-of-the-box TypeScript typings so long as `tsc` is configured to support ESM resolution. It is recommended to set `moduleResolution: 'bundler'` or `moduleResolution: node16` in your `tsconfig.json` according to your environment.

## ES Modules

`yoga-layout` is only provided as an ES Module, relying on top-level await. This allows providing a synchronous API, while still allowing async WebAssembly compilation in browsers, and will allow eventual usage of ESM/WASM interop.

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
