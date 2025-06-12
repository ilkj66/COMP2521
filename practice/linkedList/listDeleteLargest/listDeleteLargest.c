#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void listDeleteLargest(struct list *l) {
    // TODO
    struct node* curr = l->head;
    if (!curr) return;
    int max = curr->value;
    while (curr) {
        if (curr->value > max) max = curr->value;
        curr = curr->next;
    }
    curr = l->head;
    struct node* prev = NULL;
    while (curr && curr->value != max) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) return;
    if (!prev) {
        curr = curr->next;
        prev = curr;
        l->head = curr;
        return;
    } else {
        prev->next = curr->next;
        free(curr);
    }
}
