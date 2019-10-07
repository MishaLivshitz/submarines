TARGET = serverStart
CC = g++
CFLAGS = -ansi -pedantic -Wall -Werror -g3
CXXFLAGS = $(CFLAGS) -I../include -std=c++03
LDLIBS = -lpthread

SOURCES += $(wildcard *.cpp) ../mutex/mutex.cpp ../CondVar/CondVar.cpp ../MyException/MyException.cpp
OBJECTS ?= $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)

clean:
	rm -f $(TARGET) *.o