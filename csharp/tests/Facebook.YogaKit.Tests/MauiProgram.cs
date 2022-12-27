/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

using NUnit.Maui.Runner;

namespace Facebook.YogaKit.Tests
{
    public static class MauiProgram
    {
        public static MauiApp CreateMauiApp()
        {
            var builder = MauiApp.CreateBuilder();
            builder
                .UseMauiApp<NUnit.Maui.Runner.App>()
                .Services.AddSingleton<IRunnerConfiguration, RunnerConfig>();

            return builder.Build();
        }
    }
}