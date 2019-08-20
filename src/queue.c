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

#include "queue.h"

Queue* queue_init() {
	Queue* queue = malloc(sizeof(Queue));
	queue->head = queue->tail = NULL;
	return queue;
}

void queue_destroy(Queue* queue) {
	Node* node = queue->head;
	while (node) {
		Node* tmp = node;
		node = node->nextNode;
		free(tmp);
	}
	free(queue);
}

void queue_enqueue(Queue* queue, void** item) {
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
