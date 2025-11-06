#include "..\readargs.h"
#include <stdlib.h>

#define MAX_NUM 50

typedef struct {
	int num;
	int freq;
} NumFreq;

NumFreq freq[MAX_NUM];

int cmp(const void* a, const void* b) {
	NumFreq* A = (NumFreq*)a;
	NumFreq* B = (NumFreq*)b;
	if (B->freq == A->freq) {
		return B->num - A->num;
	}
	return B->freq - A->freq;
}

void swapFreq(int i, int j) {
	NumFreq tmp = freq[i];
	freq[i] = freq[j];
	freq[j] = tmp;
}

int xSum(int x) {
	int sum = 0;
	for (int i = 0; i < x; i++) {
		sum += freq[i].num * freq[i].freq;
	}
	return sum;
}

int* findXSum(int* nums, int n, int k, int x, int* retSize) {
	*retSize = n - k + 1;
	int* res = malloc(*retSize * sizeof(int));

	for (int i = 0; i < MAX_NUM; i++) {
		freq[i].num = i + 1;
		freq[i].freq = 0;
	}

	for (int i = 0; i < k; i++) {
		int idx = nums[i] - 1;
		freq[idx].freq++;
	}

	qsort(freq, MAX_NUM, sizeof(NumFreq), cmp);

	res[0] = xSum(x);

    for (int i = 1; i <= n - k; i++) {
		int oldNum = nums[i - 1];
		int newNum = nums[i + k - 1];

		for (int i = 0; i < MAX_NUM; i++) {
			if (freq[i].num == oldNum) {
				int f = --freq[i].freq;
				while (i < MAX_NUM - 1) {
					int nextF = freq[i + 1].freq;
					if (nextF > f) {
						swapFreq(i, i + 1);
						i++;
					} else if (nextF == f &&
							freq[i + 1].num > oldNum) {
						swapFreq(i, i + 1);
						i++;
					} else {
						break;
					}
				}
				break;
			}
		}

		for (int i = 0; i < MAX_NUM; i++) {
			if (freq[i].num == newNum) {
				int f = ++freq[i].freq;
				while (i > 0) {
					int prevF = freq[i - 1].freq;
					if (prevF < f) {
						swapFreq(i, i - 1);
						i--;
					} else if (prevF == f &&
							freq[i - 1].num < newNum) {
						swapFreq(i, i - 1);
						i--;
					} else {
						break;
					}
				}
				break;
			}
		}

		res[i] = xSum(x);
	}

	return res;
}

int main(int argc, char* argv[]) {
	int nums[100], n, k, x;
	readArgs(argc, argv, "#ddd", nums, &n, &k, &x);
	int size;
	int* res = findXSum(nums, n, k, x, &size);
	for (int i = 0; i < size; i++) {
		printf("%d ", res[i]);
	} printf("\n");
	return 0;
}
