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
    if (music_setState(Cancion1, NOT_LISTENED) == ERROR) {return -1;}

    if (music_setId(Cancion2, 20) == ERROR) {return -1;}
    if (music_setTitle(Cancion2, "Bohemian Rhapsody") == ERROR) {return -1;}
    if (music_setArtist(Cancion2, "Queen") == ERROR) {return -1;}
    if (music_setDuration(Cancion2, 355) == ERROR) {return -1;}
    if (music_setState(Cancion2, NOT_LISTENED) == ERROR) {return -1;}

    pf = fopen("test.txt", "w");
    if (pf == NULL) {return -1;}

    /*Reproducing music*/
    if (music_formatted_print(pf, Cancion1) == -1) {return -1;}
    if (music_setState(Cancion1, LISTENED) == ERROR) {return -1;}
    if (music_formatted_print(pf, Cancion2) == -1) {return -1;}
    if (music_setState(Cancion2, LISTENED) == ERROR) {return -1;}

    fprintf(pf, "\nEquals? ");

    /*Compare both songs and show a message with the result*/
    if (music_cmp(Cancion1, Cancion2) == 0) /*if both songs are equal*/
    {
        fprintf(pf, "Yes\n");
    }
    else {fprintf(pf, "No\n");}

    /*Prints the title of the second song*/
    fprintf(pf, "Music 2 title: %s\n", music_getTitle(Cancion2));

    /*Copies the first song in a third one*/
    Cancion3 = music_copy(Cancion1);
    if (Cancion3 == NULL) {return -1;}

    /*Prints the id of the third song*/
    fprintf(pf, "Music 3 id: %li\n", music_getId(Cancion3));


    /*Reproduces the first and the third song*/
    if (music_formatted_print(pf, Cancion1) == -1) {return -1;}
    if (music_formatted_print(pf, Cancion3) == -1) {return -1;}

    fprintf(pf, "   Equals? ");


    /*Compare both songs and show a message with the result*/
    if (music_cmp(Cancion1, Cancion3) == 0) /*if both songs are equal*/
    {
        fprintf(pf, "Yes\n");
    }
    else {fprintf(pf, "No\n");}
  
    /*Frees memory*/
    fclose(pf);
    music_free(Cancion1);
    music_free(Cancion2);
    music_free(Cancion3);
}
