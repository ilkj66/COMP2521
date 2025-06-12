// Interface to the stack ADT

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef STACK_H
#define STACK_H

typedef struct stack *Stack;

typedef int Item;

/**
 * Creates a new empty stack
 */
Stack StackNew(void);

/**
 * Frees all memory allocated to the stack
 */
void StackFree(Stack s);

/**
 * Adds an item to the top of the stack
 */
void StackPush(Stack s, Item item);

/**
 * Removes an item from the top of the stack and returns it
 * Assumes that the stack is not empty
 */
Item StackPop(Stack s);

/**
 * Returns the number of items in the stack
 */
int StackSize(Stack s);

/**
 * Returns whether the stack is empty or not
 */
bool StackIsEmpty(Stack s);

/**
 * Returns the item at the top of the stack without removing it
 * Assumes that the stack is not empty
 */
Item StackPeek(Stack s);

#endif
