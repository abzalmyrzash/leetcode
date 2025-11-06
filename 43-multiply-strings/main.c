#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* multiply(char* num1, char* num2) {
	int len1 = strlen(num1);
	int len2 = strlen(num2);
	int maxSize = len1 + len2 + 1;
	char* res = malloc(maxSize);
	memset(res, 0, maxSize);
	for (int i = 0; i < len1; i++) {
		char d1 = num1[len1 - i - 1] - '0';
		for (int j = 0; j < len2; j++) {
			char d2 = num2[len2 - j - 1] - '0';
			int k = i + j;
			int mult = d1 * d2;
			res[k] += mult % 10;
			_Bool carry = res[k] >= 10;
			res[k] %= 10;
			res[++k] += mult / 10 + carry;
			while ((carry = res[k] >= 10)) {
				res[k] %= 10;
				res[++k] += carry;
			}
		}
	}
	int i = maxSize - 1;
	while(i > 0 && res[i] == 0) i--;
	int len = i + 1;
	while (i >= 0) {
		res[i] += '0';
		i--;
	}
	// reverse
	for (int i = 0; i < len / 2; i++) {
		char tmp = res[i];
		res[i] = res[len - i - 1];
		res[len - i - 1] = tmp;
	}
	return res;
}

int main(int argc, char* argv[]) {
	if (argc != 3) return 1;
	printf("%s\n", multiply(argv[1], argv[2]));
}
