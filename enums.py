#!/usr/bin/env python3
# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

import os

ENUMS = {
    "Direction": ["Inherit", "LTR", "RTL"],
    "Unit": ["Undefined", "Point", "Percent", "Auto"],
    "FlexDirection": ["Column", "ColumnReverse", "Row", "RowReverse"],
    "Justify": [
        "FlexStart",
        "Center",
        "FlexEnd",
        "SpaceBetween",
        "SpaceAround",
        "SpaceEvenly",
    ],
    "Overflow": ["Visible", "Hidden", "Scroll"],
    "Align": [
        "Auto",
        "FlexStart",
        "Center",
        "FlexEnd",
        "Stretch",
        "Baseline",
        "SpaceBetween",
        "SpaceAround",
    ],
    "PositionType": ["Static", "Relative", "Absolute"],
    "Display": ["Flex", "None"],
    "Wrap": ["NoWrap", "Wrap", "WrapReverse"],
    "MeasureMode": ["Undefined", "Exactly", "AtMost"],
    "Dimension": ["Width", "Height"],
    "Edge": [
        "Left",
        "Top",
        "Right",
        "Bottom",
        "Start",
        "End",
        "Horizontal",
        "Vertical",
        "All",
    ],
    "NodeType": ["Default", "Text"],
    "LogLevel": ["Error", "Warn", "Info", "Debug", "Verbose", "Fatal"],
    "ExperimentalFeature": [
        # Mimic web flex-basis behavior (experiment may be broken)
        "WebFlexBasis",
        # Conformance fix: https://github.com/facebook/yoga/pull/1028
        "AbsolutePercentageAgainstPaddingEdge",
        # fix JNI local ref overflows
        "FixJNILocalRefOverflows",
    ],
    "PrintOptions": [
        ("Layout", 1 << 0),
        ("Style", 1 << 1),
        ("Children", 1 << 2),
    ],
    "Gutter": ["Column", "Row", "All"],
    # Known incorrect behavior which can be enabled for compatibility
    "Errata": [
        # Default: Standards conformant mode
        ("None", 0),
        # Allows main-axis flex basis to be stretched without flexGrow being
        # set (previously referred to as "UseLegacyStretchBehaviour")
        ("StretchFlexBasis", 1 << 0),
        # Enable all incorrect behavior (preserve compatibility)
        ("All", 0x7FFFFFFF),
        # Enable all errata except for "StretchFlexBasis" (Defaults behavior
        # before Yoga 2.0)
        ("Classic", 0x7FFFFFFF & (~(1 << 0))),
    ],
}

DO_NOT_STRIP = ["LogLevel"]

BITSET_ENUMS = ["PrintOptions", "Errata"]


def get_license(ext):
    return f"""{"/**" if ext == "js" else "/*"}
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// @{"generated"} by enums.py

"""


def _format_name(symbol, delimiter=None, transform=None):
    symbol = str(symbol)
    out = ""
    for i in range(0, len(symbol)):
        c = symbol[i]
        if str.istitle(c) and i != 0 and not str.istitle(symbol[i - 1]):
            out += delimiter or ""
        if transform is None:
            out += c
        else:
            out += getattr(c, transform)()
    return out


def to_java_upper(symbol):
    return _format_name(symbol, "_", "upper")


def to_hyphenated_lower(symbol):
    return _format_name(symbol, "-", "lower")


root = os.path.dirname(os.path.abspath(__file__))

# write out C & Objective-C headers
with open(root + "/yoga/YGEnums.h", "w") as f:
    f.write(get_license("cpp"))
    f.write("#pragma once\n")
    f.write("#include <yoga/YGMacros.h>\n\n")
    f.write("// clang-format off\n\n\n")

    f.write("YG_EXTERN_C_BEGIN\n\n")
    items = sorted(ENUMS.items())
    for name, values in items:
        if isinstance(values[0], tuple):
            f.write("YG_ENUM_DECL(\n")
        else:
            f.write("YG_ENUM_SEQ_DECL(\n")

        f.write("    YG%s,\n" % name)
        for value in values:
            if isinstance(value, tuple):
                f.write("    YG%s%s = %d" % (name, value[0], value[1]))
            else:
                f.write("    YG%s%s" % (name, value))
            if value == values[-1]:
                f.write(")\n")
            else:
                f.write(",\n")
        if name in BITSET_ENUMS:
            f.write("YG_DEFINE_ENUM_FLAG_OPERATORS(YG%s)\n" % name)
        f.write("\n")
    f.write("YG_EXTERN_C_END\n")

