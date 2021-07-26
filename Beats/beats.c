// Assignment 2 21T1 COMP1511: Beats by CSE
// beats.c
//
// This program was written by YOUR-NAME-HERE (z5555555)
// on INSERT-DATE-HERE
//
// Version 1.0.0: Assignment released.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Add any extra #includes your code needs here.

#include "beats.h"

// Add your own #defines here.

//////////////////////////////////////////////////////////////////////

typedef struct note *Note;

struct note {
    int octave;
    int key;
    Note next;
};

struct beat {
    Note notes;
    Beat next;
};

struct track {
    // TODO: You will have to add extra fields here in Stage 2.
    Beat head;
    Beat current;
};


// Add any other structs you define here.
//////////////////////////////////////////////////////////////////////

// Add prototypes for any extra functions you create here.

Note create_note(Note new_next, int new_octave, int new_key);
int compare_notes(Note curr, int octave, int key);
Note insert_after(Note insert_pos, int octave, int key);;
void print_note(Note note);


// Return a malloced Beat with fields initialized.
Beat create_beat(void) {
    Beat new_beat = malloc(sizeof (struct beat));
    assert(new_beat != NULL);

    new_beat->next = NULL;
    new_beat->notes = NULL;

    // You do not need to change this function, unless you change
    // the implementation of struct beat.

    return new_beat;
}

// You need to implement the following functions.
// You can find descriptions of what each function should do in beats.h

//////////////////////////////////////////////////////////////////////
//                        Stage 1 Functions                         //
//////////////////////////////////////////////////////////////////////

// Add a note to the end of a beat.
int add_note_to_beat(Beat beat, int octave, int key) {
    // Octave check, non-negative integer less than 10
    if(octave < 0 || octave > 9)
        return INVALID_OCTAVE;
    // Key check, non-negative integer less than 12
    if(key < 0 || key > 11)
        return INVALID_KEY;

    if(beat->notes == NULL) {
        beat->notes = insert_after(beat->notes, octave, key);
    } else {
        Note curr = beat->notes;
        Note prev = NULL;

        // Check if note exists already
        while(curr != NULL) {
            if(curr->octave == octave && curr->key == key) {
                return NOT_HIGHEST_NOTE;
            }
            curr =  curr->next;
        }

        // reset curr to head and find node to insert after
        curr = beat->notes;
        while(curr != NULL && compare_notes(curr, octave, key) < 0){
            prev = curr;
            curr = curr->next;
        }

        Note insert_result = insert_after(prev, octave, key);

        if(prev == NULL) {
            insert_result->next = beat->notes;
            beat->notes = insert_result;
        }
    }
    return VALID_NOTE;
}

// Returns a new note pointer but as our typedef
Note create_note(Note new_next, int new_octave, int new_key) {
    Note n = malloc(sizeof (struct note));
    n->octave = new_octave;
    n->key = new_key;
    n->next = new_next;
    return n;
}

// Note curr is the note in the list being examined
// octave & key are what makes up the prospective note
// Returns < 0 if given octave is greater than curr's
// Returns < 0 if given octave equals curr's but given key is
// greater than curr's
// Returns 0 if previous checks passed
int compare_notes(Note curr, int octave, int key) {

    if(octave > curr->octave) {
        return NOT_HIGHEST_NOTE;
    }

    if(octave == curr->octave) {
        if(key > curr->key) {
            return NOT_HIGHEST_NOTE;
        }
    }

    return VALID_NOTE;
}

// Inserts a node into a linked list after the node insert_pos
// Assumes the list is in working order, meaning the new octave and key
// are at least 1 of two things:
//  1) octave equals insert octave but key is higher
//  2) octave is greater than the insert_pos octave and if there is a next pointer
//     the note has either same octave and higher note OR higher octave
// Returns the insert pos or pointer to new list if given list is empty
Note insert_after(Note insert_pos, int octave, int key) {
    // Handle empty list situation
    if(insert_pos == NULL) {
        // new_note is now the head and our temporarily NULL insert_pos
        // is used to set the next pointer of this new note as it's the
        // only element in the list at the moment
        Note new_note = create_note(insert_pos, octave, key);

        // Set insert_pos as the new_note
        insert_pos = new_note;
    } else {
        // Insert into the list after the given note
        // Insert_post->next is either NULL or another note. So it will
        // either insert the note at the end of the list if insert_pos
        // was the end of the list OR it will insert the note as the next of
        // insert_pos after making the new_note point to the insert_pos'
        // next note.
        Note new_note = create_note(insert_pos->next, octave, key);
        // Actually insert the new note as the next note that
        // insert_pos points to
        insert_pos->next = new_note;

    }
    return insert_pos;
}

