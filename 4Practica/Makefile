########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic

#EJS = p4_e1
#EJS = p4_e2
#EJS = p4_e3

EJS = p4_e1 p4_e2 p4_e3
EXECUTABLES = $(EJS)
########################################################
OBJECTSp4E1 = p4_e1.o music.o radio.o stack.o queue.o
OBJECTSp4E2 = p4_e2.o music.o radio.o stack.o queue.o
OBJECTSp4E3 = p4_e3.o music.o radio.o stack.o queue.o list.o
########################################################

all: $(EJS)

#executables
p4_e1: $(OBJECTSp4E1) 
	$(CC) $(CFLAGS) -o p4_e1 $(OBJECTSp4E1)

p4_e2: $(OBJECTSp4E2) 
	$(CC) $(CFLAGS) -o p4_e2 $(OBJECTSp4E2)

p4_e3: $(OBJECTSp4E3) 
	$(CC) $(CFLAGS) -o p4_e3 $(OBJECTSp4E3)

#exe's .os
p4_e1.o: p4_e1.c radio.h music.h types.h queue.h 
	$(CC) $(CFLAGS) -c p4_e1.c

p4_e2.o: p4_e2.c radio.h music.h types.h queue.h
	$(CC) $(CFLAGS) -c p4_e2.c

p4_e3.o: p4_e3.c list.h types.h radio.h music.h
	$(CC) $(CFLAGS) -c p4_e3.c

#general .os

music.o: music.c music.h types.h
	$(CC) $(CFLAGS) -c music.c

radio.o: radio.c radio.h music.h types.h stack.h
	$(CC) $(CFLAGS) -c radio.c

stack.o: stack.c music.h types.h stack.h
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c queue.h types.h
	$(CC) $(CFLAGS) -c queue.c

list.o: list.c list.h types.h
	$(CC) $(CFLAGS) -c list.c
	
#clean all .os
clear:
	rm -rf *.o 

#clean all files made by makefile
clean:
	rm -rf *.o *.gch $(EXECUTABLES) test_queue

#without valgrind
run:
	@echo ">>>>>>Running p4_e1"
	./p4_e1 radio.txt

	@echo ">>>>>>Running p4_e2"
	./p4_e2 radio_bfs.txt 1 2

	@echo ">>>>>>Running p4_e3"
	./p4_e3 radio_bfs.txt

#valgrind
runv:
	@echo ">>>>>>Running p4_e1 with valgrind"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./p4_e1 radio.txt 4

	@echo ">>>>>>Running p4_e2 with valgrind"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./p4_e2 radio_bfs.txt 1 2

	@echo ">>>>>>Running p4_e3 with valgrind"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./p4_e3 radio.txt	

test:
	@echo "Running tests"
	gcc queue.c test_queue.c -o test_queue
	valgrind --leak-check=full ./test_queue