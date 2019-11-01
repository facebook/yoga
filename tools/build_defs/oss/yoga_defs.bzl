#
#  Copyright (c) Facebook, Inc. and its affiliates.
#
#  This source code is licensed under the MIT license found in the LICENSE
#  file in the root directory of this source tree.
#
"""Provides macros for working with yoga library."""

YOGA_ROOTS = ["//..."]

JAVA_TARGET = "//java:java"

JSR_305_TARGET = "//lib/jsr-305:jsr-305"

JUNIT_TARGET = "//lib/junit:junit"

PROGRUARD_ANNOTATIONS_TARGET = "//java/proguard-annotations/src/main/java/com/facebook/proguard/annotations:annotations"

SOLOADER_TARGET = "//lib/soloader:soloader"

GTEST_TARGET = "//lib/gtest:gtest"

JNI_TARGET = "//lib/jni:jni"

FBJNI_TARGET = "//lib/fb:fbjni"

FBJNI_JAVA_TARGET = "//lib/fb/src/main/java/com/facebook/jni:jni"

APPCOMPAT_TARGET = "//lib/appcompat:appcompat"

APPLE = ""

ANDROID = ""

ANDROID_SUPPORT_TARGET = "//lib/android-support:android-support"

ANDROID_TARGET = "//android:android"

ANDROID_JAVA_TARGET = "//android/src/main/java/com/facebook/yoga/android:android"

ANDROID_RES_TARGET = "//android:res"

ANDROID_SAMPLE_JAVA_TARGET = "//android/sample/java/com/facebook/samples/yoga:yoga"

ANDROID_SAMPLE_RES_TARGET = "//android/sample:res"

CXX_LIBRARY_WHITELIST = [
    "//:yoga",
    "//lib/fb:fbjni",
    "//java:jni",
]

BASE_COMPILER_FLAGS = [
    "-fno-omit-frame-pointer",
    "-fexceptions",
    "-fvisibility=hidden",
    "-ffunction-sections",
    "-fdata-sections",
    "-Wall",
    "-Werror",
    "-O2",
    "-std=c++11",
    "-DYG_ENABLE_EVENTS",
]

LIBRARY_COMPILER_FLAGS = BASE_COMPILER_FLAGS + [
    "-fPIC",
]

def _paths_join(path, *others):
    """Joins one or more path components."""
    result = path

    for p in others:
        if p.startswith("/"):  # absolute
            result = p
        elif not result or result.endswith("/"):
            result += p
        else:
            result += "/" + p

    return result

def subdir_glob(glob_specs, exclude = None, prefix = ""):
    """Returns a dict of sub-directory relative paths to full paths.

    The subdir_glob() function is useful for defining header maps for C/C++
    libraries which should be relative the given sub-directory.
    Given a list of tuples, the form of (relative-sub-directory, glob-pattern),
    it returns a dict of sub-directory relative paths to full paths.

    Please refer to native.glob() for explanations and examples of the pattern.

    Args:
      glob_specs: The array of tuples in form of
        (relative-sub-directory, glob-pattern inside relative-sub-directory).
        type: List[Tuple[str, str]]
      exclude: A list of patterns to identify files that should be removed
        from the set specified by the first argument. Defaults to [].
        type: Optional[List[str]]
      prefix: If is not None, prepends it to each key in the dictionary.
        Defaults to None.
        type: Optional[str]

    Returns:
      A dict of sub-directory relative paths to full paths.
    """
    if exclude == None:
        exclude = []

    results = []

    for dirpath, glob_pattern in glob_specs:
        results.append(
            _single_subdir_glob(dirpath, glob_pattern, exclude, prefix),
        )

    return _merge_maps(*results)

def _merge_maps(*file_maps):
    result = {}
    for file_map in file_maps:
        for key in file_map:
            if key in result and result[key] != file_map[key]:
                fail(
                    "Conflicting files in file search paths. " +
                    "\"%s\" maps to both \"%s\" and \"%s\"." %
                    (key, result[key], file_map[key]),
                )

            result[key] = file_map[key]

    return result

def _single_subdir_glob(dirpath, glob_pattern, exclude = None, prefix = None):
    if exclude == None:
        exclude = []
    results = {}
    files = native.glob([_paths_join(dirpath, glob_pattern)], exclude = exclude)
    for f in files:
        if dirpath:
            key = f[len(dirpath) + 1:]
        else:
            key = f
        if prefix:
            key = _paths_join(prefix, key)
        results[key] = f

    return results

def yoga_dep(dep):
    return "//" + dep

def yoga_cxx_lib(lib):
    return yoga_dep(lib)

def yoga_android_aar(*args, **kwargs):
    native.android_aar(*args, **kwargs)

def yoga_android_binary(*args, **kwargs):
    native.android_binary(*args, **kwargs)

def yoga_android_library(*args, **kwargs):
    native.android_library(*args, **kwargs)

def yoga_android_resource(*args, **kwargs):
    native.android_resource(*args, **kwargs)

def yoga_apple_library(*args, **kwargs):
    native.apple_library(*args, **kwargs)

def yoga_apple_test(*args, **kwargs):
    native.apple_test(*args, **kwargs)

def yoga_cxx_binary(*args, **kwargs):
    kwargs.pop("platforms", None)
    native.cxx_binary(*args, **kwargs)

def yoga_cxx_library(*args, **kwargs):
    # Currently unused
    kwargs.pop("platforms", None)
    kwargs.pop("allow_jni_merging", None)

    native.cxx_library(*args, **kwargs)

def yoga_cxx_test(*args, **kwargs):
    native.cxx_test(*args, **kwargs)

def yoga_java_binary(*args, **kwargs):
    native.java_binary(*args, **kwargs)

def yoga_java_library(*args, **kwargs):
    native.java_library(*args, **kwargs)

def yoga_java_test(*args, **kwargs):
    kwargs["deps"] = kwargs.get("deps", []) + ["//lib/hamcrest:hamcrest"]
    native.java_test(*args, **kwargs)

def yoga_prebuilt_cxx_library(*args, **kwargs):
    native.prebuilt_cxx_library(*args, **kwargs)

def yoga_prebuilt_jar(*args, **kwargs):
    native.prebuilt_jar(*args, **kwargs)

def is_apple_platform():
    return True

def yoga_apple_binary():
    if is_apple_platform():
        yoganet_ios_srcs = []
        for arch in [
            "iphonesimulator-x86_64",
            "iphoneos-arm64",
        ]:
            name = "yoganet-" + arch
            yoganet_ios_srcs.append(":" + name)
            native.genrule(
                name = name,
                srcs = [
                    yoga_dep(":yogaApple#%s,static" % arch),
                    yoga_dep("YogaKit:YogaKitApple#%s,static" % arch),
                    yoga_dep("csharp:yoganetApple#%s,static" % arch),
                ],
                out = "libyoga-%s.a" % arch,
                cmd = "libtool -static -o $OUT $SRCS",
                visibility = [yoga_dep("csharp:yoganet-ios")],
            )

        native.genrule(
            name = "yoganet-ios",
            srcs = yoganet_ios_srcs,
            out = "libyoga.a",
            cmd = "lipo $SRCS -create -output $OUT",
            visibility = ["PUBLIC"],
        )

        yoganet_macosx_target = "csharp:yoganetAppleMac#macosx-%s,dynamic"
        native.genrule(
            name = "yoganet-macosx",
            srcs = [
                yoga_dep(yoganet_macosx_target % "x86_64"),
            ],
            out = "libyoga.dylib",
            cmd = "lipo $SRCS -create -output $OUT",
            visibility = ["PUBLIC"],
        )
