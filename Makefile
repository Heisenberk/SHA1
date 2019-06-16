# Makefile SHA-1 
# Clément Caumes

CFLAGS=-c -g
EXEC=sha1
CC=gcc
SRC=app/src
INC=app/inc
BLD=build

compil: clean $(BLD) convert.o main.o sha.o intern.o 
	$(CC) -o $(BLD)/src/$(EXEC) $(BLD)/src/main.o $(BLD)/src/convert.o $(BLD)/src/sha.o $(BLD)/src/intern.o -lm

run: compil 
	$(BLD)/src/$(EXEC)
	
build: 
	mkdir $(BLD)/
	
build_src: build
	mkdir $(BLD)/src/
	
build_test: build
	mkdir $(BLD)/test/
	
doxygen:
	doxygen doc/Doxyfile 
	
main.o: build_src
	$(CC) $(CFLAGS) $(SRC)/main.c -o $(BLD)/src/main.o

convert.o: build_src
	$(CC) $(CFLAGS) $(SRC)/convert.c -o $(BLD)/src/convert.o
		
sha.o: build_src
	$(CC) $(CFLAGS) $(SRC)/sha.c -o $(BLD)/src/sha.o
	
intern.o: build_src
	$(CC) $(CFLAGS) $(SRC)/intern.c -o $(BLD)/src/intern.o
	
clean: 
	rm -rf build/
