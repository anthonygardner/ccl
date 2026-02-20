.PHONY: build.core build.cpp build.py clean install notebook test.core test.cpp test.py

build.core:
	cmake -S . -B build -DBUILD_PYTHON_API=OFF -DBUILD_CXX_TESTS=OFF && cmake --build build --target ccl_core ccl_core_test -j

build.cpp:
	cmake -S . -B build && cmake --build build -j

build.py:
	uv pip install -e ".[dev]"

clean:
	rm -fr build

commit:
	uv run cz c

notebook:
	uv run marimo edit notebooks/main.py --host 0.0.0.0 --port 2718 --headless --no-token

test.core:
	cmake -S . -B build -DBUILD_PYTHON_API=OFF -DBUILD_CXX_TESTS=OFF && cmake --build build --target ccl_core_test -j && ./build/ccl_core_test

test.cpp:
	cd build && ctest -V && cd -

test.py:
	uv run pytest