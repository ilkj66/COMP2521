#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void reverseDLList(struct list *l);

int main(void) {
	printf("Enter list: ");
	struct list *l = listRead();
	printf("\n");

	printf("Original list:\n");
	listPrint(l);
	printf("\n");
	
	reverseDLList(l);
	printf("Reversed list:\n");
	listPrint(l);
	
	listFree(l);
}
