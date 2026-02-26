#include "radio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    Radio *radio = NULL;
    Music *cancion1 = NULL;
    Music *cancion2 = NULL;
    Status st = ERROR;
    int n_conn = 0;
    long *adj_ids = NULL;
    
    char descr1[] = "id:\"111\" title:\"Paint It, Black\" artist:\"The Rolling Stones\" duration:\"202\"";
    char descr2[] = "id:\"222\" title:\"Every Breath You Take\" artist:\"The Police\" duration:\"253\"";

    radio = radio_init();
    if(radio == NULL)
    {
        printf("Error allocating memory for the radio\n");
        return -1;
    }

    cancion1 = music_initFromString(descr1);
    cancion2 = music_initFromString(descr2);

    if (!cancion1 || !cancion2) {
        printf("Error allocating memory for the first song\n");
        radio_free(radio);
        return -1;
    }

    st = radio_newMusic(radio, descr1);
    printf("Inserting Paint It, Black... result...: %d\n", st);

    st = radio_newMusic(radio, descr2);
    printf("Inserting Every Breath You Take... result...: %d\n", st);
    
    printf("\n");
    
    st = radio_newRelation(radio, music_getId(cancion2), music_getId(cancion1));

    printf("Inserting radio recommendation: %ld --> %ld%d\n\n", 
            music_getId(cancion2), music_getId(cancion1), st);

    printf("%ld --> %ld? ", music_getId(cancion1), music_getId(cancion2));
    if(radio_relationExists(radio, music_getId(cancion1), music_getId(cancion2))){
        printf("Yes\n");
    }else{
        printf("No\n");
    }

    printf("%ld --> %ld? ", music_getId(cancion2), music_getId(cancion1));
    if(radio_relationExists(radio, music_getId(cancion2), music_getId(cancion1))){
        printf("Yes\n");
    }else{
        printf("No\n");
    }
    
    n_conn = radio_getNumberOfRelationsFromId(radio, music_getId(cancion1));
    printf("Number of connections from %ld: %d\n", music_getId(cancion1), n_conn);

    n_conn = radio_getNumberOfRelationsFromId(radio, music_getId(cancion2));
    printf("Number of connections from %ld: %d\n", music_getId(cancion2), n_conn);

    printf("\nRadio recommendations from Paint It, Black: ");
    adj_ids = radio_getRelationsFromId(radio, music_getId(cancion2)); 
    if (adj_ids != NULL) {
        printf("%ld", adj_ids[0]);
        free(adj_ids);
    }
    printf("\n\n");

    printf("All radio recommendations:\n");
    radio_print(stdout, radio);

    music_free(cancion1);
    music_free(cancion2);
    radio_free(radio);

    return 0;
}