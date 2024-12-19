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

long long isDesignPossible(string design, vector<string> &patterns) {
    int n = design.size();
    vector<long long> dp(n, 0);
    for(int i = 0; i < n; ++i) {
        for(auto &p: patterns) {
            if( i + 1 < p.size()) {
                continue;
            }
            bool isPatternMatch = design.substr(i + 1 - p.size(), p.size()) == p;
            if( i + 1 == p.size() && isPatternMatch) {
                dp[i] += 1;
            }
            if(isPatternMatch) {
                dp[i] += dp[i - p.size()];
            }
        }
    }
    return dp[n - 1];

}

int main() {
    vector<string> patterns, designs;
    getInput(patterns, designs);

    long long count = 0;
    for(auto &d: designs) {
        count += isDesignPossible(d, patterns);
    }
    cout << count << endl;
    return 0;


}