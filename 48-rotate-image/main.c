#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// assigns *a = b and returns old value of *a
// named so because it's like post-increment
int postAssign(int* a, int b) {
	int c = *a;
	*a = b;
	return c;
}

// rotate n by n matrix
void rotate(int** matrix, int n, int* whatever) {
	int tmp;
	for (int i = 0; i < n / 2; i++) {
		for (int j = 0; j < (n + 1) / 2; j++) {
			tmp = postAssign(&matrix[j][n - i - 1], matrix[i][j]);
			tmp = postAssign(&matrix[n - i - 1][n - j - 1], tmp);
			tmp = postAssign(&matrix[n - j - 1][i], tmp);
			matrix[i][j] = tmp;
		}
	}
}

int main(int argc, char* argv[]) {
	char* s = argv[1];
	int sLen = strlen(s);

	int numRows = 0;
	for (int i = 1; i < sLen - 1; i++) {
		if (s[i] == '[') {
			numRows++;
		}
	}
	
	int numCols = 1;
	for (int i = 2; s[i] != ']'; i++) {
		if (s[i] == ',') {
			numCols++;
		}
	}

	printf("%dx%d\n", numRows, numCols);

	int** matrix = malloc(numRows * sizeof(int*));
	int* matrixColSize = malloc(numRows * sizeof(int));
	for (int i = 0; i < numRows; i++) {
		matrixColSize[i] = numCols;
	}

	for (int i = 0; i < numRows; i++) {
		while (*s != '[') s++;
		while (*s == '[') s++;
		int* row = malloc(numCols * sizeof(int));
		matrix[i] = row;
		for (int j = 0; j < numCols; j++) {
			int charsRead;
			sscanf(s, "%d%n", &row[j], &charsRead);
			s += charsRead + 1;
		}
	}

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	rotate(matrix, numRows, matrixColSize);

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}

	return 0;
}
