/**
 * @file  stack.c
 * @author Santiago Pita
 * @date 26 February 2026
 * @version 1.0
 * @brief Stack functions to interact with the stack
 *
 * @details 
 * 
 * @see
 */
#include "music.h"
#include "stack.h"

struct _Stack{
    Music *songs[MAX_MSC];
    size_t s_size; /*Size of the stack*/
};

typedef int (*P_stack_ele_print)(FILE *, const void*);


Stack * stack_init ()
{
    Stack * stack = NULL;
    int i;
    stack->s_size = 0;

    stack = (Stack*)calloc(1, sizeof(Stack));
    if (!stack) {return NULL;}

    for (i = 0; i < MAX_MSC; i++)
    {
        stack->songs[i] = music_init();
        if (!stack->songs[i]) {return NULL;}
    }

    return stack;
}


void stack_free (Stack *s)
{
    int i;
    if (!s) {return;}

    for (i = 0; i < s->s_size; i++)
    {
        music_free(s->songs[i]);
    }
    return;
}


Status stack_push (Stack *s, const void *ele)
{
    if (!s || !ele) {return ERROR;} /*if stack is null or if element is null returns error*/
    if (stack_size(s) == MAX_MSC) {return ERROR;} /*if stack is full it cannot add more songs*/

    s->songs[s->s_size] = ele; /*inserts the element in the stack*/
    s->s_size++;
    return OK;
}


void * stack_pop (Stack *s)
{
    if (!s) {return;} 
    if (stack_isEmpty(s) == TRUE) {return NULL;}

    s->s_size--; /*decreases stack size*/
    return s->songs[s->s_size+1]; /*returns top element of the stack*/
}


void * stack_top (const Stack *s)
{
    if (!s) {return NULL;}
    if (stack_isEmpty(s) == TRUE) {return NULL;}

    return s->songs[s->s_size];
}


Bool stack_isEmpty (const Stack *s)
{
    if (!s) {return FALSE;}
    if (stack_size(s) == 0) {return TRUE;}
    return FALSE;
}


size_t stack_size (const Stack *s)
{
    if (!s) {return 0;}
    return s->s_size;
}


int stack_print(FILE* fp, const Stack *s,  P_stack_ele_print f)
{
    int ch_printed = 0;
    int temp;
    int i;

    if (!s) {return -1;}
    if (!fp) {return -1;}

    for (i = 0; i < s->s_size; i++)
    {
        temp = music_plain_print(fp, s->songs[i]);
        if (temp == -1) {return -1;}
        ch_printed+=temp;
    }
    return ch_printed;
}

