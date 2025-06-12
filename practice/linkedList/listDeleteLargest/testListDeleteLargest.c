#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void listDeleteLargest(struct list *l);

int main(void) {
    printf("Enter list: ");
    struct list *l = listRead();
    printf("\n");

    printf("Original list: ");
    listPrint(l);

    listDeleteLargest(l);
    printf("After deleting largest: ");
    listPrint(l);

    listFree(l);
}
