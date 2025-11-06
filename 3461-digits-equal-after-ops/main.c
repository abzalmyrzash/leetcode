#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool hasSameDigits(char* s) {
	int len = strlen(s);
    while(len > 2) {
		for (int i = 0; i < len - 1; i++) {
			s[i] = ((s[i] - '0' + s[i + 1] - '0') % 10) + '0';
		}
		len--;
	}
	return s[0] == s[1];
}

int main(int argc, char* argv[]) {
	printf("%d\n", hasSameDigits(argv[1]));
	return 0;
}
