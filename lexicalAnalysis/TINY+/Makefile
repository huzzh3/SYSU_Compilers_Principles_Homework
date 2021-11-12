CXX		  := gcc
CXX_FLAGS := `pkg-config --cflags gtk+-3.0`

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= `pkg-config --libs gtk+-3.0`
EXECUTABLE	:= main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.c
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

justRun:
	clear
	./$(BIN)/$(EXECUTABLE)

clean:
	-rm $(BIN)/*
