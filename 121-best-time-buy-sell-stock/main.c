#define _CRT_SECURE_NO_WARNINGS
#include "..\readargs.h"
#include <limits.h>

int maxProfit(int* prices, int n) {
    int maxProf = 0;
	int min = prices[0];
	for (int i = 1; i < n; i++) {
		if (prices[i] < min) min = prices[i];
		else {
			int profit = prices[i] - min;
			if (profit > maxProf) maxProf = profit;
		}
	}
	return maxProf;
}

int main(int argc, char* argv[]) {
	int prices[100], n;
	readArgs(argc, argv, "#d", prices, &n);
	printf("%d\n", maxProfit(prices, n));
	return 0;
}
