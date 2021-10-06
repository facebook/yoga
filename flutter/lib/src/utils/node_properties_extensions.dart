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
  /// Sanitizes the difference between flutter sizes and yoga width
  /// Flutter uses floating points but yoga rounds the sizes. This method sanitizes the diff
  /// Needed to avoid the error crashing on [debugAssertDoesMeetConstraints].
  double getSanitizedWidth(double maxWidth) {
    return _getSanitizedValue(getLayoutWidth(), maxWidth);
  }

  /// Sanitizes the difference between flutter sizes and yoga height
  /// Flutter uses floating points but yoga rounds the sizes. This method sanitizes the diff
  /// Needed to avoid the error crashing on [debugAssertDoesMeetConstraints].
  double getSanitizedHeight(double maxHeight) {
    return _getSanitizedValue(getLayoutHeight(), maxHeight);
  }

  /// Sanitizes the diff between flutter sizes and yoga
  double _getSanitizedValue(double value, double maxValue) {
    final valueDiff = maxValue - value;
    return (valueDiff > 0 && valueDiff < 1) ? valueDiff + value : value;
  }
}
