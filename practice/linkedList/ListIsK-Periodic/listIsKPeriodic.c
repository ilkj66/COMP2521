#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

bool listIsKPeriodic(struct list *l, int k) {
    // TODO
    struct node* curr1 = l->head;
    struct node* curr2 = l->head;
    while (curr1) {
        for (int i = 0; i < k && curr1 && curr2; i++) {
            if (curr1->value != curr2->value) return false;
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        if (!curr1) break;
        curr2 = l->head;
    }
    return true;
}
