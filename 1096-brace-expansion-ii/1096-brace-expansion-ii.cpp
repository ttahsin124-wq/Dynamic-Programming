class Solution {
public:
    set<string> parse(string& s, int& i) {
        set<string> result = parseTerm(s, i);
        while (i < s.size() && s[i] == ',') {
            i++;
            set<string> next = parseTerm(s, i);
            for (string word : next) {
                result.insert(word);
            }
        }
        return result;
    }
    set<string> parseTerm(string& s, int& i) {
        set<string> result;
        result.insert("");
        while (i < s.size() && s[i] != ',' && s[i] != '}') {
            set<string> current;
            if (s[i] == '{') {
                i++;
                current = parse(s, i);
                i++;
            } else {
                current.insert(string(1, s[i]));
                i++;
            }
            set<string> temp;
            for (string a : result) {
                for (string b : current) {
                    temp.insert(a + b);
                }
            }
            result = temp;
        }
        return result;
    }
    vector<string> braceExpansionII(string expression) {
        int i = 0;
        set<string> result = parse(expression, i);
        vector<string> answer(result.begin(), result.end());
        return answer;
    }
};