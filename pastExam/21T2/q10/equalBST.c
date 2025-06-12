// equalBST.c ... implementation of equalBST function

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

int equalBST(struct node *t1, struct node *t2) {
    if (!t1 && !t2) {
        return 1;
    } else if (t1 && t2) {
        if (t1->key == t2->key) {
            return 1 && equalBST(t1->left, t2->left) && equalBST(t1->right, t2->right);
        } else return 0;
    } else {
        return 0;
    }
}

