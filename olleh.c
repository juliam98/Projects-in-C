#include <stdio.h>
#include <string.h>

void reverse(char *word, int len, char *rev_word) {
    int rev_idx=0;

    for (int i = len; i >= 0; i--) {
        rev_word[rev_idx] = word[i];
        rev_idx++;
    }
}

int main() {
    char word[100];
    printf("Which word would you like to reverse? ");
    scanf("%s", word);
    char result[strlen(word)+1];

    reverse(word, strlen(word)-1, result);
    printf("%s\n", result);
    return 0;
}