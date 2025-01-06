
CXX=g++
FLAGS=-g3
GTFLAGS=-lgtest

OBJDIR := build

setup:
	mkdir -p build

build/move-bytes.o: move-bytes.cpp
	$(CXX) $(FLAGS) -c -o $@ $<

OBJS := $(addprefix $(OBJDIR)/, \
	move-bytes.o )

build: $(OBJS)

TESTS := movebytes-test

movebytes-test: build/move-bytes.o move-bytes-test.cpp
	$(CXX) -o build/$@ $^ $(GTFLAGS)
	./build/$@

test: $(TESTS)

all: setup build test

.PHONY: clean

clean:
	rm -f $(OBJS) movebytes-test

