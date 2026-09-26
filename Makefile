# Simple Makefile
CXX := clang++
CXXFLAGS := -std=c++20
CPPFLAGS := -Iincludes \
            -Impdecimal-4.0.1/libmpdec \
            -Impdecimal-4.0.1/libmpdec++
OPTFLAGS := -O0 -gdwarf-4
LDFLAGS := -framework CoreFoundation \
           -Lmpdecimal-4.0.1/libmpdec \
		   -Lmpdecimal-4.0.1/libmpdec++

LDLIBS := -lmpdec++ -lmpdec

SRCS := ./src/driver.cc ./src/functions.cpp
TARGET := bin/exec

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPTFLAGS) $(SRCS) $(LDFLAGS) $(LDLIBS) -o $@

clean:
	rm -f $(TARGET)
