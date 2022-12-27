/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

using System.Collections.Generic;
using System.Reflection;
using NUnit.Runner.Services;
using NUnit.Maui.Runner;

namespace Facebook.YogaKit.Tests
{
    class RunnerConfig : IRunnerConfiguration {
        public TestOptions ProvideOption() {
            return new TestOptions() {
                AutoRun = true
            };
        }
        public IEnumerable<Assembly> ProvideAssemblies() {
            return new List<Assembly> {
                typeof(RunnerConfig).Assembly
            };
        }
    }
}