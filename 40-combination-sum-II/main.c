#include "..\readargs.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 100
#define MAX_TARGET 30

int** res;
int size, cap;
int* colSizes;
bool map[MAX_N];

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

void dfs(int* nums, int n, int target, int i) {
	if (target < 0) return;
	if (target == 0) {
		int cnt = 0;
		for (int j = 0; j < i; j++) {
			cnt += map[j];
		}
		int* arr = malloc(cnt * sizeof(int));
		int m = 0;
		for (int j = 0; j < i; j++) {
			if (map[j]) {
				arr[m++] = nums[j];
			}
		}
		push_arr(arr, cnt);
		return;
	}
	if (i == n) {
		return;
	}

	int prev = -1;
	for (; i < n; i++) {
		int num = nums[i];
		if (num == prev) continue;
		prev = num;
		int q = target / num;
		map[i] = true;
		dfs(nums, n, target - num, i + 1);
		map[i] = false;
	}
}

int cmp(const void* a, const void* b) { 
	return *(int*)a - *(int*)b;
}

int** combinationSum2(int* nums, int n, int target, int* retSize, int** retColSizes) {
	// initialization
	cap = 256;
    res = malloc(cap * sizeof(int*));
	size = 0;
	colSizes = malloc(cap * sizeof(int));
	memset(map, 0, sizeof map);
	// sort to weed out duplicates easier
	qsort(nums, n, sizeof(int), cmp);
	// depth first search
	dfs(nums, n, target, 0);
	// return
	*retSize = size;
	*retColSizes = colSizes;
	return res;
}

int main(int argc, char* argv[]) {
	int nums[100], n, target;
	readArgs(argc, argv, "#dd", nums, &n, &target);
	int size, *colSizes;
	int** res = combinationSum2(nums, n, target, &size, &colSizes);
	for (int i = 0; i < size; i++) {
		int m = colSizes[i];
		for (int j = 0; j < m; j++) {
			printf("%d ", res[i][j]);
		} printf("\n");
	}
	return 0;
}
