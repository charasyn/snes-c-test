MAKEFLAGS += --always-make

CFLAGS := -Og -g -Wall -Werror -Wextra -pedantic

all: unittest_result_updateGuessResult

unittest_result_updateGuessResult: unittest_updateGuessResult
	timeout 3 ./unittest_updateGuessResult

unittest_updateGuessResult: updateGuessResult.c
	$(CC) $(CFLAGS) -o $@ $^
