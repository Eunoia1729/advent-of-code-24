#include<bits/stdc++.h>
using namespace std;

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

set<pair<string, string>> readInput() {
    set<pair<string, string>> inputs;
    
    string input;
    while (getline(cin, input)) {
        if (input.empty())
            break;
        vector<string> nodes = split(input, '-');
        inputs.insert({ min(nodes[0], nodes[1]), max(nodes[0], nodes[1]) });
    }
    return inputs;
}


int main() {
    set<pair<string, string>> edges = readInput();
    
    set<string> allNodes;
    set<string> tNodes;
    for(auto &p: edges) {
        allNodes.insert(p.first);
        allNodes.insert(p.second);
    }

    for(auto &p: allNodes) {
        if( p[0] == 't') {
            tNodes.insert(p);
        }
    }
    set < set<string> > answers;
    for(auto &p: tNodes) {
    
        for(auto &x: allNodes) {
            for(auto &y: allNodes) {
                if(x == p || y == p || x == y) continue;
                pair<string, string> edge1 = { min(x, y) , max(x, y)};
                pair<string, string> edge2 = { min(p, y) , max(p, y)};   
                pair<string, string> edge3 = { min(x, p) , max(x, p)};;
                if(edges.find(edge1) != edges.end() && edges.find(edge2) != edges.end() && edges.find(edge3) != edges.end()) {
                    answers.insert({p, x, y});
                }
            }
        }
    }
    cout << "Ans:" << answers.size() << endl;
    return 0;
}