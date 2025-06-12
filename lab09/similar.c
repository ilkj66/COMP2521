
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HashTable.h"

bool areSimilarStrings(char *s1, char *s2);
int letterToInt (char letter);

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "usage: %s <string 1> <string 2>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	bool result = areSimilarStrings(argv[1], argv[2]);
	printf("The strings %s similar\n", result ? "are" : "are not");
	return EXIT_SUCCESS;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
////////////////////////////////////////////////////////////////////////
// Your task

/**
 * Returns true if two strings are similar, and false otherwise. Two strings s1
 * and s2 are similar if, for each character in s1, it is possible to *uniquely*
 * replace it by another character (possibly itself) such that, after all
 * replacements are done to s1, we end up with s2. For example, the strings
 * "adt" and "bst" are similar, but "adt" and "dcc" are not.
 */
bool areSimilarStrings(char *s1, char *s2) {
	if (strlen(s1) != strlen(s2)) return false;
	HashTable ht = HashTableNew();
	for (int i = 0; i < strlen(s1); i++) {
		int s1Letter = letterToInt(s1[i]);
		int s2Letter = letterToInt(s2[i]);
		if (!HashTableContains(ht, s1Letter)) {
			HashTableInsert(ht, s1Letter, s2Letter);
			HashTableInsert(ht, s2Letter, s1Letter);
		} else {
			if (HashTableGet(ht, s1Letter) != s2Letter || HashTableGet(ht, s2Letter) != s1Letter) {
				HashTableFree(ht);
				return false;
			}
		}
	}
	HashTableFree(ht);
	return true;
}

int letterToInt (char letter) {
	return letter - 'a';
}
