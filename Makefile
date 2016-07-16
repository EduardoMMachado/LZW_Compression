# Implementado por: Eduardo Machado e Victor Perszel
# 2015

CC=g++
LIB=./lib
INCLUDE=./include
SRC=./src
OBJ=./obj
FLAGS = -Wall -lm

main:	lzw
	$(CC) $(SRC)/main.cpp $(OBJ)/lzw.o $(FLAGS) -I$(INCLUDE) -L$(LIB) -o lzw

lzw:
	$(CC) -c $(SRC)/lzw.cpp $(FLAGS) -I$(INCLUDE) -o $(OBJ)/lzw.o
	ar -cru $(LIB)/lzw.a $(OBJ)/lzw.o

clean:
	rm lzw $(SRC)/*~ $(OBJ)/*o $(LIB)/*a
