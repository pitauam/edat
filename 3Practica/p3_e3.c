#include <stdio.h>
#include <string.h>

#include "list.h"
#include "radio.h"

int main(int argc, char **argv){

    List *list = NULL;
    Radio *radio = NULL;
    FILE *f = NULL;

    int n_music;
    int i;
    int j;
    char e[200];

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

    for(i=0; i< n_music; i+=2){
        if(list_pushBack(list, radio_getMusic(radio, i)) == ERROR){
            radio_free(radio);
            list_free(list);
            fclose(f);
            return -1;
        }
        if(list_pushFront(list, radio_getMusic(radio, i+1)) == ERROR){
            radio_free(radio);
            list_free(list);
            fclose(f);
            return -1;
        }
    }

    fprintf(stdout, "Finished inserting. Now we extract from the beginning: \n");
    for(i=0; i< (list_size(list)/2); i++){
        strcpy(e, list_popFront(list));
        if(list_popFront(list)){
            radio_free(radio);
            list_free(list);
            fclose(f);
            return -1;
        }
        fprintf(stdout, "%s", e);
    }
    fprintf(stdout,"Now we extract from the back: \n");
    for(i=0; i< (list_size(list)/2); i++){
        strcpy(e, list_popBack(list));
        if(list_popFront(list)){
            radio_free(radio);
            list_free(list);
            fclose(f);
            return -1;
        }
        fprintf(stdout, "%s", e);
    }
}