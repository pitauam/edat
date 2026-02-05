#include "music.h"

int main()
{

    Music *Cancion1;
    Music *Cancion2;

    Cancion1 = music_init();
    Cancion2 = music_init();

    music_setId(Cancion1, 10);
    music_setTitle(Cancion1, "Blinding Lights"); /*Falta hacer el if error*/
    music_setArtist(Cancion1, "The Weeknd");
    music_setDuration(Cancion1, 200);
    music_setState(Cancion1, 0);

    music_setId(Cancion1, 20);
    music_setTitle(Cancion2, "Bohemian Rhapsody"); /*Falta hacer el if error*/
    music_setArtist(Cancion2, "Queen");
    music_setDuration(Cancion2, 355);
    music_setState(Cancion2, 0);

    

}
