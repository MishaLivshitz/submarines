TARGET = serverRun
CC = g++
CFLAGS = -ansi -pedantic -Wall -Werror -g3 -pthread 
CXXFLAGS = $(CFLAGS) -I../include -I../Server -std=c++03

LDLIBS = -lpthread

SOURCES += $(wildcard *.cpp) ../mutex/mutex.cpp ../CondVar/CondVar.cpp ../MyException/MyException.cpp ../Server/Server.cpp ../thread/Thread.cpp
OBJECTS ?= $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)

clean:
	rm -f $(TARGET) *.o