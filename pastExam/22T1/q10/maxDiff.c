
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"
void traverse (struct node *t, int *max);
int getSubNodes (struct node *t);
int maxDiff(struct node *t) {
    // TODO
    int k = 0;
    traverse(t, &k);
    return k;
}

void traverse (struct node *t, int *max) {
    if (!t) return;
    int diff = abs(getSubNodes(t->left) - getSubNodes(t->right));
    if (diff > (*max)) (*max) = diff;
    traverse(t->left, max);
    traverse(t->right, max);
}

int getSubNodes (struct node *t) {
    if (!t) return 0;
    return 1 + getSubNodes(t->left) + getSubNodes(t->right);
}
