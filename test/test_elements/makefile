CC=g++
CFLAGS=-c -Wall -pedantic -std=c++11
LIBRARY_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lshogun-all
OPENMP_FLAGS=-fopenmp
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=testEle

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OPENMP_FLAGS) -o $@ $(OBJECTS) $(LIBRARY_FLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $(OPENMP_FLAGS) $< -o $@ $(LIBRARY_FLAGS)

clean:
	rm *.o $(EXECUTABLE)
