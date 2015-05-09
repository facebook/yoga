# Copyright (c) 2014, Facebook, Inc.
# All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree. An additional grant
# of patent rights can be found in the PATENTS file in the same directory.

FILES=src/__tests__/Layout-test.c src/Layout.c src/Layout-test-utils.c
JAVA_LIB_DIR=lib

ifeq ($(OS),Windows_NT)
	C_TEST_EXE=./c_test.exe
	ENVSEP=";"
	WGET=wget --no-check-certificate
	LLDB=gdb
else
	C_TEST_EXE=./c_test
	ENVSEP=":"
	WGET=wget
	LLDB=lldb
endif

all: c c_test java java_test

c: transpile_all

c_test: c
	@gcc -std=c99 -Werror -Wno-padded $(FILES) -lm -o "$(C_TEST_EXE)" && "$(C_TEST_EXE)"
	@rm "$(C_TEST_EXE)"

$(JAVA_LIB_DIR):
	mkdir $(JAVA_LIB_DIR)

$(JAVA_LIB_DIR)/junit4.jar: | $(JAVA_LIB_DIR)
	$(WGET) -O $(JAVA_LIB_DIR)/junit4.jar http://search.maven.org/remotecontent?filepath=junit/junit/4.10/junit-4.10.jar

$(JAVA_LIB_DIR)/jsr305.jar: | $(JAVA_LIB_DIR)
	$(WGET) -O $(JAVA_LIB_DIR)/jsr305.jar http://search.maven.org/remotecontent?filepath=net/sourceforge/findbugs/jsr305/1.3.7/jsr305-1.3.7.jar

$(JAVA_LIB_DIR)/infer-annotations-1.4.jar: | $(JAVA_LIB_DIR)
	$(WGET) -O $(JAVA_LIB_DIR)/infer-annotations-1.4.jar https://github.com/facebook/buck/raw/027ffe2b230c08cad7b340646c6f801bd6dabc78/third-party/java/infer-annotations/infer-annotations-1.4.jar

java: transpile_all src/java | $(JAVA_LIB_DIR)/junit4.jar $(JAVA_LIB_DIR)/jsr305.jar $(JAVA_LIB_DIR)/infer-annotations-1.4.jar
	@javac -cp ./$(JAVA_LIB_DIR)/junit4.jar$(ENVSEP)./$(JAVA_LIB_DIR)/jsr305.jar$(ENVSEP)./$(JAVA_LIB_DIR)/infer-annotations-1.4.jar -sourcepath ./src/java/src$(ENVSEP)./src/java/tests src/java/tests/com/facebook/csslayout/*.java

java_test: java
	@java -cp ./src/java/src$(ENVSEP)./src/java/tests$(ENVSEP)./$(JAVA_LIB_DIR)/junit4.jar$(ENVSEP)./$(JAVA_LIB_DIR)/infer-annotations-1.4.jar org.junit.runner.JUnitCore \
      com.facebook.csslayout.LayoutEngineTest \
      com.facebook.csslayout.LayoutCachingTest \
      com.facebook.csslayout.CSSNodeTest

transpile_all: ./src/transpile.js
	@node ./src/transpile.js

debug:
	@gcc -std=c99 -ggdb $(FILES) -lm -o $(C_TEST_EXE) && $(LLDB) $(C_TEST_EXE)
	@rm $(C_TEST_EXE)
