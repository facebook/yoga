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
]

LIBRARY_COMPILER_FLAGS = BASE_COMPILER_FLAGS + [
  '-fPIC',
]


def yoga_dep(dep):
  return '//' + dep


_original_android_aar = android_aar
def android_aar(*args, **kwargs):
    _original_android_aar(*args, **kwargs)


_original_android_binary = android_binary
def android_binary(*args, **kwargs):
  _original_android_binary(*args, **kwargs)


_original_android_library = android_library
def android_library(*args, **kwargs):
  _original_android_library(*args, **kwargs)


_original_android_resource = android_resource
def android_resource(*args, **kwargs):
  _original_android_resource(*args, **kwargs)


_original_apple_library = apple_library
def apple_library(*args, **kwargs):
  _original_apple_library(*args, **kwargs)


_original_apple_test = apple_test
def apple_test(*args, **kwargs):
  _original_apple_test(*args, **kwargs)


_original_cxx_library = cxx_library
def cxx_library(*args, **kwargs):
  # Currently unused
  kwargs.pop("platforms", None)
  _original_cxx_library(*args, **kwargs)


_original_cxx_test = cxx_test
def cxx_test(*args, **kwargs):
  _original_cxx_test(*args, **kwargs)


_original_java_binary = java_binary
def java_binary(*args, **kwargs):
  _original_java_binary(*args, **kwargs)


_original_java_library = java_library
def java_library(*args, **kwargs):
  _original_java_library(*args, **kwargs)


_original_java_test = java_test
def java_test(*args, **kwargs):
    _original_java_test(*args, **kwargs)


_original_prebuilt_cxx_library = prebuilt_cxx_library
def prebuilt_cxx_library(*args, **kwargs):
    _original_prebuilt_cxx_library(*args, **kwargs)


_original_prebuilt_jar = prebuilt_jar
def prebuilt_jar(*args, **kwargs):
  _original_prebuilt_jar(*args, **kwargs)


def is_apple_platform():
  return True

