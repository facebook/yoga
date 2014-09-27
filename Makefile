
FILES=src/__tests__/Layout-test.c src/Layout.c src/Layout-test-utils.c

all: c test

c:
	@node ./src/transpile.js

test:
	@gcc -Weverything -Werror -Wno-padded $(FILES) && ./a.out
	@rm a.out

debug:
	@gcc -ggdb $(FILES) && lldb ./a.out
	@rm a.out
