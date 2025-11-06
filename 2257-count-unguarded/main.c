#include "..\readargs.h"
#include <string.h>

int countUnguarded(int m, int n, int** guards, int gn, int* _,
		int** walls, int wn, int* __) {
	char grid[m][n];
	memset(grid, '.', sizeof grid);

	for (int i = 0; i < wn; i++) {
		const int row = walls[i][0];
		const int col = walls[i][1];
		grid[row][col] = 'W';
	}

	for (int i = 0; i < gn; i++) {
		const int row = guards[i][0];
		const int col = guards[i][1];
		grid[row][col] = 'G';
	}

	int res = m * n - gn - wn;

	for (int i = 0; i < gn; i++) {
		const int row = guards[i][0];
		const int col = guards[i][1];
		int x, y;

		x = col;

		for (y = row - 1; y >= 0; y--) {
			const char c = grid[y][x];
			if (c == 'W' || c == 'G') break;
			if (c == 'x') continue;
			grid[y][x] = 'x';
			res--;
		}

		for (y = row + 1; y < m; y++) {
			const char c = grid[y][x];
			if (c == 'W' || c == 'G') break;
			if (c == 'x') continue;
			grid[y][x] = 'x';
			res--;
		}

		y = row;

		for (x = col - 1; x >= 0; x--) {
			const char c = grid[y][x];
			if (c == 'W' || c == 'G') break;
			if (c == 'x') continue;
			grid[y][x] = 'x';
			res--;
		}

		for (x = col + 1; x < n; x++) {
			const char c = grid[y][x];
			if (c == 'W' || c == 'G') break;
			if (c == 'x') continue;
			grid[y][x] = 'x';
			res--;
		}
	}

	return res;
}

int main(int argc, char* argv[]) {
	int m, n;
	int guardsArr[100], guardsSize, wallsArr[100], wallsSize;
	readArgs(argc, argv, "dd#d#d", &m, &n,
			guardsArr, &guardsSize, wallsArr, &wallsSize);
	guardsSize /= 2;
	wallsSize /= 2;
	int *guards[guardsSize], *walls[wallsSize];
	for (int i = 0; i < guardsSize; i++) {
		guards[i] = guardsArr + i * 2;
	}
	for (int i = 0; i < wallsSize; i++) {
		walls[i] = wallsArr + i * 2;
	}
	printf("%d\n", countUnguarded(m, n, guards, guardsSize, NULL,
				walls, wallsSize, NULL));
	return 0;
}
