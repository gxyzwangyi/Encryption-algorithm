all: build/
	g++ -o build/main main.cpp DecryptHelper.h DecryptHelper.cpp SpellCorrector.h SpellCorrector.cpp

build/:
	mkdir -p build

clean:
	rm -rf build/

run:
	./build/main.exe

.PHONY: all clean run