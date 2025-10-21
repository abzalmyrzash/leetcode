#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void kmpTable(char* s, int len, int* T) {
	T[0] = -1;
	int i = 1, j = 0;
	while (i < len) {
		if (s[i] == s[j]) T[i] = T[j];
		else {
			T[i] = j;
			while (j >= 0 && s[i] != s[j]) {
				j = T[j];
			}
		}
		i++; j++;
	}
	// T[len] = j;
}

int strStr(char* hay, char* n) {
	int hayLen = strlen(hay);
	int nLen = strlen(n);
	int T[nLen];
	kmpTable(n, nLen, T);
	for (int i = 0; i < nLen; i++) {
		printf("%d ", T[i]);
	} printf("\n");
	int i = 0, j = 0;
	while (i < hayLen) {
		if (hay[i] == n[j]) {
			i++; j++;
			if (j == nLen) return i - j;
		} else {
			j = T[j];
			if (j < 0) {
				i++; j++;
			}
		}
	}
	return -1;
}

int main(int argc, char* argv[]) {
	if(argc != 3) {
		printf("format: program char* char*");
		return 1;
	}
	printf("%d\n", strStr(argv[1], argv[2]));
}
