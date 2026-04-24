########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic

#EJS = p4_e1
#EJS = p4_e2
#EJS = p4_e3

EJS = p4_e1 p4_e2 
#p4_e3
EXECUTABLES = $(EJS)

########################################################
OBJECTSp4E1 = p4_e1.o music.o radio.o bstree.o list.o stack.o queue.o
OBJECTSp4E2 = p4_e2.o music.o radio.o bstree.o list.o stack.o queue.o
OBJECTSp4E3 = p4_e3.o music.o radio.o bstree.o list.o stack.o queue.o
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
p4_e1.o: p4_e1.c bstree.h music.h types.h 
	$(CC) $(CFLAGS) -c p4_e1.c

p4_e2.o: p4_e2.c bstree.h music.h types.h list.h
	$(CC) $(CFLAGS) -c p4_e2.c

p4_e3.o: p4_e3.c bstree.h list.h types.h music.h
	$(CC) $(CFLAGS) -c p4_e3.c

#general .os
bstree.o: bstree.c bstree.h types.h list.h
	$(CC) $(CFLAGS) -c bstree.c

music.o: music.c music.h types.h
	$(CC) $(CFLAGS) -c music.c

radio.o: radio.c radio.h music.h types.h stack.h queue.h
	$(CC) $(CFLAGS) -c radio.c

list.o: list.c list.h types.h
	$(CC) $(CFLAGS) -c list.c

stack.o: stack.c stack.h types.h
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c queue.h types.h
	$(CC) $(CFLAGS) -c queue.c

#clean all .os
clear:
	rm -rf *.o 

clean:
	rm -rf *.o *.gch $(EXECUTABLES)

#without valgrind
run:
	@echo ">>>>>>Running p4_e1 in normal mode"
	./p4_e1 data_music_10 8 normal

	@echo ">>>>>>Running p4_e1 in sorted mode"
	./p4_e1 data_music_10 8 sorted



	@echo ">>>>>>Running p4_e2"
	./p4_e2 data_music_10.txt 3 7

# no longer needed vvv
#	@echo ">>>>>>Running p4_e2 in normal mode"
#	./p4_e2 data_music_10 8 normal

#	@echo ">>>>>>Running p4_e2 in sorted mode"
#	./p4_e2 data_music_10 8 sorted



#	@echo ">>>>>>Running p4_e3"
#	./p4_e3 data_music_10.txt 300

#valgrind
runv:
	@echo ">>>>>>Running p4_e1 in normal mode with valgrind"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./p4_e1 data_music_10 8 normal

	@echo ">>>>>>Running p4_e1 in sorted mode with valgrind"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./p4_e1 data_music_10 8 sorted



	@echo ">>>>>>Running p4_e2"
	./p4_e2 data_music_10.txt 3 7

# no longer needed vvv
#	@echo ">>>>>>Running p4_e2 in normal mode with valgrind"
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./p4_e2 data_music_10 8 normal
	
#	@echo ">>>>>>Running p4_e2 in sorted mode with valgrind"
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./p4_e2 data_music_10 8 sorted



#	@echo ">>>>>>Running p4_e3 with valgrind"
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./p4_e3 data_music_10.txt 300