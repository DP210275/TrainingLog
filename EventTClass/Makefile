.PHONY: clean all

CXXFLAGS = -g -O3 -Wpedantic -Wall -Wextra -Wmisleading-indentation -Wunused -Wuninitialized -Wshadow -Wconversion -Werror -std=c++17

OBJS = EventTTest

all: ${OBJS}

EventTTest: EventT.o
EventT.o: EventT.h

clean:
	rm -f ${OBJS} *.o
