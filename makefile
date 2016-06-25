CC=g++
DEFINES=-DPARALLEL_ENABLED
CFLAGS=-shared -fPIC -fopenmp -g -Wall -pedantic -std=c++11 -o
SFML_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system
MANAG_DIR=Management
ELEM_DIR=Elements
SOURCES= \
./src/$(MANAG_DIR)/GameLoop.cpp \
./src/$(MANAG_DIR)/GameState.cpp \
./src/$(MANAG_DIR)/GameWindow.cpp \
./src/$(MANAG_DIR)/GameWorld.cpp \
./src/$(MANAG_DIR)/Layer.cpp \
./src/$(MANAG_DIR)/InputManager.cpp \
./src/$(MANAG_DIR)/StateManager.cpp \
./src/$(ELEM_DIR)/AnimatedSprite.cpp \
./src/$(ELEM_DIR)/BoundingShape.cpp \
./src/$(ELEM_DIR)/Entity.cpp
LIBRARY_DIR=/usr/lib/
INCLUDE_DIR=/usr/include/Shogun/
LIBRARY=shogun-all

all: copy_headers compile_library

no_parallel: copy_headers compile_library_no_parallel

make_dir:
	if [ ! -d "$(INCLUDE_DIR)" ]; then mkdir $(INCLUDE_DIR); fi
	if [ ! -d "$(INCLUDE_DIR)$(MANAG_DIR)" ]; then mkdir $(INCLUDE_DIR)$(MANAG_DIR); fi
	if [ ! -d "$(INCLUDE_DIR)$(ELEM_DIR)" ]; then mkdir $(INCLUDE_DIR)$(ELEM_DIR); fi

copy_headers: make_dir
	cp ./include/$(MANAG_DIR)/*.hpp $(INCLUDE_DIR)$(MANAG_DIR)/
	cp ./include/$(ELEM_DIR)/*.hpp $(INCLUDE_DIR)$(ELEM_DIR)/

compile_library:
	$(CC) $(DEFINES) $(CFLAGS) $(LIBRARY_DIR)lib$(LIBRARY).so $(SOURCES) $(SFML_FLAGS)

compile_library_no_parallel:
	$(CC) $(CFLAGS) $(LIBRARY_DIR)lib$(LIBRARY).so $(SOURCES) $(SFML_FLAGS)

uninstall:
	if [ -f $(LIBRARY_DIR)lib$(LIBRARY).so ]; then rm $(LIBRARY_DIR)lib$(LIBRARY).so; fi
	if [ -d $(INCLUDE_DIR) ]; then rm -rf $(INCLUDE_DIR); fi
