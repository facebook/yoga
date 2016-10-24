/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include <CSSLayout/CSSLayout.h>
#include <fb/fbjni.h>
#include <iostream>

using namespace facebook::jni;
using namespace std;

static void _jniPrint(void *context) {
  const auto obj = wrap_alias(reinterpret_cast<jobject>(context));
  cout << obj->toString() << endl;
}

static CSSSize _jniMeasureFunc(void *context,
                               float width,
                               CSSMeasureMode widthMode,
                               float height,
                               CSSMeasureMode heightMode) {
  const auto obj = wrap_alias(reinterpret_cast<jobject>(context));
  static auto measureFunc =
      obj->getClass()->getMethod<jlong(jfloat, jint, jfloat, jint)>("measure");
  const auto measureResult = measureFunc(obj, width, widthMode, height, heightMode);

  static_assert(sizeof(measureResult) == 8,
                "Expected measureResult to be 8 bytes, or two 32 bit ints");

  const float measuredWidth = static_cast<float>(0xFFFFFFFF & (measureResult >> 32));
  const float measuredHeight = static_cast<float>(0xFFFFFFFF & measureResult);
  return CSSSize{measuredWidth, measuredHeight};
}

static inline CSSNodeRef _jlong2CSSNodeRef(jlong addr) {
  return reinterpret_cast<CSSNodeRef>(static_cast<intptr_t>(addr));
}

jint jni_CSSNodeGetInstanceCount(alias_ref<jclass> clazz) {
  return CSSNodeGetInstanceCount();
}

jlong jni_CSSNodeNew(alias_ref<jobject> thiz) {
  const CSSNodeRef node = CSSNodeNew();
  auto globalThiz = make_global(thiz);
  CSSNodeSetContext(node, globalThiz.release());
  CSSNodeSetPrintFunc(node, _jniPrint);
  return reinterpret_cast<jlong>(node);
}

void jni_CSSNodeFree(alias_ref<jobject> thiz, jlong nativePointer) {
  const auto globalContext =
      adopt_global(reinterpret_cast<jobject>(CSSNodeGetContext(_jlong2CSSNodeRef(nativePointer))));
  CSSNodeFree(_jlong2CSSNodeRef(nativePointer));
}

void jni_CSSNodeReset(alias_ref<jobject> thiz, jlong nativePointer) {
  const CSSNodeRef node = _jlong2CSSNodeRef(nativePointer);
  void *context = CSSNodeGetContext(node);
  CSSNodeReset(node);
  CSSNodeSetContext(node, context);
  CSSNodeSetPrintFunc(node, _jniPrint);
}

void jni_CSSNodeInsertChild(alias_ref<jobject>,
                            jlong nativePointer,
                            jlong childPointer,
                            jint index) {
  CSSNodeInsertChild(_jlong2CSSNodeRef(nativePointer), _jlong2CSSNodeRef(childPointer), index);
}

void jni_CSSNodeRemoveChild(alias_ref<jobject>, jlong nativePointer, jlong childPointer) {
  CSSNodeRemoveChild(_jlong2CSSNodeRef(nativePointer), _jlong2CSSNodeRef(childPointer));
}

void jni_CSSNodeCalculateLayout(alias_ref<jobject>, jlong nativePointer) {
  CSSNodeCalculateLayout(_jlong2CSSNodeRef(nativePointer),
                         CSSUndefined,
                         CSSUndefined,
                         CSSNodeStyleGetDirection(_jlong2CSSNodeRef(nativePointer)));
}

void jni_CSSNodeMarkDirty(alias_ref<jobject>, jlong nativePointer) {
  CSSNodeMarkDirty(_jlong2CSSNodeRef(nativePointer));
}

jboolean jni_CSSNodeIsDirty(alias_ref<jobject>, jlong nativePointer) {
  return (jboolean) CSSNodeIsDirty(_jlong2CSSNodeRef(nativePointer));
}

void jni_CSSNodeSetHasMeasureFunc(alias_ref<jobject>,
                                  jlong nativePointer,
                                  jboolean hasMeasureFunc) {
  CSSNodeSetMeasureFunc(_jlong2CSSNodeRef(nativePointer), hasMeasureFunc ? _jniMeasureFunc : NULL);
}

void jni_CSSNodeSetIsTextNode(alias_ref<jobject>, jlong nativePointer, jboolean isTextNode) {
  CSSNodeSetIsTextnode(_jlong2CSSNodeRef(nativePointer), isTextNode);
}

jboolean jni_CSSNodeGetIsTextNode(alias_ref<jobject>, jlong nativePointer) {
  return (jboolean) CSSNodeGetIsTextnode(_jlong2CSSNodeRef(nativePointer));
}

jboolean jni_CSSNodeHasNewLayout(alias_ref<jobject>, jlong nativePointer) {
  return (jboolean) CSSNodeGetHasNewLayout(_jlong2CSSNodeRef(nativePointer));
}

void jni_CSSNodeMarkLayoutSeen(alias_ref<jobject>, jlong nativePointer) {
  CSSNodeSetHasNewLayout(_jlong2CSSNodeRef(nativePointer), false);
}

#define CSS_NODE_JNI_STYLE_PROP(javatype, type, name)                                       \
  javatype jni_CSSNodeStyleGet##name(alias_ref<jobject>, jlong nativePointer) {             \
    return (javatype) CSSNodeStyleGet##name(_jlong2CSSNodeRef(nativePointer));              \
  }                                                                                         \
                                                                                            \
  void jni_CSSNodeStyleSet##name(alias_ref<jobject>, jlong nativePointer, javatype value) { \
    CSSNodeStyleSet##name(_jlong2CSSNodeRef(nativePointer), static_cast<type>(value));      \
  }

