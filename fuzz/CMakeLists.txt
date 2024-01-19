# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

# If google/oss-fuzz has set the fuzzing engine
if(DEFINED ENV{LIB_FUZZING_ENGINE})
    set(FUZZING_ENGINE $ENV{LIB_FUZZING_ENGINE})
    set(FUZZING_COMPILE_FLAGS "")
    set(FUZZING_LINK_FLAGS "${FUZZING_ENGINE}")
else()
    set(FUZZING_COMPILE_FLAGS "-fsanitize=fuzzer")
    set(FUZZING_LINK_FLAGS "-fsanitize=fuzzer")
endif()

add_executable(fuzz_layout FuzzLayout.cpp)
set_target_properties(fuzz_layout PROPERTIES
    COMPILE_FLAGS "${FUZZING_COMPILE_FLAGS}"
    LINK_FLAGS "${FUZZING_LINK_FLAGS}"
)
target_link_libraries(fuzz_layout yogacore)
