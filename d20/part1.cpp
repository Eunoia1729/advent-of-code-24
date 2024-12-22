#include<bits/stdc++.h>
using namespace std;

const int N = 141;
vector<string> grid;
int CHEAT_TIME = 20;
int MIN_SAVE_THRESHOLD = 100;
// int dist[N][N];

vector<int> moveX = {0, -1, 0, 1};
vector<int> moveY = {1, 0, -1, 0};

/** FORMAT UTILS START HERE */

void getInputGrid() {
    string s;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> s;
            grid.push_back(s);
        }
    }
}

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

/** FORMAT UTILS END HERE */

vector<vector<int>> getShortestPathMatrix(vector<int> &startPos, vector<int> &endPos) {
    vector< vector<int> > dist(N, vector<int>(N, INT_MAX));

    // apply BFS
    queue<pair<int, int> > pq;
    dist[startPos[0]][startPos[1]] = 0;
    pq.push({0, encodeIndex(startPos[0], startPos[1])});
    
    int curX, curY, curCost, curLocation, newX, newY, curDirection, cur; 
    while( pq.size() ) {
        auto [curCost, curLocation] = pq.front();
        pq.pop();
        auto [curX, curY] = decodeIndex(curLocation); 

        if( curCost > dist[curX][curY]) {
            continue;
        }

        for(int newDirection = 0; newDirection < 4; ++newDirection) {
            newX = curX + moveX[newDirection];
            newY = curY + moveY[newDirection];
            switch(grid[newX][newY]) {
                case '.': 
                case 'E': {
                    int newCost = dist[curX][curY] + 1;
                    if( dist[newX][newY] > newCost) {
                        dist[newX][newY] = newCost;
                        pq.push({newCost, encodeIndex(newX, newY)});
                    }
                }
                case '#':
                case 'S':
                    continue;
            }
        }
    }
    return dist;
}

vector<pair<int, int>> getAllFreeCells() {
    vector<pair<int, int>> freeCells;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if( grid[i][j] != '#') {
                freeCells.push_back({i, j});
            }
        }
    }
    return freeCells;
}

int getDistanceWithoutWalls(pair<int,int> source, pair<int,int> dest) {
    auto [x1, y1] = source;
    auto [x2, y2] = dest;
    return abs(x1 - x2) + abs(y1 - y2);
}

int main() {
    getInputGrid();

    vector<int> startPos = getLocation(grid, 'S');
    vector<int> endPos = getLocation(grid, 'E');
   
    vector<vector<int>> distFromStart = getShortestPathMatrix(startPos, endPos);
    
    swap(grid[startPos[0]][startPos[1]], grid[endPos[0]][endPos[1]]);
    vector<vector<int>> distFromEnd = getShortestPathMatrix(endPos, startPos);
    swap(grid[startPos[0]][startPos[1]], grid[endPos[0]][endPos[1]]);

    int shortestDistance = distFromStart[endPos[0]][endPos[1]];

    vector<pair<int, int>> freeCells = getAllFreeCells();
    int result = 0;
    for(auto &startCell: freeCells) {
        for(auto &destCell: freeCells) {
            int distanceCheated = getDistanceWithoutWalls(startCell, destCell);
            
            if( distanceCheated > CHEAT_TIME) {
                continue;
            }

            int distTillStartCell = distFromStart[startCell.first][startCell.second];
            int distAfterEndCell = distFromEnd[destCell.first][destCell.second];

            int timeSaved = shortestDistance - (distTillStartCell + distanceCheated + distAfterEndCell); 
            if( timeSaved >= MIN_SAVE_THRESHOLD) {
                result++;
            }

        } 
    }
    cout << result << endl;
}