void print_note(Note note) {
    printf("Octave: %d\n", note->octave);
    printf("Key: %d\n", note->key);
}

// Print the contents of a beat.
void print_beat(Beat beat) {
    Note curr = beat->notes;
    while(curr != NULL) {
        if(curr->next == NULL) {
            if(curr->key > 9) {
                printf(" %d %d", curr->octave, curr->key);
            } else {
                printf(" %d 0%d", curr->octave, curr->key);
            }

        } else {
            if(curr->key > 9) {
                printf(" %d %d |", curr->octave, curr->key);
            } else {
                printf(" %d 0%d |", curr->octave, curr->key);
            }

        }
        curr = curr->next;
    }
    printf("\n");
    return;
}

// Count the number of notes in a beat that are in a given octave.
// Returns 0
int count_notes_in_octave(Beat beat, int octave) {
    if(octave < 0 || octave > 9) {
        return 0;
    } else{
        Note curr = beat->notes;
        int count = 0;
        while(curr != NULL) {
            if(curr->octave == octave) {
                count++;
            }
            curr = curr->next;
        }
        return count;
    }
}

//////////////////////////////////////////////////////////////////////
//                        Stage 2 Functions                         //
//////////////////////////////////////////////////////////////////////

// Return a malloced track with fields initialized.
Track create_track(void) {
    Track new_track = malloc(sizeof (struct track));
    assert(new_track != NULL);

    new_track->head = NULL;
    new_track->current = NULL;

    return new_track;
}

// Add a beat after the current beat in a track.
void add_beat_to_track(Track track, Beat beat) {

    if(track->current != NULL) {
        beat->next = track->current->next;
        track->current->next = beat;
    }else{
        beat->next = track->head;
        track->head = beat;
    }
}

// Set a track's current beat to the next beat.
int select_next_beat(Track track) {

    if(track->current == NULL && track->head != NULL) {
        track->current = track->head;
        return TRACK_PLAYING;
    }

    if(track->current->next != NULL) {
        track->current = track->current->next;
        return TRACK_PLAYING;
    }

    track->current = NULL;
    return TRACK_STOPPED;
}

// Print the contents of a track.
void print_track(Track track) {
    Beat curr = track->head;
    int beat_count = 1;
    while(curr != NULL) {
        if(curr == track->current) {
            printf(">[%d] ", beat_count++);
            print_beat(curr);
            curr = curr->next;
        }else{
            printf(" [%d] ", beat_count++);
            print_beat(curr);
            curr = curr->next;
        }
    }
}

// Count beats after the current beat in a track.
int count_beats_left_in_track(Track track) {
    int count = 0;
    if(track->current != NULL) {
        // Find the current beat in the track's beat
        // then count from there
        // Start at head
        Beat curr = track->head;
        // Iterate till we find the current selected
        while(curr != track->current) {
            curr = curr->next;
        }
        // Now count till we hit the end of the track
        // without counting the current
        curr = curr->next;
        while(curr != NULL) {
            curr = curr->next;
            count++;
        }
    } else {
        // There was no current selected, now check if track list is not empty
        Beat curr = track->head;
        while(curr != NULL) {
            curr = curr->next;
            count++;
        }
    }
    return count;
}

//////////////////////////////////////////////////////////////////////
//                        Stage 3 Functions                         //
//////////////////////////////////////////////////////////////////////

// Free the memory of a beat, and any memory it points to.
void free_beat(Beat beat) {
    Note next;
    while(beat->notes != NULL) {
        next = beat->notes->next;
        free(beat->notes);
        beat->notes = next;
    }
    free(beat);
    return;
}

// Free the memory of a track, and any memory it points to.
void free_track(Track track) {
    if(track == NULL) {
        return;
    }
    Beat next;
    while(track->head != NULL) {
        next = track->head->next;
        free_beat(track->head);
        track->head = next;
    }
    free(track);
    return;
}

// Remove the currently selected beat from a track.
int remove_selected_beat(Track track) {
    printf("remove_selected_beat not implemented yet.");
    return TRACK_STOPPED;
}
