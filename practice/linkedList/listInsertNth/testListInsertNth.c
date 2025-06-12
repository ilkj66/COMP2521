#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void listInsertNth(struct list *l, int value, int n);

int main(void) {
    printf("Enter list: ");
    struct list *l = listRead();
    
    printf("Enter value to insert: ");
    int value = 0;
    scanf("%d", &value);
    
    printf("Enter position to insert at: ");
    int n = 0;
    scanf("%d", &n);
    
    printf("\nOriginal list: ");
    listPrint(l);
    
    listInsertNth(l, value, n);
    printf("List after inserting %d at position %d: ", value, n);
    listPrint(l);

    listFree(l);
}
