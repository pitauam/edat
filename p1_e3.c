#include "radio.h"
#include "music.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){

    Radio *radio = NULL;
    FILE *f = NULL;

    if(argc < 2){
        printf("Error, needed a text file");
        return -1;
    }

    radio = radio_init();

    if(radio == NULL){
        radio_free(radio);
        return -1;
    }


    if(!(f = fopen(*argv, "r"))){
        radio_free(radio);
        printf("Error opening file");
        return -1;
    }

    if(radio_readFromFile(f, radio)== ERROR){
        radio_free(radio);
        return -1;
    }

     if(!(radio_print(stdout, radio))){
        radio_free(radio);
        return -1;
    }

    return 0;
}