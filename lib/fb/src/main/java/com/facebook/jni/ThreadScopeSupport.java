// Copyright 2004-present Facebook. All Rights Reserved.

package com.facebook.jni;

import com.facebook.proguard.annotations.DoNotStrip;

@DoNotStrip
public class ThreadScopeSupport {
  // This is just used for ThreadScope::withClassLoader to have a java function
  // in the stack so that jni has access to the correct classloader.
  @DoNotStrip
  private static void runStdFunction(long ptr) {
    runStdFunctionImpl(ptr);
  }

  private static native void runStdFunctionImpl(long ptr);
}
