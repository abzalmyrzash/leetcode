#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

char* map[8] = {
	"abc",
	"def",
	"ghi",
	"jkl",
	"mno",
	"pqrs",
	"tuv",
	"wxyz"
};

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** letterCombinations(char* digits, int* returnSize) {
	int cnt79 = 0;
	int len = 0;
	while (digits[len] != '\0') {
		if (digits[len] == '7' || digits[len] == '9') cnt79++;
		len++;
	}
	int nCombos = pow(4, cnt79) * pow(3, len - cnt79);
	printf("nCombos = %d\n", nCombos);
	char** res = malloc(nCombos * sizeof(char*));
	for (int i = 0; i < nCombos; i++) {
		res[i] = malloc(len + 1);
		res[i][len] = '\0';
	}
	int dist = nCombos;
	int cnt = 0;
	for (int i = 0; i < len; i++) {
		char digit = digits[i] - '2';
		char* letters = map[digit];
		int nLetters = strlen(letters);
		dist /= nLetters; // distance between each different letter
		printf("dist = %d\n", dist);
		int j = 0;
		while (j < nCombos) {
			int l = 0;
			for (int k = 0; k < nLetters; k++) {
				for (; l < (k+1)*dist; l++) {
					res[j+l][i] = letters[k];
				}
			}
			j+=l;
		}
	}
	*returnSize = nCombos;
	return res;
}

int main(int argc, char* argv[]) {
	if (argc != 2) return 1;
	int returnSize;
	char** letterCombos = letterCombinations(argv[1], &returnSize);
	for (int i = 0; i < returnSize; i++) {
		printf("%s\n", letterCombos[i]);
	}
}
