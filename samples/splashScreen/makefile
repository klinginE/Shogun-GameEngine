CC=g++
CFLAGS=-c -g -Wall -pedantic -std=c++11
LIB_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lshogun-all
OPENMP_FLAGS=-fopenmp
SOURCES=BaseState.cpp TitleState.cpp MainGame.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=myGame

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OPENMP_FLAGS) -o $@ $(OBJECTS) $(LIB_FLAGS)

.cpp.o:
	$(CC) $(OPENMP_FLAGS) $(CFLAGS) $< -o $@ $(LIB_FLAGS)

clean:
	rm *.o $(EXECUTABLE)
