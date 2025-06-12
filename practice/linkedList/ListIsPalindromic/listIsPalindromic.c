
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

bool listIsPalindromic(struct list *l) {
    if (!l) return true;
    struct node* curr1 = l->head;
    struct node* curr2 = l->tail;
    int mid = l->size / 2;
    for (int i = 0; i < mid; i++) {
        if (curr1->value != curr2->value) return false;
        curr1 = curr1->next;
        curr2 = curr2->prev;
    }
    return true;
}
