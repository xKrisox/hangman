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