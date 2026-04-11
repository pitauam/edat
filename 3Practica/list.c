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

/**
 * @brief Creates a new node
 *
 * @return Returns a new node
 */
Node *node_new ();

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


List *list_new(){
    List *pl = NULL;

    if (!(pl = calloc(1, sizeof(List)))) {
        return NULL; 
    }

    pl->first = NULL;
    pl->last = NULL;
    pl->size = 0;

    return pl;
}


Bool list_isEmpty(const List *pl){
    if (!pl) return TRUE;

    if (pl->first == NULL)
    {
        return TRUE;
    }

    return FALSE;
}


Status list_pushFront(List *pl, const void *e) {
    Node *pn = NULL;

    if (pl == NULL || e == NULL) {
        return ERROR;
    }

    pn = node_new();
    if (!pn) {
        return ERROR;
    }

    pn->info = (void *)e;
    pn->next = pl->first;
    pl->first = pn;

    if (!pl->last) 
    {
        pl->last = pn;
    }

    pl->size++;
    return OK;
}


Status list_pushBack(List *pl, const void *e) {
    Node *pn = NULL;

    if (!pl || !e) return ERROR;

    pn = node_new();
    if (!pn) {
        return ERROR;
    }

    pn->info = (void *)e;
    pn->next = NULL;

    if (list_isEmpty(pl) == TRUE) {
        pl->first = pn;
        pl->last = pn;
    } else {
        pl->last->next = pn;
        pl->last = pn;
    }

    pl->size++;
    return OK;
}


void *list_popFront(List *pl) {
    void *e = NULL;
    Node *node_to_remove = NULL;

    if (!pl || list_isEmpty(pl) == TRUE) {
        return NULL;
    }

    node_to_remove = pl->first;
    e = node_to_remove->info;
    
    pl->first = node_to_remove->next;
    
    if (pl->first == NULL) {
        pl->last = NULL;
    }

    free(node_to_remove);
    pl->size--;

    return e;
}


void *list_popBack(List *pl) {
    void *e = NULL;
    Node *node_to_remove = NULL;

    if (pl == NULL || list_isEmpty(pl) == TRUE) {
        return NULL;
    }

    /*if there is only one element*/
    if (pl->first->next == NULL) 
    {
        e = pl->first->info;
        free((void *)pl->first);
        pl->first = NULL;
        pl->last = NULL;
        pl->size--;
        return e;
    }

    node_to_remove = pl->first;
    while (node_to_remove->next->next != NULL) 
    {
        node_to_remove = node_to_remove->next;
    }

    e = node_to_remove->next->info;
    free((void *)node_to_remove->next);
    node_to_remove->next = NULL;
    
    pl->last = node_to_remove;
    pl->size--;

    return e;
}


void *list_getFront(List *pl) {
    if (!pl || list_isEmpty(pl) == TRUE) {
        return NULL;
    }

    return pl->first->info; 
}


void *list_getBack(List *pl){
    if (!pl || list_isEmpty(pl) == TRUE) {
        return NULL;
    }
    
    return pl->last->info;
}


void list_free(List *pl) {
    if (pl == NULL) {
        return;
    }

    while (list_isEmpty(pl) == FALSE) {
        list_popFront(pl);
    }

    free((void *)pl);
    return;
}


int list_size(const List *pl){
    if (!pl) {
        return -1;
    }

    return pl->size;
}


int list_print(FILE *fp, const List *pl, p_list_ele_print f){
    Node *pn = NULL; // Puntero auxiliar para recorrer los nodos
    int total = 0;   // Para ir sumando los caracteres que se imprimen
    int printed = 0; // Para guardar lo que devuelve 'f' en cada paso

    if (!pl || !fp || !f) {
        return -1;
    }

    pn = pl->first;

    while (pn != NULL)
    {
        printed = f(fp, (void*)pn->info);
        if (printed == -1)
        {
            return -1;
        }
        
        total+=printed;

        pn = pn->next;
    }

    return total;
}