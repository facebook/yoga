
FILES=src/__tests__/Layout-test.c src/Layout.c src/Layout-test-utils.c

all: c test

c:
	@node ./src/transpile.js

test:
	@gcc -std=c99 -Werror -Wno-padded $(FILES) -lm && ./a.out
	@rm a.out

debug:
	@gcc -ggdb $(FILES) -lm && lldb ./a.out
	@rm a.out
