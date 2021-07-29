#
# Copyright 2020 ZUP IT SERVICOS EM TECNOLOGIA E INOVACAO SA
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

#
# This file is part of https://github.com/facebook/yoga which is originally released under MIT License.
# See file https://github.com/facebook/yoga/blob/master/CMakeLists.txt
# or go to https://github.com/facebook/yoga/blob/master/LICENSE for full license details.
#

project(yogacore)
cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_VERBOSE_MAKEFILE on)
add_definitions(-DIS_FLUTTER_ANDROID=1)

add_compile_options(
    -fno-omit-frame-pointer
    -fexceptions
    -fvisibility=hidden
    -ffunction-sections
    -fdata-sections
    -Wall
    -std=c++11)

file(GLOB_RECURSE yogacore_SRC .deps/yoga/*.cpp)
add_library(yogacore SHARED ${yogacore_SRC})

target_include_directories(yogacore PUBLIC .)
target_link_libraries(yogacore android log)
set_target_properties(yogacore PROPERTIES CXX_STANDARD 11)
