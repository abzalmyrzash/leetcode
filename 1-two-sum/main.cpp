#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res(2);
		map<int, int> map;

		for (int i = 0; i < nums.size(); i++) {
			map.insert({target - nums[i], i});
		}
		for (int i = 0; i < nums.size(); i++) {
			if (map.find(nums[i]) != map.end() && map[nums[i]] != i) {
				res[0] = map[nums[i]];
				res[1] = i;
				return res;
			}
		}
		return res;
    }
};

int main ()
{
	int n;
	cin >> n;
	vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	int target;
	cin >> target;
	Solution s;
	vector<int> res = s.twoSum(nums, target);
	for (int i = 0; i < 2; i++) {
		cout << res[i] << " ";
	}
	cout << "\n";
}
