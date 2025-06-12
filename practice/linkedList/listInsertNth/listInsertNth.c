#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void listInsertNth(struct list *l, int value, int n) {
    // TODO
    struct node* curr = l->head;
    struct node* prev = NULL;
    int i = n;
    for (; i > 0 && curr; i--) {
        prev = curr;
        curr = curr->next;
    }
    struct node* new = malloc(sizeof(struct node));
    new->value = value;
    new->next = curr;
    if (!prev) {
        l->head = new;
    } else {
        prev->next = new;
    }

}
