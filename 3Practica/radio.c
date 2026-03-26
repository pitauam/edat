#include "radio.h"
#include "music.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "queue.h"

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

    for (i = 0; r->songs[i] != NULL && i < MAX_MSC; i++)
    {
        music_free(r->songs[i]);
        r->songs[i] = NULL;
    }
    free(r);
    r = NULL;
    return;
}


Status radio_newMusic(Radio *r, char *desc){
    if (r == NULL || desc == NULL) {return ERROR;}
    Music *music;

    /*musicid = music_getId(music);
    if (musicid == -1) {return ERROR;}*/
    music = music_initFromString(desc);
    if (!music) {return ERROR;}

    if (radio_contains(r, music_getId(music)) == TRUE){
        music_free(music);
        return OK;
    }

    music_setIndex(music,r->num_music);
    
    r->songs[r->num_music] = music;
    r->num_music++;

    return OK;
}


Status radio_newRelation(Radio *r, long orig, long dest){
    int i;

    int p1 = -1;
    int p2 = -1; /*p1 y p2 son el indice donde estan ubicados los id de orig y dest*/
    if (r == NULL){return ERROR;}
    if (orig == dest) {return ERROR;} /*si dest = orig hay un error*/

    if (radio_contains(r, orig) == FALSE || radio_contains(r, dest) == FALSE)
    {
        return ERROR;
    }

    if (radio_relationExists(r, orig, dest) == TRUE)
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

    /*if origin song is not related to destination song then sum one relation and set that relation to true*/
    if (r->relations[p1][p2] == FALSE) 
        {
            r->relations[p1][p2] = TRUE;
            r->num_relations++;
        }

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
    int i;
    int p1 = -1;
    int p2 = -1;
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
        if (music_getId(r->songs[i]) == dest)
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

Status radio_readFromFile(FILE *fin, Radio *r) {
    int i, n_songs;
    char line[1024];
    long orig, dest;

    if (fin == NULL || r == NULL) return ERROR;

    if (fscanf(fin, "%d", &n_songs) != 1) return ERROR;
    
    fgets(line, sizeof(line), fin); 

    for (i = 0; i < n_songs; i++) {
        if (fgets(line, sizeof(line), fin) != NULL) {
            radio_newMusic(r, line); 
        }
    }
    
    while (fscanf(fin, "%ld %ld", &orig, &dest) == 2 ) 
    {
        radio_newRelation(r, orig, dest);
    }

    return OK;
}

Music *radio_getMusic(Radio *r, int i){

    if(r == NULL || i > radio_getnumber(r) || !(radio_getnumber(r))){
        return NULL;
    }

    return r->songs[i];
}

int radio_getnumber(Radio *r){
    if(r == NULL){
        return -1;
    }

    return r->num_music;
}
Status radio_depthSearch (Radio *r, long from_id, long to_id)
{
    if (!r || r->num_music < 0 || r->num_relations < 0 || from_id < 0 || to_id < 0) return ERROR;

    Music *from_m = NULL;
    Music *to_m = NULL;
    int i, p_orig = -1;
    Status st = OK;
    Stack *s = NULL;

    for (i = 0; i < radio_getNumberOfMusic(r); i++) {
        if (music_getId(r->songs[i]) == from_id) from_m = r->songs[i];
        if (music_getId(r->songs[i]) == to_id) to_m = r->songs[i];
    }

    if (!from_m || !to_m) return ERROR;

    for (i = 0; i < radio_getNumberOfMusic(r); i++) {
        music_setState(r->songs[i], NOT_LISTENED);
    }

    s = stack_init();
    if (!s) return ERROR;

    music_setState(from_m, LISTENED);
    stack_push(s, from_m);

    while (stack_isEmpty(s) == FALSE && st == OK){

        from_m = stack_pop(s);
        
        music_plain_print_p2_e3(stdout, from_m);
        fprintf(stdout, "\n");

        if (music_cmp(from_m, to_m) == 0) {
            st = ERROR;
        } else {
            p_orig = music_getIndex(from_m);
            for (i = 0; i < radio_getNumberOfMusic(r); i++) {
                if (r->relations[p_orig][i] == TRUE) {
                    if (music_getState(r->songs[i]) == NOT_LISTENED) {
                        music_setState(r->songs[i], LISTENED);
                        stack_push(s, r->songs[i]);
                    }
                }
            }
        }
    }
    
    stack_free(s);
    return OK;
}

Status radio_breadthSearch (Radio *r, long from_id, long to_id){

    if (!r || r->num_music < 0 || r->num_relations < 0 || from_id < 0 || to_id < 0) return ERROR;

    Music *from_m = NULL;
    Music *to_m = NULL;
    int i, p_orig = -1;
    Status st = OK;
    Queue *q = NULL;

    for (i = 0; i < radio_getNumberOfMusic(r); i++) {
        if (music_getId(r->songs[i]) == from_id) from_m = r->songs[i];
        if (music_getId(r->songs[i]) == to_id) to_m = r->songs[i];
    }

    if (!from_m || !to_m) return ERROR;

    for (i = 0; i < radio_getNumberOfMusic(r); i++) {
        music_setState(r->songs[i], NOT_LISTENED);
    }

    q = queue_new();
    if (!q) return ERROR;

    music_setState(from_m, LISTENED);
    queue_push(q, from_m);

    while (queue_is_empty(q) == FALSE && st == OK){

        from_m = queue_pop(q);
        
        music_plain_print_p2_e3(stdout, from_m);
        fprintf(stdout, "\n");

        if (music_cmp(from_m, to_m) == 0) {
            st = ERROR;
        } else {
            p_orig = music_getIndex(from_m);
            for (i = 0; i < radio_getNumberOfMusic(r); i++) {
                if (r->relations[p_orig][i] == TRUE) {
                    if (music_getState(r->songs[i]) == NOT_LISTENED) {
                        music_setState(r->songs[i], LISTENED);
                        queue_push(q, r->songs[i]);
                    }
                }
            }
        }
    }
    
    queue_free(q);
    return OK;
}