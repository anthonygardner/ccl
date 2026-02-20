.PHONY: build.core build.cpp build.py clean install notebook test.core test.cpp test.py

build.core:

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

test.cpp:
	cd build && ctest -V && cd -

test.py:
	uv run pytest