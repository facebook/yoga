/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */
#include <fbjni/detail/References.h>

namespace facebook {
namespace jni {

JniLocalScope::JniLocalScope(JNIEnv* env, jint capacity) : env_(env) {
  hasFrame_ = false;
  auto pushResult = env->PushLocalFrame(capacity);
  FACEBOOK_JNI_THROW_EXCEPTION_IF(pushResult < 0);
  hasFrame_ = true;
}

JniLocalScope::~JniLocalScope() {
  if (hasFrame_) {
    env_->PopLocalFrame(nullptr);
  }
}

namespace {

#ifdef __ANDROID__

int32_t getAndroidApiLevel() {
  // This is called from the static local initializer in
  // isObjectRefType(), and creating fbjni references can call
  // isObjectRefType().  So, to avoid recursively entering the block
  // where the static is initialized (which is undefined behavior), we
  // avoid using standard fbjni references here.

  JNIEnv* env = Environment::current();
  jclass cls = detail::findClass(env, "android/os/Build$VERSION");
  jfieldID field = env->GetStaticFieldID(
      cls, "SDK_INT", jtype_traits<jint>::descriptor().c_str());
  if (!field) {
    env->DeleteLocalRef(cls);
  }
  FACEBOOK_JNI_THROW_EXCEPTION_IF(!field);
  int32_t ret = env->GetStaticIntField(cls, field);
  env->DeleteLocalRef(cls);
  return ret;
}

bool doesGetObjectRefTypeWork() {
  auto level = getAndroidApiLevel();
  return level >= 14;
}

#else

bool doesGetObjectRefTypeWork() {
  auto jni_version = Environment::current()->GetVersion();
  return jni_version >= JNI_VERSION_1_6;
}

#endif

} // namespace

bool isObjectRefType(jobject reference, jobjectRefType refType) {
  // null-check first so that we short-circuit during (safe) global
  // constructors, where we won't have an Environment::current() yet
  if (!reference) {
    return true;
  }

  static bool getObjectRefTypeWorks = doesGetObjectRefTypeWork();

  return !getObjectRefTypeWorks ||
      Environment::current()->GetObjectRefType(reference) == refType;
}

} // namespace jni
} // namespace facebook
