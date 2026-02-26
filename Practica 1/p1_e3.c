#include "radio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){

    Radio *radio = NULL;
    FILE *f = NULL;

    if(argc < 2){
        printf("Error, needed a text file (you entered %i arguments)\n", argc);
        return -1;
    }

    radio = radio_init();

    if(radio == NULL){
        radio_free(radio);
        printf("Error allocating memory for radio\n");
        return -1;
    }

    if(!(f = fopen(argv[1], "r"))){
        radio_free(radio);
        printf("Error opening file\n");
        return -1;
    }

    if(radio_readFromFile(f, radio)== ERROR){
        radio_free(radio);
        printf("Error reading the file '%s'\n", argv[1]);
        return -1;
    }

     if(!(radio_print(stdout, radio))){
        radio_free(radio);
        printf("Error printing\n");
        fclose(f);
        return -1;
    }
    
    radio_free(radio);
    fclose(f);
    return 0;
}