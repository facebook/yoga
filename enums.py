# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

from __future__ import absolute_import, division, print_function, unicode_literals

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
        # Conformance fix: https://github.com/facebook/yoga/pull/1028
        "FixAbsoluteTrailingColumnMargin",
    ],
    "PrintOptions": [("Layout", 1), ("Style", 2), ("Children", 4)],
    "Gutter": ["Column", "Row", "All"],
}

# Generated Java enums used to emit @DoNotStrip, but D17519844 removed them
# manually from all but YogaLogLevel. TODO: Is it safe to remove from it as
# well?
DO_NOT_STRIP = ["LogLevel"]


def get_license(ext):
    prologue = "/**" if ext == "js" else "/*"
    return """{}
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// @{} by enums.py

""".format(
        prologue, "generated"
    )


def to_java_upper(symbol):
    symbol = str(symbol)
    out = ""
    for i in range(0, len(symbol)):
        c = symbol[i]
        if str.istitle(c) and i is not 0 and not str.istitle(symbol[i - 1]):
            out += "_"
        out += c.upper()
    return out


def to_log_lower(symbol):
    symbol = str(symbol)
    out = ""
    for i in range(0, len(symbol)):
        c = symbol[i]
        if str.istitle(c) and i is not 0 and not str.istitle(symbol[i - 1]):
            out += "-"
        out += c.lower()
    return out


root = os.path.dirname(os.path.abspath(__file__))

# write out C & Objective-C headers
with open(root + "/yoga/YGEnums.h", "w") as f:
    f.write(get_license("cpp"))
    f.write("#pragma once\n")
    f.write('#include "YGMacros.h"\n\n')
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
        f.write("\n")
    f.write("YG_EXTERN_C_END\n")

# write out C body for printing
with open(root + "/yoga/YGEnums.cpp", "w") as f:
    f.write(get_license("cpp"))
    f.write('#include "YGEnums.h"\n\n')
    items = sorted(ENUMS.items())
    for name, values in items:
        f.write("const char* YG%sToString(const YG%s value) {\n" % (name, name))
        f.write("  switch (value) {\n")
        for value in values:
            if isinstance(value, tuple):
                f.write("    case YG%s%s:\n" % (name, value[0]))
                f.write('      return "%s";\n' % to_log_lower(value[0]))
            else:
                f.write("    case YG%s%s:\n" % (name, value))
                f.write('      return "%s";\n' % to_log_lower(value))
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

# write out csharp files
for name, values in sorted(ENUMS.items()):
    with open(root + "/csharp/Facebook.Yoga/Yoga%s.cs" % name, "w") as f:
        f.write(get_license("cs"))
        f.write("namespace Facebook.Yoga\n{\n")
        if isinstance(next(iter(values or []), None), tuple):
            f.write("    [System.Flags]\n")
        f.write("    public enum Yoga%s\n    {\n" % name)
        for value in values:
            if isinstance(value, tuple):
                f.write("        %s = %d,\n" % (value[0], value[1]))
            else:
                f.write("        %s,\n" % value)
        f.write("    }\n")
        f.write("}\n")

# write out javascript file
with open(root + "/javascript/src_js/generated/YGEnums.js", "w") as f:
    f.write(get_license("js"))
    items = sorted(ENUMS.items())
    for name, values in items:
        base = 0
        for value in values:
            value_arg = value[0] if isinstance(value, tuple) else value
            ordinal_arg = value[1] if isinstance(value, tuple) else base

            f.write(
                "exports.%s_%s = %d;\n"
                % (to_java_upper(name), to_java_upper(value_arg), ordinal_arg)
            )
            base = ordinal_arg + 1

        if name != items[-1][0]:
            f.write("\n")

with open(root + "/javascript/src_js/generated/YGEnums.d.ts", "w") as f:
    f.write(get_license("js"))

    for name, values in sorted(ENUMS.items()):
        base = 0
        for value in values:
            value_arg = value[0] if isinstance(value, tuple) else value
            ordinal_arg = value[1] if isinstance(value, tuple) else base

            f.write(
                (
                    "type {name}_{value} = {ordinal} & ['{name}']\n"
                    + "export const {name}_{value}: {name}_{value};\n\n"
                ).format(
                    name=to_java_upper(name),
                    value=to_java_upper(value_arg),
                    ordinal=ordinal_arg,
                )
            )

            base = ordinal_arg + 1

        f.write("\n")

    for name, values in sorted(ENUMS.items()):
        f.write("export type {} =\n".format(name))
        for value in values:
            unpackedValue = value[0] if isinstance(value, tuple) else value
            f.write(
                "  | typeof {}_{}".format(
                    to_java_upper(name), to_java_upper(unpackedValue)
                )
            )
            if values[-1] == value:
                f.write(";\n")
            else:
                f.write("\n")

        f.write("\n")
