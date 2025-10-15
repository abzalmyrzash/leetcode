#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char* convert(char* s, int numRows) {
	int len = strlen(s);
	if (numRows >= len || numRows == 1) return s;
	char* res = malloc(len + 1);
	int iRes = 0;
	int colDiff = numRows * 2 - 2;
	for (int row = 0; row < numRows; row++) {
		int i = row;
		bool middle = false;
		int diff;
		while (1) {
			res[iRes++] = s[i];
			if (row == 0 || row == numRows - 1) {
				i += colDiff;
				middle = false;
			} else {
				if (!middle) {
					middle = true;
					i += colDiff - row * 2;
				} else {
					middle = false;
					i += row * 2;
				}
			}
			if (i >= len) break;
		}
	}
	res[len] = '\0';
	return res;
}

int main(int argc, char* argv[]) {
	if (argc != 3) return 1;
	char *s = argv[1];
	int numRows;
	sscanf(argv[2], "%d", &numRows);
	printf("%s\n", convert(s, numRows));
	return 0;
}
