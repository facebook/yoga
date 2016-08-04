#!/usr/bin/env bash

clang-format \
  -style="{ \
    BasedOnStyle: WebKit, \
    IndentWidth: 2, \
    ColumnLimit: 100, \
    BreakBeforeBraces: Attach, \
    BinPackParameters: false, \
    PointerAlignment: Right, \
  }" "$@" \
  -i ./**/*.{h,c,cpp}
