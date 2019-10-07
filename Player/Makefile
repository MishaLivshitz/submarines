TARGET = playerApp
CC = g++
CFLAGS = -ansi -pedantic -Wall -Werror -g3
CXXFLAGS = $(CFLAGS) -I../include -I../Client -std=c++03


$(TARGET): Player.o ../Client/Client.o $(wildcard ../Table/*.o) ../Submarine/Submarine.cpp

clean:
	rm -f $(TARGET) *.o