#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

typedef struct player *Player;

// Allocate memory for a player node
// Populate that node with new next
// Return a pointer to the allocated memory
Player create_player(char new_name[MAX_NAME_LENGTH], Player new_next);

// Loop through and display the linked list
// Displays one per line on terminal
int print_players(Player head);

// Insert a player node into a list after a given Player
Player insert_after(Player insert_pos, char new_name[MAX_NAME_LENGTH]);

// Insert into a list in alphabetical order.
// Returns the head of the list (even if it has changed)
Player insert_alpha(Player head, char new_name[MAX_NAME_LENGTH]);

// Find the player that matches the given name in the list starting at head.
// Remove and free the player, return the head (it may have changed).
Player remove_player(Player head, char rem_name[MAX_NAME_LENGTH]);

// Prompts the user for input of name to be knocked out
// Removes player from the list if they exist
// Returns the head
Player remove_by_name(Player head);

void free_players(Player head);
