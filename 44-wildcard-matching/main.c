#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 2000
static char arr[MAX_LEN+1][MAX_LEN+1];
static int sLen, pLen;

bool isMatchRecursive(char* s, char* p, int i, int j) {
	if (arr[i][j] >= 0) return arr[i][j];
	char* ans = &arr[i][j];

	while(i < sLen) {
		if (p[j] == '*') {
			while(p[j] == '*') j++;
			if (j == pLen) return true;
			while (i < sLen) {
				if (isMatchRecursive(s, p, i, j)) {
					*ans = true;
					return *ans;
				}
				i++;
			}
			*ans = false;
			return *ans;
		}

		else if (p[j] == '?' || p[j] == s[i]) {
			i++;
			j++;
		}

		else {
			*ans = false;
			return *ans;
		}
	}

	while (j < pLen) {
		if (p[j] != '*') {
			*ans = false;
			return false;
		}
		j++;
	}

	*ans = true;
	return *ans;
}

bool isMatch(char* s, char* p) {
	sLen = strlen(s);
	pLen = strlen(p);
	for (int i = 0; i <= sLen; i++) {
		memset(arr + i, -1, (pLen+1) * sizeof(bool));
	}
	return isMatchRecursive(s, p, 0, 0);
}

int main(int argc, char* argv[]){
	if (argc != 3) return 1;
	printf("%d\n", isMatch(argv[1], argv[2]));

	return 0;
}
