#include<bits/stdc++.h>
using namespace std;

const int N = 141;
vector<string> grid;
int dist[N][N][4];

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

int getCheapestPathCost(vector<int> &startPos, vector<int> &endPos) {
    
    // apply djikstra
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
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
            return curCost;
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
    return -1;
}

int getOppositeDirection(int curDirection) {
     return (4 + curDirection - 2) % 4;
}

vector<vector<int>> getNeighouringPositions(vector<int> curPos) {
    vector<vector<int>> neighbours;
    int newX, newY;
    for(int i = 0; i < 4; ++i) {
        for(int direction = 0; direction < 4; ++direction) {
            newX = curPos[0] + moveX[i];
            newY = curPos[1] + moveY[i];
            neighbours.push_back({newX, newY, direction});
        }
    }
    return neighbours;
}

void generatePathViaDfs(vector<int> curPos) {
    int newX, newY, curX = curPos[0], curY = curPos[1], newDirection, curDirection = curPos[2];
    grid[curX][curY] = 'O';
    
    vector<vector<int>> neighbours = getNeighouringPositions(curPos);
    for(auto &neighbour: neighbours) {
        newX = neighbour[0], newY = neighbour[1], newDirection = neighbour[2];
        int rotationCost = (getOppositeDirection(newDirection) != curDirection) * 1000;

            switch(grid[newX][newY]) {
                case '.': 
                case 'S':
                case 'O': {
                    if( dist[newX][newY][getOppositeDirection(newDirection)] + 1 + rotationCost == dist[curX][curY][curDirection]) {
                        generatePathViaDfs({newX, newY, getOppositeDirection(newDirection)});
                    }
                }
            }
    }
}


void getInputGrid() {
    string s;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> s;
            grid.push_back(s);
        }
    }
}

void displayGrid() {
    for(int i = 0; i < N; ++i) {
        cout << (to_string(i) + "   ").substr(0, 4) << grid[i] << endl;
    }
}

int getScore2() {
    int score = 0;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if( grid[i][j] == 'O') {
                score++;
            }
        }
    }
    return score;
}

int main() {
    
    string s;
    char c;
    getInputGrid();

    vector<int> startPos = getLocation(grid, 'S');
    vector<int> endPos = getLocation(grid, 'E');
    
    initializeDistArray();
    
    int leastCost = getCheapestPathCost(startPos, endPos);
    cout << "Least cost: " << leastCost <<endl;


    // apply DFS to find the path
    for(int i = 0; i < 4; ++i) {
        if( dist[endPos[0]][endPos[1]][i] == leastCost) {
            generatePathViaDfs({endPos[0], endPos[1], i});
        }
    }
    displayGrid();
    cout << "\nNumber of unique tiles covered: " << getScore2() << endl;
}   