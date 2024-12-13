CXX :=g++
CFLAGS :=-g -Wall -Werror -Ihelpers
LIBS := 

SOURCES := $(wildcard *.cpp) $(wildcard helpers/*.cpp)
OBJS := $(SOURCES:.cpp=.o)

.PHONY: clean test

all: aoc 

test: aoc test.py
	python test.py 

aoc: $(OBJS)
	$(CXX) $(CFLAGS) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@ $(LIBS)

clean:
	rm -f $(OBJS)
	rm aoc