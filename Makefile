
test:
	@gcc src/__tests__/Layout-test.c src/Layout.c && ./a.out
	@rm a.out
