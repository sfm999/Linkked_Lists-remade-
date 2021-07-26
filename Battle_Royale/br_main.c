/*
    - Start by adding players to the game (create_node) DONE
    - Be able to print all players currently in the game (print_nodes) DONE
    - Be able to control the order of the list. E.g. insert at particular position.
    - Be able to find and remove players from the list if they're knocked out
      of the round. (free() each player we remove).

*/
#include "br_lib.h"

int main(int argc, char *argv[]) {
  Player head = NULL;
  head = insert_alpha(head, "Goku");
  head = insert_alpha(head, "Anakin");
  head = insert_alpha(head, "Obi-wan");
  head = insert_alpha(head, "Kvothe");
  head = insert_alpha(head, "Buu");
  head = insert_alpha(head, "Vegeta");
  head = insert_alpha(head, "Freezer");


  while(print_players(head) > 1) {
      head = remove_by_name(head);
      printf("--------------\n");
  }

  printf("is the winner!\n");

  free_players(head);

  return 0;
}
