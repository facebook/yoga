/**
 * Copyright 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE-examples file in the root directory of this source tree.
 */

//#define DEBUG_LAYOUT
using System;

using AppKit;
using Foundation;
using CoreGraphics;

namespace Facebook.Yoga.Mac.Sample
{
    public static class NSViewYogaExtensions
    {
        public static void ApplyYogaLayout (this NSView view, YogaNode n, bool root = true)
        {
#if DEBUG_LAYOUT
            Console.WriteLine ($"ApplyYogaLayout {view.ToolTip}, {n.LayoutX}, {n.LayoutY}, {n.LayoutWidth}, {n.LayoutHeight}");
#endif

            // A bit of gross special casing
            // This really should mostly go away if/when the UIView+Yoga.m magic gets ported to AppKit
            if (root)
                view.Frame = new CGRect (n.LayoutX, n.LayoutY, n.LayoutWidth, n.LayoutHeight);
#if DEBUG_LAYOUT
            Console.WriteLine ($"Setting {view.ToolTip} frame to {view.Frame}");
#endif

            // This assumes your YogaNode and NSView children were inserted in same order
            for (int i = 0; i < n.Count; ++i) {
                YogaNode childNode = n[i];
                // Cocoa coord space is from bottom left not top left
                view.Subviews[i].Frame = new CGRect (childNode.LayoutX, n.LayoutHeight - childNode.LayoutY - childNode.LayoutHeight, childNode.LayoutWidth, childNode.LayoutHeight);
#if DEBUG_LAYOUT
                Console.WriteLine ($"Setting {view.Subviews[i].ToolTip} frame to {view.Subviews[i].Frame}");
#endif
                if (childNode.Count > 0){
#if DEBUG_LAYOUT
                    Console.WriteLine ($"Calling ApplyYogaLayout recursively on {view.Subviews[i].ToolTip}");
#endif
                    ApplyYogaLayout (view.Subviews[i], childNode, false);
                }
            }
        }
    }
    
    public partial class ViewController : NSViewController
    {
        public ViewController(IntPtr handle) : base(handle)
        {
        }

        public override void ViewDidLoad()
        {
            base.ViewDidLoad ();

            NSImage image = NSImage.ImageNamed (NSImageName.TrashFull);

            NSView root = CreateViewHierarchy (image);
            var rootNode = CalculateLayout (View.Frame, image.Size);

            root.ApplyYogaLayout (rootNode);

            View.AddSubview (root);
        }

        static NSView CreateViewHierarchy (NSImage image)
        {
            var root = new NSView () {
                WantsLayer = true,
                ToolTip = "Root"
            };
            root.Layer.BackgroundColor = NSColor.Red.CGColor;

            NSView child1 = new NSView () {
                WantsLayer = true,
                ToolTip = "Child 1"
            };
            child1.Layer.BackgroundColor = NSColor.Blue.CGColor;

            NSView child2 = new NSView () {
                WantsLayer = true,
                ToolTip = "Child 2"
            };
            child2.Layer.BackgroundColor = NSColor.Green.CGColor;

            NSView child3 = new NSView () {
                WantsLayer = true,
                ToolTip = "Child 3"
            };
            child3.Layer.BackgroundColor = NSColor.Yellow.CGColor;

            root.AddSubview (child1);
            root.AddSubview (child2);
            child2.AddSubview (child3);

            return root;
        }

        static YogaNode CalculateLayout (CGRect rootFrame, CGSize imageSize)
        {
            var rootNode = new YogaNode () {
                Width = (float)rootFrame.Width,
                Height = (float)rootFrame.Height,
                AlignItems = YogaAlign.Center,
                JustifyContent = YogaJustify.Center
            };

            var child1Node = new YogaNode () {
                Width = 100,
                Height = 100
            };

            var child2Node = new YogaNode () {
                Width = 200,
                Height = 100
            };

            var child3Node = new YogaNode () {
                Width = 100,
                Height = 100
            };

            rootNode.Insert (0, child1Node);
            rootNode.Insert (1, child2Node);
            child2Node.Insert (0, child3Node);
            rootNode.CalculateLayout ();

            return rootNode;
        }
    }
}
