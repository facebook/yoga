using System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace Facebook.Yoga.App
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            this.Loaded += MainWindow_Loaded;
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            string result = "Success";

            try
            {
                var node = new YogaNode();

                node.SetMeasureFunction((_, width, widthMode, height, heightMode) => MeasureOutput.Make(100f, 150f));
                node.CalculateLayout();

                if (Math.Abs(100f - node.LayoutWidth) > 0.01)
                {
                    throw new Exception("Unexpected Width");
                }
                if (Math.Abs(150f - node.LayoutHeight) > 0.01)
                {
                    throw new Exception("Unexpected Height");
                }
            }
            catch (Exception ex)
            {
                result = ex.Message + Environment.NewLine + ex.StackTrace;
            }

            if (textBlock != null)
            {
                textBlock.Text = result;
            }
        }
    }
}
