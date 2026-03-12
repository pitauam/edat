#include <stdio.h>
#include <stdlib.h>

#include "radio.h"
#include "music.h"
#include "stack.h"

int main(int argc, char **arga, long *argb){
    Radio *radio = NULL;
    int i =0;

    radio = radio_init();

    if(radio == NULL){
        return -1;
    }

    if(radio_readFromFile(arga[1], radio) == ERROR){
        radio_free(radio);
    }
    fprintf(stdout, "Radio: ");
    printf("\n");

    radio_print(stdout, radio);

    printf("\n");
    fprintf(stdout, "From Music with id: %ld\n", argb[1]);
    fprintf(stdout, "To Music with id: %ld\n", argb[2]);
    
    fprintf(stdout, "Music exportation path: \n");
    radio_depthSearch(radio, argb[1], argb[2]);

    for(i=0; i< radio_getNumberOfMusic(radio); i++){
        if(music_getIndex)
    }
    

}