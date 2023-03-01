.phony: clean all

OBJS = userTest

CXXFLAGS = -O3 -g -Wall -Wpedantic -Wextra -Wshadow -Wunused -Wunused-parameter  -Wunused -Wuninitialized -Wshadow -Werror -Wmisleading-indentation -Wconversion  -std=c++17 

all: ${OBJS}

userTest: userT.o userListT.o
userT.o: userT.h
userListT.o: userListT.h userT.h

clean:
	rm -f ${OBJS} *.o
