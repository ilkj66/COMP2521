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

bool isExist(int value, struct node* head) {
    if (!head) return false;
    struct node* curr = head;
    while (curr) {
        if (curr->value == value) return true;
        curr = curr->next;
    }
    return false;
}

bool isRepeated(int value, struct node* head) {
    if (!head) return false;
    struct node* curr = head;
    while (curr) {
        if (value == curr->value) return true;
        curr = curr->next;
    }
    return false;
}

struct list *listSetIntersection(struct list *s1, struct list *s2) {
    // TODO
    if (!s1->head || !s2->head) return listNew();
    struct list* set = listNew();
    struct node* curr = set->head;
    struct node* curr1 = s1->head;
    while (curr1) {
        if (isExist(curr1->value, s2->head) && !isRepeated(curr1->value, set->head)) {
            if (!curr) {
                set->head = newNode(curr1->value);
                curr = set->head;
            } else {
                curr->next = newNode(curr1->value);
                curr = curr->next;
            }
        }
        curr1 = curr1->next;
    }

    return set;
}
