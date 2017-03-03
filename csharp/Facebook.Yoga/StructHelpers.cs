using System;
using System.Runtime.InteropServices;

namespace Facebook.Yoga
{
    static class StructHelpers
    {
        public static T MarshalStruct<T>(IntPtr ptr)
            where T : struct
        {
            return (T)Marshal.PtrToStructure(ptr, typeof(T));
        }
    }
}
