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

#include "exprfix.h"

char* infixToPostfix(char* expr, IS_BINARY isBin, IS_UNARY isUn, OP_PROPERTIES getOpProps) {
	Stack* operatorStack = stack_init(20);
	Queue* outputQueue = queue_init();
	char* token = PARSE_TOKEN(expr, &progress);
	do {
		if (isUn(token) || token[0] == '(') {
			stack_push(operatorStack, token);
		} else if (isBin(token)) {
			int prec, left, tPrec, tLeft;
			getOpProps(token, &prec, &left);
			char* top = stack_peek(operatorStack);
			if (isBin(top)) getOpProps(top, &tPrec, &tLeft);
			while (top && top[0] != '(' && (isUn(top) || (isBin(top) && (tPrec > prec || (tPrec == prec && tLeft))))) {
				stack_pop(operatorStack);
				queue_enqueue(outputQueue, top);
				top = stack_peek(operatorStack);
				if (isBin(top)) getOpProps(top, &tPrec, &tLeft);
			}
			stack_push(operatorStack, token);
		} else if (token[0] == ')') {
			char* top = stack_peek(operatorStack);
			while (top && top[0] != '(') {
				stack_pop(operatorStack);
				queue_enqueue(outputQueue, top);
				top = stack_peek(operatorStack);
			}
			if (!top) {
				stack_destroy(operatorStack, NULL);
				queue_destroy(outputQueue, NULL);
				return NULL;
			}
			stack_pop(operatorStack);
		} else {
			queue_enqueue(outputQueue, token);
		}
	} while (token = PARSE_TOKEN(NULL, &progress));
	while (token = stack_pop(operatorStack)) {
		queue_enqueue(outputQueue, token);
	}
	char* postfix = malloc(2 * strlen(expr));
	while (token = queue_dequeue(outputQueue)) {
		sprintf(postfix, "%s %s", postfix, token);
	}
	return postfix;
}

char* postfixToPrefix(char* expr, IS_BINARY isBin, IS_UNARY isUn) {
	Stack* stack = stack_init(50);
	char* progress = NULL;
	char* token = PARSE_TOKEN(expr, &progress);
	do {
		if (isBin(token)) {
			char* op1 = stack_pop(stack);
			char* op2 = stack_pop(stack);
			char* res = malloc(strlen(token) + strlen(op1) + strlen(op2) + 3);
			sprintf(res, "%s %s %s", token, op1, op2);
			free(op1);
			free(op2);
			stack_push(stack, res);
		} else {
			char* operand;
			if (isUn(token)) {
				char* unaryOperand = PARSE_TOKEN(NULL, &progress);
				operand = malloc(strlen(token) + strlen(unaryOperand) + 2);
				sprintf(operand, "%s %s", token, unaryOperand);
			} else {
				operand = malloc(strlen(token) + 1);
				sprintf(operand, "%s", token);
			}
			stack_push(stack, operand);
		}
	} while (token = PARSE_TOKEN(NULL, &progress));
	char* prefix = stack_pop(stack);
	stack_destroy(stack, free);
	return prefix;
}

char* infixToPrefix(char* expr, IS_BINARY isBin, IS_UNARY isUn, OP_PROPERTIES getOpProps) {
	char* postfix = infixToPostfix(expr, isBin, isUn, getOpProps);
	char* prefix = postfixToPrefix(postfix, isBin, isUn);
	free(postfix);
	return prefix;
}
