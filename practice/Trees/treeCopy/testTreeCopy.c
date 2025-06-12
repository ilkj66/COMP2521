
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

struct node *treeCopy(struct node *t, int depth);

int main(void) {
	struct node *t = treeRead(0);
	
	printf("Enter depth: ");
	int depth = 0;
	scanf("%d", &depth);
	printf("\n");

	printf("Tree:\n");
	treePrint(t);

	struct node *copy = treeCopy(t, depth);
	
	printf("Copy of the tree up to depth %d:\n", depth);
	treePrint(copy);
	
	treeFree(t);
	treeFree(copy);
}
