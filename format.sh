#!/usr/bin/env bash

clang-format \
  -style="{ \
    AlignEscapedNewlinesLeft: true, \
    AlignOperands: true, \
    AllowAllParametersOfDeclarationOnNextLine: false, \
    AllowShortBlocksOnASingleLine: false, \
    AllowShortCaseLabelsOnASingleLine: true, \
    AllowShortFunctionsOnASingleLine: false, \
    AllowShortIfStatementsOnASingleLine: false, \
    AllowShortLoopsOnASingleLine: false, \
    BinPackArguments: false, \
    BinPackParameters: false, \
    BreakBeforeBraces: Attach, \
    ColumnLimit: 100, \
    ContinuationIndentWidth: 4, \
    IndentCaseLabels: true, \
    IndentWidth: 2, \
    KeepEmptyLinesAtTheStartOfBlocks: false, \
    Language: Cpp, \
    PenaltyBreakBeforeFirstCallParameter: 100, \
    PenaltyBreakString: 100, \
    PenaltyExcessCharacter: 100, \
    PointerAlignment: Right, \
    SortIncludes: true, \
    SpaceAfterCStyleCast: true, \
    UseTab: Never, \
  }" "$@" \
  -i $(dirname $0)/**/*.{h,c,cpp}
