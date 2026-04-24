#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bstree.h"
#include "music.h"
#include "radio.h"

int main(int argc, char **argv) {
  BSTree *tree = NULL;
  Radio *r = NULL;
  Music *m = NULL;
  Music *to_remove = NULL;
  long id_to_remove;
  FILE *f = NULL;
  int i, n_songs;

  if (argc < 3) {
      fprintf(stderr, "Uso: %s <fichero_musica> <id_a_eliminar>\n", argv[0]);
      return EXIT_FAILURE;
  }

  id_to_remove = atol(argv[2]);

  
  r = radio_init();
  f = fopen(argv[1], "r");
  if (!f || !r) {
      fprintf(stderr, "Error al abrir el fichero o inicializar radio.\n");
      return EXIT_FAILURE;
  }
  radio_readFromFile(f, r);
  fclose(f);

  tree = tree_init(music_plain_print, music_cmp_id);
  if (!tree) {
    radio_free(r);
    return EXIT_FAILURE;
  }

    
  n_songs = radio_getnumber(r);
  for (i = 0; i < n_songs; i++) {
      m = radio_getMusic(r, i);
      tree_insert(tree, m);
  }

  printf("Número de nodos inicial: %ld\n", tree_size(tree));
  printf("Recorrido InOrder inicial:\n");
  tree_inOrder(stdout, tree);

  printf("\nEliminando canción con ID: %ld...\n", id_to_remove);
    
  to_remove = music_init();
  music_setId(to_remove, id_to_remove);
    
  if (tree_remove(tree, to_remove) == OK) {
    printf("Canción eliminada correctamente.\n");
  } else {
    printf("Error: No se encontró la canción con ID %ld.\n", id_to_remove);
  }

  printf("\nNúmero de nodos final: %ld\n", tree_size(tree));
  printf("Recorrido InOrder final:\n");
  tree_inOrder(stdout, tree);

  music_free(to_remove);
  tree_destroy(tree);
  radio_free(r);

    return 0;
}