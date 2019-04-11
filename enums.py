# Copyright (c) Facebook, Inc. and its affiliates.
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
    "PositionType": ["Relative", "Absolute"],
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
        # Mimic web flex-basis behavior.
        "WebFlexBasis"
    ],
    "PrintOptions": [("Layout", 1), ("Style", 2), ("Children", 4)],
}

LICENSE = """/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

"""


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
    f.write(LICENSE)
    f.write("#pragma once\n\n")
    f.write('#include "YGMacros.h"\n\n')
    f.write("YG_EXTERN_C_BEGIN\n\n")
    for name, values in sorted(ENUMS.items()):
        f.write("#define YG%sCount %s\n" % (name, len(values)))
        f.write("typedef YG_ENUM_BEGIN(YG%s) {\n" % name)
        for value in values:
            if isinstance(value, tuple):
                f.write("  YG%s%s = %d,\n" % (name, value[0], value[1]))
            else:
                f.write("  YG%s%s,\n" % (name, value))
        f.write("} YG_ENUM_END(YG%s);\n" % name)
        f.write(
            "WIN_EXPORT const char *YG%sToString(const YG%s value);\n" % (name, name)
        )
        f.write("\n")
    f.write("YG_EXTERN_C_END\n")

# write out C body for printing
with open(root + "/yoga/YGEnums.cpp", "w") as f:
    f.write(LICENSE)
    f.write('#include "YGEnums.h"\n\n')
    for name, values in sorted(ENUMS.items()):
        f.write("const char *YG%sToString(const YG%s value){\n" % (name, name))
        f.write("  switch(value){\n")
        for value in values:
            if isinstance(value, tuple):
                f.write("    case YG%s%s:\n" % (name, value[0]))
                f.write('      return "%s";\n' % to_log_lower(value[0]))
            else:
                f.write("    case YG%s%s:\n" % (name, value))
                f.write('      return "%s";\n' % to_log_lower(value))
        f.write("  }\n")
        f.write('  return "unknown";\n')
        f.write("}\n\n")

# write out java files
for name, values in sorted(ENUMS.items()):
    with open(root + "/java/com/facebook/yoga/Yoga%s.java" % name, "w") as f:
        f.write(LICENSE.replace("/**", "/*", 1))
        f.write("package com.facebook.yoga;\n\n")
        f.write("import com.facebook.proguard.annotations.DoNotStrip;\n\n")
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
        f.write("  private int mIntValue;\n")
        f.write("\n")
        f.write("  Yoga%s(int intValue) {\n" % name)
        f.write("    mIntValue = intValue;\n")
        f.write("  }\n")
        f.write("\n")
        f.write("  public int intValue() {\n")
        f.write("    return mIntValue;\n")
        f.write("  }\n")
        f.write("\n")
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
        f.write(LICENSE)
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
with open(root + "/javascript/sources/YGEnums.js", "w") as f:
    f.write(LICENSE)
    f.write("module.exports = {\n\n")
    for name, values in sorted(ENUMS.items()):
        f.write("  %s_COUNT: %s,\n" % (to_java_upper(name), len(values)))
        base = 0
        for value in values:
            if isinstance(value, tuple):
                f.write(
                    "  %s_%s: %d,\n"
                    % (to_java_upper(name), to_java_upper(value[0]), value[1])
                )
                base = value[1] + 1
            else:
                f.write(
                    "  %s_%s: %d,\n" % (to_java_upper(name), to_java_upper(value), base)
                )
                base += 1
        f.write("\n")
    f.write("};\n")
