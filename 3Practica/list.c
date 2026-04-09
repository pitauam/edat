#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct _Node
{
    void *info;         /*!< Info of the list*/
    struct _Node *next; /*!< Next node of the list*/
};

typedef struct _Node Node;

struct _List
{
    Node *first;        /*!< First node of the list*/
    Node *last;         /*!< Last node of the list*/
    int size;           /*!< size of the list */
};


List *list_new(){
    List *pl = NULL;

    if (!(pl = calloc(1, sizeof(List)))) {
        return NULL; 
    }

    /*
    if (!(pl->first = calloc(1, sizeof(Node)))) {
        return NULL; 
    }

    if (!(pl->last = calloc(1, sizeof(Node)))) {
        return NULL; 
    }
    */

    pl->first = NULL;
    pl->last = NULL;
    pl->size = 0;

    return pl;
}


Bool list_isEmpty(const List *pl){
    if (!pl) return FALSE;

    if (pl->first == NULL)
    {
        return TRUE;
    }

    return FALSE;
}


Status list_pushFront(List *pl, const void *e){
Node *pn = NULL;
if ((pl == NULL) || (e == NULL)) {
return ERROR;
}
pn = node_new ();
if (pn == NULL) {
return ERROR;
}
pn ->info = (void *)e;
pn ->next = pl ->first;
pl ->first = pn;
return OK;
}


Status list_pushBack(List *pl, const void *e){
    Node *pn;
    Node *pn_last;

    if (!pl || !e) return ERROR;

    pn = node_new();
    if (!pn) return ERROR;

    pn->info = (void*)e;

    if (list_isEmpty(pl) == TRUE)
    {
        pl->first = pn;
        pl->size++;
        return OK;
    }

    pn_last = pl->first;
    while (pn_last->next != NULL)
    {   
        pn_last = pn_last ->next;
    }

    pn_last->next = pn;
    pl->size++;

    return OK;
}


void *list_popFront(List *pl){
    void *e = NULL;
    Node *pn = NULL;
    if ((!pl) || (list_is_empty(pl) == TRUE)) 
    {
        return NULL;
    }
    
    pn = pl ->first;
    e = pn ->info;
    pl ->first = pn ->next;
    free((void *)pn);
    return e;
}


void *list_popBack(List *pl){
void *e = NULL;
Node *pn = NULL;
if ((pl == NULL) || (list_is_empty(pl) == TRUE)) {
return NULL;
}
if (pl ->first ->next == NULL) {
e = pl ->first ->info;
free((void *)pl ->first);
pl ->first = NULL;
return e;
}
pn = pl ->first;
while (pn ->next ->next != NULL) {
pn = pn ->next;
}
e = pn ->next ->info;
free((void *)pn ->next);
pn ->next = NULL;
return e;
}


void *list_getFront(List *pl){
    if (!pl) return;
    return pl->first;
}
void *list_getBack(List *pl){
    if (!pl) return;
    return pl->first;
}


void list_free(List *pl){
if (pl == NULL) {
return;
}
while (list_is_empty(pl) == FALSE) {
list_pop_front(pl);
}
free((void *)pl);
}


int list_size(const List *pl){
    if (!pl) return -1;

    return pl->size;
}


int list_print(FILE *fp, const List *pl, p_list_ele_print f){

    


}


Node *node_new () {
    Node *pn = NULL;
    pn = (Node *) malloc(sizeof(Node));
    if (pn == NULL) {
        return NULL;
    }
    pn->info = NULL;
    pn->next = NULL;
    return pn;
}