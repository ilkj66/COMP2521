
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
struct node *flas(struct node *l) {
    if (l == NULL || l->next == NULL) return NULL;

    struct node *curr = l;
    struct node *start = l;
    struct node *longStart = NULL;
    struct node *longEnd = NULL;

    int count = 1;
    int largestCount = 1;

    while (curr->next != NULL) {
        if (curr->value < curr->next->value) {
            count++;
        } else {
            if (count > largestCount) {
                largestCount = count;
                longStart = start;
                longEnd = curr;
            }
            count = 1;
            start = curr->next;
        }
        curr = curr->next;
    }

    if (count > largestCount) {
        largestCount = count;
        longStart = start;
        longEnd = curr;
    }

    if (largestCount == 1) return NULL;

    // free before longStart
    for (curr = l; curr != longStart; ) {
        struct node *tmp = curr;
        curr = curr->next;
        free(tmp);
    }

    // free after longEnd
    for (curr = longEnd->next; curr != NULL; ) {
        struct node *tmp = curr;
        curr = curr->next;
        free(tmp);
    }

    longEnd->next = NULL;
    return longStart;
}
