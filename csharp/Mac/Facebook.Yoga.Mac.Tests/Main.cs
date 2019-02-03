/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

using System;
using System.Collections.Generic;
using AppKit;
using Foundation;
using GuiUnit;
using NUnit.Framework;

namespace Facebook.Yoga.Mac.Tests
{
	static class MainClass
	{
		static void Main(string[] args)
		{
			NSApplication.Init();
			RunTests();
		}

		static void RunTests()
		{
			TestRunner.MainLoop = new NSRunLoopIntegration();
			List<string> args = new List<string>() { typeof(MainClass).Assembly.Location, "-labels", "-noheader", "-result=TEST-Mac.xml" };


			TestRunner.Main(args.ToArray());

		}

		[System.Runtime.InteropServices.DllImport("/usr/lib/libSystem.dylib")]
		static extern void _exit(int exit_code);

		class NSRunLoopIntegration : NSObject, IMainLoopIntegration
		{
			public void InitializeToolkit()
			{
			}

			public void RunMainLoop()
			{
				NSApplication.SharedApplication.Run();
			}

			public void InvokeOnMainLoop(InvokerHelper helper)
			{
				NSApplication.SharedApplication.InvokeOnMainThread(helper.Invoke);
			}

			public void Shutdown()
			{
                _exit(TestRunner.ExitCode);
			}
		}
	}
}
