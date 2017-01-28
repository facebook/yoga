/**
 * Copyright 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE-examples file in the root directory of this source tree.
 */

using System.Reflection;
using Android.App;
using Android.OS;
using Xamarin.Android.NUnitLite;

namespace Facebook.Yoga.Android.Tests
{
	[Activity(Label = "Facebook.Yoga.Android.Tests", MainLauncher = true)]
	public class MainActivity : TestSuiteActivity
	{
		protected override void OnCreate(Bundle bundle)
		{
			AddTest(Assembly.GetExecutingAssembly());
			base.OnCreate(bundle);
		}
	}
}
