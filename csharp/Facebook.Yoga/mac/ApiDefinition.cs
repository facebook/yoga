using System;

using AppKit;
using Foundation;
using ObjCRuntime;
using CoreGraphics;

namespace Facebook.Yoga.Mac
{
	// We're actually abusing the Xamarin.Mac binding project
	// to bundle in the static lib for us. There is no objective-c
	// lib to bind, but the build will fail without ApiDefinition.cs
}
