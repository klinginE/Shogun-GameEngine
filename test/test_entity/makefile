CC=g++
CFLAGS=-c -Wall -pedantic -std=c++11
SFML_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system
SHOGUN_LIB=shogun
LINKER_PATH=-L../../lib -l$(SHOGUN_LIB)
SOURCES=testEntity.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=testE

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(INC_PATH) -o $@ $(OBJECTS) $(LINKER_PATH) $(SFML_FLAGS)

.cpp.o:
	$(CC) $(INC_PATH) $(CFLAGS) $(INC_PATH) $< -o $@ $(LINKER_PATH) $(SFML_FLAGS)

clean:
	rm *.o $(EXECUTABLE)
