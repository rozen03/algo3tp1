CC = g++
CFLAGS = -Wall -std=c++0x -O0 -g
LDFLAGS = -lm
SRC = kamehameha 
OBJ = $(SRC:=.o)
DEP = $(TEST:=.cpp)
EXE = kamehameha


.phony: all clean

all: $(EXE) 

$(EXE): $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

%.o: %.cpp %.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

clean:
	rm -f *.o 
	rm -f $(EXE)
