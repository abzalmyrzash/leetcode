#include "..\readargs.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    long long* balance;
    int balanceSize;
} Bank;

Bank* bankCreate(long long* balance, int balanceSize) {
    Bank* bank = malloc(sizeof(Bank));
	bank->balance = balance;
	bank->balanceSize = balanceSize;
	return bank;
}

bool bankTransfer(Bank* obj, int account1, int account2, long long money) {
	if (account1 > obj->balanceSize) return false;
	if (account2 > obj->balanceSize) return false;
	if (obj->balance[account1 - 1] < money) return false;
	obj->balance[account1 - 1] -= money;
	obj->balance[account2 - 1] += money;
	return true;
}

bool bankDeposit(Bank* obj, int account, long long money) {
	if (account > obj->balanceSize) return false;
	obj->balance[account - 1] += money;
	return true;
}

bool bankWithdraw(Bank* obj, int account, long long money) {
	if (account > obj->balanceSize) return false;
	if (obj->balance[account - 1] < money) return false;
	obj->balance[account - 1] -= money;
	return true;
}

void bankFree(Bank* obj) {
	free(obj->balance);
    free(obj);
}

/**
 * Your Bank struct will be instantiated and called as such:
 * Bank* obj = bankCreate(balance, balanceSize);
 * bool param_1 = bankTransfer(obj, account1, account2, money);
 
 * bool param_2 = bankDeposit(obj, account, money);
 
 * bool param_3 = bankWithdraw(obj, account, money);
 
 * bankFree(obj);
*/

int main(int argc, char* argv[]) {
	char* actions[100];
	int m;
	readArgs(argc, argv, "#s", actions, &m);
	char* str = argv[2] + 3;
	int charsRead;
	long long balances[100];
	int n = 0;
	while(1 == sscanf(str, "%lld,%n", &balances[n], &charsRead)) {
		n++;
		str += charsRead;
	}
	Bank* bank = bankCreate(balances, n);
	int acc1, acc2;
	long long money;
	for (int i = 1; i < m; i++) {
		while(*(str++) != '[');
		switch (actions[i][0]) {
			case 'w': // withdraw
				sscanf(str, "%d,%lld", &acc1, &money);
				if (bankWithdraw(bank, acc1, money))
					printf("withdraw successful\n");
				else printf("withdraw failed\n");
				break;
			case 'd': // deposit
				sscanf(str, "%d,%lld", &acc1, &money);
				if (bankDeposit(bank, acc1, money))
					printf("deposit successful\n");
				else printf("deposit failed\n");
				break;
			case 't': // transfer
				sscanf(str, "%d,%d,%lld", &acc1, &acc2, &money);
				if (bankTransfer(bank, acc1, acc2, money))
					printf("transfer successful\n");
				else printf("transfer failed\n");
				break;
			default:
				printf("invalid action\n");
				return 1;
		}
	}
	return 0;
}
