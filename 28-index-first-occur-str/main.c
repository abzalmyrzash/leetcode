#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int strStr(char* h, char* n) {
	int i, j, f, f2;
	for (i = 0; h[i] != '\0';) {
		if (h[i] == n[0]) {
		search:
			f = i;
			f2 = 0;
			j = 0;
			do {
				i++; j++;
				if (n[j] == '\0') return f;
				if (h[i] == n[0] && f2 == 0) {
					f2 = i;
				}
			} while(h[i] == n[j]);
			if (f2 > 0) {
				i = f2;
				goto search;
			}
		} else {
			i++;
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
