using System;
using System.Runtime.InteropServices;

namespace Facebook.Yoga
{
    static class StructHelpers
    {
#if WINDOWS_UWP_ARM
        public static T MarshalStruct<T>(IntPtr ptr)
            where T : struct
        {
            return Marshal.PtrToStructure<T>(ptr);
        }
#else
        public static T MarshalStruct<T>(T value)
            where T : struct
        {
            return value;
        }
#endif
    }
}
