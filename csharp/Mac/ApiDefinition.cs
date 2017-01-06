using System;

using AppKit;
using Foundation;
using ObjCRuntime;
using CoreGraphics;

namespace Facebook.Yoga.Mac
{
	// Xamarin.Mac binding projects allow you to include native libraries inside C# DLLs for easy consumption
	// later. However, the binding project build files currently assume you are binding some objective-c API
	// and that you need an ApiDefinition.cs for that. yoga is all C APIs, so just include this "blank" file so
	// the dylib gets packaged
}
