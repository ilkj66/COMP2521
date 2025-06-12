// Implementation of the Huffman module

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "character.h"
#include "Counter.h"
#include "File.h"
#include "huffman.h"

static struct huffmanTree *newhuffmanNode (int freq, char *character);
static void bubbleSort (struct huffmanTree **nodeList, int size);
static void lessCombineNode (struct huffmanTree **nodeList, int *size);
static int treeHeight (struct huffmanTree *tree);
static int max (int a, int b);
static bool findPath (struct huffmanTree *tree, char *target, char *encode, int index);


// Task 1
void decode(struct huffmanTree *tree, char *encoding, char *outputFilename) {
	File file = FileOpenToWrite(outputFilename);

	struct huffmanTree *curr = tree;
	// go to the node
	for (int i = 0; encoding[i] != '\0'; i++) {
		if (encoding[i] == '0') {
			curr = curr->left;
		} else if (encoding[i] == '1') {
			curr = curr->right;
		} else {
			fprintf(stderr, "Invalid encoding %c\n", encoding[i]);
			return;
		}

		if (curr->left == NULL && curr->right == NULL) { // arrive the leave node
			FileWrite(file, curr->character);
			curr = tree; // starting from the root
		}
	}
	
	FileClose(file);
}

// Task 3
struct huffmanTree *createHuffmanTree(char *inputFilename) {
	Counter newCounter = CounterNew();
	File file = FileOpenToRead(inputFilename);

	char buffer[MAX_CHARACTER_LEN+1];
	while (FileReadCharacter(file, buffer)) { // create new counter
		CounterAdd(newCounter, buffer);
	}

	FileClose(file);
	int itemsNum = CounterNumItems(newCounter);
	struct item *items = CounterItems(newCounter, &itemsNum); // get all items' info
	int listSize = itemsNum;
	struct huffmanTree **nodeList = malloc (itemsNum * sizeof(struct huffmanTree *));
	if (nodeList == NULL) {
		fprintf(stderr, "Memory Allocation Failed.\n");
		exit(1);
	}
	for (int i = 0; i < itemsNum; i++) {
		nodeList[i] = newhuffmanNode(items[i].freq, items[i].character); // fill the list
	}
	// sort the list
	bubbleSort(nodeList, listSize);
	while (listSize > 1) {
		lessCombineNode(nodeList, &listSize);
	}
	struct huffmanTree *root = nodeList[0];
	CounterFree(newCounter);
	free(nodeList);
	free(items);

	return root;
}

// Task 4
char *encode(struct huffmanTree *tree, char *inputFilename) {
	File file = FileOpenToRead(inputFilename);
	char *str = calloc(1, sizeof(char)); // allocate the initial string
	if (str == NULL) {
	 	fprintf(stderr, "Calloc Failed.\n");
		exit(1);
	}
   
	str[0] = '\0';
	int height = treeHeight(tree); // get height of tree
	char *encode = calloc(height + 2, sizeof(char)); // alocate the encoding array
	if (encode == NULL) {
	 	fprintf(stderr, "Calloc Failed.\n");
	 	exit(1);
	}
	size_t strLength = 0;
	size_t capacity = 1;
   
	char buffer[MAX_CHARACTER_LEN + 1];
	while (FileReadCharacter(file, buffer)) { // get path after getting a character
	 
	 	if (findPath(tree, buffer, encode, 0)) {

			size_t encLength = 0;
			while (encode[encLength] != '\0') encLength++;
			size_t newLength = strLength + encLength + 1;

			if (newLength > capacity) {
				char *newString = realloc(str, newLength);
				if (newString == NULL) {
					fprintf(stderr, "Memory Reallocation Failed.\n");
					exit(1);
				}
				str = newString;
				capacity = newLength;
			}
			// append the new encode string to string
			memcpy(str + strLength, encode, encLength);
			strLength += encLength;
			str[strLength] = '\0';
		}
	}
   
	free(encode);
	FileClose(file);
   
	return str;
}

// helper functions in task3

static struct huffmanTree *newhuffmanNode (int freq, char *character) {
	struct huffmanTree *newNode = malloc(sizeof(struct huffmanTree));
	if (newNode == NULL) {
		fprintf(stderr, "Failed Memory Allocated.\n");
		exit(1);
	}
	newNode->freq = freq;
	newNode->character = strdup(character);
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

static void bubbleSort (struct huffmanTree **nodeList, int size) {
	for (int i = size - 1; i > 0; i--) {
		bool swapped = false;
		for (int k = 0; k < i; k++) {
			if (nodeList[k]->freq > nodeList[k + 1]->freq) { // sort the list
				struct huffmanTree *temp = nodeList[k];
				nodeList[k] = nodeList[k + 1];
				nodeList[k + 1] = temp;
				swapped = true;
			}
		}
		if (!swapped) break;
	}
}

static void lessCombineNode (struct huffmanTree **nodeList, int *size) {
	struct huffmanTree *newParent = malloc(sizeof(struct huffmanTree));
	if (newParent == NULL) {
		fprintf(stderr, "Memory Allocation Failed.\n");
		exit(1);
	}
	// combine the first and second elements (nodes) in the array
	newParent->freq = nodeList[0]->freq + nodeList[1]->freq;
	newParent->character = NULL;
	newParent->left = nodeList[0];
	newParent->right = nodeList[1];
	// fill the gap with subsequent elements
	for (int i = 2; i < *size; i++) {
		nodeList[i - 2] = nodeList[i];
	}
	// add the combined root in the end of the list
	nodeList[*size - 2] = newParent;
	(*size)--; // update new size
	
	bubbleSort(nodeList, *size); // sort the array

}

// helper functions in task4

static int treeHeight (struct huffmanTree *tree) {
	if (tree == NULL) return -1;
	return 1 + max(treeHeight(tree->left), treeHeight(tree->right));
}

static int max (int a, int b) {
	if (a > b) return a;
	return b;
}

static bool findPath (struct huffmanTree *tree, char *target, char *encode, int index) {
	if (tree == NULL) return false;
	if (tree->left == NULL && tree->right == NULL) { // base case: tree is empty or arrive the leaf node
		if (strcmp(tree->character, target) == 0) {
			encode[index] = '\0';
			return true;
		} else return false;
	}
	// find the path recursivly
	encode[index] = '0';
	if(findPath(tree->left, target, encode, index + 1)) return true;

	encode[index] = '1';
	if (findPath(tree->right, target, encode, index + 1)) return true;

	return false; // NULL or can't find
}
