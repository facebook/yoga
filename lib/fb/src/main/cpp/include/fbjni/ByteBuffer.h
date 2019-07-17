/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */
#pragma once

#include <fbjni/fbjni.h>

namespace facebook {
namespace jni {

class JBuffer : public JavaClass<JBuffer> {
public:
  static constexpr const char* kJavaDescriptor = "Ljava/nio/Buffer;";

  void rewind() const;
  bool isDirect() const;
  void* getDirectAddress() const;
  size_t getDirectCapacity() const;
};

// JNI's NIO support has some awkward preconditions and error reporting. This
// class provides much more user-friendly access.
class JByteBuffer : public JavaClass<JByteBuffer, JBuffer> {
 public:
  static constexpr const char* kJavaDescriptor = "Ljava/nio/ByteBuffer;";

  static local_ref<JByteBuffer> wrapBytes(uint8_t* data, size_t size);
  static local_ref<JByteBuffer> allocateDirect(jint size);

  uint8_t* getDirectBytes() const {
    return static_cast<uint8_t*>(getDirectAddress());
  }

  size_t getDirectSize() const {
    return getDirectCapacity();
  }
};

}}
