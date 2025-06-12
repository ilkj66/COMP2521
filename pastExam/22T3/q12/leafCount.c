
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

int leafCount(BSTree t, int pathLength) {
    if (!t) return 0;
    if (!t->left && !t->right && pathLength <= 0) return 1;
    return leafCount(t->left, pathLength - 1) + leafCount(t->right, pathLength - 1);
}

