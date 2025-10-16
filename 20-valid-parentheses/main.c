#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum : char {
	ROUND,
	SQUARE,
	CURLY
} Bracket;

bool isValid(char* s) {
	int len = strlen(s);
	Bracket stack[len];
	int cnt = 0;
    while(*s != '\0') {
		switch(*s) {
			case '(':
				stack[cnt++] = ROUND;
				break;
			case ')':
				if (cnt == 0 || stack[--cnt] != ROUND) return false;
				break;
			case '[':
				stack[cnt++] = SQUARE;
				break;
			case ']':
				if (cnt == 0 || stack[--cnt] != SQUARE) return false;
				break;
			case '{':
				stack[cnt++] = CURLY;
				break;
			case '}':
				if (cnt == 0 || stack[--cnt] != CURLY) return false;
				break;
		}
		s++;
	}
	return cnt == 0;
}


int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("format: program char*");
		return 1;
	}
	printf("%d", isValid(argv[1]));
	return 0;
}
