CC=emcc

all: clean dir asm

asm:
	$(CC) sources/yoga/*.cpp sources/yoga/**/*.cpp sources/*.cc \
		--bind \
		-Isources \
		-g0 \
		-Os \
		-flto \
		--closure 1 \
		--memory-init-file 0 \
		-s WASM=0 \
		-s WASM_ASYNC_COMPILATION=0 \
		-s USE_CLOSURE_COMPILER=1 \
		-s USE_ES6_IMPORT_META=0 \
		-s MODULARIZE=1 \
		-s ASSERTIONS=0 \
		-s ALLOW_MEMORY_GROWTH=1 \
		-s DYNAMIC_EXECUTION=0 \
		-s TEXTDECODER=0 \
		-s ENVIRONMENT='web' \
		-s FILESYSTEM=0 \
		-s MALLOC="emmalloc" \
		-s EXPORT_NAME="yoga" \
		-o dist/asm.js

clean:
	rm -rf dist

dir:
	mkdir -p dist
