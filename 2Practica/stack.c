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
    void *elements[MAX_MSC];
    size_t s_size; /*Size of the stack*/
};

typedef int (*P_stack_ele_print)(FILE *, const void*);


Stack * stack_init ()
{
    Stack * stack = NULL;

    stack = (Stack*)calloc(1, sizeof(Stack));
    if (!stack) {return NULL;}

    stack->s_size = 0;

    return stack;
}


void stack_free (Stack *s)
{
    if (!s) {return;}

    free(s);

    return;
}


Status stack_push (Stack *s, const void *ele)
{
    if (!s || !ele) {return ERROR;} /*if stack is null or if element is null returns error*/
    if (stack_size(s) == MAX_MSC) {return ERROR;} /*if stack is full it cannot add more songs*/

    s->elements[s->s_size] = (Music*)ele; /*inserts the element in the stack*/
    s->s_size++;
    return OK;
}


void * stack_pop (Stack *s)
{
    if (!s) {return NULL;} 
    if (stack_isEmpty(s) == TRUE) {return NULL;}

    s->s_size--; /*decreases stack size*/
    return s->elements[s->s_size+1]; /*returns top element of the stack*/
}


void * stack_top (const Stack *s)
{
    if (!s) {return NULL;}
    if (stack_isEmpty(s) == TRUE) {return NULL;}

    return s->elements[s->s_size];
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
        temp = music_plain_print(fp, s->elements[i]);
        printf("\n");
        if (temp == -1) {return -1;}
        ch_printed+=temp;
    }
    return ch_printed;
}


Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout)
{
    void *e;        /*pointer to an element in the stack*/
    Stack *ps;      /*pointer to a stack*/

    if (!sin1 || !sin2 || !sout || sin1->s_size < 1 || sin2->s_size < 1 || !sin1->elements[0] || !sin2->elements[0]) {return ERROR;}

    /*if the stack is not empty then the function won't work because it will concatenate instead of merging*/
    if (stack_size(sout) != 0) {return ERROR;}

    while (stack_isEmpty(sin1) == FALSE && stack_isEmpty(sin2) == FALSE)
    {

        if (music_getDuration(stack_top(sin1)) > music_getDuration(stack_top(sin2)))
        {
            e = stack_pop(sin1);
        }
        else 
        {
            e = stack_pop(sin2);
        }
        stack_push(sout, e);
    }
    
    if (stack_isEmpty(sin1) == TRUE)
    {
        ps = sin2;
    }
    else
    {
        ps = sin1;
    }

    while (stack_isEmpty(ps) == FALSE)
    {
        e = stack_pop(ps);
        stack_push(sout, e);
    }

    return OK;
}

