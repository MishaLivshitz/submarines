TARGET = test
CC = g++
CFLAGS = -ansi -pedantic -Wall -Werror -g3
CXXFLAGS = $(CFLAGS) -std=c++03
CPPFLAGS = -I ../include

SOURCES = $()

$(TARGET): ../Submarine/Submarine.o SubmarinesTable.o OpponentTable.o

clean:
	rm -f test *.o
