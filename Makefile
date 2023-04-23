CXX = g++
CFLAGS = --std=c++14 -g
SRCS_DIR = $(PWD)/srcs
TESTS_DIR = $(PWD)/tests

SRCS = $(wildcard $(SRCS_DIR)/*.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

TEST_TARGETS = header_test request_test response_test http_parser_test

.PHONY: all clean

all: $(TEST_TARGETS)
	echo "complete code compliation"

header_test: $(SRCS_DIR)/header.hpp $(TESTS_DIR)/header_test.cpp
	$(CXX) -o $@ $(CFLAGS) $(TESTS_DIR)/header_test.cpp
request_test: $(SRCS_DIR)/header.hpp $(OBJS) $(TESTS_DIR)/request_test.cpp
	$(CXX) -o $@ $(CFLAGS) $(TESTS_DIR)/request_test.cpp $(OBJS)
response_test: $(SRCS_DIR)/header.hpp $(OBJS) $(TESTS_DIR)/response_test.cpp
	$(CXX) -o $@ $(CFLAGS) $(TESTS_DIR)/response_test.cpp $(OBJS)
http_parser_test: $(SRCS_DIR)/header.hpp $(OBJS) $(TESTS_DIR)/http_parser_test.cpp
	$(CXX) -o $@ $(CFLAGS) $(TESTS_DIR)/http_parser_test.cpp $(OBJS)

%.o: $(SRCS_DIR)/%.cpp $(SRCS_DIR)/%.hpp
	$(CXX) $(CFLAGS) -c $<

clean:
	rm $(TEST_TARGETS) *.o