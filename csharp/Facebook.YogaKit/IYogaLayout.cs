using System;
using System.Drawing;
using Facebook.Yoga;

namespace Facebook.YogaKit
{
	public interface IYogaLayout : IDisposable
	{
		bool IsEnabled { get; set; }
		bool IsIncludeInLayout { get; set; }

		//YogaDirection Direction { get; set; }
		YogaFlexDirection FlexDirection { get; set; }
		YogaJustify JustifyContent { get; set; }
		YogaAlign AlignContent { get; set; }
		YogaAlign AlignSelf { get; set; }
		YogaAlign AlignItems { get; set; }
		YogaPositionType Position { get; set; }
		YogaWrap FlexWrap { get; set; }
		YogaOverflow Overflow { get; set; }


		float FlexGrow { get; set; }
		float FlexShrink { get; set; }
		float FlexBasis { get; set; }

		float Left { get; set; }
		float Top { get; set; }
		float Right { get; set; }
		float Bottom { get; set; }
		float Start { get; set; }
		float End { get; set; }

		float MarginLeft { get; set; }
		float MarginTop { get; set; }
		float MarginRight { get; set; }
		float MarginBottom { get; set; }
		float MarginStart { get; set; }
		float MarginEnd { get; set; }
		float MarginHorizontal { get; set; }
		float MarginVertical { get; set; }
		float Margin { get; set; }

		float PaddingLeft { get; set; }
		float PaddingTop { get; set; }
		float PaddingRight { get; set; }
		float PaddingBottom { get; set; }
		float PaddingStart { get; set; }
		float PaddingEnd { get; set; }
		float PaddingHorizontal { get; set; }
		float PaddingVertical { get; set; }
		float Padding { get; set; }

		float BorderLeftWidth { get; set; }
		float BorderTopWidth { get; set; }
		float BorderRightWidth { get; set; }
		float BorderBottomWidth { get; set; }
		float BorderStartWidth { get; set; }
		float BorderEndWidth { get; set; }
		float BorderWidth { get; set; }

		float Width { get; set; }
		float Height { get; set; }
		float MinWidth { get; set; }
		float MinHeight { get; set; }
		float MaxWidth { get; set; }
		float MaxHeight { get; set; }

		// Yoga specific properties, not compatible with flexbox specification

		// Returns the size of the view if no constraints were given. This could equivalent to calling [self sizeThatFits:CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX)];
		SizeF IntrinsicSize { get; }
		float AspectRatio { get; set; }
		// Get the resolved direction of this node. This won't be YGDirectionInherit
		YogaDirection ResolvedDirection { get; }
		// Returns the number of children that are using Flexbox.
		int NumberOfChildren { get; }
		// Return a BOOL indiciating whether or not we this node contains any subviews that are included in Yoga's layout.
		bool IsLeaf { get; }
		// Perform a layout calculation and update the frames of the views in the hierarchy with the results
		void ApplyLayout();
		// Mark that a view's layout needs to be recalculated. Only works for leaf views.
		void MarkDirty();
	}
}
