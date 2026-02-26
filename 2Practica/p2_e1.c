#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stack.h"
#include "music.h"
#include "radio.h"

int show_player_menu(Stack *history);
int show_player_menu(Stack *history) {
    int option;
    Music *m = NULL;
	
	/* Obtenemos canción actual del top de la pila */
	m = (Music *)stack_top (history);
    if (m != NULL) {
		music_formatted_print(stdout, m);
    } else {
        printf("\nNo song currently playing.\n");
    }
	
	/* Imprimimos historial (pila) */
	printf("\nRecently Played:\n");
	stack_print(stdout, history, music_plain_print);
	
	/* Mostramos menu y esperamos selección */
    printf("\n1. Back to previous song\n");
    printf("2. Exit\n");
    printf("Choose an option: ");

    scanf("%d", &option);

    return option;
}

/* TODO MAIN FUNCTION */
int main (int argc, char **argv) {
    FILE *f= NULL;
    Radio *radio = NULL;
    Stack *history = NULL;

    int n_music = 0;
    int i;
    int option;

    if(!(f= fopen(argv[1], "r"))){
        return 1;
    }
    radio = radio_init();

    if(radio == NULL){
        fclose(f);
        return 1;
    }

    if(radio_readFromFile(f, radio) == ERROR){
        fclose(f);
        radio_free(radio);
        return 1;
    }

    history = stack_init();

    if(history == NULL){
        fclose(f);
        radio_free(radio);
        return 1;
    }

    n_music = radio_getNumberOfMusic(radio);

    for(i= 0; i< n_music; i++){
        if(stack_push(history,radio_getMusic(radio, i)) == ERROR){
            radio_free(radio);
            stack_free(history);
            fclose(f);
            return -1;
        }
    }

    option = show_player_menu(history);

    while(option != 2 ){
        if(option){
            stack_pop(history);
            show_player_menu(history);
        }else {
            fprintf(stdout, "Error, please select one of the options\n");
            show_player_menu(history);
        }
    }

    radio_free(radio);
    stack_free(history);
    fclose(f);
    return 0;
}


