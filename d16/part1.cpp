#include<bits/stdc++.h>
using namespace std;

const int N = 141;
int dist[N][N][4];
vector<string> grid;

vector<int> moveX = {0, -1, 0, 1};
vector<int> moveY = {1, 0, -1, 0};

int encodeIndex(int i, int j) {
    return (i * N) + j;
}

pair<int, int> decodeIndex(int x) {
    return {x / N, x % N };
}

vector<int> getLocation(vector<string> &grid, char c) {
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if( grid[i][j] == c) {
                return {i, j};
            }
        }   
    }
    return {-1, -1};
}

void initializeDistArray() {
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            for(int k = 0; k < 4; ++k) {
                dist[i][j][k] = INT_MAX;
            }
        }
    }
}


int main() {
    
    string s;
    char c;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> s;
            grid.push_back(s);
        }
    }

    initializeDistArray();

    // apply djikstra
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    vector<int> startPos = getLocation(grid, 'S');
    vector<int> endPos = getLocation(grid, 'E');
    
    dist[startPos[0]][startPos[1]][0] = 0;
    pq.push({0, encodeIndex(startPos[0], startPos[1]), 0});
    
    int curX, curY, curCost, curLocation, newX, newY, curDirection;
    int finalAns = INT_MAX;
    vector<int> cur;    
    while( pq.size() ) {
        cur = pq.top();
        curCost = cur[0], curLocation = cur[1], curDirection = cur[2];
        pq.pop();
        auto [curX, curY] = decodeIndex(curLocation); 

        if( curCost > dist[curX][curY][curDirection]) {
            continue;
        }

        if( curX == endPos[0] && curY == endPos[1]) {
            cout << curCost << endl;
            break;
        }

        for(int newDirection = 0; newDirection < 4; ++newDirection) {
            // skip trying to go back in the source direction
            if( abs(newDirection - curDirection) == 2) {
                continue;
            }

            newX = curX + moveX[newDirection];
            newY = curY + moveY[newDirection];
            int rotationCost = (newDirection != curDirection) * 1000;
            
            switch(grid[newX][newY]) {
                case '.': 
                case 'E': {
                    int newCost = dist[curX][curY][curDirection] + 1 + rotationCost;
                    if( dist[newX][newY][newDirection] > newCost) {
                        dist[newX][newY][newDirection] = newCost;
                        pq.push({newCost, encodeIndex(newX, newY), newDirection});
                    }
                }
                case '#':
                case 'S':
                    continue;
            }
        }
    }
}