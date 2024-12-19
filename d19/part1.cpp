#include<bits/stdc++.h>
using namespace std;

/**
 * INPUT HELPERS START HERE
 */
string trimLeadingSpaces(const string& input) {
    string res = input;
    res.erase(0, res.find_first_not_of(' '));
    return res;
}
vector<string> split(const string& input, char delim) {
    vector<string> res;
    stringstream ss(input);

    string tok;
    while (getline(ss, tok, delim)) {
        res.push_back(trimLeadingSpaces(tok));
    }
    return res;
}

void getInput(vector<string> &patterns, vector<string> &designs) {
    string input;
    getline(cin, input);
    patterns = split(input, ',');

    getline(cin, input); // empty string
    
    while (getline(cin, input)) {
        if (input.empty())
            break;
        designs.push_back(input);
    }
}
/**
 * INPUT HELPERS END HERE
 */

bool isDesignPossible(string design, vector<string> &patterns) {
    int n = design.size();
    vector<bool> dp(n, false);
    for(int i = 0; i < n; ++i) {
        for(auto &p: patterns) {
            if( i + 1 < p.size()) {
                continue;
            }
            bool isPatternMatch = design.substr(i + 1 - p.size(), p.size()) == p;
            if( (i + 1 == p.size() || dp[i - p.size()]) && isPatternMatch) {
                dp[i] = true;
            }
        }
    }
    return dp[n - 1];

}

int main() {
    vector<string> patterns, designs;
    getInput(patterns, designs);

    int count = 0;
    for(auto &d: designs) {
        count += isDesignPossible(d, patterns);
    }
    cout << count << endl;
    return 0;


}