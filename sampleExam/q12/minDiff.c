
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

void find(struct node *t, struct node *t1, struct node* t2, int l) {
    if (!t) return;
    if (l == 0) {
        if (!t1) {
            t1 = t;
        } else {
            if (t1->value < t) {
                t1 = t;
            }
        }
        if (!t2) {
            t2 = t;
        } else {
            if (t2->value > t->value) {
                t2 = t;
            }
        }
    }
    find(t->left, t1, t2, l - 1);
    find(t->right, t1, t2, l - 1);
}

int minDiff(struct node *t, int l) {
    // TODO
    struct node* t1 = NULL;
    struct node* t2 = NULL;
    find (t, t1, t2, l);
    if (!t1 || t2) return 0;
    if (t1->value == t2->value) return 0;
    return abs(t1->value - t2->value);
}
