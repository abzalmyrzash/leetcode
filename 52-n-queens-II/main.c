#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int directions[8][2] = {
	{ 1, -1}, { 1, 0}, { 1, 1},
	{ 0, -1},          { 0, 1},
	{-1, -1}, {-1, 0}, {-1, 1}
};

#define MAX_N 9

bool board[MAX_N * MAX_N];
int attack[MAX_N * MAX_N];
 
int n, nn;

void setN(int n_) {
	n = n_;
	nn = n * n;
}

void placeQueen(int pos, bool remove) {
	board[pos] = !remove;
	int add = remove ? -1 : 1;
	int r = pos / n; // rank
	int f = pos % n; // file
	for (int i = 0; i < 8; i++) {
		int stepR = directions[i][0];
		int stepF = directions[i][1];
		int newR = r;
		int newF = f;
		for (int j = 1; j < n; j++) {
			newR += stepR;
			newF += stepF;
			if (newR < 0 || newF < 0 || newR >= n || newF >= n) break;
			attack[newR*n + newF] += add;
		}
	}
}

int dfs(int cnt, int pos) {
	if (cnt == n) {
		return 1;
	}
	int available = 0;
	for (int i = pos; i < nn; i++) {
		if (!board[i] && !attack[i]) available++;
	}
	if (available < n - cnt) return 0;
	int res = 0;
	for (int i = pos; i < nn; i++) {
		if (board[i] || attack[i]) continue;
		placeQueen(i, 0); // 0 means place
		res += dfs(cnt + 1, i + 1);
		placeQueen(i, 1); // 1 means remove
	}
	return res;
}

int totalNQueens(int n) {
	setN(n);
	memset(board, 0, sizeof(board));
	memset(attack, 0, sizeof(attack));
    return dfs(0, 0);
}

int main(int argc, char* argv[]) {
	if(argc != 2) return 1;
	int n;
	sscanf(argv[1], "%d", &n);
	printf("%d\n", totalNQueens(n));
	return 0;
}
