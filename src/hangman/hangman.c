#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "array.h"

char *select_random_word(void);
void print_word(void);
bool letter_is_guessed(char letter);
bool check_guess(char letter);
void init_guessed_letters(void);

static char *filename = "words.txt";
static char *word_to_guess = NULL;
static array *guessed_letters = NULL;

int main(void)
{
    int max_attempts = 10;
    int attempts = 0;
    bool user_won = false;
    bool print_msg = true;
    word_to_guess = select_random_word();
    int letters_to_guess = (int) strlen(word_to_guess);
    init_guessed_letters();
    print_word();

    while (attempts <= max_attempts) {
        if (print_msg) {
            printf("Pick a guess: ");
        }
        char guess = getchar();
        if (guess != EOF) {
            if (guess == '\n') {
                print_msg = false;
                continue;
            } else {
                print_msg = true;
            }
            attempts++;
            if (check_guess(guess)) {
                print_word();
                if (letters_to_guess == (int)guessed_letters->len) {
                    puts("You won!");
                    user_won = true;
                    break;
                }
            } else {
                puts("Wrong guess");
                print_word();
            }
        }
    }
    if (!user_won) {
        puts("You lost sucka!!!");
    }

    return 0;
}

bool check_guess(char guess)
{
    bool correct = false;
    char *word_p = word_to_guess;
    while (*word_p != '\0') {
        if (guess == *word_p) {
            correct = true;
            char *letter_p = malloc(sizeof(char));
            *letter_p = guess;
            array_push(guessed_letters, letter_p);
        }
        word_p++;
    }

    return correct;
}

void init_guessed_letters(void)
{
    guessed_letters = array_new(15, sizeof(char*));
    if (!guessed_letters) {
        puts("Could not initialize the array of guessed letters");
        exit(EXIT_FAILURE);
    }
}

void print_word(void)
{
    char *word_p = word_to_guess;
    while (*word_p != '\0') {
        if (letter_is_guessed(*word_p)) {
            printf("%c", *word_p);
        } else {
            printf("_");
        }
        word_p++;
    }
    printf("\n");
}

bool letter_is_guessed(char letter)
{
    bool found = false;
    ARRAY_FOREACH(guessed_letters) {
        char *cur_letter = (char*)array_get(guessed_letters, i);
        if (cur_letter && *cur_letter == letter) {
            found = true;
            break;
        }
    }
    return found;
}

char *select_random_word(void)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        puts("The file could not be found!");
        exit(EXIT_FAILURE);
    }

    int word_len = 30;
    char word[word_len];
    array* words = array_new(100, sizeof(char*));
    if (!words) {
        puts("Not enough space for the words array!");
        exit(EXIT_FAILURE);
    }

    while (fgets(word, word_len, fp) != NULL) {
        char *cur_word = strdup(word);
        array_push(words, cur_word);
    }
    srand(time(NULL));
    int rand_i = rand() % words->len;
    char* cur_word = (char*)array_get(words, rand_i);
    if (!cur_word) {
        puts("A random word was not selected succesfully!");
        exit(EXIT_FAILURE);
    }
    char *word_to_guess = strdup(cur_word);
    if (!word_to_guess) {
        puts("The word to guess was not duplicated succesfully!");
        exit(EXIT_FAILURE);
    }
    char *word_p = word_to_guess;
    while (*word_p != '\0') {
        if (*word_p == '\n') {
            *word_p = '\0';
            break;
        }
        word_p++;
    }
    fclose(fp);
    array_free(words, NULL);
    return word_to_guess;
}
