using System.Runtime.InteropServices;

namespace Facebook.CSSLayout
{
    [StructLayout(LayoutKind.Sequential)]
    public struct CSSStyle
    {
        CSSDirection direction;
        CSSFlexDirection flexDirection;
        CSSJustify justifyContent;
        CSSAlign alignContent;
        CSSAlign alignItems;
        CSSAlign alignSelf;
        CSSPositionType positionType;
        CSSWrapType flexWrap;
        CSSOverflow overflow;
        float flexGrow;
        float flexShrink;
        float flexBasis;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 9)]
        float[] margin;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 9)]
        float[] position;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 9)]
        float[] padding;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 9)]
        float[] border;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        float[] dimensions;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        float[] minDimensions;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        float[] maxDimensions;
    }
}
