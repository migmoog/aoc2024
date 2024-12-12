CXX :=g++
CFLAGS :=-g -Wall -Werror
LIBS := 

SOURCES := $(wildcard *.cpp)
OBJS := $(SOURCES:.cpp=.o)

.PHONY: clean

all: aoc 

test: clean aoc test.py
	python test.py 

aoc: $(OBJS)
	$(CXX) $(CFLAGS) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@ $(LIBS)

clean:
	rm -f $(OBJS)
	rm aoc