#include "music.h"
#include <stdlib.h>

int main()
{
    /*Music initialization*/
    Music *Cancion1;
    Music *Cancion2;
    Music *Cancion3;

    FILE *pf;

    Cancion1 = music_init();
    Cancion2 = music_init();
    
    if (Cancion1 == NULL || Cancion2 == NULL){return -1;}
    
    /*Setting music information*/
    if (music_setId(Cancion1, 10) == ERROR) {return -1;}
    if (music_setTitle(Cancion1, "Blinding Lights") == ERROR) {return -1;}
    if (music_setArtist(Cancion1, "The Weeknd") == ERROR) {return -1;}
    if (music_setDuration(Cancion1, 200) == ERROR) {return -1;}
    if (music_setState(Cancion1, 0) == ERROR) {return -1;}

    if (music_setId(Cancion1, 20) == ERROR) {return -1;}
    if (music_setTitle(Cancion2, "Bohemian Rhapsody") == ERROR) {return -1;}
    if (music_setArtist(Cancion2, "Queen") == ERROR) {return -1;}
    if (music_setDuration(Cancion2, 355) == ERROR) {return -1;}
    if (music_setState(Cancion2, 0) == ERROR) {return -1;}

    pf = fopen("test.txt", "w"); /*Fichero de prueba*/
    if (!pf) {return -1;}

    /*Reproducing music*/
    if (music_formatted_print(pf, Cancion1) == -1) {return -1;}
    printf("\n");
    if (music_formatted_print(pf, Cancion2) == -1) {return -1;}

    printf("\n");
    printf("Equals? ");

    /*Compare both songs and show a message with the result*/
    if (music_cmp(Cancion1, Cancion2) == 0) /*if both songs are equal*/
    {
        printf("Yes\n");
    }
    else {printf("No\n");}

    /*Prints the title of the second song*/
    printf("Music 2 title: %s\n", music_getTitle(Cancion2));

    /*Copies the first song in a third one*/
    Cancion3 = music_copy(Cancion1);
    if (Cancion3 == NULL) {return -1;}

    /*Prints the id of the third song*/
    printf("Music 3 id: %li\n", music_getId(Cancion3));

    /*Reproduces the first and the third song*/
    if (music_formatted_print(pf, Cancion1) == -1) {return -1;}
    printf("\n");
    if (music_formatted_print(pf, Cancion3) == -1) {return -1;}
    printf("\n");

    /*Compare both songs and show a message with the result*/
    if (music_cmp(Cancion1, Cancion3) == 0) /*if both songs are equal*/
    {
        printf("Yes\n");
    }
    else {printf("No\n");}
  
    /*Frees memory*/
    music_free(Cancion1);
    music_free(Cancion2);
    music_free(Cancion3);
    fclose(pf);
}
