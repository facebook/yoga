# yoga-layout

This package provides prebuilt WebAssembly bindings for the Yoga layout engine.

See more at https://yogalayout.dev

## Usage

```ts
import {Yoga, Align} from 'yoga-layout';

const node = Yoga.Node.create();
node.setAlignContent(Align.Center);
```

## Requirements

`yoga-layout` requires a toolchain that supports ES Modules and top-level await.

If top-level-await is not supported, use the `yoga-layout/load` entry point instead. This requires to load yoga manually:

```ts
import {loadYoga, Align} from 'yoga-layout/load';

const node = (await loadYoga()).Node.create();
node.setAlignContent(Align.Center);
```
