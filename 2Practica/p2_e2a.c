#include <stdio.h>
#include <stdlib.h>

#include "music.h"
#include "radio.h"
#include "stack.h"


int main(int argc, char **argv) {
    FILE *f1= NULL;
    FILE *f2= NULL;
    Radio *radio1 = NULL;
    Radio *radio2 = NULL;
    Stack *Playlist1 = NULL;
    Stack *Playlist2 = NULL;
    Stack *MergedPlay = NULL;

    int n_music1 = 0;
    int n_music2 = 0;
    int i;

    if(!(f1= fopen(argv[1], "r"))){
        return -1;
    }

    if(!(f1= fopen(argv[2], "r"))){
        return -1;
    }
    radio1 = radio_init();
    radio2 = radio_init();

    if(radio1 == NULL){
        fclose(f1);
        fclose(f2);
        return 1;
    }

    if(radio2 == NULL){
        fclose(f1);
        fclose(f2);
        radio_free(radio1);
        return 1;
    }

    if(radio_readFromFile(f1, radio1) == ERROR){
        fclose(f1);
        fclose(f2);
        radio_free(radio1);
        radio_free(radio2);
        return 1;
    }

    if(radio_readFromFile(f2, radio2) == ERROR){
        fclose(f1);
        fclose(f2);
        radio_free(radio1);
        radio_free(radio2);
        return 1;
    }

    fclose(f1);
    fclose(f2);

    Playlist1 = stack_init();
    Playlist2 = stack_init();
    MergedPlay = stack_init();

    if(Playlist1 == NULL){
        radio_free(radio1);
        radio_free(radio2);
        return 1;
    }

    if(Playlist2 == NULL){
        radio_free(radio1);
        radio_free(radio2);
        stack_free(Playlist1);
        return 1;
    }

    if(MergedPlay == NULL){
        radio_free(radio1);
        radio_free(radio2);
        stack_free(Playlist1);
        stack_free(Playlist2);
        return 1;
    }
    n_music1 = radio_getNumberOfMusic(radio1);
    n_music2 = radio_getNumberOfMusic(radio2);

    for(i=0; i< n_music1; i++){
        if(stack_push(Playlist1, radio_getMusic(radio1, i)) == ERROR){
            radio_free(radio1);
            radio_free(radio2);
            stack_free(Playlist1);
            stack_free(Playlist2);
            stack_free(MergedPlay);
            return -1;
        }
    }

    for(i=0; i< n_music2; i++){
        if(stack_push(Playlist2, radio_getMusic(radio2, i)) == ERROR){
            radio_free(radio1);
            radio_free(radio2);
            stack_free(Playlist1);
            stack_free(Playlist2);
            stack_free(MergedPlay);
            return -1;
        }
    }

    if(mergeStacks(Playlist1, Playlist2, MergedPlay) == ERROR){
        printf("Error merging the playlist");
        radio_free(radio1);
        radio_free(radio2);
        stack_free(Playlist1);
        stack_free(Playlist2);
        stack_free(MergedPlay);
    }

    stack_print(stdout, MergedPlay, music_plain_print);
    fprintf(stdout, "patata");
    radio_free(radio1);
    radio_free(radio2);
    stack_free(Playlist1);
    stack_free(Playlist2);
    stack_free(MergedPlay);

    return 0;
}