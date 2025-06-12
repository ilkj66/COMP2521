#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

int bstGetKth(struct node *t, int k);

int main(void) {
	struct node *t = bstRead(0);

	printf("\n");
	printf("BST:\n");
	bstPrint(t);

	int k;
	printf("Enter k: ");
	while (scanf("%d", &k) == 1) {
		int value = bstGetKth(t, k);
		printf("For k = %d, bstGetKth returned %d\n", k, value);
		printf("Enter k: ");
	}

	bstFree(t);
}
