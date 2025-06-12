#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct node* newNode(int value) {
	struct node* new = malloc(sizeof(struct node));
	new->value = value;
	new->next = NULL;
	return new;
}

bool isRepeated (struct node* head, int value) {
	if (!head) return false;
	struct node* curr = head;
	while (curr) {
		if (curr->value == value) return true;
		curr = curr->next;
	}
	return false;
}

struct list *listSetUnion(struct list *s1, struct list *s2) {
	// TODO
	if (!s1->head && !s2->head) return listNew();
	struct list *set = listNew();
	struct node* curr1 = s1->head;
	struct node* curr2 = s2->head;
	struct node* curr = set->head;
	while (curr1) {
		if (!isRepeated(set->head, curr1->value)) {
			if (!curr) {
				set->head = newNode(curr1->value);
				curr = set->head;
			} else {
				curr->next = newNode(curr1->value);
				curr = curr->next;
			}
		}
		curr1 = curr1->next;
	}
	while (curr2) {
		if (!isRepeated(set->head, curr2->value)) {
			if (!curr) {
				set->head = newNode(curr2->value);
				curr = set->head;
			} else {
				curr->next = newNode(curr2->value);
				curr = curr->next;
			}
		}
		curr2 = curr2->next;
	}

	return set;
}
