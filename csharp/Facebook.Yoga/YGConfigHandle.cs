/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

using System;
using System.Runtime.InteropServices;

namespace Facebook.Yoga
{
    internal class YGConfigHandle : SafeHandle
    {
        internal static readonly YGConfigHandle Default = Native.YGConfigGetDefault();
        private GCHandle _managedConfigHandle;

        private YGConfigHandle() : base(IntPtr.Zero, true)
        {
        }

        public override bool IsInvalid
        {
            get
            {
                return this.handle == IntPtr.Zero;
            }
        }

        protected override bool ReleaseHandle()
        {
            if (this.handle != Default.handle)
            {
                ReleaseManaged();
                if (!IsInvalid)
                {
                    Native.YGConfigFree(this.handle);
                }
            }
            GC.KeepAlive(this);
            return true;
        }

        public void SetContext(YogaConfig config)
        {
            if (!_managedConfigHandle.IsAllocated)
            {
#if UNITY_5_4_OR_NEWER
                // Weak causes 'GCHandle value belongs to a different domain' error
                _managedConfigHandle = GCHandle.Alloc(config);
#else
                _managedConfigHandle = GCHandle.Alloc(config, GCHandleType.Weak);
#endif
                var managedConfigPtr = GCHandle.ToIntPtr(_managedConfigHandle);
                Native.YGConfigSetContext(this.handle, managedConfigPtr);
            }
        }

        private void ReleaseManaged()
        {
            if (_managedConfigHandle.IsAllocated)
            {
                _managedConfigHandle.Free();
            }
        }

        public static YogaConfig GetManaged(IntPtr unmanagedConfigPtr)
        {
            if (unmanagedConfigPtr != IntPtr.Zero)
            {
                var managedConfigPtr = Native.YGConfigGetContext(unmanagedConfigPtr);
                var config = GCHandle.FromIntPtr(managedConfigPtr).Target as YogaConfig;
                if (config == null)
                {
                    throw new InvalidOperationException("YogaConfig is already deallocated");
                }
                return config;
            }
            return null;
        }
    }
}
