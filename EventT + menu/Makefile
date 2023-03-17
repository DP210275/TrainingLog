.phony: clean all

CXXFLAGS = -g -O3 -Wpedantic -Wall -Wextra -Wmisleading-indentation -Wunused -Wuninitialized -Wshadow -Wconversion -Werror -std=c++17

OBJS = trainingLogMERGE

all: ${OBJS}

trainingLogMERGE: EventT.o userT.o userListT.o

EventT.o: EventT.h
userT.o: userT.h
userListT.o: userListT.h userT.h


clean:
	rm -f ${OBJS} *.o 