#define CSS_NODE_JNI_STYLE_EDGE_PROP(javatype, type, name)                                 \
  javatype jni_CSSNodeStyleGet##name(alias_ref<jobject>, jlong nativePointer, jint edge) { \
    return (javatype) CSSNodeStyleGet##name(_jlong2CSSNodeRef(nativePointer),              \
                                            static_cast<CSSEdge>(edge));                   \
  }                                                                                        \
                                                                                           \
  void jni_CSSNodeStyleSet##name(alias_ref<jobject>,                                       \
                                 jlong nativePointer,                                      \
                                 jint edge,                                                \
                                 javatype value) {                                         \
    CSSNodeStyleSet##name(_jlong2CSSNodeRef(nativePointer),                                \
                          static_cast<CSSEdge>(edge),                                      \
                          static_cast<type>(value));                                       \
  }

#define CSS_NODE_JNI_LAYOUT_PROP(javatype, type, name)                           \
  javatype jni_CSSNodeLayoutGet##name(alias_ref<jobject>, jlong nativePointer) { \
    return (javatype) CSSNodeLayoutGet##name(_jlong2CSSNodeRef(nativePointer));  \
  }

CSS_NODE_JNI_STYLE_PROP(jint, CSSDirection, Direction);
CSS_NODE_JNI_STYLE_PROP(jint, CSSFlexDirection, FlexDirection);
CSS_NODE_JNI_STYLE_PROP(jint, CSSJustify, JustifyContent);
CSS_NODE_JNI_STYLE_PROP(jint, CSSAlign, AlignItems);
CSS_NODE_JNI_STYLE_PROP(jint, CSSAlign, AlignSelf);
CSS_NODE_JNI_STYLE_PROP(jint, CSSAlign, AlignContent);
CSS_NODE_JNI_STYLE_PROP(jint, CSSPositionType, PositionType);
CSS_NODE_JNI_STYLE_PROP(jint, CSSWrapType, FlexWrap);
CSS_NODE_JNI_STYLE_PROP(jint, CSSOverflow, Overflow);

void jni_CSSNodeStyleSetFlex(alias_ref<jobject>, jlong nativePointer, jfloat value) {
  CSSNodeStyleSetFlex(_jlong2CSSNodeRef(nativePointer), static_cast<float>(value));
}
CSS_NODE_JNI_STYLE_PROP(jfloat, float, FlexGrow);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, FlexShrink);
CSS_NODE_JNI_STYLE_PROP(jfloat, float, FlexBasis);

CSS_NODE_JNI_STYLE_EDGE_PROP(jfloat, float, Position);
CSS_NODE_JNI_STYLE_EDGE_PROP(jfloat, float, Margin);
CSS_NODE_JNI_STYLE_EDGE_PROP(jfloat, float, Padding);
CSS_NODE_JNI_STYLE_EDGE_PROP(jfloat, float, Border);

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

#define CSSMakeNativeMethod(name) makeNativeMethod(#name, name)

jint JNI_OnLoad(JavaVM *vm, void *) {
  return initialize(vm, [] {
    registerNatives("com/facebook/csslayout/CSSNode",
                    {
                        CSSMakeNativeMethod(jni_CSSNodeNew),
                        CSSMakeNativeMethod(jni_CSSNodeFree),
                        CSSMakeNativeMethod(jni_CSSNodeReset),
                        CSSMakeNativeMethod(jni_CSSNodeInsertChild),
                        CSSMakeNativeMethod(jni_CSSNodeRemoveChild),
                        CSSMakeNativeMethod(jni_CSSNodeSetIsTextNode),
                        CSSMakeNativeMethod(jni_CSSNodeGetIsTextNode),
                        CSSMakeNativeMethod(jni_CSSNodeCalculateLayout),
                        CSSMakeNativeMethod(jni_CSSNodeHasNewLayout),
                        CSSMakeNativeMethod(jni_CSSNodeMarkDirty),
                        CSSMakeNativeMethod(jni_CSSNodeIsDirty),
                        CSSMakeNativeMethod(jni_CSSNodeMarkLayoutSeen),
                        CSSMakeNativeMethod(jni_CSSNodeSetHasMeasureFunc),

                        CSSMakeNativeMethod(jni_CSSNodeStyleGetDirection),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetDirection),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetFlexDirection),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetFlexDirection),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetJustifyContent),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetJustifyContent),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetAlignItems),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetAlignItems),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetAlignSelf),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetAlignSelf),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetAlignContent),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetAlignContent),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetPositionType),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetPositionType),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetFlexWrap),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetOverflow),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetOverflow),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetFlex),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetFlexGrow),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetFlexGrow),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetFlexShrink),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetFlexShrink),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetFlexBasis),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetFlexBasis),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetMargin),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetMargin),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetPadding),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetPadding),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetBorder),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetBorder),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetPosition),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetPosition),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetWidth),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetWidth),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetHeight),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetHeight),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetMinWidth),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetMinWidth),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetMinHeight),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetMinHeight),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetMaxWidth),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetMaxWidth),
                        CSSMakeNativeMethod(jni_CSSNodeStyleGetMaxHeight),
                        CSSMakeNativeMethod(jni_CSSNodeStyleSetMaxHeight),

                        CSSMakeNativeMethod(jni_CSSNodeLayoutGetLeft),
                        CSSMakeNativeMethod(jni_CSSNodeLayoutGetTop),
                        CSSMakeNativeMethod(jni_CSSNodeLayoutGetWidth),
                        CSSMakeNativeMethod(jni_CSSNodeLayoutGetHeight),
                        CSSMakeNativeMethod(jni_CSSNodeLayoutGetDirection),

                        CSSMakeNativeMethod(jni_CSSNodeGetInstanceCount),
                    });
  });
}
