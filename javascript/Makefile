CXX=em++

SOURCES=\
	sources/yoga/*.cpp \
	sources/yoga/**/*.cpp \
	sources/*.cc

CXXFLAGS=\
	-Isources \
	-DEMSCRIPTEN_HAS_UNBOUND_TYPE_NAMES=0 \
	-std=c++11 \
	-g0 \
	-Os \
	-flto \
	-fno-exceptions \
	-fno-rtti \

EMCCFLAGS=\
	--closure 1 \
	--memory-init-file 0 \
	--no-entry

EMCCOPTS=\
	-s ALLOW_MEMORY_GROWTH=1 \
	-s ASSERTIONS=0 \
	-s DEFAULT_TO_CXX=1 \
	-s DYNAMIC_EXECUTION=0 \
	-s ENVIRONMENT="web,node" \
	-s EXPORT_NAME="yoga" \
	-s FETCH_SUPPORT_INDEXEDDB=0 \
	-s FILESYSTEM=0 \
	-s MALLOC="emmalloc" \
	-s MODULARIZE=1 \
	-s STRICT=1 \
	-s TEXTDECODER=0 \
	-s USE_ES6_IMPORT_META=0 \
	-s WASM_ASYNC_COMPILATION=0

LDLIBS=\
	-lembind

all: clean dir asm wasm

asm:
	$(CXX) $(SOURCES) \
		$(INCLUDE) \
		$(CXXFLAGS) \
		$(EMCCFLAGS) \
		$(LDLIBS) \
		$(EMCCOPTS) \
		-s WASM=0 \
		-o dist/asm.js

wasm:
	$(CXX) $(SOURCES) \
		$(INCLUDE) \
		$(CXXFLAGS) \
		$(EMCCFLAGS) \
		$(LDLIBS) \
		$(EMCCOPTS) \
		-s WASM=1 \
		-o dist/wasm.js

clean:
	rm -rf dist

dir:
	mkdir -p dist
