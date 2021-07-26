#include "br_lib.h"


struct player {
  struct player *next;
  char name[MAX_NAME_LENGTH];
};

Player create_player(char new_name[MAX_NAME_LENGTH], Player new_next) {
  Player p = malloc(sizeof (struct player));
  strcpy(p->name, new_name);
  p->next = new_next;

  return p;
}

int print_players(Player head) {
  Player current = head;
  int player_count = 0;
  while(current != NULL) {
    player_count++;
    printf("%s\n", current->name);
    current = current->next;
  }
  return player_count;
}

// Inserts a node into a linked list after the node insert_pos
// Assumes that this is a working linked list
// Returns the insert pos or pointer to new list if it had been given an empty list
Player insert_after(Player insert_pos, char new_name[MAX_NAME_LENGTH]) {
  if(insert_pos == NULL) {
    // Inserting into an empty list
    Player new_player = create_player(new_name, NULL);
    insert_pos = new_player;
  }else{
    // Inserting in to a list that already exists
    // Create the new player using the next of insert_pos
    Player new_player = create_player(new_name, insert_pos->next);

    // Change the insert_pos' next to now aim at the new player
    insert_pos->next = new_player;
  }

  return insert_pos;
}

// Inserts into a list (head), alphabetically
// Assumes the list is already in alphabetical order
// Returns the head of the list (it may have changed)
Player insert_alpha(Player head, char new_name[MAX_NAME_LENGTH]) {
  // Loop through and find the insertion point
  Player curr = head;
  Player prev = NULL;
  // Go past any names that are earlier than us, alphabetically
  while(curr != NULL && strcmp(curr->name, new_name) < 0) {
    prev = curr;
    curr = curr->next;
  } // curr is now the 1st player in the list with a name "higher" the new_name
    // prev is now the last player in the list w/ a name "lower" than new_name

  Player insert_result = insert_after(prev, new_name);

  // Inserting into an empty list
  if(prev == NULL) {
    insert_result->next = head;
    head = insert_result;
  }

  return head;
}

// Loop through list looking for a match with between player's name and
// rem_name. Remove and free that node (if it exists).
// Return the head of the list (special case if we removed the old head).
Player remove_player(Player head, char rem_name[MAX_NAME_LENGTH]) {
    Player curr = head;
    Player prev = NULL;
    while(curr != NULL && strcmp(rem_name, curr->name) != 0) {
        prev = curr;
        curr = curr->next;
    }
    // curr is now pointing at either a player that matches rem name OR
    // it may come back as NULL if list doesn't contain name
    if(curr != NULL) {
        if(prev == NULL) { // curr is head of the list
            head = curr->next; // make head curr's next thereby bypassing curr
        }else{
            prev->next = curr->next; // curr is not the head
        }
        free(curr);
    }
    return head;
}

// Asks the user to enter the name of the player to remove
// Remove the player and return the head (the head may have changed)
Player remove_by_name(Player head) {
    printf("Who's getting knocked out?\n");
    char input[MAX_NAME_LENGTH];
    fgets(input, MAX_NAME_LENGTH, stdin);
    if(input[strlen(input)-1] == '\n') {
        input[strlen(input)-1] = '\0';
    }
    head = remove_player(head, input);
    return head;
}


void free_players(Player head) {
  Player next;
  while(head != NULL) {
    next = head->next;
    free(head);
    head = next;
  }
}
