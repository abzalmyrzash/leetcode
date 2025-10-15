#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int directions[8][2] = {
	{ 1, -1}, { 1, 0}, { 1, 1},
	{ 0, -1},          { 0, 1},
	{-1, -1}, {-1, 0}, {-1, 1}
};

#define MAX_N 9

bool board[MAX_N * MAX_N];
int attack[MAX_N * MAX_N];
 
int n, nn;

void setN(int n_) {
	n = n_;
	nn = n * n;
}

void placeQueen(int pos, bool remove) {
	board[pos] = !remove;
	int add = remove ? -1 : 1;
	int r = pos / n; // rank
	int f = pos % n; // file
	for (int i = 0; i < 8; i++) {
		int stepR = directions[i][0];
		int stepF = directions[i][1];
		int newR = r;
		int newF = f;
		for (int j = 1; j < n; j++) {
			newR += stepR;
			newF += stepF;
			if (newR < 0 || newF < 0 || newR >= n || newF >= n) break;
			attack[newR*n + newF] += add;
		}
	}
}

char*** getRes(int capacity) {
	char*** res = malloc(sizeof(char**) * capacity);
	res[0] = malloc(sizeof(char*) * n);
	for (int i = 0; i < n; i++) {
		res[0][i] = malloc(sizeof(char) * (n + 1));
		for (int j = 0; j < n; j++) {
			if (board[i*n + j]) {
				res[0][i][j] = 'Q';
			} else {
				res[0][i][j] = '.';
			}
		}
		res[0][i][n] = '\0';
	}
	return res;
}

void addRes(char**** res, int *size, int *capacity,
		char*** res2, int size2, int cap2) {
	if (*res == NULL) {
		*res = res2;
		*capacity = cap2;
		*size = size2;
	} else {
		int newSize = *size + size2;
		if (newSize > *capacity) {
			do *capacity *= 2; while (newSize > *capacity);
			*res = realloc(*res, sizeof(char**) * *capacity);
		}
		for (int i = 0; i < size2; i++) {
			(*res)[*size + i] = res2[i];
		}
		*size = newSize;
		free(res2);
	}
}

char*** dfs(int cnt, int pos, int* size, int* capacity) {
	char*** res = NULL;
	*size = 0;
	if (cnt == n) {
		*size = 1;
		*capacity = 8;
		return getRes(*capacity);
	}

	for (int i = pos; i < nn; i++) {
		if (board[i] || attack[i]) continue;
		fflush(stdout);
		placeQueen(i, 0); // 0 means place
		int size2, cap2;
		char*** res2 = dfs(cnt + 1, i + 1, &size2, &cap2);
		if (res2 != NULL) addRes(&res, size, capacity, res2, size2, cap2);
		placeQueen(i, 1); // 1 means remove
	}
	return res;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes) {
	int capacity = 256;
	setN(n);
	memset(board, 0, nn * sizeof(bool));
	memset(attack, 0, nn * sizeof(int));
	int cap;
	char*** res = dfs(0, 0, returnSize, &cap);
	if (res == NULL) res = malloc(sizeof(char**));
	*returnColumnSizes = malloc(sizeof(int) * *returnSize);
	for (int i = 0; i < *returnSize; i++) {
		(*returnColumnSizes)[i] = n;
	}
	return res;
}

int main(int argc, char* argv[]) {
	if(argc != 2) return 1;
	int n;
	sscanf(argv[1], "%d", &n);
	int size, *colSizes;
	char*** res = solveNQueens(n, &size, &colSizes);
	printf("Got here\n");
	for (int i = 0; i < size; i++) {
		printf("Solution %d:\n", i);
		for (int j = 0; j < n; j++) {
			printf("%s\n", res[i][j]);
		}
		printf("\n");
	}
	return 0;
}
