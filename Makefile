build-alu-tests:
	clear; clang -x c -O -std=c17 -Iinclude/ -Wall -Werror -o bin/alu.tests src/alu.c tests/alu.tests.c

build-lib:
	clear; test -d lib; if [ $$? = 1 ]; then mkdir lib; fi; clang -c -x c -O -std=c17 -fpic -Iinclude/ -Wall -Werror -o lib/libAlu.so src/alu.c; echo "Generated lib/libAlu.so"

build-profiler:
	clear; clang -x c -std=c17 -O -Wall -Werror -Iinclude/ -o bin/alu.profiler profiler/alu.profiler.c -Wl,lib/libAlu.so

build-tests:
	clear; test -d lib; if [ $$? = 1 ]; then mkdir lib; fi; clang -c -x c -O -std=c17 -fpic -Iinclude/ -Wall -Werror -o lib/libAlu.so src/alu.c; clang -x c -O -std=c17 -Iinclude/ -Wall -Werror -o bin/unit.tests src/alu.c tests/unit.tests.c

build-unit-tests:
	clear; clang -x c -O -std=c17 -Iinclude/ -Wall -Werror -o bin/unit.tests src/alu.c tests/unit.tests.c

run-alu-tests:
	clear; ./bin/alu.tests

run-profiler:
	clear; ./bin/alu.profiler 10

run-unit-tests:
	clear; ./bin/unit.tests

run-tests:
	clear; echo "Running unit tests."; ./bin/unit.tests; echo "Running tests on ALU."; ./bin/alu.tests; echo "All tests passed."
