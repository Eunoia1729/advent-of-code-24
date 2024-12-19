#include<bits/stdc++.h>
using namespace std;

vector<long long> potentialAnswers;
void dfs(stack<long long> &st, long long ans) {
    if( st.empty()) {
        potentialAnswers.push_back(ans);
        return;
    }
    long long a, rhs = st.top();
    st.pop();
    for(long long b = 0; b <= 7; ++b) {
        a = (ans * 8) + b;
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

    for(auto &p: potentialAnswers) {
        cout << p << " ";
    }
    cout << endl;
}
