CXX :=g++
CFLAGS :=-g -Wall -Werror
LIBS := 

SOURCES := $(wildcard *.cpp)
OBJS := $(SOURCES:.cpp=.o)

.PHONY: clean

all: aoc 

aoc: $(OBJS)
	$(CXX) $(CFLAGS) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@ $(LIBS)

clean:
	rm -f $(OBJS)
	rm aoc