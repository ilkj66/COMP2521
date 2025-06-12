
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// Worst case time complexity of this solution: O(...)
List zipList(List l1, int x, List l2, int y) {
    // TODO
    if (x == 0) return l2;
    else if (y == 0) return l1;
    else if (x == 0 && y == 0) return NULL;

    List l = ListNew();
    struct node *list1 = l1->first;
    struct node *list2 = l2->first;

    while (list1 && list2) {
        for (int i = 0; i < x && list1 != NULL; i++) {
            struct node *n = newNode(list1->value);
            if (!l->first) {
                l->first = n;
                l->last = n;
            } else {
                l->last->next = n;
                l->last = l->last->next;
            }
            list1 = list1->next;
        }
        for (int i = 0; i < y && list2 != NULL; i++) {
            struct node* n = newNode(list2->value);
            if (!l->first) {
                l->first = n;
                l->last = n;
            } else {
                l->last->next = n;
                l->last = l->last->next;
            }
            list2 = list2->next;
        }
    }
    
    return l;
}

