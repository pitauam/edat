#include "radio.h"

#include <stdio.h>
#include <string.h>

int main(){

    Radio *radio = NULL;
    Music *cancion1 = NULL;
    Music *cancion2 = NULL;
    int n_relation = 0;
    char descr1 [300] = "id:111 title:Paint It, Black artist:The Rolling Stones duration:202";
    char descr2 [300] = "id:222 title:Every Breath You Take artist:The Police duration:253";

    radio = radio_init();

    if(radio == NULL){return -1;}
    cancion1 = music_initFromString(descr1);
    cancion2 = music_initFromString(descr2);

    if(!(radio_newMusic(radio, descr1))){
        radio_free(radio);    
        return -1;
    }

    if(!(radio_newMusic(radio, descr2))){
        radio_free(radio);
        return -1;
    }
    
    if(!(radio_newRelation(radio, music_getId(cancion2) , music_getId(cancion1)))){
        radio_free(radio);
        return -1;
    }
    printf("Inserting radio recomendation 222 --> 111\n");
    printf("\n111-->222?");

    if(radio_relationExists(radio, music_getId(cancion1) , music_getId(cancion2))){
        printf("Yes\n");
    }else{
        printf("No\n");
    }
    printf("222-->111?");
    if(radio_relationExists(radio, music_getId(cancion2) , music_getId(cancion1))){
        printf("Yes\n");
    }else{
        printf("No\n");
    }
    
    if( (n_relation = radio_getNumberOfRelationsFromId(radio, music_getId(cancion1))) == -1){
        return -1;
    }

    printf("Number of connections from %ld: %d\n",music_getId(cancion1), n_relation);

    if( (n_relation = radio_getNumberOfRelationsFromId(radio, music_getId(cancion2))) == -1){
        return -1;
    }
    printf("Number of connections from %ld: %d\n",music_getId(cancion2), n_relation);

    radio_print(stdout, radio);

    radio_free(radio);

    return 0;

}