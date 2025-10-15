#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MOD (int)(1e9+7)

#define MAX_N 50
#define MAX_M 30
#define MAX_K 30

int Pascal[MAX_M + 1][MAX_M + 1];
int powers[MAX_N][MAX_M + 1];
bool isPascalCalculated = false;

void calcPascal() {
	for (int i = 0; i <= MAX_M; i++) {
		Pascal[i][0] = Pascal[i][i] = 1;
		for (int j = 1; j <= i/2; j++) {
			Pascal[i][j] = (Pascal[i-1][j-1] + Pascal[i-1][j]);
            Pascal[i][i-j] = Pascal[i][j];
		}
	}
	isPascalCalculated = true;
}

void calcPowers(int m, int* nums, int n) {
	for (int i = 0; i < n; i++) {
		powers[i][0] = 1;
		long long num = nums[i];
		for (int j = 1; j <= m; j++) {
			powers[i][j] = (powers[i][j-1] * num) % MOD;
		}
	}
}

// m is size of magical sequence
// k is number of required set bits for a magical sequence
// nums points to array of numbers
// n is nums size
// pos is index into nums
// chosen is number of chosen indices
// prod is array product of seq until i
// set is number of set bits
// carry is the carry

// first index is position in nums
// second index is number of chosen indices
// third index is number of set bits
// fourth index is the carry
int dp[MAX_N + 1][MAX_M + 1][MAX_K + 1][MAX_M + 1];

int dfs(int m, int k, int* nums, int n, int pos, int chosen, int set, int carry) {
	int* dp1 = &dp[pos][chosen][set][carry];
	if (*dp1 >= 0) return *dp1;
	if (chosen > m) return *dp1 = 0;
	if (chosen == m) {
		return *dp1 = (set == k);
	} else if (pos >= n) {
		return *dp1 = 0;
	}
	int remaining = m - chosen;
	int chosen2, set2, carry2;
	int carryCnt = __builtin_popcount(carry);
	unsigned int sum = 0;
	long long prod, dp2;
	for (int i = 0; i <= remaining; i++) {
		chosen2 = chosen + i;
		carry2 = carry + i;
		bool bitSet = carry2 & 1;
		set2 = set + carry2;
		carry2 >>= 1;
		dp2 = dfs(m, k, nums, n, pos + 1, chosen2, set2, carry2);
		prod = (dp2 * powers[pos][i]) % MOD;
		prod = (prod * Pascal[remaining][i]) % MOD;
		sum = (sum + prod) % MOD;
	}
	return *dp1 = sum;
}

int magicalSum(int m, int k, int* nums, int n) {
	// calculate Pascal if it hasn't been
	if (!isPascalCalculated) calcPascal();
	calcPowers(m, nums, n);
	// init dp
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			for (int l = 0; l <= m; l++) {
				memset(dp[i][j][l], -1, sizeof(int)*(m + 1));
			}
		}
	}
	return dfs(m, k, nums, n, 0, 0, 0, 0);
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
	printf("\n\n");
	printf("%d\n", magicalSum(m, k, nums, cnt));
}
