#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char str[16];
static char** arr;
static int cnt = 0;

void dfs(int n, int m, int i) {
	if (n == 0) {
		char* copy = malloc(i + 1);
		memcpy(copy, str, i);
		copy[i] = '\0';
		arr[cnt++] = copy;
		return;
	}
	if (m < n) {
		str[i] = '(';
		dfs(n, m + 1, i + 1);
	}
	if (m > 0) {
		str[i] = ')';
		dfs(n - 1, m - 1, i + 1);
	}
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** generateParenthesis(int n, int* returnSize) {
	int capacity = 1430;
	arr = malloc(sizeof(char*) * capacity);
    cnt = 0;
	dfs(n, 0, 0);
	*returnSize = cnt;
	return arr;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("format: program int\n");
		return 1;
	}
	int n;
	sscanf(argv[1], "%d", &n);
	int size;
	char** arr = generateParenthesis(n, &size);
	for (int i = 0; i < size; i++) {
		printf("%s\n", arr[i]);
	} printf("\n");
	printf("%d\n", size);
}
