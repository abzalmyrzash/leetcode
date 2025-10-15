#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>

int reverse(int x){
	int res = 0;
	while(x) {
		char digit = x % 10;
		if (abs(res) > 214748364) return 0;
		res = res * 10 + digit;
		x /= 10;
	}
	return res;
}

int main(int argc, char* argv[]) {
	if (argc != 2) return 1;
	int x;
	sscanf(argv[1], "%d", &x);
	printf("%d\n", reverse(x));
	return 0;
}
