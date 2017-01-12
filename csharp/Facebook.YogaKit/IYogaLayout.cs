using System;
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
		float AspectRatio { get; set; }
		YogaDirection ResolvedDirection { get; }
		int NumberOfChildren { get; }
		bool IsLeaf { get; }
		void ApplyLayout();
		void MarkDirty();
	}
}
