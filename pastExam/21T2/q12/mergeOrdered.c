// mergeOrdered.c ... implementation of mergeOrdered function

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct list *mergeOrdered(struct list *list1, struct list *list2) {
    struct list *newList = ListNew();
    struct node *tail = NULL;
    struct node *l1 = list1->first;
    struct node *l2 = list2->first;
    while (l1 && l2) {
        struct node *new;
        if (l1->value > l2->value) {
            new = newNode(l2->value);
            l2 = l2->next;
        } else {
            new = newNode(l1->value);
            l1 = l1->next;
        }
        if (newList->first == NULL) {
            newList->first = new;
            tail = new;
        } else {
            tail->next = new;
            tail = new;
        }
    }
    
    while (l1) {
        struct node *new = newNode(l1->value);
        if (newList->first == NULL) {
            newList->first = new;
            tail = new;
        } else {
            tail->next = new;
            tail = new;
        }
        l1 = l1->next;
    }

    while (l2) {
        struct node *new = newNode(l2->value);
        if (newList->first == NULL) {
            newList->first = new;
            tail = new;
        } else {
            tail->next = new;
            tail = new;
        }
        l2 = l2->next;
    }
    newList->last = tail;
    return newList;
    
}

