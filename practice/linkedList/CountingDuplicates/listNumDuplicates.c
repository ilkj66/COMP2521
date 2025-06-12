#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int listNumDuplicates(struct list *l) {
    // TODO
    int count = 0;
    struct node* curr = l->head;
    struct node* prev = NULL;
    while (curr) {
        if (prev) {
            if (prev->value == curr->value) count++;
        }
        prev = curr;
        curr = curr->next;
    }
    return count;
}
