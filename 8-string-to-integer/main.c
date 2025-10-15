#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

int myAtoi(char* s) {
	int res = 0;
	static const int powersOf10[10] = {
		1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
	};
	int i = 0;
	char c = s[0];

	// skip whitespace
	while (c == ' ') c = s[++i];

	// read sign
	int sign = 1;
	if (c == '-') {
		sign = -1;
		c = s[++i];
	}
	else if (c == '+') c = s[++i];
	// if non-digit character, return zero
	else if (c < '0' || c > '9') return 0;

	char digits[10];
	int cntDig = 0;
	// skip leading zeroes
	while (c == '0') c = s[++i];
	// check non digit
    if (c < '0' || c > '9') return 0;
	// read digits
	while (c >= '0' && c <= '9') {
		// if more than 10 digits, return max/min
		if (cntDig == 10) {
			if (sign == 1) return INT_MAX;
			else return INT_MIN;
		}
		digits[cntDig++] = c - '0';
		c = s[++i];
	}

	// add digits
	for (i = 0; i < cntDig-1; i++) {
		res += digits[cntDig - i - 1] * powersOf10[i];
	}
	// check overflow
	if (cntDig == 10) {
		if (digits[0] == 2 && res > INT_MAX - 2e9) {
			if (sign == 1) return INT_MAX;
			else return INT_MIN;
		} else if (digits[0] > 2) {
			if (sign == 1) return INT_MAX;
			else return INT_MIN;
		}
	}
	// add last digit
	res += digits[0] * powersOf10[i];

	// flip sign if minus
	res *= sign;
    return res;
}

int main(int argc, char* argv[]) {
	if (argc != 2) return 1;
	printf("%d\n", myAtoi(argv[1]));
}
