using System;

using UIKit;
using Foundation;
using ObjCRuntime;
using CoreGraphics;

namespace Facebook.Yoga.iOS
{
	// We're actually abusing the Xamarin.iOS binding project
	// to bundle in the static lib for us. There is no objective-c
	// lib to bind, but the build will fail without ApiDefinition.cs
}
