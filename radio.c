#include "radio.h"
#include "music.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct _Radio{
    Music *songs[MAX_MSC];           /*Array with the radio music*/
    Bool relations[MAX_MSC][MAX_MSC];/*Adjacency Matrix*/
    int num_music;                   /*Total number of music*/
    int num_relations;               /*Total number of relations*/
};


Radio * radio_init(){
    Radio *radio;
    radio = (Radio *)calloc(1, sizeof(Radio));
    if (!radio) {return NULL;}

    radio->num_music =0;
    radio->num_relations = 0;

    return radio;
}


void radio_free(Radio *r){
    if (r == NULL) {return;}

    free(r->songs);
    free(r);
    return;
}


Status radio_newMusic(Radio *r, char *desc){
    if (r == NULL ) {return ERROR;}
    Music *music;
    long musicid;
    int i;

    music = music_initFromString(desc);
    musicid = music_getId(music);
    if (musicid == -1) {return ERROR;}

    for (i = 0; i < r->num_music; i++)
    {
        if (music_getId(r->songs[i]) == musicid)
        {
            return OK;
        }
    }

    r->num_music++;
    r->songs[r->num_music] = music;

    return OK;
}


Status radio_newRelation(Radio *r, long orig, long dest){

    int i;
    if (r == NULL){return ERROR;}
    int music_exists_in_radio = 0;

    for (i = 0; i < r->num_music; i++)
    {
        if ((music_getId(r->songs[i]) == dest))
        {
            music_exists_in_radio = 1;
        }
        if ((music_getId(r->songs[i]) == orig))
        {
            music_exists_in_radio = 1;
        }
    }

    if (music_exists_in_radio == 0) {return ERROR;}

    r->relations[r->num_music][r->num_relations] = TRUE;

    r->num_relations++;

    /*falta terminar esta funcion*/
    
    return OK;
}

Bool radio_contains(const Radio *r, long id){

    int i;
    for (i = 0; i < r->num_music; i++)
    {
        if (music_getId(r->songs[i]) == id)
        {
            return OK;
        }
    }


}

int radio_getNumberOfMusic(const Radio *r);

int radio_getNumberOfRelations(const Radio *r);

Bool radio_relationExists(const Radio *r, long orig, long dest);

int radio_getNumberOfRelationsFromId(const Radio *r, long id);

long *radio_getRelationsFromId(const Radio *r, long id);

int radio_print (FILE *pf, const Radio *r);

Status radio_readFromFile (FILE *fin, Radio *r);
