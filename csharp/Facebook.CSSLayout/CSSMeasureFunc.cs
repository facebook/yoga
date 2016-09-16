using System;

namespace Facebook.CSSLayout
{
    public delegate CSSSize CSSMeasureFunc(
        IntPtr context, 
        float width,
        CSSMeasureMode widthMode,
        float height,
        CSSMeasureMode heightMode);
}
