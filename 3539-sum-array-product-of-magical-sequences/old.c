#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9+7)

int combinations(int n, int r) {
	long long res = 1;
	if (r < n - r) r = n - r;
	int nr = n - r;
	int j = 2;
	for (int i = r + 1; i <= n; i++) {
		res *= i;
		while (j <= nr && res % j == 0) {
			res /= j;
			j++;
		}
		if (j > nr) res %= MODULO;
	}
	return res;
}

int distinctPermutations(int* arr, int n) {
	long long res = 1;
	int available = n;
	for (int i = 0; i < n; ) {
		int num = arr[i];
		int repetitions = 0;
		while(i < n && arr[i] == num) {
			repetitions++;
			i++;
		}
		res *= combinations(available, repetitions) % MODULO;
		available -= repetitions;
		res %= MODULO;
	}
	return res;
}

int popCount(long long mask) {
	int cnt = 0;
	if (mask) do {
		cnt++;
	} while (mask &= mask - 1);
	return cnt;
}

// m is size of magical sequence
// k is number of required set bits for a magical sequence
// nums points to array of numbers
// n is nums size
// a is index into nums
// seq points to array to store magical sequence
// i is index into seq
// p is array product of seq until i
// j is number of set bits
// carry is the carry
// carryCnt is number of set bits in carry

int recursion(int m, int k, int* nums, int n, int a, int* seq,
		int i, long long p, int j, long long carry, int carryCnt) {

	int sum = 0;
	int a2, j2, carry2Cnt;
	long long carry2;
	long long p2;
	int a0 = a;

	for (; a < n; a++) {
		int diff = a - a0;
		carry2 = carry + (1LL << diff);
		carry2Cnt = __builtin_popcount(carry2);
		j2 = j + carry2Cnt - carryCnt;
		carry2 >>= diff;
		carry2Cnt = __builtin_popcount(carry2);

		seq[i] = a;
		p2 = (p * nums[a]) % MODULO;

		if (i == m - 1) {
			if (j2 == k) {
				int perms = distinctPermutations(seq, m);
				p2 *= perms;
				p2 %= MODULO;
				sum += p2;
				sum %= MODULO;
			}
		}

		else {
			int rec = recursion(m, k, nums, n, a, seq, i + 1, p2, j2, carry2, carry2Cnt);
			sum += rec;
			sum %= MODULO;
		}
	}

	printf("a = %d, i = %d, j = %d, carry = %lld, sum = %d\n", a0, i, j, carry, sum);
	return sum;
}

#define MAX_N 50
#define MAX_M 30
#define MAX_K 30

int magicalSum(int m, int k, int* nums, int numsSize) {
	int seq[m];
	return recursion(m, k, nums, numsSize, 0, seq, 0, 1, 0, 0, 0);
}

int main(int argc, char* argv[]) {
	if (argc != 4) return 1;
	int m, k;
	sscanf(argv[1], "%d", &m);
	sscanf(argv[2], "%d", &k);
	int nums[30];
	int cnt = 0;
	int offset = 0;
	int charsRead;
	while (1 == sscanf(argv[3] + offset, "%*c%d%n", &nums[cnt], &charsRead)) {
		offset += charsRead;
		cnt++;
	}
	printf("%d\n", cnt);
	for (int i = 0; i < cnt; i++) printf("%d ", nums[i]);
	printf("\n");
	printf("%d\n", magicalSum(m, k, nums, cnt));
}
