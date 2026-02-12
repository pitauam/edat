#include "music.h"
#include <stdlib.h>

int main()
{
    /*Music initialization*/
    Music *Cancion1;
    Music *Cancion2;
    Music *Cancion3;

    Cancion1 = music_init();
    Cancion2 = music_init();

    /*Error control*/
    if (Cancion1 == NULL ){return -1;}

    if (Cancion2 == NULL)
    {
        music_free(Cancion1);
        return -1;
    }
    
    /*Setting music information*/
    music_setId(Cancion1, 10);
    music_setTitle(Cancion1, "Blinding Lights");
    music_setArtist(Cancion1, "The Weeknd");
    music_setDuration(Cancion1, 200);
    music_setState(Cancion1, NOT_LISTENED);

    music_setId(Cancion2, 20);
    music_setTitle(Cancion2, "Bohemian Rhapsody");
    music_setArtist(Cancion2, "Queen");
    music_setDuration(Cancion2, 355);
    music_setState(Cancion2, NOT_LISTENED);

    /*Reproducing music*/
    music_formatted_print(stdout, Cancion1);
    music_setState(Cancion1, LISTENED);
    music_formatted_print(stdout, Cancion2);
    music_setState(Cancion2, LISTENED);

    printf("\nEquals? ");

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
    if (Cancion3 == NULL)
    {
        music_free(Cancion1);
        music_free(Cancion2);
        return -1;
    }

    /*Prints the id of the third song*/
    printf("Music 3 id: %li\n", music_getId(Cancion3));

    /*Reproduces the first and the third song*/
     music_formatted_print(stdout, Cancion1);
     music_formatted_print(stdout, Cancion3);

    printf("\nEquals? ");

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
}
