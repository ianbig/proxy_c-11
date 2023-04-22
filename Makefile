CXX = g++
CFLAGS = --std=c++14
SRCS_DIR = $(PWD)/srcs
TESTS_DIR = $(PWD)/tests

OBJS = requestAbstract.o getRequest.o

TEST_TARGETS = header_test request_test

.PHONY: all clean

all: $(TEST_TARGETS)
	echo "complete code compliation"
header_test: $(SRCS_DIR)/header.hpp $(TESTS_DIR)/header_test.cpp
	$(CXX) -o $@ $(CFLAGS) $(TESTS_DIR)/header_test.cpp
request_test: $(SRCS_DIR)/header.hpp $(SRCS_DIR)/messageInterface.hpp $(OBJS) $(TESTS_DIR)/request_test.cpp
	$(CXX) -o $@ $(CFLAGS) $(TESTS_DIR)/request_test.cpp $(OBJS)
%.o: $(SRCS_DIR)/%.cpp $(SRCS_DIR)/%.hpp
	$(CXX) $(CFLAGS) -c $<

clean:
	rm $(TEST_TARGETS) $(OBJS)