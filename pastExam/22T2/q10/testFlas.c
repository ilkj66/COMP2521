// Main program for testing flas

// !!! DO NOT MODIFY THIS FILE !!!

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct node *flas(struct node *l);

int main(int argc, char *argv[]) {
    List l = ListRead(stdin);
    printf("List: ");
    ListShow(l);

    List longest = flas(l);	
    printf("FLAS: ");
    ListShowAscending(longest);

    ListFree(l);
}

