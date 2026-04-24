#include <stdio.h>
#include <stdlib.h>
#include "radio.h"
#include "bstree.h"
#include "music.h"
#include "list.h"

int main(int argc, char **argv)
{
  Radio *r = NULL;
  FILE *pf = NULL;
  BSTree *tree = NULL;
  List *list = NULL;
  Music *min_music = NULL;
  Music *max_music = NULL;
  Music *m = NULL;
  long min_id, max_id;
  int i, n_songs;

  if (argc < 4)
  {
    printf("You need more than %i arguments, insert text file and the min/max ids.\n", argc);
    return -1;
  }

  min_id = atol(argv[2]);
  max_id = atol(argv[3]);

  if (!(r = radio_init()))
  {
    printf("Error while creating radio\n");
    return -1;
  }

  if (!(pf = fopen(argv[1], "r")))
  {
    printf("Error while opening file\n");
    radio_free(r);
    return -1;
  }

  if (radio_readFromFile(pf, r) == ERROR)
  {
    printf("Error while reading from file\n");
    radio_free(r);
    fclose(pf);

    return -1;
  }

  if (!(tree = tree_init(music_plain_print, music_cmp_id)))
  {
    printf("Error while creating tree\n");
    radio_free(r);
    fclose(pf);

    return -1;
  }

  n_songs = radio_getnumber(r);
  for (i = 0; i < n_songs; i++)
  {
    m = radio_getMusic(r, i);
    if (m)
    {
      tree_insert(tree, m);
    }
  }

  if (!(min_music = music_init()))
  {
    printf("Error while creating min music\n");
    tree_destroy(tree);
    radio_free(r);
    fclose(pf);

    return -1;
  }

  if (music_setId(min_music, min_id) == ERROR)
  {
    printf("Error while setting min id\n");
    music_free(min_music);
    tree_destroy(tree);
    radio_free(r);
    fclose(pf);

    return -1;
  }

  if (!(max_music = music_init()))
  {
    printf("Error while creating max music\n");
    music_free(min_music);
    tree_destroy(tree);
    radio_free(r);
    fclose(pf);

    return -1;
  }

  if (music_setId(max_music, max_id) == ERROR)
  {
    printf("Error while setting max id\n");
    music_free(min_music);
    music_free(max_music);
    tree_destroy(tree);
    radio_free(r);
    fclose(pf);

    return -1;
  }

  list = tree_rangeSearch(tree, min_music, max_music);

  printf("Lista de canciones desde id %ld hasta id %ld\n", min_id, max_id);
  if (list)
  {
    list_print(stdout, list, (p_list_ele_print)music_plain_print_p2_e3);
    list_free(list);
  }

  fclose(pf);
  music_free(min_music);
  music_free(max_music);
  tree_destroy(tree);
  radio_free(r);

  return 0;
}

/*
 * P2 ¿qué características observas en la lista resultante?, ¿a qué se debe?
 *
 * RESPUESTA:
 * 
 * La lista resultante está automáticamente ordenada de menor a mayor (ID ascendente).
 * Esto se debe a que la función recursiva _tree_rangeSearch_rec realiza el 
 * equivalente a un recorrido InOrder (rama izquierda, luego nodo actual, luego 
 * rama derecha) pero con "poda" (saltándose ramas fuera de rango). Dado que en 
 * un Árbol Binario de Búsqueda los elementos menores siempre están a la izquierda 
 * y los mayores a la derecha, al insertar las canciones en la lista usando este 
 * recorrido, inevitablemente se guardan ya ordenadas.
 */
