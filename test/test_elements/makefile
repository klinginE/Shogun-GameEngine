CC=g++
CFLAGS=-c -Wall -pedantic -std=c++17
LIBRARY_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lshogun-all
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=testEle

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LIBRARY_FLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(LIBRARY_FLAGS)

clean:
	rm *.o $(EXECUTABLE)
