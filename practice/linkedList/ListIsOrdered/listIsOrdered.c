#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

bool listIsOrdered(struct list *l) {
    // TODO
    struct node* curr = l->head;
    bool res1 = true, res2 = true;
    while (curr) {
        if (curr->next) {
            if (curr->value > curr->next->value) res1 = false;
        }
        curr = curr->next;
    }
    curr = l->head;
    while (curr) {
        if (curr->next) {
            if (curr->value < curr->next->value) res2 = false;
        }
        curr = curr->next;
    }
    return res1 || res2;
}
