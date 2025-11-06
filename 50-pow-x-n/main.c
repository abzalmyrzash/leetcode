#include <stdio.h>
#include <limits.h>

double myPow(double x, int n) {
	if (n == 0) return 1;

    unsigned int absN;
	if (n >= 0 || n == INT_MIN) {
		absN = n;
	} else {
		absN = -n;
	}

	double y = x;

	if (absN > 1) {
		unsigned long long i = 2;
		int cntBits = 1;
		while (i <= absN) {
			cntBits++;
			i <<= 1;
		}
		//printf("%d\n", cntBits);

		double exp[cntBits];
		cntBits = 0;
		i = 2;
		while (i <= absN) {
			y *= y;
			exp[cntBits++] = y;
			//printf("%lf\n", y);
			i <<= 1;
		}

		if (absN & 1) y = x;
		else y = 1;
		absN >>= 1;
		for (int j = 0; j < cntBits; j++) {
			if (absN & 1) y *= exp[j];
			absN >>= 1;
		}
	}

	if (n < 0) y = 1 / y;
	return y;
}

int main(int argc, char* argv[]) {
	if (argc != 3) return 1;
	double x;
	int n;
	sscanf(argv[1], "%lf", &x);
	sscanf(argv[2], "%d", &n);
	printf("%lf\n", myPow(x, n));
}
