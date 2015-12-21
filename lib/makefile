CC=g++
AR=ar cr
CFLAGS=-fPIC -c -Wall -pedantic -std=c++11
LIBFLAGS=
SFML_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system
MANAG_DIR=../src/management
ELEM_DIR=../src/elements
SOURCES= \
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
LIBRARY=shogun

all: compile_objects compile_library clean

compile_objects:
	$(CC) $(CFLAGS) $(SOURCES) $(SFML_FLAGS)

compile_library:
	$(AR) $(LIBFLAGS) lib$(LIBRARY).a $(OBJECTS)

clean:
	rm *.o
