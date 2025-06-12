#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

void bstPostfix(struct node *t);

int main(void) {
	struct node *t = bstRead(0);

	printf("\n");
	printf("BST:\n");
	bstPrint(t);
	
	printf("Values in postfix order: ");
	bstPostfix(t);
	printf("\n");
	
	bstFree(t);
}
