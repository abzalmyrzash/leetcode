#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	char row;
	char col;
	char sqr;
} Position;

bool taken[9][9][9];
char takenCnt[9][9];
char cache[9][9][9];
Position solveQueue[81];
int solveQSize;
int nonEmpty;

void copyBoard(char copy[][9], char** board) {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) 
			copy[i][j] = board[i][j];
}

void restoreBoard(char** board, char copy[][9]) {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) 
			board[i][j] = copy[i][j];
}

int getSquare(int row, int column) {
	return (row / 3) * 3 + column / 3;
	// PS: (row / 3) * 3 does not equal row because of integer division
}

void takeRow(char** board, int row, int val);
void takeColumn(char** board, int col, int val);
void takeSquare(char** board, int sqr, int val);
void takeNeighbors(char** board, int row, int col, int sqr, int val);

void solveCells(char** board) {
	for(int i = 0; i < solveQSize; i++) {
		int row = solveQueue[i].row;
		int col = solveQueue[i].col;
		int sqr = solveQueue[i].sqr;
		for (int val = 0; val < 9; val++) {
			if (taken[row][col][val]) continue;
			board[row][col] = val + '1';
			nonEmpty++;
			int sqr = getSquare(row, col);
			takeNeighbors(board, row, col, sqr, val);
		}
	}
	solveQSize = 0;
}

void takeNeighbors(char** board, int row, int col, int sqr, int val) {
	takeRow(board, row, val);
	takeColumn(board, col, val);
	takeSquare(board, sqr, val);
}

void takeCell(char** board, int row, int col, int sqr, int val) {
	if (board[row][col] == '.' && !taken[row][col][val]) {
		taken[row][col][val] = true;
		takenCnt[row][col]++;
		if (takenCnt[row][col] == 8) {
			solveQueue[solveQSize++] = (Position){.row=row, .col=col, .sqr=sqr};
		}
	}
}

void takeRow(char** board, int row, int val) {
	for (int col = 0; col < 9; col++) {
		int sqr = getSquare(row, col);
		takeCell(board, row, col, sqr, val);
	}
}

void takeColumn(char** board, int col, int val) {
	for (int row = 0; row < 9; row++) {
		int sqr = getSquare(row, col);
		takeCell(board, row, col, sqr, val);
	}
}

void takeSquare(char** board, int sqr, int val) {
	int row0 = (sqr / 3) * 3;
	int col0 = (sqr % 3) * 3;
	for (int row = row0; row < row0 + 3; row++) {
		for (int col = col0; col < col0 + 3; col++) {
			takeCell(board, row, col, sqr, val);
		}
	}
}

bool makeGuessesUntilSolved(char** board);

bool makeAGuess(char** board, int row, int col, int val) {
	//if (cache[row][col][val] >= 0) return cache[row][col][val];

	//printf("Making guess: %d %d %d\n", row, col, val);
	board[row][col] = val + '1';
	nonEmpty++;
	int sqr = getSquare(row, col);
	takeNeighbors(board, row, col, sqr, val);
	solveCells(board);
	bool solved = (nonEmpty == 81);
	//printf("%d\n", nonEmpty);

	if (!solved) {
		solved = makeGuessesUntilSolved(board);
	}
	cache[row][col][val] = solved;
	return solved;
}

bool makeGuessesUntilSolved(char** board) {
	bool solved = true;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] != '.') continue;
			solved = false;
			for (int val = 0; val < 9; val++) {
				if (taken[i][j][val]) continue;

				bool takenCopy[9][9][9];
				int takenCntCopy[9][9];
				char boardCopy[9][9];
				int nonEmptyCopy = nonEmpty;
				copyBoard(boardCopy, board);
				memcpy(takenCopy, taken, sizeof taken);
				memcpy(takenCntCopy, takenCnt, sizeof takenCnt);

				if (!makeAGuess(board, i, j, val)) {
					//printf("backtrack\n");
					restoreBoard(board, boardCopy);
					memcpy(taken, takenCopy, sizeof taken);
					memcpy(takenCnt, takenCntCopy, sizeof takenCnt);
					nonEmpty = nonEmptyCopy;
					taken[i][j][val] = true;
					takenCnt[i][j]++;
				} else {
					solved = true;
					goto quit_loop;
				}
			}
			goto quit_loop;
		}
	}
quit_loop:
	return solved;
}

void solveSudoku(char** board, int boardSize, int* boardColSize) {
	nonEmpty = 0;
	memset(taken, 0, sizeof taken);
	memset(takenCnt, 0, sizeof takenCnt);
	memset(cache, -1, sizeof cache);
	solveQSize = 0;
	
	int nonEmpty0 = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int sqr = getSquare(i, j);
			char c = board[i][j];
			if (c != '.' && takenCnt[i][j] == 0) {
				int val = c - '1';
				nonEmpty0++;
				nonEmpty++;
				takeNeighbors(board, i, j, sqr, val);
				solveCells(board);
			}
		}
	}
	bool solved = (nonEmpty == 81);
//	printf("%d\n", nonEmpty0);
//	printf("%d\n", nonEmpty);
//	for (int i = 0; i < 9; i++) {
//		for (int j = 0; j < 9; j++)
//			printf("%c", board[i][j]);
//		printf("\n");
//	}

	if (!solved) solved = makeGuessesUntilSolved(board);
	if (!solved) {
		printf("COULDN'T SOLVE!\n");
	}
}

int main(int argc, char** argv) {
	char** board;
	if (argc == 2) {
		FILE* file = fopen(argv[1], "r");
		for (int i = 0; i < 9; i++) {
			char* buffer = malloc(11);
			fgets(buffer, 11, file);
			buffer[9] = '\0';
			board[i] = buffer;
		}
		fclose(file);
	}
	if (argc == 10) {
		board = argv + 1;
	}
	for (int i = 0; i < 9; i++) {
		printf("%s\n", board[i]);
		if (strlen(board[i]) != 9) return 1;
	}
	int colSize = 9;
	solveSudoku(board, 9, &colSize);
	printf("\n");
	for (int i = 0; i < 9; i++) {
		printf("%s\n", board[i]);
	}
}
