"""Provides macros for working with yoga library."""

YOGA_ROOTS = ['//...']
JAVA_TARGET = '//java:java'
INFER_ANNOTATIONS_TARGET = '//lib/infer-annotations:infer-annotations'
JSR_305_TARGET = '//lib/jsr-305:jsr-305'
JUNIT_TARGET = '//lib/junit:junit'
PROGRUARD_ANNOTATIONS_TARGET = '//java/proguard-annotations/src/main/java/com/facebook/proguard/annotations:annotations'
SOLOADER_TARGET = '//lib/soloader:soloader'
GTEST_TARGET = '//lib/gtest:gtest'
JNI_TARGET = '//lib/jni:jni'
FBJNI_TARGET = '//lib/fb:fbjni'
FBJNI_JAVA_TARGET = '//lib/fb/src/main/java/com/facebook/jni:jni'
APPCOMPAT_TARGET = '//lib/appcompat:appcompat'
APPLE = ''
ANDROID = ''
ANDROID_SUPPORT_TARGET = '//lib/android-support:android-support'
ANDROID_TARGET = '//android:android'
ANDROID_JAVA_TARGET = '//android/src/main/java/com/facebook/yoga/android:android'
ANDROID_RES_TARGET = '//android:res'
ANDROID_SAMPLE_JAVA_TARGET = '//android/sample/java/com/facebook/samples/yoga:yoga'
ANDROID_SAMPLE_RES_TARGET = '//android/sample:res'

CXX_LIBRARY_WHITELIST = [
    '//:yoga',
    '//lib/fb:fbjni',
    '//java:jni',
]

BASE_COMPILER_FLAGS = [
    '-fno-omit-frame-pointer',
    '-fexceptions',
    '-Wall',
    '-Werror',
    '-O3',
    '-ffast-math',
]

LIBRARY_COMPILER_FLAGS = BASE_COMPILER_FLAGS + [
    '-fPIC',
]


def yoga_dep(dep):
    return '//' + dep


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
    native.cxx_library(*args, **kwargs)


def yoga_cxx_test(*args, **kwargs):
    native.cxx_test(*args, **kwargs)


def yoga_java_binary(*args, **kwargs):
    native.java_binary(*args, **kwargs)


def yoga_java_library(*args, **kwargs):
    native.java_library(*args, **kwargs)


def yoga_java_test(*args, **kwargs):
    native.java_test(*args, **kwargs)


def yoga_prebuilt_cxx_library(*args, **kwargs):
    native.prebuilt_cxx_library(*args, **kwargs)


def yoga_prebuilt_jar(*args, **kwargs):
    native.prebuilt_jar(*args, **kwargs)


def is_apple_platform():
    return True
