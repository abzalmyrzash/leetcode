#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static char arr[20][20] = { {0} };
static int sLen, pLen;

bool isMatchRecursive(char* s, char* p, int i, int j) {
	if (arr[i][j] != 0) return arr[i][j] == 1;
	int i0 = i, j0 = j;
	char c = s[i], d = p[j];
	bool nextIsStar;
	while(c != '\0') {
		nextIsStar = ((j + 1 < pLen) && p[j + 1] == '*');
		if (c != d && d != '.' && !nextIsStar) {
			arr[i0][j0] = -1;
			return false;
		} 
		if (nextIsStar) {
			if (j + 2 == pLen) {
				if (d == '.') {
					arr[i0][j0] = true;
					return true;
				}
				while(c == d) c = s[++i];
				if (i == sLen) {
					arr[i0][j0] = true;
					return true;
				}
				arr[i0][j0] = -1;
				return false;
			}
			j += 2;
			while (c == d || d == '.') {
				if (isMatchRecursive(s, p, i, j)) {
					arr[i0][j0] = true;
					return true;
				}
				c = s[++i];
				if (c == '\0') goto checkLastStars;
			}
			d = p[j];
		}
		else {
			j++;
			if (j == pLen) {
				if(i == sLen - 1) {
					arr[i0][j0] = true;
					return true;
				}
				arr[i0][j0] = -1;
				return false;
			}
			d = p[j];
			c = s[++i];
		}
	}
checkLastStars:
	do {
		nextIsStar = ((j + 1 < pLen) && p[j + 1] == '*');
		j += 2;
	} while (nextIsStar && j < pLen);
    if (nextIsStar) {
		arr[i0][j0] = true;
		return true;
	}
	arr[i0][j0] = -1;
	return false;
}

bool isMatch(char* s, char* p) {
	sLen = strlen(s);
	pLen = strlen(p);
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			arr[i][j] = 0;
		}
	}
	return isMatchRecursive(s, p, 0, 0);
}

int main(int argc, char* argv[]){
	if (argc != 3) return 1;
	printf("%d\n", isMatch(argv[1], argv[2]));

	return 0;
}
