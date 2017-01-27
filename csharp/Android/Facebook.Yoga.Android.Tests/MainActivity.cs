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
