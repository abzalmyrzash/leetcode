#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <string>

class Solution {
public:
    std::string fractionToDecimal(long long numerator, long long denominator) {
		char* str = (char*)malloc(10000);
		int strI = 0;

		if ((numerator > 0 && denominator < 0)
			|| (numerator < 0 && denominator > 0))
		{
			str[strI++] = '-';
		}
		numerator = llabs(numerator);
		denominator = llabs(denominator);
		long long quotient, remainder;
		quotient = numerator / denominator;
		strI += sprintf(str + strI, "%lld", quotient);
		remainder = numerator % denominator;
		std::map<long long, int> remPos; // maps remainder to strI position

		if (remainder == 0) return std::string(str);

		str[strI++] = '.';

		while (remainder > 0) {
			numerator = remainder * 10;
			quotient = numerator / denominator;
			str[strI] = quotient + '0';

			if (remPos.find(remainder) == remPos.end()) {
				remPos.insert({remainder, strI});
				strI++;
			}

			else {
				int bracketPos = remPos[remainder];
				memmove(str + bracketPos + 1, str + bracketPos, strI - bracketPos);
				str[bracketPos] = '(';
				strI++;
				str[strI++] = ')';
				break;
			}

			remainder = numerator % denominator;

			if (strI == 10000) break;
		}
		str[strI] = '\0';

		return std::string(str);
    }
};

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	Solution solution;
	printf("%s\n", solution.fractionToDecimal(n, m).c_str());
}
