#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct list *listSetDifference(struct list *s1, struct list *s2);

int main(void) {
    printf("Enter list 1: ");
    struct list *l1 = listRead();
    
    printf("Enter list 2: ");
    struct list *l2 = listRead();
    
    struct list *l3 = listSetDifference(l1, l2);
    printf("\n");
    
    printf("Set 1: ");
    listPrintAsSet(l1);
    printf("Set 2: ");
    listPrintAsSet(l2);
    printf("Difference: ");
    struct list *sortedl3 = listSortedCopy(l3);
    listPrintAsSet(sortedl3);
    
    listFree(l1);
    listFree(l2);
    listFree(l3);
    listFree(sortedl3);
}
