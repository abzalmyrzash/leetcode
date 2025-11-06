#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

bool** _splitSum(int sum, int start, int remaining,
		int* retSize, int* retCap) {
	bool** res = NULL;
	int curSize = 0;
	int curCap = 0;

	for (int i = start; i * 2 < remaining; i++) {
		int size, cap;
		bool** arr = _splitSum(sum, i + 1, remaining - i,
				&size, &cap);

		for (int j = 0; j < size; j++) {
			arr[j][i - 1] = true;
		}

		if (res == NULL) {
			res = arr;
			curSize = size;
			curCap = cap;
			continue;
		}

		int newSize = curSize + size;
		if (newSize > curCap) {
			do {
				curCap *= 2;
			} while (newSize > curCap);
			res = realloc(res, curCap * sizeof(bool*));
		}
		memcpy(res + curSize, arr, size * sizeof(bool*));
		curSize = newSize;
	}

	if (curSize == curCap) {
		curCap++;
		res = realloc(res, curCap * sizeof(bool*));
	}

	res[curSize] = calloc(sum, sizeof(bool));
	res[curSize][remaining - 1] = true;
	curSize++;
	*retCap = curCap;
	*retSize = curSize;

	return res;
}

bool** splitSum(int sum, int* retSize) {
	int cap;
	return _splitSum(sum, 1, sum, retSize, &cap);
}

void swap(char* nums, int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}
void reverse(char* nums, int start, int numsSize) {
    int i = start, j = numsSize - 1;
    while (i < j) {
        swap(nums, i, j);
        i++;
        j--;
    }
}
bool nextPermutation(char* nums, char numsSize) {
    int i = numsSize - 2;
    while (i >= 0 && nums[i + 1] <= nums[i]) {
        i--;
    }
    if (i >= 0) {
        int j = numsSize - 1;
        while (nums[j] <= nums[i]) {
            j--;
        }
        swap(nums, i, j);
    }
    reverse(nums, i + 1, numsSize);
	return i >= 0;
}

int cmp(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}

int powersOfTen[10] = {
	1, 10, 100, 1000,
	10000, 100000, 1000000,
	10000000, 100000000, 1000000000
};

// n - number of digits
int* nDigitBeautifulNumbers(int n, int* retSize, int* retCap) {
	int BSize;
	bool** B = splitSum(n, &BSize);
	int *res = NULL;
	int curSize = 0;
	int curCap = 0;
	for (int i = 0; i < BSize; i++) {
		char A[n];
		int cnt = 0;
		for (int j = 0; j < n; j++) {
			if (B[i][j]) {
				for (int k = 0; k <= j; k++) {
					A[cnt + k] = j + 1;
				}
				cnt += j + 1;
			}
		}
		do {
			int bNum = 0;
			for (int j = 0; j < cnt; j++) {
				bNum += A[j] * powersOfTen[cnt - j - 1];
			}
			if (curSize >= curCap) {
				if (curCap == 0) curCap = 2;
				else do {
					curCap *= 2;
				} while(curSize >= curCap);
				res = realloc(res, curCap * sizeof(int));
			}
			res[curSize++] = bNum;
		} while(nextPermutation(A, cnt));
	}
	qsort(res, curSize, sizeof(int), cmp);
	*retSize = curSize;
	*retCap = curCap;
	return res;
}

int* bNums = NULL;
int bNumsSize = 0;
void getBeautifulNumbers() {
	static bool firstTime = true;
	if (!firstTime) return;
	firstTime = false;
	int curCap = 0;
	for (int i = 1; i <= 6; i++) {
		int size, cap;
		int* arr = nDigitBeautifulNumbers(i, &size, &cap);
		if (bNums == NULL) {
			bNums = arr;
			bNumsSize = size;
			curCap = cap;
			continue;
		}
		int newSize = bNumsSize + size;
		if (newSize > curCap) {
			do {
				curCap *= 2;
			} while (newSize > curCap);
			bNums = realloc(bNums, curCap * sizeof(int));
		}
		memcpy(bNums + bNumsSize, arr, size * sizeof(int));
		bNumsSize = newSize;
	}
}

// find next beautiful number greater than n
int nextBeautifulNumber(int n) {
	if (n < 1) return 1;
	if (n >= 666666) return 1224444;
	getBeautifulNumbers();
	int low = 0;
	int high = bNumsSize - 1;
	int i;
	while (low <= high) {
		i = low + (high - low) / 2;
		if (bNums[i] == n) break;
		if (bNums[i] < n) {
			if (i < bNumsSize && bNums[i + 1] > n) break;
			low = i + 1;
		} else {
			high = i - 1;
		}
	}
	return bNums[i + 1];
}

int main(int argc, char* argv[]) {
	int n;
	sscanf(argv[1], "%d", &n);
	getBeautifulNumbers();
	printf("%d\n", bNumsSize);
	for (int i = 0; i < bNumsSize; i++) {
		printf("%d ", bNums[i]);
	} printf("\n");
	printf("%d\n", nextBeautifulNumber(n));
	return 0;
}
