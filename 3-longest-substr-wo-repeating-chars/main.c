#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int lengthOfLongestSubstring(char* s) {
	int seen[128] = {0};
	int i = 0, iStart = 0;
	char c = s[0];
	int max = 0, curLen = 0;
	while (c != '\0') {
		if (seen[c] <= iStart) {
			curLen++;
			if (curLen > max) max = curLen;
		}
		else {
			iStart = seen[c];
			curLen = i - iStart + 1;
		}
		seen[c] = i + 1;
		c = s[++i];
	}
    return max;
}

int main () {
	char s[10000];
	scanf("%s", s);
	printf("%d\n", lengthOfLongestSubstring(s));
}
