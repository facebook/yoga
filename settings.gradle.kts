/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

pluginManagement {
  repositories {
    gradlePluginPortal()
    mavenCentral()
    google()
  }
}

plugins { id("com.gradle.enterprise").version("3.7.1") }

include(":yoga")

project(":yoga").projectDir = file("java")

rootProject.name = "yoga-github"

// If you specify a file inside gradle/gradle-enterprise.gradle.kts
// you can configure your custom Gradle Enterprise instance
if (file("./gradle/gradle-enterprise.gradle.kts").exists()) {
  apply(from = "./gradle/gradle-enterprise.gradle.kts")
}
