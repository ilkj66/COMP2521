// printWords.c ... implementation of printWords function

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Trie.h"
void print(Trie t, int count, char *word);
void printWords(Trie t) {
    // TODO
    // Implement this function
    char *word = malloc(sizeof(char) * MAXWORD);
    print(t, 0, word);
    free(word);
}

void print(Trie t, int count, char *word) {
    if (!t) return;
    if (t->isEndOfWord) {
        word[count] = '\0';
        printf("%s\n", word);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (t->children[i]) {
            word[count] = 'a' + i;
            print(t->children[i], count + 1, word);
        }
    }

}

