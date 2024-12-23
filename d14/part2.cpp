#include<bits/stdc++.h>
using namespace std;

int N = 103;
int M = 101;

void inputRobotVectors(vector<pair<pair<int,int>,pair<int,int>>> &input) {
    string line;
    while (getline(cin, line)) {
        size_t p = line.find("p=");
        size_t v = line.find("v=");
        size_t comma = line.find(",", p + 2);
        int x = stoi(line.substr(p + 2, comma - p - 2));
        int y = stoi(line.substr(comma + 1, v - comma - 1));
        comma = line.find(",", v + 2);
        int a = stoi(line.substr(v + 2, comma - v - 2));
        int b = stoi(line.substr(comma + 1));
        input.push_back({{y, x}, {b, a}});
    }
}

void displayGrid(vector<string> &grid) {
    for(auto &s: grid) {
        cout << s << endl;
    }
}

vector<string> getNewGrid(vector<pair<int, int>> &finalPositions) {
    vector<string> grid(N, string(M, ' '));
    for(auto &p: finalPositions) {
        auto [x, y] = p;
        grid[x][y] = '*';
    }
    return grid;
}

vector<int> diagX = {-1, -1, 1, 1};
vector<int> diagY = {-1, 1, -1, 1};

int dfs(vector<string> &grid, int x, int y) {
    grid[x][y] = ' ';
    int ans = 1;
    for(int i = 0; i < 4; ++i) {
        int newX = x + diagX[i];
        int newY = y + diagY[i];
        if(newX >= 0 && newX < N && newY >= 0 && newY < M && grid[newX][newY] == '*') {
            ans += dfs(grid, newX, newY);
        }
    }
    return ans;
}

int calculateScore(vector<string> &grid) {
    vector<string> newGrid = grid;
    int ans = 0;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            if(newGrid[i][j] == '*') {
                ans = max(ans, dfs(newGrid, i, j));
            }
        }
    }
    return ans;
}


vector<pair<int, int>> updateFinalPositions(vector<pair<pair<int,int>,pair<int,int>>> &initialVectors, int timeElapsed) {
    vector<pair<int, int>> finalPositions;
    for(auto &p: initialVectors) {
        auto [x, y] = p.first;
        auto [a, b] = p.second;

        long long finalX = (N + x + (a * timeElapsed) % N ) % N;
        long long finalY = (M + y + (b * timeElapsed) % M ) % M;

        finalPositions.push_back({finalX, finalY});
    }
    return finalPositions;
}

int main() {
    vector<pair<pair<int,int>,pair<int,int>>> input;
    vector<pair<int, int>> finalPositions;
    vector<string> grid;

    inputRobotVectors(input);
    
    int bestTime = -1;
    int score, maxx = INT_MIN;
    for(int t = 0; t < 50000; ++t) {
        finalPositions = updateFinalPositions(input, t);
        grid = getNewGrid(finalPositions);
        score = calculateScore(grid);
        if(score > maxx) {
            maxx = score;
            bestTime = t;
        }
    }
    finalPositions = updateFinalPositions(input, bestTime);
    grid = getNewGrid(finalPositions);
    displayGrid(grid);
    cout << "TimeTaken: " << bestTime << " Score: " << maxx << endl;

    return 0;
}

