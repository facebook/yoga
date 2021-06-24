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

import 'dart:ffi';

import 'package:get_it/get_it.dart';
import 'package:yoga_engine/src/utils/node_helper.dart';
import 'package:yoga_engine/src/utils/methods.dart';

import 'ffi/mapper.dart';

/// Class responsible to initialize all dependencies of yoga_engine.
/// Call the init method only once before start the application.
class Yoga {
  static void init() {
    _setupServiceLocator();
  }
}

final serviceLocator = GetIt.instance;

void _setupServiceLocator() {
  serviceLocator.registerSingleton<DynamicLibrary>(loadYoga());
  serviceLocator.registerSingleton<Mapper>(Mapper(serviceLocator.get()));
  serviceLocator
      .registerSingleton<NodeHelper>(NodeHelper(serviceLocator.get()));
}
