#include<bits/stdc++.h>
using namespace std;

int N = 50;
int M = 100;

vector<string>  parseWarehouse() {
    vector<string> w;
    string s;
    int n = N;
    while(n--) {
        cin >> s;
        w.push_back(s);
    }
    return w;
}

vector<string> getNewWarehouse(vector<string> w) {
    vector<string> newWarehouse;
    for(auto &row: w) {
        string s = "";
        for(auto &p: row) {
            switch(p) {
                case '#':
                    s += "##";
                    break;
                case 'O':
                    s += "[]";
                    break;
                case '.':
                    s += "..";
                    break;
                case '@':
                    s += "@.";
                    break;
            }
        }
        newWarehouse.push_back(s);
    }
    return newWarehouse;
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
    int i = 0;
    for(auto &s: warehouse) {
        string rowNum = (to_string(i) + "  ").substr(0, 3); 
        cout << rowNum << s << endl;
        i++;
    }
}

// MAIN LOGIC STARTS HERE

void swapPosition(int x1, int y1, int x2, int y2, vector<string> &w) {
    int tmp = w[x1][y1];
    w[x1][y1] = w[x2][y2];
    w[x2][y2] = tmp; 
}

void displaceHorizontally(int disY, int x, int start, int end, vector<string> &w) {
    int i = end;
    while( i != start) {
        swapPosition(x, i, x, i - disY, w);
        i -= disY;
    }
}

// returns true if (x, y) can be moved or pushed by 1 cell
bool canMoveVertically(int x, int y, vector<string> &w, int direction) {
    switch(w[x][y]) {
        case '.':
            return true;
        case '#':
            return false;
        case '@':
            return canMoveVertically(x + direction, y, w, direction);
        case '[':
            return canMoveVertically(x + direction, y + 1, w, direction) 
                && canMoveVertically(x + direction, y, w, direction);
        case ']':
            return canMoveVertically(x + direction, y - 1, w, direction) 
                && canMoveVertically(x + direction, y, w, direction);
    }
}

void shiftPositionVertically(int x, int y, vector<string> &w, int direction) {
    switch(w[x][y]) {
        case '#':
        case '.':
            return;
        case '@':
            shiftPositionVertically(x + direction, y, w, direction);
            swapPosition(x, y, x + direction, y, w);
            return;
        case '[':
            shiftPositionVertically(x + direction, y + 1, w, direction);
            shiftPositionVertically(x + direction, y, w, direction);
            swapPosition(x, y + 1, x + direction, y + 1, w);
            swapPosition(x, y, x + direction, y, w);
        return;
        case ']':
            shiftPositionVertically(x + direction, y - 1, w, direction);
            shiftPositionVertically(x + direction, y, w, direction);
            swapPosition(x, y - 1, x + direction, y - 1, w);
            swapPosition(x, y, x + direction, y, w);
            return;
    }
}

pair<int,int> updateNextPosition(int curX, int curY, vector<string> &w, int disX, int disY) {
    int i = curX + disX;
    int j = curY + disY;
    // if next move is not possible
    if( !(i < N && j < M) || w[i][j] == '#') {
        return {curX, curY};
    }

    // if next pos is free
    if( w[i][j] == '.') {
        swapPosition(curX, curY, i, j, w);
        return {i, j};
    }    

    // if next pos is a box:
    // it's horizontal movement
    if( disX == 0) {
        while( i < N && j < M && i >= 0 && j >= 0) {
            i += disX;
            j += disY;
            if( w[i][j] == '#') {
                return {curX, curY};
            }
            if( w[i][j] == '.') {
                displaceHorizontally(disY, curX, curY, j, w);
                return {curX + disX, curY + disY};
            }
        }
    }
    // it's vertical movement
    if(disY == 0) {
        bool canShift = canMoveVertically(curX, curY, w, disX);
        if( canShift) {
            shiftPositionVertically(curX, curY, w, disX);
            return {curX + disX, curY + disY};
        }
        else {
            return {curX, curY};
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

long long calculateScore2(vector<string> w) {
    long long ans = 0;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            if( w[i][j] == '[') {
                ans += (100 * i + j); 
            }
        }
    
    }
    return ans;
}


int main() {
    vector<string> oldW = parseWarehouse();
    vector<string> w = getNewWarehouse(oldW);
    string moves = parseMoves();
    auto rPos = findRobotPosition(w);

    int curX, curY;
    curX = rPos.first, curY = rPos.second;

    for(auto & curMove: moves) {
        rPos = makeMove(curX, curY, curMove, w);
        curX = rPos.first, curY = rPos.second;
    }
    displayWarehouse(w);
    cout << calculateScore2(w) << endl;
}