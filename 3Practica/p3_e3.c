#include <stdio.h>
#include <string.h>

#include "list.h"
#include "radio.h"

int main(int argc, char **argv){

    List *list = NULL;
    Radio *radio = NULL;
    FILE *f = NULL;
    void *music=NULL;

    int n_music, total;
    int i;

    if (argc < 2) {
        printf("You need more than %i argument(s), insert text file.\n", argc);
        return -1;
    }

    if (!(radio = radio_init())){
        printf("Error while creating radio\n");
        return -1;
    }

    if (!(list = list_new())){
        printf("Error while creating radio\n");
        return -1;
    }

    if(!(f = fopen(argv[1], "r"))) {
        printf("Error while opening file\n");
        radio_free(radio);
        list_free(list);
        return -1;
    }

    if(radio_readFromFile(f, radio) == ERROR){
        radio_free(radio);
        list_free(list);
        fclose(f);
        return -1;
    }

    n_music = radio_getNumberOfMusic(radio);

    for (i = 0; i < n_music; i++) {
        music = radio_getMusic(radio, i);
        if (i % 2 == 0) {
            list_pushBack(list, music);
        } else {
            list_pushFront(list, music);
        }
    }

    total = list_size(list);

    fprintf(stdout, "Finished inserting. Now we extract from the beginning: \n");
    for (i = 0; i < total / 2; i++) {
        void *e = list_popFront(list);
        if (e) {
            music_plain_print_p2_e3(stdout, e);
            printf(" ");
        }
    }

    fprintf(stdout, "\n");

    fprintf(stdout, "\nNow we extract from the end:\n");
    while (!list_isEmpty(list)) {
        void *e = list_popBack(list);
        if (e) {
            music_plain_print_p2_e3(stdout, e);
            printf(" ");
        }
    }
    fprintf(stdout, "\n");


    radio_free(radio);
    list_free(list);
    fclose(f);

    return 0;
}