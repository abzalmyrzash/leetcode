#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 4463
 
char* countAndSay(int n) {
	char* str = calloc(MAX_SIZE, sizeof(char));
	str[0] = '1';
	if (n == 1) return str;
	char* str2 = malloc(MAX_SIZE * sizeof(char));
	int len = 1;
	for (int i = 2; i <= n; i++) {
		//printf("%s\n", str);
		int len2 = 0;
		char c = str[0];
		int cnt = 1;
		for (int j = 1; j <= len; j++) {
			if (str[j] == c) {
				cnt++;
			} else {
				//len2 += sprintf(str2 + len2, "%d", cnt);
				str2[len2++] = cnt + '0';
				str2[len2++] = c;
				c = str[j];
				cnt = 1;
			}
		}
		memcpy(str, str2, len2);
		str[len2] = '\0';
		len = len2;
	}
	return str;
}

int main (int argc, char* argv[]) {
	if (argc != 2) return 1;
	int n;
	sscanf(argv[1], "%d", &n);
	char* str = countAndSay(n);
	printf("%s\n%zu\n", str, strlen(str));
}
