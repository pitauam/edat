#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "radio.h"
#include "queue.h"
#include "music.h"


int main(int argc, char **argv)
{
    Radio *r = NULL;
    FILE *pf = NULL;
    long from_id, to_id;

    int i;

    if (argc < 4) {
        printf("You need more than %i arguments, insert text file and two song ids.\n", argc);
        printf("You entered: \n");
        for (i = 0; i < argc; i++)
        {
            printf("%s\n", argv[i]);
        }
        return -1;
    }

    if (!(r = radio_init())){
        printf("Error while creating radio\n");
        return -1;
    }

    if(!(pf = fopen(argv[1], "r"))) {
        printf("Error while opening file\n");
        radio_free(r);
        return -1;
    }

    if ((radio_readFromFile(pf, r)) == ERROR) {
        printf("Error while reading from file\n");
        radio_free(r);
        fclose(pf);

        return -1;
    }

    /*atol is used to convert a string to a long*/
    from_id = atol(argv[2]);
    to_id = atol(argv[3]);

    printf("Radio:\n");
    radio_print(stdout, r);

    printf("\n--------DFS--------\n");
    printf("From music id: %li", from_id);
    printf("\nTo music id: %li", to_id);
    printf("\nOutput:\n");

    if (radio_depthSearch(r, from_id, to_id) == ERROR){
        printf("Error while executing DFS\n");
        radio_free(r);
        fclose(pf);
        return -1;
    }

    printf("\n--------BFS--------\n");
    printf("From music id: %li", from_id);
    printf("\nTo music id: %li", to_id);
    printf("\nOutput:\n");

    if (radio_breadthSearch(r, from_id, to_id) == ERROR){
        printf("Error while executing BFS\n");
        radio_free(r);
        fclose(pf);
        return -1;
    }

    fclose(pf);
    radio_free(r);

    return 0;
}
