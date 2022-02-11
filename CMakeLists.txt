# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)

add_compile_options(
    -fno-omit-frame-pointer
    -fexceptions
    -fvisibility=hidden
    -ffunction-sections
    -fdata-sections
    -Wall
    -std=c++11)

file(GLOB_RECURSE yogacore_SRC yoga/*.cpp)
add_library(yogacore STATIC ${yogacore_SRC})

target_include_directories(yogacore
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include/yoga>)

if (ANDROID)
    target_link_libraries(yogacore android log)
endif()

set_target_properties(yogacore PROPERTIES CXX_STANDARD 11)

# cmake install config
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# declare target to install
install(TARGETS yogacore EXPORT yoga-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# install header files
install(DIRECTORY
    "${CMAKE_CURRENT_LIST_DIR}/yoga"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
)

# install target config
install(EXPORT yoga-targets
    FILE yogaTargets.cmake
    NAMESPACE yoga::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/yoga
)


# generate config file
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/scripts/yoga-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/yogaConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/yoga
)

# install config file
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/yogaConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/yoga
)
