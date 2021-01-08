#!/bin/sh
# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

if [ ! -f "CONTRIBUTING.md" ]; then
  echo "ERROR: Please execute this script in project directory"
  exit 1
fi

if [ ! -d "LPM" ]; then
  rm -rf LPM libprotobuf-mutator
  git clone --depth 1 https://github.com/google/libprotobuf-mutator.git
  mkdir LPM && cd LPM && cmake ../libprotobuf-mutator \
    -GNinja -DLIB_PROTO_MUTATOR_DOWNLOAD_PROTOBUF=ON \
    -DLIB_PROTO_MUTATOR_TESTING=OFF \
    -DCMAKE_BUILD_TYPE=Release && ninja && ninja install
else
  echo "INFO: LPM already exists, skipping libprotobuf-mutator build"
fi

rm -rf build
mkdir -p build
cd build

rm -rf genfiles && mkdir genfiles && ../LPM/external.protobuf/bin/protoc ../fuzzers/yoga.proto \
  --cpp_out=genfiles --proto_path=../fuzzers
$CXX $CXXFLAGS \
    -g   -fno-omit-frame-pointer -fexceptions \
    -fvisibility=hidden -ffunction-sections -fdata-sections \
    -Wall -fsanitize=address,fuzzer \
    ../fuzzers/main.cpp genfiles/yoga.pb.cc ../yoga/*.cpp ../yoga/internal/*.cpp ../yoga/event/*.cpp \
    -I genfiles -I .. -I../yoga \
    -I ../libprotobuf-mutator/ -I ../LPM/external.protobuf/include \
    ../LPM/src/libfuzzer/libprotobuf-mutator-libfuzzer.a \
    ../LPM/src/libprotobuf-mutator.a \
    ../LPM/external.protobuf/lib/libprotobuf.a -lstdc++ \
    -o yoga_proto_fuzzer
