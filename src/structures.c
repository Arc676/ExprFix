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

#include "structures.h"

Queue* queue_init() {
	Queue* queue = malloc(sizeof(Queue));
	queue->head = queue->tail = NULL;
	return queue;
}

void queue_destroy(Queue* queue, DEALLOC_ITEM* dealloc) {
	Node* node = queue->head;
	while (node) {
		Node* tmp = node;
		node = node->nextNode;
		if (dealloc) dealloc(tmp->value);
		free(tmp);
	}
	free(queue);
}

void queue_enqueue(Queue* queue, void* item) {
	Node* newNode = malloc(sizeof(Node));
	newNode->value = item;
	newNode->nextNode = NULL;
	if (!queue->head && !queue->tail) {
		queue->head = queue->tail = newNode;
	} else {
		queue->tail->nextNode = newNode;
		queue->tail = newNode;
	}
}

void* queue_dequeue(Queue* queue) {
	Node* node = queue->head;
	if (!node) {
		return NULL;
	}
	queue->head = node->nextNode;
	if (!queue->head) {
		queue->tail = NULL;
	}
	void* value = node->value;
	free(node);
	return value;
}

Stack* stack_init(size_t size) {
	Stack* stack = malloc(sizeof(Stack));
	stack->stackSize = size;
	stack->stack = malloc(50 * sizeof(void*));
	stack->stackPointer = 0;
	return stack;
}

void stack_destroy(Stack* stack, DEALLOC_ITEM* dealloc) {
	if (dealloc) {
		for (int i = 0; i < stack->stackPointer; i++) {
			if (stack->stack[i]) {
				dealloc(stack->stack[i]);
			}
		}
	}
	free(stack->stack);
	free(stack);
}

int stack_push(Stack* stack, void* item) {
	stack->stack[stack->stackPointer++] = item;
	if (stack->stackPointer >= stack->stackSize) {
		size_t newSize = stack->stackSize * 2;
		void** newStack = realloc(stack->stack, newSize);
		if (newStack) {
			stack->stackSize = newSize;
			stack->stack = newStack;
		} else {
			return 0;
		}
	}
	return 1;
}

void* stack_pop(Stack* stack) {
	if (stack->stackPointer > 0) {
		return stack->stack[--stack->stackPointer];
	}
	return NULL;
}
