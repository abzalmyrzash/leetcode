#define _CRT_SECURE_NO_WARNINGS
#include "..\readargs.h"
#include <limits.h>
#include <stdbool.h>

int divide(long long a, long long b) {
	long long c = 0;
	long long d, e;
	bool sign = (a >= 0) ^ (b > 0);
	if (a == INT_MIN && b == -1) return INT_MAX;
	a = (a >= 0) ? a : -a;
	b = (b >= 0) ? b : -b;
	if (b > a) return 0;
	while(a >= b) {
		if (b > a) break;
		d = b;
		e = 1;
		while (d <= a) {
			d <<= 1;
			e <<= 1;
		}
		d >>= 1;
		e >>= 1;
		a -= d;
		c |= e;
	}
	if (sign) c = -c;
    return c;
}

int main(int argc, char* argv[]) {
	int a, b;
	if (readArgs(argc, argv, "dd", &a, &b) == 1) return 1;
	printf("%d\n", divide(a, b));
	return 0;
}
