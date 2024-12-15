#include<bits/stdc++.h>
using namespace std;

int N = 50;
vector<string>  parseWarehouse() {
    cout << "Entered here\n";
    vector<string> w;
    string s;
    int n = N;
    while(n--) {
        cin >> s;
        w.push_back(s);
    }
    return w;
}

string parseMoves() {
    string s, moves = "";
    int n = 20;
    while(n--) {
        cin >> s;
        moves += s;
    }
    return moves;
}


void displayWarehouse(vector<string> warehouse) {
    for(auto &s: warehouse) {
        cout << s << endl;
    }
}

void swapPosition(int x1, int y1, int x2, int y2, vector<string> &w) {
    int tmp = w[x1][y1];
    w[x1][y1] = w[x2][y2];
    w[x2][y2] = tmp; 
}

pair<int,int> updateNextPosition(int curX, int curY, vector<string> &w, int disX, int disY) {
    int i = curX + disX;
    int j = curY + disY;
    // if next move is not possible
    if( !(i < N && j < N) || w[i][j] == '#') {
        return {curX, curY};
    }

    // if next pos is free
    if( w[i][j] == '.') {
        swapPosition(curX, curY, i, j, w);
        return {i, j};
    }    

    // if next pos is a box
    while( i < N && j < N && i >= 0 && j >= 0) {
        i += disX;
        j += disY;
        if( w[i][j] == '#') {
            return {curX, curY};
        }
        if( w[i][j] == '.') {
            swapPosition(curX + disX, curY + disY, i, j, w);
            swapPosition(curX + disX, curY + disY, curX, curY, w);
            return {curX + disX, curY + disY};
        }
    }
    return {-1, -1};
}

pair<int, int> makeMove(int x, int y, char curMove, vector<string> &w) {
    switch(curMove) {
        case '>':
            return updateNextPosition(x, y, w, 0, 1);
        case '<':
            return updateNextPosition(x, y, w, 0, -1);
        case '^':
            return updateNextPosition(x, y, w, -1, 0);
        case 'v':
            return updateNextPosition(x, y, w, 1, 0);
    }
    return {-1, -1};
}

pair<int, int> findRobotPosition(vector<string> &w) {
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if( w[i][j] == '@') {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

long long calculateScore(vector<string> w) {
    long long ans = 0;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if( w[i][j] == 'O') {
                ans += (100 * i + j); 
            }
        }
    
    }
    return ans;
}

int main() {
    vector<string> w = parseWarehouse();
    string moves = parseMoves();
    auto rPos = findRobotPosition(w);

    int curX, curY;
    curX = rPos.first, curY = rPos.second;

    for(auto & curMove: moves) {
        rPos = makeMove(curX, curY, curMove, w);
        curX = rPos.first, curY = rPos.second;
    }
    displayWarehouse(w);
    cout << calculateScore(w) << endl;
}