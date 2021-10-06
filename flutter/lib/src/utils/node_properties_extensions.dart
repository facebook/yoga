/*
 * Copyright 2020 ZUP IT SERVICOS EM TECNOLOGIA E INOVACAO SA
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import 'package:yoga_engine/src/layout/node_properties.dart';

extension NodePropertiesExtensions on NodeProperties {
  /// Sanitizes the diference between flutter sizes and yoga sizes
  /// Flutter uses floating points but yoga rounds the sizes. This method sanitizes the diff
  /// when needed to avoid the error crashing on [debugAssertDoesMeetConstraints].
  double getSanitizedWidth(double maxWidth) {
    final widthDiff = maxWidth - getLayoutWidth();
    return (widthDiff > 0 && widthDiff < 1) ? widthDiff + getLayoutWidth() : getLayoutWidth();
  }

  /// Sanitizes the diference between flutter sizes and yoga sizes
  /// Flutter uses floating points but yoga rounds the sizes. This method sanitizes the diff
  /// when needed to avoid the error crashing on [debugAssertDoesMeetConstraints].
  double getSanitizedHeight(double maxHeight) {
    final heightDiff = maxHeight - getLayoutHeight();
    return (heightDiff > 0 && heightDiff < 1) ? heightDiff + getLayoutHeight() : getLayoutHeight();
  }
}
