/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

plugins {
  id("com.android.library")
  id("maven-publish")
  id("signing")
}

group = "com.facebook.yoga"

val compileSdkVersionProperty: Int by rootProject.extra
val minSdkVersionProperty: Int by rootProject.extra
val targetSdkVersionProperty: Int by rootProject.extra
val buildToolsVersionProperty: String by rootProject.extra
val ndkVersionProperty: String by rootProject.extra

android {
  namespace = "com.facebook.yoga"
  compileSdk = 34
  buildToolsVersion = "34.0.0"
  ndkVersion = "26.0.10792818"

  defaultConfig {
    minSdk = 21
    consumerProguardFiles("proguard-rules.pro")

    ndk { abiFilters.addAll(setOf("x86", "x86_64", "armeabi-v7a", "arm64-v8a")) }
  }

  externalNativeBuild { cmake { path("CMakeLists.txt") } }

  compileOptions {
    targetCompatibility(JavaVersion.VERSION_1_8)
    sourceCompatibility(JavaVersion.VERSION_1_8)
  }

  sourceSets {
    named("main") {
      java.srcDir("com")
      manifest.srcFile("AndroidManifest.xml")
      res.srcDir("res")
    }
  }

  publishing {
    multipleVariants {
      withSourcesJar()
      withJavadocJar()
      includeBuildTypeValues("debug", "release")
    }
  }
}

dependencies {
  implementation("com.google.code.findbugs:jsr305:3.0.2")
  implementation("com.facebook.soloader:soloader:0.10.5")
  testImplementation("junit:junit:4.12")
}

version =
    if ("USE_SNAPSHOT".byProperty.toBoolean()) {
      "${"VERSION_NAME".byProperty}-SNAPSHOT"
    } else {
      "VERSION_NAME".byProperty.toString()
    }

publishing {
  publications {
    register<MavenPublication>("default") {
      groupId = project.group.toString()
      artifactId = project.name
      version = project.version.toString()
      afterEvaluate { from(components["default"]) }
      pom {
        description.set(
            "An embeddable and performant flexbox layout engine with bindings for multiple languages")
        name.set(project.name)
        url.set("https://github.com/facebook/yoga.git")
        licenses {
          license {
            name.set("MIT License")
            url.set("https://github.com/facebook/yoga/blob/main/LICENSE")
            distribution.set("repo")
          }
        }
        developers {
          developer {
            id.set("Meta Open Source")
            name.set("Meta Open Source")
            email.set("opensource@meta.com")
          }
        }
        scm { url.set("scm:git:git@github.com:facebook/yoga.git") }
      }
    }
  }
}

val signingKey = "SIGNING_KEY".byProperty
val signingPwd = "SIGNING_PWD".byProperty

if (signingKey.isNullOrBlank() || signingPwd.isNullOrBlank()) {
  logger.info("Signing disabled as the GPG key was not found")
} else {
  logger.info("GPG Key found - Signing enabled")
}

signing {
  useInMemoryPgpKeys(signingKey, signingPwd)
  sign(publishing.publications)
  isRequired = !(signingKey.isNullOrBlank() || signingPwd.isNullOrBlank())
}

// Fix for https://youtrack.jetbrains.com/issue/KT-46466/
// On Gradle 8+, the signing task is not correctly wired to the publishing tasks.
// This requires a fix on KGP that is currently pending.
val signingTasks = tasks.withType<Sign>()

tasks.withType<AbstractPublishToMaven>().configureEach { dependsOn(signingTasks) }

val String.byProperty: String?
  get() = providers.gradleProperty(this).orNull
