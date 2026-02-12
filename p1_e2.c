#include "radio.h"

#include <stdio.h>
#include <string.h>

int main(){

    Radio *radio = NULL;
    int n_relation = 0;
    char descr1 [300] = "id:111 title:Paint It, Black artist:The Rolling Stones duration:202";
    char descr2 [300] = "id:222 title:Every Breath You Take artist:The Police duration:253";

    radio = radio_init();

    if(radio == NULL){return -1;}

    if(!(radio_newMusic(radio, descr1))){
        radio_free(radio);    
        return -1;
    }

    if(!(radio_newMusic(radio, descr2))){
        radio_free(radio);
        return -1;
    }
    
    if(!(radio_newRelation(radio, 222 , 111))){
        radio_free(radio);
        return -1;
    }
    printf("Inserting radio recomendation 222 --> 111\n");
    printf("\n111-->222?");

    if(radio_relationExists(radio, 111, 222)){
        printf("Yes\n");
    }else{
        printf("No\n");
    }
    printf("222-->111?");
    if(radio_relationExists(radio, 222,111)){
        printf("Yes\n");
    }else{
        printf("No\n");
    }
    
    if(n_relation = radio_getNumberOfRelationsFromId(radio, 111) == -1){
        return -1;
    }
    printf("Number of connections from 111: %d\n", n_relation);



}