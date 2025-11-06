#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 30000

typedef struct {
	int idx[MAX_SIZE];
	int size;
	int fullPairs;
	int strLen;
} Stack;

Stack stack;

void stack_init() {
	stack.size = 0;
	stack.fullPairs = 0;
	stack.strLen = 0;
}

bool stack_push(char c) {
	if (c == '(') {
		stack.idx[stack.size++] = stack.strLen;
	}
	else {
		if (stack.size == 0) return false;
		stack.fullPairs++;
		stack.size--;
	}
	stack.strLen++;
	return true;
}

int stack_peek() {
	if (stack.size == 0) return -1;
	return stack.idx[stack.size - 1];
}

int getValidLen() {
	return stack.strLen - stack_peek() - 1;
}

int longestValidParentheses(char* s) {
	int max = 0;
	int n = strlen(s);
	int i = 0, validLen;
	stack_init();
	for (i = 0; i < n; i++) {
		if (!stack_push(s[i])) {
			stack_init();
			continue;
		}
		validLen = getValidLen();
		if (validLen > max) max = validLen;
	}
	return max;
}

int main(int argc, char* argv[]) {
	if (argc != 2) return 1;
	printf("%d\n", longestValidParentheses(argv[1]));
	return 0;
}
