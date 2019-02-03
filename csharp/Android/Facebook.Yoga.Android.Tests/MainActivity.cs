/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
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
