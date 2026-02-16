#include "radio.h"
#include "music.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STR_LENGTH 64

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
    int i;
    if (r == NULL) {return;}

    for (i = 0; r->songs[i] != NULL; i++)
    {
        music_free(r->songs[i]);
    }
    free(r);
    return;
}


Status radio_newMusic(Radio *r, char *desc){
    if (r == NULL || desc == NULL) {return ERROR;}
    Music *music;

    /*musicid = music_getId(music);
    if (musicid == -1) {return ERROR;}*/
    music = music_initFromString(desc);
    if (!music) {return ERROR;}

    if (radio_contains(r, music_getId(music)) == TRUE){return OK;}
    

    r->songs[r->num_music] = music;
    r->num_music++;
    return OK;
}


Status radio_newRelation(Radio *r, long orig, long dest){
    int i;

    int p1,p2; /*p1 y p2 son el indice donde estan ubicados los id de orig y dest*/
    if (r == NULL){return ERROR;}
    if (orig == dest) {return ERROR;} /*si dest = orig hay un error*/

    if (radio_contains(r, orig) == FALSE || radio_contains(r, dest) == FALSE)
    {
        return ERROR;
    }

    /*stores in p1 and p2 the position of the origin and destination songs respectively*/
    for (i = 0; i < r->num_music;i++)
    {
        if (music_getId(r->songs[i]) == orig)
        {
            p1 = i;
        }
        if (music_getId(r->songs[i]) == dest)
        {
            p2 = i;
        }
    }
    /*origin song is related to destination song*/
    r->relations[p1][p2] = TRUE; 

    /*adds one relation created*/
    r->num_relations++;

    return OK;
}


Bool radio_contains(const Radio *r, long id){
    int i;
    for (i = 0; i < r->num_music; i++)
    {
        if (music_getId(r->songs[i]) == id)
        {
            return TRUE;
        }
    }
    return FALSE;
}


int radio_getNumberOfMusic(const Radio *r){
    if (r == NULL) {return -1;}
    return r->num_music;
}


int radio_getNumberOfRelations(const Radio *r){
    if (r == NULL){return -1;}
    return r->num_relations;
}


Bool radio_relationExists(const Radio *r, long orig, long dest){
    int i,p1,p2;
    if (r == NULL){return FALSE;}
    if (orig == dest) {return FALSE;}
    
    if (radio_contains(r, orig) == FALSE || radio_contains(r, dest) == FALSE)
    {
        return FALSE;
    }

    for (i = 0; i < r->num_music;i++)
    {
        if (music_getId(r->songs[i]) == orig)
        {
            p1 = i;
        }
        if (music_getId(r->songs[i]) == orig)
        {
            p2 = i;
        }
    }

    if (r->relations[p1][p2] == TRUE) {return TRUE;}
    return FALSE;
}


int radio_getNumberOfRelationsFromId(const Radio *r, long id){
    int i;
    int count;
    int p1;
    if (r == NULL){return -1;}
    
    for (i = 0; i < r->num_music;i++)
    {
        if (music_getId(r->songs[i]) == id)
        {
            p1 = i;
            break;
        }
    }

    count = 0;

    for (i = 0; i < r->num_music; i++)
    {
        if (r->relations[p1][i] == TRUE)
        {   
            count++;
        }
    }

    return count;
}


long *radio_getRelationsFromId(const Radio *r, long id){

    long *array; /*array with the ids*/
    int i;       /*counter*/
    int n;       /*number of longs needed*/
    int p1;      /*position of the id in the songs array*/
    int count;   /*total number of relations, used as a counter*/

    if (r == NULL){return NULL;}

    n = radio_getNumberOfRelationsFromId(r, id);
    if (n == -1) {return NULL;}

    array = (long *)calloc(n, sizeof(long));
    if (!array){return NULL;}

    for (i = 0; i < r->num_music;i++)
    {
        if (music_getId(r->songs[i]) == id)
        {
            p1 = i;
            break;
        }
    }

    count = 0;
    for (i = 0; i < r->num_music;i++)
    {
        if (r->relations[p1][i] == TRUE)
        {
            array[count] = music_getId(r->songs[i]);
            count++;
        }
    }

    return array;
}


int radio_print (FILE *pf, const Radio *r){

    int i, j, total_chars = 0, sum = 0;
    if (!pf || !r) return -1;
    
    for (i = 0; i < r->num_music;i++)
    {
        sum = music_plain_print(pf, r->songs[i]);
        if (sum == -1) {return -1;}
        total_chars += sum;

        sum = fprintf(pf, ":");
        if (sum < 0) return -1;
        total_chars += sum;

        for (j = 0; j < r->num_music; j++) {
            if (r->relations[i][j] == TRUE) 
            {
                fprintf(pf, " "); 
                total_chars++;

                sum = music_plain_print(pf, r->songs[j]);
                if (sum == -1) return -1;
                total_chars += sum;
            }
        }
        fprintf(pf, "\n");
        total_chars++;
    }
    return total_chars;
}


Status radio_readFromFile (FILE *fin, Radio *r){

    int i; /*int for the loop*/
    int n_songs;
    char line[1024];
    char *ptr;

    long orig, dest; /*used to create a new relation*/
    

    if (fin == NULL || r == NULL)
    {
        return ERROR;
    }
    /*reads number of songs*/
    fscanf(fin, "%i", &n_songs);

    /*reads the n_songs songs and sets parameters for each song */

    for (i = 0; i < n_songs; i++) {
        if (fgets(line, sizeof(line), fin) != NULL) 
        {
            r->songs[i] = music_initFromString(line);
        }
    }

    /*relation_count = 0;
    while(fscanf(fin, "%i %i") >=2)
    {
        relation_count;
    }*/

    while (fgets(line, sizeof(line), fin) != NULL) {
        /* Extraemos el primer ID: el ORIGEN */
        ptr = strtok(line, " \t\n\r");
        if (!ptr) continue; /* Línea vacía */
        orig = atol(ptr);

        /* Los siguientes IDs en la MISMA línea son los DESTINOS */
        while ((ptr = strtok(NULL, " \t\n\r")) != NULL) {
            dest = atol(ptr);
            radio_newRelation(r, orig, dest);
        }
    }

    /*
    for (i = 0; i < relation_count; i++)
    {

        if (fscanf(fin, "%li %li", &orig, &dest) == 2)
        {
            radio_newRelation(r, orig,dest);

        }
        else if (fscanf(fin, "%li %li %li", &orig, &dest, &id3) == 3)
        {


        }



    }


        //radio_newRelation(r, orig,dest);

        */

    return OK;
}
