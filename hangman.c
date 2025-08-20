#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>
#include <time.h>

void decide_on_random_word(char *word, size_t size) {
    // Decide on a random word from a list
    int r = rand() % 9999; // there are 10k words in the file
    FILE *fptr = fopen("words.txt", "r");
    for (int i = 0; i <= r; i++) {
        fgets(word, size, fptr);
    }
    fclose(fptr);
    // Remove trailing newline if present
    size_t len = strlen(word);
    if (len > 0 && word[len - 1] == '\n') {
        word[len - 1] = '\0';
    }
    while (len > 0 && (word[len - 1] == '\n' || word[len - 1] == '\r')) {
        word[--len] = '\0';
}

}

void init_display(const char *word, char *display) {
    int len = strlen(word);
    for (int i = 0; i < len; i++) display[i] = '_';
    display[len] = '\0';
}

void get_letter_positions(const char *word_to_guess, char guess, int *positions, int *count) {
    *count = 0;
    // iterate through the word and find all positions of the guessed letter
    for (int i = 0; word_to_guess[i] != '\0'; i++) {
        // if the letter matches the guess, store the position
        if (word_to_guess[i] == guess) {
            positions[*count] = i;
            (*count)++;
        }
    }
}

int main() {
    int guesses_count = 0;
    srand((unsigned int)time(NULL));
    char word[100];
    decide_on_random_word(word, sizeof(word));
    int len = strlen(word);
    char display[len + 1];
    bool won = false;
    char guessed_letters[27] = {0}; // Array to store guessed letters

    // Clear the console and initialize display
    printf("\033[2J\033[H");
    init_display(word, display);
    printf("%s (wrong guesses: %i/10)\r", display, guesses_count);
    
    while (won==false)
    {
        // user input
        char guess;
        char * pch;
        printf("\nGuess a letter: ");
        scanf(" %c", &guess);

        // Check if the guessed letter is in the word
        int positions[len]; // Array to store indices
        int count;          // Variable to store how many matches
        get_letter_positions(word, guess, positions, &count);
        for (int i = 0; i < count; i++) {
            display[positions[i]] = guess; // Update the display with the guessed letter
        }
        
        if (count == 0) {
            if (strchr(guessed_letters, guess) == NULL) { // Check if letter was not guessed before
                guesses_count++;
                guessed_letters[guesses_count - 1] = guess; // Store the guessed letter
            } else {
                printf("You have already guessed the letter '%c'. Try again.\n", guess);
            }
        }
        printf("\033[2J\033[H");
        printf("%s (wrong guesses: %i/10)\r", display, guesses_count);
        printf("\n(Letters guessed: %s)", guessed_letters);
        // printf("\nLetters guessed: %s", guessed_letters);
        if (strcmp(display, word) == 0) {
            won = true;
            printf("Congratulations! You've guessed the word: %s\n", word);
            break;
        }

        if (guesses_count >= 10) {
            printf("\033[2J\033[H");
            printf("YOU LOOSE. You have used all your guesses. The word was: %s\n", word);
            break;
        }
    }
    
}