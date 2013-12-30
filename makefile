#!makefile

CC = g++
CXXFLAGS = -Wall -ansi -Wextra -g 
LDFLAGS = -lm

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
EXE = exe

all : $(EXE)
%.o : %.cpp %.hpp
	$(CC) -c $< $(CXFLAGS)

$(EXE) : $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(LDFLAGS) 

clean:
	rm -f $(OBJ) *~
