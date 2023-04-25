CXX = g++
CFLAGS = --std=c++14 -ggdb3
SRCS_DIR = $(PWD)/srcs
TESTS_DIR = $(PWD)/tests

SRCS = $(wildcard $(SRCS_DIR)/*.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

HDRS = $(SRCS_DIR)/header.hpp

TEST_TARGETS = header_test request_test response_test http_parser_test get_test

.PHONY: all clean

all: $(TEST_TARGETS)
	echo "complete code compliation"

header_test: $(OBJS) $(HDRS)
	$(CXX) -o $@ $(CFLAGS) $(TESTS_DIR)/header_test.cpp
request_test: $(OBJS) $(HDRS) $(TESTS_DIR)/request_test.cpp
	$(CXX) -o $@ $(CFLAGS) $(OBJS) $(TESTS_DIR)/response_test.cpp
response_test: $(OBJS) $(HDRS) $(TESTS_DIR)/response_test.cpp
	$(CXX) -o $@ $(CFLAGS)  $(OBJS) $(TESTS_DIR)/response_test.cpp
http_parser_test:$(OBJS) $(HDRS) $(TESTS_DIR)/http_parser_test.cpp
	$(CXX) -o $@ $(CFLAGS) $(OBJS) $(TESTS_DIR)/http_parser_test.cpp
get_test: $(OBJS) $(HDRS) $(TESTS_DIR)/get_test.cpp
	$(CXX) -o $@ $(CFLAGS) $(OBJS) $(TESTS_DIR)/get_test.cpp

$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.cpp $(SRCS_DIR)/%.hpp
	$(CXX) -c $< $(CFLAGS) -o $@

clean:
	rm $(TEST_TARGETS) $(SRCS_DIR)/*.o
