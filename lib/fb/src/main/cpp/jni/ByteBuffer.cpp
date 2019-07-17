/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */
#include <fbjni/ByteBuffer.h>

#include <stdexcept>

namespace facebook {
namespace jni {

void JBuffer::rewind() const {
  static auto meth = javaClassStatic()->getMethod<alias_ref<JBuffer>()>("rewind");
  meth(self());
}

void* JBuffer::getDirectAddress() const {
  if (!self()) {
    throwNewJavaException("java/lang/NullPointerException", "java.lang.NullPointerException");
  }
  void* addr = Environment::current()->GetDirectBufferAddress(self());
  FACEBOOK_JNI_THROW_PENDING_EXCEPTION();
  if (!addr) {
    throw std::runtime_error(
        isDirect() ?
          "Attempt to get direct bytes of non-direct buffer." :
          "Error getting direct bytes of buffer.");
  }
  return addr;
}

size_t JBuffer::getDirectCapacity() const {
  if (!self()) {
    throwNewJavaException("java/lang/NullPointerException", "java.lang.NullPointerException");
  }
  int size = Environment::current()->GetDirectBufferCapacity(self());
  FACEBOOK_JNI_THROW_PENDING_EXCEPTION();
  if (size < 0) {
    throw std::runtime_error(
        isDirect() ?
          "Attempt to get direct size of non-direct buffer." :
          "Error getting direct size of buffer.");
  }
  return static_cast<size_t>(size);
}

bool JBuffer::isDirect() const {
  static auto meth = javaClassStatic()->getMethod<jboolean()>("isDirect");
  return meth(self());
}

local_ref<JByteBuffer> JByteBuffer::wrapBytes(uint8_t* data, size_t size) {
  // env->NewDirectByteBuffer requires that size is positive. Android's
  // dalvik returns an invalid result and Android's art aborts if size == 0.
  // Workaround this by using a slow path through Java in that case.
  if (!size) {
    return allocateDirect(0);
  }
  auto res = adopt_local(static_cast<javaobject>(Environment::current()->NewDirectByteBuffer(data, size)));
  FACEBOOK_JNI_THROW_PENDING_EXCEPTION();
  if (!res) {
    throw std::runtime_error("Direct byte buffers are unsupported.");
  }
  return res;
}

local_ref<JByteBuffer> JByteBuffer::allocateDirect(jint size) {
  static auto cls = JByteBuffer::javaClassStatic();
  static auto meth = cls->getStaticMethod<JByteBuffer::javaobject(int)>("allocateDirect");
  return meth(cls, size);
}

}}
