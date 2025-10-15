#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int maxcmp(const void* a, const void* b){
	if (*(int*)a < *(int*)b) return 1;
	if (*(int*)a > *(int*)b) return -1;
	return 0;
}

long long maxSum(long long* spellSum, long long* cache, int size, int i) {
	if (i >= size) return 0;
	if (cache[i] >= 0) return cache[i];
	long long max = 0;
	for (int j = 0; j < 3; j++) {
		int k = i + j;
		if (k == size) break;
		long long sum = spellSum[k] + maxSum(spellSum, cache, size, k + 3);
		if (sum > max) max = sum;
	}
	cache[i] = max;
	return max;
}

long long maxTotalOfPartition(int* power, int powerSize) {
	int max = power[0], min = power[powerSize - 1];
	int rangeLength = max - min + 1;
	long long spellSum[rangeLength];
	memset(spellSum, 0, sizeof spellSum);
	for (int i = 0; i < powerSize; i++) {
		spellSum[power[i] - min] += power[i];
	}

	long long cache[rangeLength];
	memset(cache, -1, sizeof cache);
	return maxSum(spellSum, cache, rangeLength, 0);
}

long long partition(int* power, int powerSize) {
	long long total = 0;
	int i;
	for (i = 1; i < powerSize; i++) {
		if (power[i] < power[i-1] - 2) {
			total += partition(power + i, powerSize - i);
			break;
		}
	}
	total += maxTotalOfPartition(power, i);

	return total;
}

long long maximumTotalDamage(int* power, int powerSize) {
	qsort(power, powerSize, sizeof(int), maxcmp);
	return partition(power, powerSize);
}

int main(int argc, char* argv[]) {
	if (argc == 1) return 1;
	int power[argc - 1];
	for (int i = 1; i < argc; i++) {
		sscanf(argv[i], "%d", &power[i - 1]);
	}
	printf("%lld\n", maximumTotalDamage(power, argc - 1));
	return 0;
}
