/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include <CSSLayout/CSSLayout.h>
#include <jni.h>

#define JNI_VERSION JNI_VERSION_1_6

#define CSS_NODE_JNI(type, func) JNIEXPORT type JNICALL Java_com_facebook_csslayout_CSSNodeJNI_jni_1##func

#define CSS_NODE_JNI_STYLE_PROP(javatype, type, name) \
CSS_NODE_JNI(javatype, CSSNodeStyleGet##name(JNIEnv *env, jobject instance, jint nativePointer) { \
  return (javatype) CSSNodeStyleGet##name((CSSNodeRef) nativePointer); \
}) \
 \
CSS_NODE_JNI(void, CSSNodeStyleSet##name(JNIEnv *env, jobject instance, jint nativePointer, javatype value) { \
  CSSNodeStyleSet##name((CSSNodeRef) nativePointer, (type) value); \
})

#define CSS_NODE_JNI_LAYOUT_PROP(javatype, type, name) \
CSS_NODE_JNI(javatype, CSSNodeLayoutGet##name(JNIEnv *env, jobject instance, jint nativePointer) { \
  return (javatype) CSSNodeLayoutGet##name((CSSNodeRef) nativePointer); \
})

static JavaVM* jvm = NULL;

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
  jvm = vm;
  return JNI_VERSION;
}

static void _jniPrint(void *context) {
  JNIEnv *env = NULL;
  CSS_ASSERT((*jvm)->GetEnv(jvm, (void**) &env, JNI_VERSION) == JNI_OK, "Must have valid jni env");

  static jclass cssNodeClass = NULL;
  if (!cssNodeClass) {
    cssNodeClass = (*env)->FindClass(env, "com/facebook/csslayout/CSSNodeJNI");
    CSS_ASSERT(cssNodeClass, "Could not find CSSNode class");
  }

  static jmethodID toStringID = NULL;
  if (!toStringID) {
    toStringID = (*env)->GetMethodID(env, cssNodeClass, "toString", "()Ljava/lang/String");
    CSS_ASSERT(toStringID, "Could not find toString method");
  }

  jstring javaString = (jstring) (*env)->CallObjectMethod(env, context, toStringID);
  const char *nativeString = (*env)->GetStringUTFChars(env, javaString, 0);
  printf("%s\n", nativeString);

  (*env)->ReleaseStringUTFChars(env, javaString, nativeString);
}

static CSSSize _jniMeasureFunc(void *context, float width, CSSMeasureMode widthMode, float height, CSSMeasureMode heightMode) {
  JNIEnv *env = NULL;
  CSS_ASSERT((*jvm)->GetEnv(jvm, (void**) &env, JNI_VERSION) == JNI_OK, "Must have valid jni env");

  static jclass cssNodeClass = NULL;
  if (!cssNodeClass) {
    cssNodeClass = (*env)->FindClass(env, "com/facebook/csslayout/CSSNodeJNI");
    CSS_ASSERT(cssNodeClass, "Could not find CSSNode class");
  }

  static jmethodID measureID = NULL;
  if (!measureID) {
    measureID = (*env)->GetMethodID(env, cssNodeClass, "measure", "(FIFI)J");
    CSS_ASSERT(measureID, "Could not find measure method");
  }

  jlong measureResult = (*env)->CallLongMethod(env, context, measureID, width, widthMode, height, heightMode);
  CSSSize size = {
    .width = (int32_t) (measureResult >> 32),
    .height = (int32_t) measureResult,
  };

  return size;
}

CSS_NODE_JNI(jint, CSSNodeNew(JNIEnv *env, jobject thiz) {
  CSSNodeRef node = CSSNodeNew();
  CSSNodeSetContext(node, (*env)->NewGlobalRef(env, thiz));
  CSSNodeSetPrintFunc(node, _jniPrint);
  return (jint) node;
})

CSS_NODE_JNI(void, CSSNodeFree(JNIEnv *env, jobject thiz, jint nativePointer) {
  (*env)->DeleteGlobalRef(env, (jobject) CSSNodeGetContext((CSSNodeRef) nativePointer));
  CSSNodeFree((CSSNodeRef) nativePointer);
})

CSS_NODE_JNI(void, CSSNodeInsertChild(JNIEnv *env, jobject thiz, jint nativePointer, jint childPointer, jint index) {
  CSSNodeInsertChild((CSSNodeRef) nativePointer, (CSSNodeRef) childPointer, index);
})

