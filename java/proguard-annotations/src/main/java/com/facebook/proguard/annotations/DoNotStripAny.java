/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.proguard.annotations;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.Target;

import static java.lang.annotation.RetentionPolicy.CLASS;

/**
 * Add this annotation to a class to instruct Proguard to not strip it or any of its fields or
 * methods out.
 *
 * <p>This is useful for methods called via reflection that could appear as unused to Proguard.
 */
@Target({ElementType.TYPE})
@Retention(CLASS)
public @interface DoNotStripAny {}
