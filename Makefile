CC:=c++
CPPFLAGS:=-std=c++20
SDL2_INCLUDE:=-I/opt/homebrew/include
SDL2_LIBRARY:=-L/opt/homebrew/lib
LDFLAGS:=-lSDL2 -lSDL2_image -lSDL2_ttf -framework CoreGraphics
DESTINATION:=bin/
SOURCES:=$(wildcard *.cpp components/*.cpp)
EXECUTABLE:=$(DESTINATION)conway

SOURCES:=$(wildcard src/*.cpp *.cpp)
OBJECTS:=$(addprefix bin/,$(notdir $(SOURCES:.cpp=.o)))

TARGETS:=compile

all: $(TARGETS)
.PHONY: all

compile: $(EXECUTABLE)
.PHONY: compile

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(SDL2_LIBRARY) $(LDFLAGS)

bin/%.o: src/%.cpp
	$(CC) $(CPPFLAGS) $(SDL2_INCLUDE) -c $< -o $@

bin/main.o: main.cpp
	$(CC) $(CPPFLAGS) $(SDL2_INCLUDE) -c $< -o $@

run:
	@./$(EXECUTABLE) $(CONFIG)
.PHONY: run

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
.PHONY: clean