########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic

EJS = p3_e1
#EJS = p3_e2
#EJS = p3_e3

#EJS = p3_e1 p3_e2 p3_e3
EXECUTABLES = $(EJS)
########################################################
OBJECTSP3E1 = p3_e1.o
OBJECTSP3E2 = p3_e2.o
OBJECTSP3E3 = p3_e3.o
########################################################

all: $(EJS) clear

#executables
p3_e1: $(OBJECTSP3E1) 
	$(CC) $(CFLAGS) -o p3_e1 $(OBJECTSP3E1)

p3_e2: $(OBJECTSP3E2) 
	$(CC) $(CFLAGS) -o p3_e2 $(OBJECTSP3E2)

p3_e3: $(OBJECTSP3E3) 
	$(CC) $(CFLAGS) -o p3_e3 $(OBJECTSP3E3)

#exe's .os
p3_e1.o: 
	$(CC) $(CFLAGS) -c p3_e1.c

p3_e2.o: 
	$(CC) $(CFLAGS) -c p3_e2.c

p3_e3.o: 
	$(CC) $(CFLAGS) -c p3_e3.c

#general .os

music.o: music.c music.h types.h
	$(CC) $(CFLAGS) -c music.c

radio.o: radio.c radio.h music.h types.h stack.h
	$(CC) $(CFLAGS) -c radio.c

stack.o: stack.c music.h types.h stack.h
	$(CC) $(CFLAGS) -c stack.c

list.o: list.c
	
#clean all .os
clear:
	rm -rf *.o 

#clean all files made by makefile
clean:
	rm -rf *.o $(EXECUTABLES)

#without valgrind
run:
	@echo ">>>>>>Running p3_e1"
	./p3_e1 radio.txt

	@echo ">>>>>>Running p3_e2"
	./p3_e2

	@echo ">>>>>>Running p3_e3"
	./p3_e3

#valgrind
runv:
	@echo ">>>>>>Running p3_e1 with valgrind"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./p3_e1 radio.txt

	@echo ">>>>>>Running p3_e2 with valgrind"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./p3_e2 radio.txt

	@echo ">>>>>>Running p3_e3 with valgrind"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./p3_e3 radio.txt	