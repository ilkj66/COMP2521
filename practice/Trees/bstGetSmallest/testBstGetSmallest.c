#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

struct node *bstGetSmallest(struct node *t);

int main(void) {
	struct node *t = bstRead(0);
	printf("\n");
	
	printf("BST:\n");
	bstPrint(t);
	
	struct node *smallest = bstGetSmallest(t);
	printf("bstGetSmallest returned: ");
	if (smallest == NULL) {
		printf("NULL\n");
	} else {
		printf("%d\n", smallest->value);
	}

	bstFree(t);
}
