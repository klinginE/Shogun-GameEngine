CC=g++
CFLAGS=-c -g -Wall -pedantic -std=c++11
SFML_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system
SHOGUN_LIB=shogun
LINKER_PATH=-L../../lib -l$(SHOGUN_LIB)
SOURCES=main.cpp
INC_PATH=-I../../src/management -I../../src/elements
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(INC_PATH) -o $@ $(OBJECTS) $(LINKER_PATH) $(SFML_FLAGS)

.cpp.o:
	$(CC) $(INC_PATH) $(CFLAGS) $(INC_PATH) $< -o $@ $(LINKER_PATH) $(SFML_FLAGS)

clean:
	rm *.o $(EXECUTABLE)
