#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void reverseDLList(struct list *l) {
    // TODO
    struct node* curr = l->head;
    if (!curr || !curr->next) return;
    struct node* prev = NULL;
    struct node* nxt = curr->next;
    while (curr) {
        curr->prev = nxt;
        curr->next = prev;
        prev = curr;
        curr = nxt;
        if (!nxt) nxt = NULL;
        else nxt = nxt->next;
    }
    struct node* temp = l->head;
    l->head = l->tail;
    l->tail = temp;
}
