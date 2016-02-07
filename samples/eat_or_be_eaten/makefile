CC=g++
CFLAGS=-c -g -Wall -pedantic -std=c++11
SFML_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system
OPENMP_FLAGS=-fopenmp
SHOGUN_LIB=shogun
LINKER_PATH=-L../../lib -l$(SHOGUN_LIB)
SOURCES=main.cpp
INC_PATH=-I../../src/management -I../../src/elements
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=eat_or_be_eaten

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(INC_PATH) $(OPENMP_FLAGS) -o $@ $(OBJECTS) $(LINKER_PATH) $(SFML_FLAGS)

.cpp.o:
	$(CC) $(INC_PATH) $(OPENMP_FLAGS) $(CFLAGS) $(INC_PATH) $< -o $@ $(LINKER_PATH) $(SFML_FLAGS)

clean:
	rm *.o $(EXECUTABLE)
