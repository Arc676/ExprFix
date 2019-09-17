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

void usage() {
	fprintf(stderr, "Usage: exprfix mode expr\nPass expression as single argument\nModes: 0 - infix->postfix, 1 - postfix->prefix, 2 - infix->prefix\n");
}

int isBin(char* token) {
	char c = token[0];
	return c == '+' || c == '-' || c == '*' || c == '/';
}

int isUn(char* token) {
	return token[0] == '~';
}

void getOpProps(char* token, int* prec, int* left) {
	*left = 1;
	switch (token[0]) {
	case '+':
		*prec = 8;
		break;
	case '-':
		*prec = 7;
		break;
	case '*':
		*prec = 10;
		break;
	case '/':
		*prec = 9;
		break;
	default:
		*prec = *left = 0;
	}
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		usage();
		return 1;
	}
	int mode = (int)strtol(argv[1], (char**)NULL, 0);
	char* expr = argv[2];
	char* output;
	switch (mode) {
	case 0:
		output = infixToPostfix(expr, isBin, isUn, getOpProps);
		break;
	case 1:
		output = postfixToPrefix(expr, isBin, isUn);
		break;
	case 2:
		output = infixToPrefix(expr, isBin, isUn, getOpProps);
		break;
	default:
		usage();
		return 1;
	}
	printf("%s\n", output);
	free(output);
	return 0;
}
