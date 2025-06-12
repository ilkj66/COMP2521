#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct node* newNode(int value) {
    struct node* new = malloc(sizeof(struct node));
    new->value = value;
    new->next = NULL;
    return new;
}

bool isIn(int value, struct node* head) {
    if (!head) return false;
    struct node* curr = head;
    while (curr) {
        if (curr->value == value) return true;
        curr = curr->next;
    }
    return false;
}

struct list *listSetDifference(struct list *l1, struct list *l2) {
    // TODO
    if (!l1->head) return listNew();
    struct list* l = listNew();
    struct node* curr = NULL;
    struct node* curr1 = l1->head;
    while (curr1) {
        if (!isIn(curr1->value, l2->head)) {
            if (!curr) {
                l->head = newNode(curr1->value);
                curr = l->head;
            } else {
                curr->next = newNode(curr1->value);
                curr = curr->next;
            }
        }
        curr1 = curr1->next;
    }
    return l;
}
