.PHONY: all test clean
all:
	cmake -S . -B build && cmake --build build -j2

test: all
	ctest --test-dir build --output-on-failure

clean:
	rm -rf build
