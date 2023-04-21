CC = g++
CFLAGS = --std=c++14
SRCS_DIR = $(PWD)/srcs/
TESTS_DIR = $(PWD)/tests

TEST_TARGETS = header_test

.PHONY: all clean

all: header_test
	echo "complete code compliation"
header_test: $(SRCS_DIR)/header.hpp $(TESTS_DIR)/header_test.cpp
	$(CC) -o $@ $(CFLAGS) $(TESTS_DIR)/header_test.cpp