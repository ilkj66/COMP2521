
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// Worst case time complexity of this solution: O(...)
// int numSubsequences(struct list *listA, struct list *listB, int tolerance) {
// 	// TODO
// 	if (listA == NULL || listB == NULL || listB->first == NULL) {
// 		return 0;
// 	}

// 	int count = 0;

// 	struct node *currA = listA->first;

// 	while (currA != NULL) {
// 		struct node *a = currA;
// 		struct node *b = listB->first;
// 		int mismatches = 0;

// 		while (a != NULL && b != NULL) {
// 			if (a->value != b->value) {
// 				mismatches++;
// 				if (mismatches > tolerance) {
// 					break;
// 				}
// 			}
// 			a = a->next;
// 			b = b->next;
// 		}

// 		if (b == NULL) {
// 			count++; // matched whole listB
// 		}

// 		currA = currA->next;
// 	}

// 	return count;
// }

int numSubsequences(struct list *listA, struct list *listB, int tolerance) {
	// TODO
	struct node *curr1 = listA->first;
	struct node* curr2 = listB->first;
	if (!curr2 || !curr1) return 0;
	int count = 0;
	while (curr1 != NULL) {
		struct node* now1 = curr1;
		curr2 = listB->first;
		int dismatch = 0;
		while (now1 && curr2) {
			if (now1->value != curr2->value) {
				dismatch++;
				if (dismatch > tolerance) break;
			}
			curr2 = curr2->next;
			now1 = now1->next;
		}
		if(!curr2) count++;
		curr1 = curr1->next;
	}
	return count;
}
