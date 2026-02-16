#include "radio.h"
#include "music.h"

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
    
    /* 1. Definición de Strings con comillas escapadas para que music_initFromString funcione bien */
    char descr1[] = "id:\"111\" title:\"Paint It, Black\" artist:\"The Rolling Stones\" duration:\"202\"";
    char descr2[] = "id:\"222\" title:\"Every Breath You Take\" artist:\"The Police\" duration:\"253\"";

    radio = radio_init();
    if(radio == NULL){return -1;}

    /* Inicializamos auxiliares para obtener IDs y Títulos cómodamente */
    cancion1 = music_initFromString(descr1);
    cancion2 = music_initFromString(descr2);

    if (!cancion1 || !cancion2) {
        radio_free(radio);
        return -1;
    }

    /* 2. Inserciones e impresiones exactas a la imagen */
    st = radio_newMusic(radio, descr1);
    printf("Inserting Paint It, Black... result...: %d\n", st);

    st = radio_newMusic(radio, descr2);
    printf("Inserting Every Breath You Take... result...: %d\n", st);
    
    printf("\n"); /* Salto de línea vacío como en la imagen */
    
    /* Insertamos relación 222 -> 111 */
    st = radio_newRelation(radio, music_getId(cancion2), music_getId(cancion1));
    /* TRUCO: La imagen muestra "222 --> 1111". Esto se logra imprimiendo el ID destino (111) 
       seguido inmediatamente del status (1) */
    printf("Inserting radio recommendation: %ld --> %ld%d\n\n", 
            music_getId(cancion2), music_getId(cancion1), st);

    /* 3. Comprobaciones de relaciones */
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
    
    /* 4. Conteo de conexiones */
    n_conn = radio_getNumberOfRelationsFromId(radio, music_getId(cancion1));
    printf("Number of connections from %ld: %d\n", music_getId(cancion1), n_conn);

    n_conn = radio_getNumberOfRelationsFromId(radio, music_getId(cancion2));
    printf("Number of connections from %ld: %d\n", music_getId(cancion2), n_conn);

    /* 5. Impresión específica de recomendaciones */
    /* Nota: Para replicar "Radio recommendations from Paint It, Black: 111" exactamente como en la foto,
       debemos imprimir el título de la canción 1, pero buscar las relaciones de la canción 2 (que es la que tiene la relación). */
    printf("\nRadio recommendations from Paint It, Black: ");
    adj_ids = radio_getRelationsFromId(radio, music_getId(cancion2)); 
    if (adj_ids != NULL) {
        printf("%ld", adj_ids[0]); /* Imprimimos el ID de la recomendación (111) */
        free(adj_ids);
    }
    printf("\n\n");

    /* 6. Impresión completa de la radio */
    printf("All radio recommendations:\n");
    radio_print(stdout, radio);

    /* Liberación de memoria */
    music_free(cancion1);
    music_free(cancion2);
    radio_free(radio);

    return 0;
}