#include<bits/stdc++.h>
using namespace std;

const int N = 71;
vector<string> grid;
vector<vector<bool>> vis(N, vector<bool>(N, false));

vector<int> moveX = {0, -1, 0, 1};
vector<int> moveY = {1, 0, -1, 0};

void getInputGrid() {
    char c;
    for(int i = 0; i < N; ++i) {
        grid.push_back("");
        for(int j = 0; j < N; ++j) {
            grid[i] += ".";
        }
    }
}

void displayGrid() {
    for(int i = 0; i < N; ++i) {
        cout << (to_string(i) + "   ").substr(0, 4) << grid[i] << endl;
    }
}

bool inRange(int curX, int curY) {
    return 0 <= curX && curX < N && 
           0 <= curY && curY < N;
}
int getShortestPathCostByBfs() {
    queue<vector<int>> st;
    st.push({0, 0, 0});

    vector<int> cur;
    int curX, curY, curCost, newX, newY;
    while( st.size()) {
        cur = st.front();
        curX = cur[0], curY = cur[1], curCost = cur[2];
        st.pop();
        if(vis[curX][curY]) {
            continue;
        }
        vis[curX][curY] = 1;
        if( curX == 70 && curY == 70) {
            return curCost;
        }

        for(int i = 0; i < 4; ++i) {
            newX = curX + moveX[i];
            newY = curY + moveY[i];
            if(!inRange(newX, newY)) {
                continue;
            }
            switch( grid[newX][newY]) {
                case '.':
                    {   
                        if(!vis[newX][newY])
                            st.push({newX, newY, curCost + 1});
                    }
            }
        }
    }
    return -1;
}

int main() {
    
    string s;
    char c;
    getInputGrid();

    int x, y;
    for(int i = 0; i < 1024; ++i) {
        cin >> y >> c >> x;
        grid[x][y] = '#';
    }

    displayGrid();
    int numSteps = getShortestPathCostByBfs();
    cout << numSteps << endl;
}   