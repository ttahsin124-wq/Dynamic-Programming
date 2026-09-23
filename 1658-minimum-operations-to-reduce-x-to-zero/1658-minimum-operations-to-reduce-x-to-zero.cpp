class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();

        int total = 0;
        for (int num : nums) {
            total += num;
        }
        int target = total - x;
        if (target < 0) return -1;
        if (target == 0) return n;

        unordered_map<int, int> mp;
        mp[0] = -1;

        int prefixSum = 0;
        int maxLength = -1;

        for (int i = 0; i < n; i++) {
            prefixSum += nums[i];

            int remain = prefixSum - target;

            if (mp.count(remain)) {
                int length = i - mp[remain];
                maxLength = max(maxLength, length);
            }

            if (!mp.count(prefixSum)) {
                mp[prefixSum] = i;
            }
        }

        if (maxLength == -1) {
            return -1;
        }

        return n - maxLength;
    }
};