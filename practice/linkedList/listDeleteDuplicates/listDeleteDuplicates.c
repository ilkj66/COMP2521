#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void listDeleteDuplicates(struct list *l) {
    // TODO
    struct node* prev = NULL;
    struct node* curr1 = l->head;
    struct node* curr2 = l->head;
    while (curr1) {
        prev = curr1;
        curr2 = curr1->next;
        while (curr2) {
            if (curr2->value == curr1->value) {
                prev->next = curr2->next;
                struct node* tmp = curr2;
                curr2 = curr2->next;
                free(tmp);
                
            } else {
                prev = curr2;
                curr2 = curr2->next;
            }
        }
        curr1 = curr1->next;
    }

}
