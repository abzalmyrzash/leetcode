// https://leetcode.com/problems/add-two-numbers/
#include <iostream>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* digit1 = l1;
        ListNode* digit2 = l2;

		ListNode* result = new ListNode();
		ListNode* digit3 = result;

		bool carry = 0;

		// add two numbers while both digits are present
		while (1) {
			digit3->val = digit1->val + digit2->val + carry;

			if (digit3->val >= 10) {
				digit3->val -= 10;
				carry = 1;
			} else {
				carry = 0;
			}

			digit1 = digit1->next;
			digit2 = digit2->next;

			// break cycle if one of the digits is no longer present
			if (digit1 == nullptr || digit2 == nullptr) {
				// if both digits are not present the last digit of the result is the carry
				if (digit1 == nullptr && digit2 == nullptr) {
					if (carry) {
						digit3->next = new ListNode(carry);
					}
					return result;
				}
				break;
			}

			digit3->next = new ListNode();
			digit3 = digit3->next;
		}

		digit3->next = new ListNode();
		digit3 = digit3->next;

		// digit of the remaining number
		ListNode* digit;
		if (digit1 != nullptr) digit = digit1;
		else digit = digit2;

		// add carry digit to the remaining digits
		while (1) {
			digit3->val = digit->val + carry;

			if (digit3->val == 10) {
				digit3->val = 0;
				carry = 1;
			} else {
				carry = 0;
			}

			digit = digit->next;

			if (digit == nullptr) {
				if (carry) {
					digit3->next = new ListNode(carry);
				}
				return result;
			}

			digit3->next = new ListNode();
			digit3 = digit3->next;
		}

		return result;
    }
};

int main()
{
	int n1, n2;
	ListNode *l1 = new ListNode(), *l2 = new ListNode();
	ListNode *d1 = l1, *d2 = l2;

	cin >> n1;

	for (int i = 0;;) {
		cin >> d1->val;
		i++;
		if (i == n1) break;
		d1->next = new ListNode();
		d1 = d1->next;
	}

	cin >> n2;

	for (int i = 0;;) {
		cin >> d2->val;
		i++;
		if (i == n2) break;
		d2->next = new ListNode();
		d2 = d2->next;
	}

	Solution s;
	ListNode *l3 = s.addTwoNumbers(l1, l2);
	ListNode *d3 = l3;

	while(d3 != nullptr) {
		cout << d3->val;
		d3 = d3->next;
	}
	cout << endl;
}
