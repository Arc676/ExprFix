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

#ifndef EXPRFIX_H
#define EXPRFIX_H

#include <stdio.h>
#include <string.h>

#include "structures.h"

#ifdef THREADSAFE
#define PARSE_TOKEN(expr, ptr) strtok_r(expr, " ", ptr)
#else
#define PARSE_TOKEN(expr, ptr) strtok(expr, " ")
#endif

typedef int IS_BINARY(char* c);

typedef int IS_UNARY(char* c);

typedef void OP_PROPERTIES(char* c, int* precedence, int* isLeftAssoc);

char* infixToPostfix(char* expr, IS_BINARY isBin, IS_UNARY isUn, OP_PROPERTIES getOpProps);

char* postfixToPrefix(char* expr, IS_BINARY isBin, IS_UNARY isUn);

char* infixToPrefix(char* expr, IS_BINARY isBin, IS_UNARY isUn, OP_PROPERTIES getOpProps);

#endif

#ifdef __cplusplus
}
#endif
