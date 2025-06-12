#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void reverseList(struct list *l);

int main(void) {
	printf("Enter list: ");
	struct list *l = listRead();
	printf("\n");

	printf("Original list: ");
	listPrint(l);

	reverseList(l);
	printf("Reversed list: ");
	listPrint(l);

	listFree(l);
}
