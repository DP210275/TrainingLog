.phony: clean all

OBJS = trainingLog

CXXFLAGS = -O3 -g -Wall -Wpedantic -Wextra -Wshadow -Wunused -Wunused-parameter  -Wuninitialized -Werror -Wmisleading-indentation -Wconversion  -std=c++17 

all: ${OBJS}

clean:
	rm -f ${OBJS} *.o 