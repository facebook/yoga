/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
using System;

namespace Facebook.Yoga
{
    // This attribute is recognized by the Mono AOT compiler by name
    // and indicates that marshalling information must be generated for 
    // the attributed method as if it is marshalled with the provided delegate
    // type to unmanaged code.
    // We define our own copy to avoid having to conditionally build this project for
    // iOS and Unity.
    [System.AttributeUsage(System.AttributeTargets.Method)]
    internal sealed class MonoPInvokeCallbackAttribute : System.Attribute
    {
        public MonoPInvokeCallbackAttribute(Type t)
        {
            DelegateType = t;
        }

        public Type DelegateType { get; set; }
    }
}