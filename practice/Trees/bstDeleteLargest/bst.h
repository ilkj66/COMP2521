// Header file for BST exercises

#ifndef BSTREE_H
#define BSTREE_H

#define MAX_LINE_LEN 8096
#define MAX_BST_SIZE 1024

struct node {
	int value;
	struct node *left;
	struct node *right;
};

////////////////////////////////////////////////////////////////////////
// Utility Functions

// You shouldn't use any of these functions in your code. (You shouldn't
// need to.)

/**
 * Reads  in a line of integers representing the preorder traversal of a
 * BST from stdin and converts it into a BST.
 * Assumes  that the line consists entirely of space-separated integers,
 * is  no  longer  than  8096 characters, and contains no more than 1024
 * integers.
 * If  only one BST needs to be read in for a particular exercise, bstNo
 * should  be set to 0. Otherwise, bstNo specifies the number of the BST
 * that is being read in (1, 2, ...).
 */
struct node *bstRead(int bstNo);

void bstPrint(struct node *t);

void bstFree(struct node *t);

#endif
