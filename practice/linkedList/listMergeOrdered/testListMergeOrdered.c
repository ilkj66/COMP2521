#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct list *listMergeOrdered(struct list *l1, struct list *l2);

int main(void) {
    printf("Enter list 1: ");
    struct list *l1 = listRead();
    printf("Enter list 2: ");
    struct list *l2 = listRead();

    struct list *l3 = listMergeOrdered(l1, l2);

    printf("\n");

    printf("List 1: ");
    listPrint(l1);
    printf("List 2: ");
    listPrint(l2);
    printf("Merged: ");
    listPrint(l3);

    listFree(l1);
    listFree(l2);
    listFree(l3);
}
