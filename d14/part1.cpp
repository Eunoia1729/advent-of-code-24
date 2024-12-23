#include<bits/stdc++.h>
using namespace std;

long long TIME_ELAPSED = 100L;
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

int main() {
    vector<pair<pair<int,int>,pair<int,int>>> input;
    vector<pair<int, int>> finalPositions;

    inputRobotVectors(input);
    sort(input.begin(), input.end());
    for(auto &p: input) {
        auto [x, y] = p.first;
        auto [a, b] = p.second;

        long long finalX = (N + x + (a * TIME_ELAPSED) % N ) % N;
        long long finalY = (M + y + (b * TIME_ELAPSED) % M ) % M;

        finalPositions.push_back({finalX, finalY});
    }
    map<pair<int, int>, long long> quadrantCounts;
    sort(finalPositions.begin(), finalPositions.end());
    for(auto &p: finalPositions) {
        auto [x, y] = p;
        if( (x * 2 == N - 1) || (y * 2 == M - 1) ) continue;
        quadrantCounts[{  ( x < (N / 2) ), ( y < (M / 2) )  }]++;
    }

    long long ans = 1L;
    for(auto &p: quadrantCounts) {
        ans *= p.second;
    }
    cout << ans << endl;
    return 0;
}

