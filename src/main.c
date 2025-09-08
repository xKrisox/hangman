#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "hangman.h"

static void clear_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

static void print_state(const Game *g) {
    printf("\nWord: ");
    for (size_t i = 0; g->progress[i]; ++i) {
        printf("%c ", g->progress[i]);
    }
    printf("\nErrors: %d/%d\n", g->wrong_guesses, g->max_guesses);
    printf("Used letters: %s\n", g->guessed[0] ? g->guessed : "(none)");
    draw_hangman(g->wrong_guesses);
}

int main(void) {
    srand((unsigned)time(NULL));

    char words[MAX_WORDS][MAX_WORD_LEN];
    int count = 0;
    if (!load_words("words.txt", words, &count)) {
        fprintf(stderr, "Load error words.txt (file invalid).\n");
        return 1;
    }

    char again = 't';
    while (again == 't') {
        char secret[MAX_WORD_LEN];
        pick_random_word(words, count, secret);

        Game g;
        init_game(&g, secret);

        printf("=== HANGMAN ===\nGuess. You have %d chances\n", g.max_guesses);

        while (!is_won(&g) && !is_lost(&g)) {
            print_state(&g);
            printf("Input letter: ");
            int ch = getchar();
            if (ch == EOF) break;
            if (ch == '\n') continue;
            clear_input();

            bool was_new = false;
            if (!apply_guess(&g, (char)ch, &was_new)) {
                printf("Single letter [a-z].\n");
                continue;
            }
            if (!was_new) {
                printf("Letter already used.\n");
            }
        }

        bool won = is_won(&g);
        print_state(&g);
        if (won) {
            printf("\n✅ Win! Word: %s\n", g.secret);
        } else {
            printf("\n❌ Losse. Word: %s\n", g.secret);
        }
        save_score("scores.txt", &g, won);

        printf("\nTry again? (y/n): ");
        int ch = getchar();
        if (ch != EOF) again = (char)tolower((unsigned char)ch);
        clear_input();
    }

    printf("FINAL!\n");
    return 0;
}
