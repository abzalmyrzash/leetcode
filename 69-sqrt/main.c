#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int mySqrt(int x) {
	int low = 0;
	int high = x;
	long long n;
	long long sqr;
	while (low <= high) {
		n = low + (high - low) / 2;
		sqr = n * n;
		if (sqr == x) {
			return n;
		}
		if (sqr < x) {
			if (sqr + 2 * n + 1 > x) {
				return n;
			}
			low = n + 1;
		}
		else {
			high = n - 1;
		}
	}
	return n;
}

int main (int argc, char* argv[]) {
	if (argc != 2) return 1;
	int x;
	sscanf(argv[1], "%d", &x);
	printf("%d\n", mySqrt(x));
	
	return 0;
}
