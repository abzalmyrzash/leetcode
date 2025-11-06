#include "..\readargs.h"

int minCost(char* colors, int* neededTime, int n) {
	int first = 0;
	int max = 0;
	int sum = 0;
	for (int i = 1; i < n; i++) {
		if (colors[i] == colors[i - 1]) {
			if (neededTime[i] > neededTime[max])
				max = i;
		} else {
			for (int j = first; j < i; j++) {
				if (j == max) continue;
				sum += neededTime[j];
			}
			first = i;
			max = i;
		}
	}
	for (int j = first; j < n; j++) {
		if (j == max) continue;
		sum += neededTime[j];
	}
	return sum;
}

int main(int argc, char* argv[]) {
	char* str;
	int nums[100], n;
	readArgs(argc, argv, "s#d", &str, nums, &n);
	for (int i = 0; i < n; i++) {
		printf("%d ", nums[i]);
	} printf("\n");
	printf("%d\n", minCost(str, nums, n));
	return 0;
}
