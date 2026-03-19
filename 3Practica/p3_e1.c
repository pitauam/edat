#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "radio.h"
#include "queue.h"



int now_playing_menu(Queue *q);



int main(int argc, char **argv)
{
    Radio *r = NULL;
    FILE *pf = NULL;
    Queue *q = NULL;
    Music *m;

    int i;

    if (argc < 2) {
        printf("You need more than %i arguments, insert text file.\n", argc);
        return -1;
    }

    if (!(r = radio_init())){
        printf("Error while creating radio\n");
        return -1;
    }

    if(!(pf = fopen(argv[0], "r"))) {
        printf("Error while opening file\n");
        radio_free(r);
        return -1;
    }

    if ((radio_readFromFile(pf, r)) == ERROR) {
        printf("Error while reading from file\n");
        radio_free(r);
        fclose(pf);

        return -1;
    }

    if (!(q = queue_new())){
        printf("Error while creating queue\n");
        radio_free(r);
        fclose(pf);

        return -1;
    }

    i = 0;
    for (i = 0; i < radio_getNumberOfMusic(r); i++){
        if (queue_push(q, (void*)radio_getMusic(r, i)) == ERROR){
            printf("Error while pushing elements into queue\n");
            radio_free(r);
            fclose(pf);
            queue_free(q);
            return -1;
        }
    }

    queue_free(q);
    fclose(pf);
    radio_free(r);

    return 0;
}




int now_playing_menu(Queue *q){
    int i;
    Music *m = NULL;
    int choice;

    if (!q) {
        return -1;
    }

    i = 0;

    m = (Music*)queue_pop(q);
    if (m != NULL) {
        music_formatted_print(stdout, m);
    }
    else{
        printf("\nNo song currently playing.\n");
    }
    	
	printf("\nUpcoming:\n");
	queue_print(stdout, q, music_plain_print);

    printf("\n1. Next song\n");
    printf("2. Exit\n");
    printf("Choose an option: ");

    scanf("%d", &choice);

    return choice;
}