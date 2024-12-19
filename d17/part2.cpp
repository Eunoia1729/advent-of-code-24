#include<bits/stdc++.h>
using namespace std;

vector<long long> potentialAnswers;

/** FORMATTING UTILS START HERE */
string numberAsBinaryString(long long x) {
    string s1, s = bitset<64>(x).to_string();
    reverse(s.begin(), s.end());
    for(int i = 0; i + 3 < s.size(); i+=3) {
        s1 = s1 + s.substr(i, 3) + " ";
    }
    while(s1.back() == ' ' || s1.back() == '0') {
        s1.pop_back();    
    }
    reverse(s1.begin(), s1.end());
    return s1;
}
/** FORMATTING UTILS END HERE */

void dfs(stack<long long> &st, long long ans) {
    if( st.empty()) {
        potentialAnswers.push_back(ans);
        return;
    }
    long long a, rhs = st.top();
    st.pop();
    for(long long b = 0; b <= 7; ++b) {
        a = (ans * 8) + b;
        // (last 3 digits of a) ^ b'100' ^ ( a / 2 ^^ ( (last 3 digits of a) ^ b'001' ) )
        if( (b ^ 4 ^ ( a >> (b ^ 1))) % 8 == rhs) {
            dfs(st, a);
        }
    }
    st.push(rhs);
}


int main() {
    vector<int> v = {2, 4, 1, 1, 7, 5, 1, 5, 4, 0, 5, 5, 0, 3, 3, 0};
    stack<long long> st;
    for(auto &p: v) {
        st.push(p);
    }
    dfs(st, 0L);
    cout << potentialAnswers[0] << endl;
}

/*
 * ROUGH SKETCH OF THE ALGORITHM:
 * b = last 3 digits of a, 
 * b = (last 3 digits of a)^001(bits), 
 * c = a / 2^^( (last 3 digits of a)^001(bits) ), 
 * b = (last 3 digits of a)^100(bits),  
 * b = (last 3 digits of a) ^100(bits) ^ ( a / 2^^( (last 3 digits of a)^001(bits) ) ),  
 * print(b % 8), 
 * a = a / 8, 
 * jump to start
 */