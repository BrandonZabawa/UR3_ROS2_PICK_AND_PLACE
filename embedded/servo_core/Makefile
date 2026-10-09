CC      ?= gcc
CFLAGS  ?= -std=c11 -Wall -Wextra -Wpedantic -Werror -O2 -Iinclude
SRC     := $(wildcard src/*.c)

test: build/test_servo_core
	./build/test_servo_core

# Same tests under sanitizers: catches UB / out-of-bounds in the parser.
test-asan: CFLAGS += -g -O1 -fsanitize=address,undefined -fno-omit-frame-pointer
test-asan: clean build/test_servo_core
	./build/test_servo_core

build/test_servo_core: $(SRC) test/test_servo_core.c | build
	$(CC) $(CFLAGS) $^ -o $@

build:
	mkdir -p build

clean:
	rm -rf build

.PHONY: test test-asan clean
