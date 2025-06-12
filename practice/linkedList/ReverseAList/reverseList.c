#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void reverseList(struct list *l) {
    // TODO
    struct node* prev = NULL;
    struct node* curr = l->head;
    if (!curr || !curr->next) return;
    struct node* nxt = curr->next;
    while (curr) {
        curr->next = prev;
        prev = curr;
        curr = nxt;
        if (!nxt) nxt = NULL;
        else nxt = nxt->next;
    }
    l->head = prev;
}
