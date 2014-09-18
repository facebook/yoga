
FILES=src/__tests__/Layout-test.c src/Layout.c src/Layout-test-utils.c

all: c c_test java java_test

c: transpile_all

c_test: c
	@gcc -std=c99 -Werror -Wno-padded $(FILES) -lm && ./a.out
	@rm a.out

java: transpile_all src/java
	@javac -cp ./lib/junit4.jar -sourcepath ./src/java/src:./src/java/tests src/java/tests/com/facebook/csslayout/*.java

java_test: java
	@java -cp ./src/java/src:./src/java/tests:./lib/junit4.jar org.junit.runner.JUnitCore \
      com.facebook.csslayout.LayoutEngineTest \
      com.facebook.csslayout.LayoutCachingTest \
      com.facebook.csslayout.CSSNodeTest
  
transpile_all: ./src/transpile.js
	@node ./src/transpile.js

debug:
	@gcc -ggdb $(FILES) -lm && lldb ./a.out
	@rm a.out
