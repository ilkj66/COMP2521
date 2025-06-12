
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List findShortestSublist(List l, int start, int end) {
    if (!l) {
        List list = ListNew();
        return list;
    }
    struct node* curr = l->first;
    struct node* goodStart = NULL;
    struct node* goodLast = NULL;
    int bestLength = -1;
    int length = 0;
    while (curr) {
        if (curr->value == start && bestLength == -1) {
            goodStart = curr;
            struct node* temp = curr;
            while (temp && temp->value != end) {
                temp = temp->next;
                length++;
            }
            if (!temp) break;
            goodLast = temp;
            bestLength = length;
        }
        if (curr->value == start && bestLength != -1) {
            struct node* temp = curr;
            length = 0;
            while (temp && temp->value != end) {
                temp = temp->next;
                length++;
            }
            if (!temp) break;
            if (length < bestLength) {
                bestLength = length;
                goodStart = curr;
                goodLast = temp;
            }
        }
        curr = curr->next;
    }
    List list = ListNew();
    if (!goodStart || !goodLast) return list;
    curr = goodStart;
    while(curr->value != end) {
        if (!list->first) {
            list->first = newNode(curr->value);
            list->last = list->first;
        } else {
            list->last->next = newNode(curr->value);
            list->last = list->last->next;
        }
        curr = curr->next;
    }
    if (!list->first) {
        list->first = newNode(curr->value);
        list->last = list->first;
        return list;
    }
    list->last->next = newNode(curr->value);
    list->last = list->last->next;
    return list;
}