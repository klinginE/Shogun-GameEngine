CC=g++
DEFINES=-DPARALLEL_ENABLED
CFLAGS=-shared -fPIC -fopenmp -g -Wall -pedantic -std=c++11 -o
SFML_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system
MANAG_DIR=./src/management
ELEM_DIR=./src/elements
SOURCES= \
$(MANAG_DIR)/GameLoop.cpp \
$(MANAG_DIR)/GameState.cpp \
$(MANAG_DIR)/GameWindow.cpp \
$(MANAG_DIR)/GameWorld.cpp \
$(MANAG_DIR)/InputManager.cpp \
$(MANAG_DIR)/StateManager.cpp \
$(ELEM_DIR)/AnimatedSprite.cpp \
$(ELEM_DIR)/BoundingShape.cpp \
$(ELEM_DIR)/Entity.cpp
LIBRARY_DIR=/usr/lib/
INCLUDE_DIR=/usr/include/Shogun/
LIBRARY=shogun-all

all: copy_headers compile_library

no_parallel: copy_headers compile_library_no_parallel

make_dir:
	if [ ! -d "$(INCLUDE_DIR)" ]; then mkdir $(INCLUDE_DIR); fi

copy_headers: make_dir
	cp $(MANAG_DIR)/*.hpp $(INCLUDE_DIR)
	cp $(ELEM_DIR)/*.hpp $(INCLUDE_DIR)

compile_library:
	$(CC) $(DEFINES) $(CFLAGS) $(LIBRARY_DIR)lib$(LIBRARY).so $(SOURCES) $(SFML_FLAGS)

compile_library_no_parallel:
	$(CC) $(CFLAGS) $(LIBRARY_DIR)lib$(LIBRARY).so $(SOURCES) $(SFML_FLAGS)

uninstall:
	if [ -f $(LIBRARY_DIR)lib$(LIBRARY).so ]; then rm $(LIBRARY_DIR)lib$(LIBRARY).so; fi
	if [ -d $(INCLUDE_DIR) ]; then rm -rf $(INCLUDE_DIR); fi
