#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "radio.h"
#include "queue.h"
#include "music.h"



int now_playing_menu(Queue *q);



int main(int argc, char **argv)
{
    Radio *r = NULL;
    FILE *pf = NULL;
    Queue *q = NULL;

    int i;
    int choice;

    if (argc < 2) {
        printf("You need more than %i arguments, insert text file.\n", argc);
        return -1;
    }

    if (!(r = radio_init())){
        printf("Error while creating radio\n");
        return -1;
    }

    if(!(pf = fopen(argv[1], "r"))) {
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

    choice = now_playing_menu(q);

    while (choice !=2){

        if (choice){
            queue_pop(q);
            choice = now_playing_menu(q);
        }
        else{
            printf("Error, select one of the options");
            choice = now_playing_menu(q);
        }
    }

    queue_free(q);
    fclose(pf);
    radio_free(r);

    return 0;
}




int now_playing_menu(Queue *q){
    Music *m = NULL;
    int choice;

    if (!q) {
        return 2; /*error, exiting*/
    }

    m = (Music*)queue_pop(q);

    if (m != NULL) {
        music_formatted_print(stdout, m);
        printf("\nUpcoming:\n");
	    queue_print(stdout, q, music_plain_print);
    }
    else{
        printf("\nNo songs available in the queue.\n");
    }
    	
	

    printf("\n1. Next song\n");
    printf("2. Exit\n");
    printf("Choose an option: ");

    scanf("%d", &choice);

    return choice;
}