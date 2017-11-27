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
ANDROID_SUPPORT_TARGET = '//lib/android-support:android-support'
ANDROID_TARGET = '//android:android'
ANDROID_JAVA_TARGET = '//android/src/main/java/com/facebook/yoga/android:android'
ANDROID_RES_TARGET = '//android:res'
ANDROID_SAMPLE_JAVA_TARGET = '//android/sample/java/com/facebook/samples/yoga:yoga'
ANDROID_SAMPLE_RES_TARGET = '//android/sample:res'

THIS_IS_FBOBJC = False

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
