#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define MIN(A, B) ((A) < (B) ? (A) : (B))

char* longestPalindrome(char* s) {
	int len = strlen(s);
	int iPal = 0, maxPalLen = 1;
	for (int pMid = 1; pMid <= len - 1; pMid++) {
		int oddPalLen = 1, evenPalLen = 0;
		int maxHalfLen = MIN(pMid, len - pMid);
		for (int i = 1; i <= maxHalfLen; i++) {
			if (s[pMid - i] == s[pMid + i]) {
				oddPalLen += 2;
			} else break;
		}
		for (int i = 1; i <= maxHalfLen; i++) {
			if (s[pMid - i] == s[pMid + i - 1]) {
				evenPalLen += 2;
			} else break;
		}
		int foundPalLen = MAX(oddPalLen, evenPalLen);
		if (foundPalLen > maxPalLen) {
			maxPalLen = foundPalLen;
			iPal = pMid - foundPalLen / 2;
		}
	}
	s[iPal + maxPalLen] = '\0';
	return s + iPal;
}

int main(int argc, char* argv[]) {
	if (argc != 2) return 1;
	printf("%s\n", longestPalindrome(argv[1]));
	return 0;
}
