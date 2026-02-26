########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic
EJS = p2_e2
EJS = p2_e1 p2_e2 p2_e3
########################################################
OBJECTSP2E1 = p2_e1.o stack.o radio.o music.o
OBJECTSP2E2 = p2_e2.o radio.o music.o
OBJECTSP2E3 = p2_e3.o radio.o music.o
########################################################

all: $(EJS) clear

p2_e1: $(OBJECTSP2E1) 
	$(CC) $(CFLAGS) -o p2_e1 $(OBJECTSP2E1)

#p2_e2: $(OBJECTSP2E2) 
#	$(CC) $(CFLAGS) -o p2_e2 $(OBJECTSP2E2)

#p2_e3: $(OBJECTSP2E3) 
#	$(CC) $(CFLAGS) -o p2_e3 $(OBJECTSP2E3)


p2_e1.o: p2_e1.c stack.h types.h music.h radio.h
	$(CC) $(CFLAGS) -c p2_e1.c

#p2_e2.o: p2_e2.c music.h radio.h
#	$(CC) $(CFLAGS) -c p2_e2.c
	
#p2_e3.o: p2_e3.c music.h radio.h
#	$(CC) $(CFLAGS) -c p2_e3.c

file_utils.o: file_utils.c file_utils.h types.h
	$(CC) $(CFLAGS) -c file_utils.c

music.o: music.c music.h types.h
	$(CC) $(CFLAGS) -c music.c

radio.o: radio.c radio.h music.h
	$(CC) $(CFLAGS) -c radio.c

stack.o: stack.c music.h types.h stack.h
	$(CC) $(CFLAGS) -c stack.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p2_e1"
	./p2_e1
#	@echo ">>>>>>Running p2_e2"
#	./p2_e2 
#	@echo ">>>>>>Running p2_e3"
#	./p2_e3 radio1.txt

runv:
	@echo ">>>>>>Running p2_e1 with valgrind"
	valgrind --leak-check=full --show-leak-kinds=all ./p2_e1
#	@echo ">>>>>>Running p2_e2 with valgrind"
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./p2_e2 
#	@echo ">>>>>>Running p2_e3 with valgrind"
#	valgrind --leak-check=full --show-leak-kinds=all ./p2_e3 radio1.txt

	