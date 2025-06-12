// Implementation of the queue ADT

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

struct queue {
    struct node *head;
    struct node *tail;
    int size;
};

struct node {
    Item item;
    struct node *next;
};

static struct node *newNode(Item it);

Queue QueueNew(void) {
    Queue q = malloc(sizeof(struct queue));
    if (q == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

void QueueFree(Queue q) {
    struct node *curr = q->head;
    while (curr != NULL) {
        struct node *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(q);
}

void QueueEnqueue(Queue q, Item it) {
    struct node *n = newNode(it);
    if (q->size == 0) {
        q->head = n;
    } else {
        q->tail->next = n;
    }
    q->tail = n;
    q->size++;
}

static struct node *newNode(Item it) {
    struct node *n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    n->item = it;
    n->next = NULL;
    return n;
}

Item QueueDequeue(Queue q) {
    if (q->size == 0) {
        fprintf(stderr, "error: queue is empty!\n");
        return 0;
    }

    struct node *newHead = q->head->next;
    Item it = q->head->item;

    free(q->head);
    q->head = newHead;
    if (newHead == NULL) {
        q->tail = NULL;
    }
    q->size--;

    return it;
}

int QueueSize(Queue q) {
    return q->size;
}

bool QueueIsEmpty(Queue q) {
    return q->size == 0;
}

Item QueuePeek(Queue q) {
    if (q->size == 0) {
        fprintf(stderr, "error: queue is empty!\n");
        return 0;
    }

    return q->head->item;
}
