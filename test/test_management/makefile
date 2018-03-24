CC=g++
CFLAGS=-c -g -Wall -pedantic -std=c++17
LIB_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lshogun-all
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=testManag

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LIB_FLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(LIB_FLAGS)

clean:
	rm *.o $(EXECUTABLE)
