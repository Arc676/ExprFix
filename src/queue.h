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

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

typedef struct Node {
	void* value;
	Node* nextNode;
} Node;

typedef struct Queue {
	Node* head;
	Node* tail;
} Queue;

Queue* queue_init();

void queue_destroy(Queue* queue);

void queue_enqueue(Queue* queue, void* item);

void* queue_dequeue(Queue* queue);

#endif

#ifdef __cplusplus
}
#endif
