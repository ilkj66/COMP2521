#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void listDeleteDuplicates(struct list *l);

int main(void) {
    printf("Enter list: ");
    struct list *l = listRead();
    printf("\n");

    printf("Original list: ");
    listPrint(l);

    listDeleteDuplicates(l);
    printf("After deleting duplicates: ");
    listPrint(l);

    listFree(l);
}