CSS_NODE_JNI(void, CSSNodeRemoveChild(JNIEnv *env, jobject thiz, jint nativePointer, jint childPointer) {
  CSSNodeRemoveChild((CSSNodeRef) nativePointer, (CSSNodeRef) childPointer);
})

CSS_NODE_JNI(void, CSSNodeCalculateLayout(JNIEnv *env, jobject thiz, jint nativePointer) {
  CSSNodeCalculateLayout((CSSNodeRef) nativePointer, NAN, NAN, CSSNodeStyleGetDirection(((CSSNodeRef) nativePointer)));
})

CSS_NODE_JNI(void, CSSNodeMarkDirty(JNIEnv *env, jobject thiz, jint nativePointer) {
  CSSNodeMarkDirty((CSSNodeRef) nativePointer);
})

CSS_NODE_JNI(jboolean, CSSNodeIsDirty(JNIEnv *env, jobject instance, jint nativePointer) {
  return (jboolean) CSSNodeIsDirty((CSSNodeRef) nativePointer);
})

CSS_NODE_JNI(void, CSSNodeSetHasMeasureFunc(JNIEnv *env, jobject thiz, jint nativePointer, jboolean hasMeasureFunc) {
  CSSNodeSetMeasureFunc((CSSNodeRef) nativePointer, hasMeasureFunc ? _jniMeasureFunc : NULL);
})

CSS_NODE_JNI(void, CSSNodeSetIsTextNode(JNIEnv *env, jobject instance, jint nativePointer, jboolean isTextNode) {
  CSSNodeSetIsTextnode((CSSNodeRef) nativePointer, isTextNode);
})

CSS_NODE_JNI(jboolean, CSSNodeGetIsTextNode(JNIEnv *env, jobject instance, jint nativePointer) {
  return (jboolean) CSSNodeGetIsTextnode((CSSNodeRef) nativePointer);
})

CSS_NODE_JNI(jboolean, CSSNodeHasNewLayout(JNIEnv *env, jobject instance, jint nativePointer) {
  return (jboolean) CSSNodeGetHasNewLayout((CSSNodeRef) nativePointer);
})

CSS_NODE_JNI(void, CSSNodeMarkLayoutSeen(JNIEnv *env, jobject instance, jint nativePointer) {
  CSSNodeSetHasNewLayout((CSSNodeRef) nativePointer, false);
})

CSS_NODE_JNI_STYLE_PROP(jint, CSSDirection, Direction);
CSS_NODE_JNI_STYLE_PROP(jint, CSSFlexDirection, FlexDirection);
CSS_NODE_JNI_STYLE_PROP(jint, CSSJustify, JustifyContent);
CSS_NODE_JNI_STYLE_PROP(jint, CSSAlign, AlignItems);
CSS_NODE_JNI_STYLE_PROP(jint, CSSAlign, AlignSelf);
CSS_NODE_JNI_STYLE_PROP(jint, CSSPositionType, PositionType);
CSS_NODE_JNI_STYLE_PROP(jint, CSSWrapType, FlexWrap);
CSS_NODE_JNI_STYLE_PROP(jint, CSSOverflow, Overflow);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, Flex);

CSS_NODE_JNI_STYLE_PROP(jfloat, float, MarginLeft);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, MarginTop);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, MarginRight);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, MarginBottom);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, MarginStart);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, MarginEnd);

CSS_NODE_JNI_STYLE_PROP(jfloat, float, PaddingLeft);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, PaddingTop);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, PaddingRight);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, PaddingBottom);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, PaddingStart);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, PaddingEnd);

CSS_NODE_JNI_STYLE_PROP(jfloat, float, BorderLeft);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, BorderTop);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, BorderRight);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, BorderBottom);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, BorderStart);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, BorderEnd);

CSS_NODE_JNI_STYLE_PROP(jfloat, float, PositionLeft);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, PositionTop);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, PositionRight);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, PositionBottom);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, PositionStart);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, PositionEnd);

CSS_NODE_JNI_STYLE_PROP(jfloat, float, Width);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, MinWidth);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, MaxWidth);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, Height);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, MinHeight);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, MaxHeight);

CSS_NODE_JNI_LAYOUT_PROP(jfloat, float, Width);
CSS_NODE_JNI_LAYOUT_PROP(jfloat, float, Height);
CSS_NODE_JNI_LAYOUT_PROP(jfloat, float, Left);
CSS_NODE_JNI_LAYOUT_PROP(jfloat, float, Top);
CSS_NODE_JNI_LAYOUT_PROP(jint, CSSDirection, Direction);
