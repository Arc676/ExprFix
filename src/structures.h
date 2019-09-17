// Copyright (C) 2019 Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation (version 3).

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#ifdef __cplusplus
extern "C" {
#endif

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdlib.h>

/**
 * Deallocation handler for deallocating items in queues and stacks
 * @param item An item to be deallocated
 */
typedef void DEALLOC_ITEM(void* item);

/**
 * Node type for linked list
 */
typedef struct Node {
	void* value;
	struct Node* nextNode;
} Node;

/**
 * Queue structure implemented as a linked list
 */
typedef struct Queue {
	Node* head;
	Node* tail;
} Queue;

/**
 * Initialize an empty queue
 * @return A new, empty queue
 */
Queue* queue_init();

/**
 * Deallocates a queue
 * @param queue Queue to deallocate
 * @param dealloc Deallocation function for the elements in the queue (if needed)
 */
void queue_destroy(Queue* queue, DEALLOC_ITEM* dealloc);

/**
 * Adds an element to a queue
 * @param queue Queue to which to add the element
 * @param item Element to add to the queue
 */
void queue_enqueue(Queue* queue, void* item);

/**
 * Removes an element from a queue
 * @param queue Queue from which to remove the element
 * @return The element at the front of the queue
 */
void* queue_dequeue(Queue* queue);

/**
 * Stack structure implemented as an array
 */
typedef struct Stack {
	size_t stackSize;
	void** stack;
	int stackPointer;
} Stack;

/**
 * Initializes an empty struct with the given initial size
 * @param size Initial stack size
 * @return Newly allocated stack
 */
Stack* stack_init(size_t size);

void stack_destroy(Stack* stack, DEALLOC_ITEM* dealloc);

/**
 * Pushes a new element onto a stack
 * @param stack Stack onto which to push the element
 * @param item Element to push onto the stack
 * @return Whether the push succeeded
 */
int stack_push(Stack* stack, void* item);

/**
 * Removes and returns the element at the top of a stack
 * @param stack Stack from which to pop
 * @return Element on top of the given stack
 */
void* stack_pop(Stack* stack);

/**
 * Check the top element of a stack without removing it
 * @param stack Stack whose top element to view
 * @return Element on top of the given stack
 */
void* stack_peek(Stack* stack);

#endif

#ifdef __cplusplus
}
#endif
