#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

struct node *bstDeleteLargest(struct node *t, int *max);

int main(void) {
	struct node *t = bstRead(0);

	printf("\n");
	printf("BST:\n");
	bstPrint(t);

	int max = 0;
	t = bstDeleteLargest(t, &max);

	printf("BST after deleting largest:\n");
	bstPrint(t);
	printf("The largest value was %d\n", max);

	bstFree(t);
}
