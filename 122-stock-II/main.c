#define _CRT_SECURE_NO_WARNINGS
#include "..\readargs.h"
#include <limits.h>

int maxProfit(int* prices, int n) {
	int total = 0;
	int buyDay = -1;
	int i, profit;
	for (i = 0; i < n - 1; i++) {
		if (prices[i] < prices[i + 1]) {
			buyDay = i;
			i++;
			break;
		}
	}
	if (buyDay == -1) return 0;
//	printf("buy day = %d\n", buyDay);
	for (; i < n - 1; i++) {
		if (prices[i] > prices[i + 1]) {
			profit = prices[i] - prices[buyDay];
			total += profit;
//			printf("sell day = %d\n", i);
//			printf("profit = %d\n", profit);
			buyDay = i + 1;
//			printf("buy day = %d\n", buyDay);
		}
	}
	profit = prices[i] - prices[buyDay];
	total += profit;
	return total;
}

int main(int argc, char* argv[]) {
	int prices[100], n;
	readArgs(argc, argv, "#d", prices, &n);
	printf("%d\n", maxProfit(prices, n));
	return 0;
}
