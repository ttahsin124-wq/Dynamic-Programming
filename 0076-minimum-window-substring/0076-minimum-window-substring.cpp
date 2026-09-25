class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> need;
        for (char ch : t) {
            need[ch]++;
        }
        unordered_map<char, int> have;
        int left = 0;
        int required = t.size();
        int minLength = INT_MAX;
        int start = 0;
        for (int right = 0; right < s.size(); right++) {

            char ch = s[right];
            have[ch]++;
            if (need.count(ch) && have[ch] <= need[ch]) {
                required--;
            }
            while (required == 0) {
                if (right - left + 1 < minLength) {
                    minLength = right - left + 1;
                    start = left;
                }
                char removeChar = s[left];
                have[removeChar]--;
                if (need.count(removeChar) &&
                    have[removeChar] < need[removeChar]) {
                    required++;
                }

                left++;
            }
        }
        if (minLength == INT_MAX) {
            return "";
        }
        return s.substr(start, minLength);
    }
};