// Header file for tree exercises

#ifndef TREE_H
#define TREE_H

#define MAX_LINE_LEN  8096
#define MAX_TREE_SIZE 1024

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
 * Displays  prompts and reads in two lines of integers representing the
 * preorder and in-order traversals of a tree from  stdin  and  converts
 * them  into  a binary tree. Assumes that the lines consist entirely of
 * space-separated integers, are no longer  than  8096  characters,  and
 * contain no more than 1024 integers.
 * If  this  function  is called multiple times, treeNo should be set to
 * the number of the tree (1, 2, ...). Otherwise, treeNo should  be  set
 * to 0.
 */
struct node *treeRead(int treeNo);

void treePrint(struct node *t);

void treeFree(struct node *t);

#endif
