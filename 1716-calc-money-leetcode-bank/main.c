#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int totalMoney(int n) {
	int week = (n - 1) / 7;
	int day = n - week * 7;
	int weekTotal = week * (56 + 7 * (week - 1)) / 2;
	int dayTotal = day * (2 * week + (1 + day)) / 2;
	return weekTotal + dayTotal;
}

int main(int argc, char* argv[]) {
	if (argc != 2) return 1;
	int n;
	sscanf(argv[1], "%d", &n);
}
