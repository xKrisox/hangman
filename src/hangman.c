#include "hangman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

bool load_words(const char *path, char words[][MAX_WORD_LEN], int *count)
{
    FILE *f = fopen(path, "r");
    if (!f) return false;
    char buf[256];
    int i = 0;
    while (i < MAX_WORDS && fgets(buf, sizeof(buf), f))
    {
        buf[strcspn(buf, "\r\n")] = 0;
        if (buf[0] == '\0') continue;
        if (strlen(buf) >= MAX_WORD_LEN) continue;
        for (size_t j = 0; buf[j]; j++)
            buf[j] = (char)tolower((unsigned char)buf[j]);
        strcpy(words[i++], buf);
    }
    fclose(f);
    *count = i;
    return i > 0;
}

void pick_random_word(char words[][MAX_WORD_LEN], int count, char out[MAX_WORD_LEN])
{
    int idx = rand() % count;
    strcpy(out, words[idx]);
}

void init_game(Game *g, const char *word)
{
    memset(g, 0, sizeof(*g));
    g->max_guesses = MAX_GUESSES;
    strncpy(g->secret, word, MAX_WORD_LEN - 1);
    size_t len = strlen(word);
    for (size_t i = 0; i < n; ++i)
        g->progress[i] = (word[i] == '-' || word[i] == ' ') ? word[i] : '_';
    g->progress[n] = '\0';
}

static int already_guessed_index(const Game *g, char ch)
{
    for (int i = 0; g->guessed[i]; ++i)
        if (g->guessed[i] == ch)
            return i;
    return -1;
}

bool apply_guess(Game *g, char ch, bool *was_new)
{
    ch = (char)tolower((unsigned char)ch);
    *was_new = false;

    if (!isalpha((unsigned char)ch)) return false;
    if (already_guessed_index(g, ch) >= 0) return true;

    size_t len = strlen(g->guessed);
    g->guessed[len] = ch;
    g->guessed[len + 1] = '\0';
    *was_new = true;

    int hits = 0;
    for (size_t i = 0; g->secret[i]; ++i)
    {
        if (g->secret[i] == ch)
        {
            g->progress[i] = ch;
            ++hits;
        }
    }
    if (hits == 0) g->wrong_guesses++;
    return true;
}

bool is_won(const Game *g)
{
    return strcmp(g->secret, g->progress) == 0;
}

bool is_lost(const Game *g)
{
    return g->wrong_guesses >= g->max_guesses;
}

void draw_hangman(int w)
{
    const char *stages[] = {
        " \n \n \n \n=====",
        " +---+\n |   |\n     |\n     |\n=====",
        " +---+\n |   |\n O   |\n     |\n=====",
        " +---+\n |   |\n O   |\n |   |\n=====",
        " +---+\n |   |\n O   |\n/|   |\n=====",
        " +---+\n |   |\n O   |\n/|\\  |\n=====",
        " +---+\n |   |\n O   |\n/|\\  |\n/    |\n=====",
        " +---+\n |   |\n O   |\n/|\\  |\n/ \\  |\n====="
    };
    if (w < 0) w = 0;
    if (w > 7) w = 7;
    printf("%s\n", stages[w]);
}

void save_score(const char *path, const Game *g, bool won)
{
    FILE *f = fopen(path, "a");
    if (!f) return;
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm);
    fprintf(f, "%s;result=%s;word=%s;wrong=%d\n",
            buf, won ? "win" : "lose", g->secret, g->wrong_guesses);
    fclose(f);
}