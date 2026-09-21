class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> result(k, 0);
        vector<long long> pC(k, 0);
        for (int i = 0; i < n; i++) {
            vector<long long> cC(k, 0);
            for (int oldR = 0; oldR < k; oldR++) {
                if (pC[oldR] > 0) {
                    int newR = (1LL * oldR * nums[i]) % k;
                    cC[newR] += pC[oldR];
                }
            }
            int singleR = nums[i] % k;
            cC[singleR] += 1;
            pC = move(cC);
            for (int r = 0; r < k; r++) {
                result[r] += pC[r];
            }
        }
        return result;
    }
};