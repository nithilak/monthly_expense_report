# Simple Makefile
CXX := clang++
CXXFLAGS := -std=c++20
CPPFLAGS := -Iincludes
OPTFLAGS := -O0 -gdwarf-4

SRCS := ./src/driver.cc ./src/functions.cpp
TARGET := bin/exec

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPTFLAGS) $(SRCS) -o $@

clean:
	rm -f $(TARGET)
