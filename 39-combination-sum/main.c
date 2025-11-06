#include "..\readargs.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 30
#define MAX_TARGET 40

int** res;
int size, cap;
int* colSizes;

void push_arr(int* arr, int n) {
	if (size == cap) {
		cap *= 2;
		res = realloc(res, cap * sizeof(int*));
		colSizes = realloc(colSizes, cap * sizeof(int));
	}
	res[size] = arr;
	colSizes[size] = n;
	size++;
}

void dfs(int* nums, int n, int target, int i, int* cnt) {
	if (target == 0) {
		int totalCnt = 0;
		for (int j = 0; j < n; j++) {
			totalCnt += cnt[j];
		}
		int* arr = malloc(totalCnt * sizeof(int));
		int m = 0;
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < cnt[j]; k++) {
				arr[m++] = nums[j];
			}
		}
		push_arr(arr, totalCnt);
		return;
	}
	if (i == n) {
		return;
	}

	for (; i < n; i++) {
		int num = nums[i];
		int q = target / num;
		for (int j = 1; j <= q; j++) {
			cnt[i] = j;
			dfs(nums, n, target - j * num, i + 1, cnt);
			cnt[i] = 0;
		}
	}
}

int** combinationSum(int* nums, int n, int target, int* retSize, int** retColSizes) {
	cap = 256;
    res = malloc(cap * sizeof(int*));
	size = 0;
	colSizes = malloc(cap * sizeof(int));
	int cnt[n];
	memset(cnt, 0, sizeof cnt);
	dfs(nums, n, target, 0, cnt);
	*retSize = size;
	*retColSizes = colSizes;
	return res;
}

int main(int argc, char* argv[]) {
	int nums[100], n, target;
	readArgs(argc, argv, "#dd", nums, &n, &target);
	int size, *colSizes;
	int** res = combinationSum(nums, n, target, &size, &colSizes);
	for (int i = 0; i < size; i++) {
		int m = colSizes[i];
		for (int j = 0; j < m; j++) {
			printf("%d ", res[i][j]);
		} printf("\n");
	}
	return 0;
}