# write out C body for printing
with open(root + "/yoga/YGEnums.cpp", "w") as f:
    f.write(get_license("cpp"))
    f.write("#include <yoga/YGEnums.h>\n\n")
    items = sorted(ENUMS.items())
    for name, values in items:
        f.write("const char* YG%sToString(const YG%s value) {\n" % (name, name))
        f.write("  switch (value) {\n")
        for value in values:
            if isinstance(value, tuple):
                f.write("    case YG%s%s:\n" % (name, value[0]))
                f.write('      return "%s";\n' % to_hyphenated_lower(value[0]))
            else:
                f.write("    case YG%s%s:\n" % (name, value))
                f.write('      return "%s";\n' % to_hyphenated_lower(value))
        f.write("  }\n")
        f.write('  return "unknown";\n')
        f.write("}\n")
        if name != items[-1][0]:
            f.write("\n")

# write out java files
for name, values in sorted(ENUMS.items()):
    with open(root + "/java/com/facebook/yoga/Yoga%s.java" % name, "w") as f:
        f.write(get_license("java"))
        f.write("package com.facebook.yoga;\n\n")
        if name in DO_NOT_STRIP:
            f.write("import com.facebook.yoga.annotations.DoNotStrip;\n\n")
            f.write("@DoNotStrip\n")
        f.write("public enum Yoga%s {\n" % name)
        if len(values) > 0:
            for value in values:
                if isinstance(value, tuple):
                    f.write("  %s(%d)" % (to_java_upper(value[0]), value[1]))
                else:
                    f.write("  %s(%d)" % (to_java_upper(value), values.index(value)))
                if values.index(value) is len(values) - 1:
                    f.write(";\n")
                else:
                    f.write(",\n")
        else:
            f.write("__EMPTY(-1);")
        f.write("\n")
        f.write("  private final int mIntValue;\n")
        f.write("\n")
        f.write("  Yoga%s(int intValue) {\n" % name)
        f.write("    mIntValue = intValue;\n")
        f.write("  }\n")
        f.write("\n")
        f.write("  public int intValue() {\n")
        f.write("    return mIntValue;\n")
        f.write("  }\n")
        f.write("\n")
        if name in DO_NOT_STRIP:
            f.write("  @DoNotStrip\n")
        f.write("  public static Yoga%s fromInt(int value) {\n" % name)
        f.write("    switch (value) {\n")
        for value in values:
            if isinstance(value, tuple):
                f.write(
                    "      case %d: return %s;\n" % (value[1], to_java_upper(value[0]))
                )
            else:
                f.write(
                    "      case %d: return %s;\n"
                    % (values.index(value), to_java_upper(value))
                )
        f.write(
            '      default: throw new IllegalArgumentException("Unknown enum value: " + value);\n'
        )
        f.write("    }\n")
        f.write("  }\n")
        f.write("}\n")

# write out TypeScript file
with open(root + "/javascript/src/generated/YGEnums.ts", "w") as f:
    f.write(get_license("js"))
    enums = sorted(ENUMS.items())
    for enum_name, ordinals in enums:
        f.write(f"export enum {enum_name} {{\n")
        for ordinal_index, ordinal in enumerate(ordinals):
            ordinal_name = ordinal[0] if isinstance(ordinal, tuple) else ordinal
            ordinal_value = ordinal[1] if isinstance(ordinal, tuple) else ordinal_index
            f.write(f"  {ordinal_name} = {ordinal_value},\n")

        f.write("}\n\n")

    f.write("const constants = {\n")
    for enum_name, ordinals in enums:
        for ordinal in ordinals:
            ordinal_name = ordinal[0] if isinstance(ordinal, tuple) else ordinal
            ordinal_value = ordinal[1] if isinstance(ordinal, tuple) else ordinal_index
            f.write(
                f"  {to_java_upper(enum_name)}_{to_java_upper(ordinal_name)}: {enum_name}.{ordinal_name},\n"
            )

    f.write("}\n")
    f.write("export default constants")
