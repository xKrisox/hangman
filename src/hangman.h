#ifndef HANGMAN_H
#define HANGMAN_H

#include <stdbool.h>

#define MAX_WORD_LEN 64
#define MAX_WORDS 2048
#define MAX_GUESSES 8

typedef struct {
    char secret[MAX_WORD_LEN];  // The word to guess
    char progress[MAX_WORD_LEN];    // Current progress (e.g., "_ a _ _ m a n")
    char guessed[128];       // Letters already guessed
    int wrong_guesses;
    int max_guesses;
} Game;

// Function declarations
bool load_words(const char *path, char words[][MAX_WORD_LEN], int *count);
void pick_random_word(char words[][MAX_WORD_LEN], int count, char out[MAX_WORD_LEN]);
void init_game(Game *g, const char *word);
bool apply_guess(Game *g, char ch, bool *was_new);
bool is_won(const Game *g);
bool is_lost(const Game *g);
void draw_hangman(int wrong);
void save_score(const char *path, const Game *g, bool won);

#endif