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

typedef void DEALLOC_ITEM(void* item);

typedef struct Node {
	void* value;
	Node* nextNode;
} Node;

typedef struct Queue {
	Node* head;
	Node* tail;
} Queue;

Queue* queue_init();

void queue_destroy(Queue* queue, DEALLOC_ITEM* dealloc);

void queue_enqueue(Queue* queue, void* item);

void* queue_dequeue(Queue* queue);

typedef struct Stack {
	size_t stackSize;
	void** stack;
	int stackPointer;
} Stack;

Stack* stack_init(size_t size);

void stack_destroy(Stack* stack, DEALLOC_ITEM* dealloc);

int stack_push(Stack* stack, void* item);

void* stack_pop(Stack* stack);

#endif

#ifdef __cplusplus
}
#endif
