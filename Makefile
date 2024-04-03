# Makefile

# Compiler settings
CC = gcc
CFLAGS = -Wall -std=c99

# Paths
INCLUDE_PATH = include/raylib
LIB_PATH = lib/raylib

# Files
SOURCES = $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/**/**/*.c)
OBJECTS = $(SOURCES:src/%.c=obj/%.o)
EXECUTABLE = out

# Targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIB_PATH) -lraylib -framework OpenGL -framework OpenAL -framework Cocoa -framework IOKit -framework CoreVideo
	install_name_tool -change @rpath/libraylib.500.dylib /Users/rohit/staging/raylib-test/lib/raylib/libraylib.500.dylib $@

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCLUDE_PATH)

clean:
	rm -f obj/*.o $(EXECUTABLE)

run: $(EXECUTABLE)
	DYLD_LIBRARY_PATH=$(LIB_PATH):$$DYLD_LIBRARY_PATH ./$(EXECUTABLE)
