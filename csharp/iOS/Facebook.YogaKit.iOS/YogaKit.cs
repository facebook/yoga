using System;
using System.Runtime.InteropServices;
using Foundation;
using UIKit;

namespace Facebook.YogaKit
{
	public static partial class YogaKit
	{
		static NSString YogaNodeKey = new NSString("YogaNode");

		public static IYogaLayout Yoga(this UIView view)
		{
			return YogaLayoutNative(view);
		}

		static IYogaLayout YogaLayoutNative(UIView view)
		{
			var yoga = ObjCRuntime.Runtime.GetNSObject(objc_getAssociatedObject(view.Handle, YogaNodeKey.Handle)) as YogaLayout;
			if (yoga == null)
			{
				yoga = new YogaLayout(view);
				objc_setAssociatedObject(view.Handle, YogaNodeKey.Handle, yoga.Handle, AssociationPolicy.RETAIN_NONATOMIC);
			}
			return yoga;
		}

		[DllImport("/usr/lib/libobjc.dylib")]
		static extern void objc_setAssociatedObject(IntPtr @object, IntPtr key, IntPtr value, AssociationPolicy policy);

		[DllImport("/usr/lib/libobjc.dylib")]
		static extern IntPtr objc_getAssociatedObject(IntPtr @object, IntPtr key);

		enum AssociationPolicy
		{
			ASSIGN = 0,
			RETAIN_NONATOMIC = 1,
			COPY_NONATOMIC = 3,
			RETAIN = 01401,
			COPY = 01403,
		}
	}
}
