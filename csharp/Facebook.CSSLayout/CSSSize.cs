using System.Runtime.InteropServices;

namespace Facebook.CSSLayout
{
    [StructLayout(LayoutKind.Sequential)]
    public struct CSSSize
    {
        public float width;
        public float height;
    }
}
