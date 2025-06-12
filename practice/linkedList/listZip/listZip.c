#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct node* newNode(int val) {
    struct node* new = malloc(sizeof(struct node));
    new->value = val;
    new->next = NULL;
    return new;
}

struct list *listZip(struct list *l1, struct list *l2) {
    // TODO
    if (!l1->head && !l2->head) return listNew();
    
    struct node* curr1 = l1->head;
    struct node* curr2 = l2->head;
    struct list* l = listNew();
    while (curr1 && curr2) {
        if (!l->head) {
            l->head = newNode(curr1->value);
            l->tail = l->head;
        } else {
            l->tail->next = newNode(curr1->value);
            l->tail = l->tail->next;
        }
        l->tail->next = newNode(curr2->value);
        l->tail = l->tail->next;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    while (curr1) {
        if (!l->head) {
            l->head = newNode(curr1->value);
            l->tail = l->head;
        }else {
            l->tail->next = newNode(curr1->value);
            l->tail = l->tail->next;
        }
        curr1 = curr1->next;
    }
    while (curr2) {
        if (!l->head) {
            l->head = newNode(curr2->value);
            l->tail = l->head;
        } else {
            l->tail->next = newNode(curr2->value);
            l->tail = l->tail->next;
        }
        curr2 = curr2->next;
    }
    return l;
}
