// Linked list utility functions

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

static struct node *newNode(int value);

// Creates a new empty list
struct node *ListNew(void) {
    return NULL;
}

// Frees all memory associated with the given list
void ListFree(struct node *l) {
    struct node *curr = l;
    while (curr != NULL) {
        struct node *temp = curr;
        curr = curr->next;
        free(temp);
    }
}

// Inserts a value at the end of the given list
// Returns the beginning of the updated list
struct node *ListInsert(struct node *l, int value) {
    struct node *n = newNode(value);
    if (l == NULL) {
        return n;
    }
    struct node *curr = l;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = n;
    return l;
}

// Creates a new list node
static struct node *newNode(int value) {
    struct node *n = malloc(sizeof(*n));
    assert(n != NULL);
    n->value = value;
    n->next = NULL;
    return n;
}

// Prints a list to stdout
void ListShow(struct node *l) {
    struct node *curr;
    for (curr = l; curr != NULL; curr = curr->next) {
        printf("%d -> ", curr->value);
    }
    printf("<END>\n");
}

// Prints the ascending prefix of a list to stdout
void ListShowAscending(struct node *l) {
    if (l != NULL) {
        struct node *curr = l;
        int v = l->value;
        do {
            printf("%d -> ", curr->value);
            v = curr->value;
            curr = curr->next;
        } while (curr != NULL && curr->value > v);
    }
    printf("<END>\n");
}

// Creates a list by reading integer values from a line 
struct node *ListRead(FILE *fp) {
    struct node *head = NULL;
    struct node *curr = NULL;

    int value;
    while (fscanf(fp, "%d", &value) == 1) {
        if (head == NULL) {
            head = newNode(value);
            curr = head;
        } else {
            curr->next = newNode(value);
            curr = curr->next;
        }
    }

    return head;
}

