#!/usr/bin/env bash

FILES=$(find . \( -path ./buck-out -o -path ./lib \) -prune -o \
  \( -name  \*.h -o -name \*.c -o -name \*.cpp \) -print)

for f in $FILES "$@"; do
  clang-format \
    -style="{ \
      AlignAfterOpenBracket: Align, \
      AlignEscapedNewlinesLeft: true, \
      AlignOperands: true, \
      AllowAllParametersOfDeclarationOnNextLine: false, \
      AllowShortBlocksOnASingleLine: false, \
      AllowShortCaseLabelsOnASingleLine: false, \
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
      PenaltyBreakString: 1000, \
      PenaltyExcessCharacter: 100, \
      PenaltyReturnTypeOnItsOwnLine: 100, \
      PointerAlignment: Right, \
      SortIncludes: true, \
      SpaceAfterCStyleCast: true, \
      UseTab: Never, \
      ObjCSpaceAfterProperty: true, \
    }" -i "$f"
done
