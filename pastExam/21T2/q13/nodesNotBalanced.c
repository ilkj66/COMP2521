// nodesNotBalanced.c ... implementation of nodesNotBalanced function

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

int nodeCount (struct node *t) {
    if (!t) return 0;
    return 1 + nodeCount(t->left) + nodeCount(t->right);
}

void traversal(struct node *t, int *n) {
    if (!t) return;
    if (abs(nodeCount(t->left) - nodeCount(t->right)) > 1) {
        (*n)++;
    }
    traversal(t->left, n);
    traversal(t->right, n);
}

int nodesNotBalanced(struct node *t) {
    // if (abs(nodeCount(t->left) - nodeCount(t->right)) > 1) {
    //     return t->key;
    // }
    // nodesNotBalanced(t->left);
    // nodesNotBalanced(t->right);
    int n = 0;
    traversal(t, &n);
    return n;
}