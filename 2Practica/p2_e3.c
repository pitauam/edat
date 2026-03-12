#include <stdio.h>
#include <stdlib.h>

#include "radio.h"
#include "music.h"
#include "stack.h"

int main(int argc, char **argv){
    Radio *radio = NULL;
    FILE *f = NULL;
    long from_id, to_id;

    if(argc < 4){
        return -1;
    }

    radio = radio_init();
    if(radio == NULL){
        return -1;
    }

    if(!(f = fopen(argv[1], "r"))){
        radio_free(radio);
        return -1;
    }

    if(radio_readFromFile(f, radio) == ERROR){
        radio_free(radio);
        fclose(f);
        return -1;
    }
    fclose(f); 

    from_id = atol(argv[2]);
    to_id = atol(argv[3]);

    fprintf(stdout, "Radio:\n");
    radio_print(stdout, radio);

    /* Textos exactos del PDF */
    fprintf(stdout, "\nFrom music with id: %ld\n", from_id);
    fprintf(stdout, "To music with id: %ld\n", to_id);
    fprintf(stdout, "Music exploration path:\n");
    
    radio_depthSearch(radio, from_id, to_id);

    radio_free(radio);
    return 0;
}