#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longestCommonPrefix(char** strs, int strsSize) {
	char* str = strs[0];
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		char c = str[i];
		for (int j = 1; j < strsSize; j++) {
			if (strs[j][i] != c) {
				str[i] = '\0';
				return str;
			}
		}
	}
	return str;
}

int main(int argc, char* argv[]) {
	if (argc == 1) return 1;
	printf("%s\n", longestCommonPrefix(argv + 1, argc - 1));
}
