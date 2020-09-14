// Copyright (C) 2019-20 Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

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

/**
 * Utility function; determines whether a string describes a binary
 * operator. This should be implemented by the caller and passed to the
 * conversion methods.
 * @param c Token string
 * @return Integer representation of whether the string is a binary operator
 */
typedef int IS_BINARY(char* c);

/**
 * Utility function; determines whether a string describes a unary
 * operator. This should be implemented by the caller and passed to the
 * conversion methods.
 * @param c Token string
 * @return Integer representation of whether the string is a unary operator
 */
typedef int IS_UNARY(char* c);

/**
 * Utility function; determines the properties of an operator
 * @param c Operator
 * @param precedence Pointer to integer in which to store the operator's precedence level
 * @param isLeftAssoc Pointer to integer in which to store whether the operator is left associative
 */
typedef void OP_PROPERTIES(char* c, int* precedence, int* isLeftAssoc);

/**
 * Converts an infix expression to a postfix expression
 * @param expr Expression to convert
 * @param isBin Function to identify binary operators in the expression
 * @param isUn Function to identify unary operators in the expression
 * @param getOpPropos Function to determine operator properties
 * @return A newly allocated string containing the postfix representation of the given expression
 */
char* infixToPostfix(char* expr, IS_BINARY isBin, IS_UNARY isUn, OP_PROPERTIES getOpProps);

/**
 * Converts a postfix expression to a prefix expression
 * @param expr Expression to convert
 * @param isBin Function to identify binary operators in the expression
 * @param isUn Function to identify unary operators in the expression
 * @param getOpPropos Function to determine operator properties
 * @return A newly allocated string containing the prefix representation of the given expression
 */
char* postfixToPrefix(char* expr, IS_BINARY isBin, IS_UNARY isUn);

/**
 * Converts an infix expression to a prefix expression
 * @param expr Expression to convert
 * @param isBin Function to identify binary operators in the expression
 * @param isUn Function to identify unary operators in the expression
 * @param getOpPropos Function to determine operator properties
 * @return A newly allocated string containing the prefix representation of the given expression
 */
char* infixToPrefix(char* expr, IS_BINARY isBin, IS_UNARY isUn, OP_PROPERTIES getOpProps);

#endif

#ifdef __cplusplus
}
#endif
