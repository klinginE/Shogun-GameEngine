CC=g++
CFLAGS=-c -Wall -pedantic -std=c++11
SFML_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system
MANAG_DIR=../../src/management
ELEM_DIR=../../src/elements
SOURCES=main.cpp \
$(MANAG_DIR)/GameLoop.cpp \
$(MANAG_DIR)/GameState.cpp \
$(MANAG_DIR)/GameWindow.cpp \
$(MANAG_DIR)/GameWorld.cpp \
$(MANAG_DIR)/InputManager.cpp \
$(MANAG_DIR)/StateManager.cpp \
$(ELEM_DIR)/AnimatedSprite.cpp \
$(ELEM_DIR)/BoundedSprite.cpp \
$(ELEM_DIR)/BoundingShape.cpp \
$(ELEM_DIR)/Entity.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(SFML_FLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(SFML_FLAGS)

clean:
	rm *.o $(EXECUTABLE)
