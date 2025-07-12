#include <stdio.h>
#include <queue>
#include <algorithm>
#include <string>

#ifndef ONLINE_JUDGE
#define DEBUG_H
#include "..\..\Debug.h"
#else
    #define dbgf(fmt, x)
    #define p_vi(v)
    #define dbgvi(v)
    #define dbgmi(mtx, rows)
    #define p_v(v)
    #define dbgv(v)
    #define dbgm(m)
    #define dbg(...)
    #define dbg2(...)
#endif

constexpr int maxN = 3e3+1;

std::string bfs(char mtx[maxN][maxN], int n) {
    bool visited[maxN][maxN] = {false};
    std::queue<std::pair<int, int>> q;
    q.push({0,0});
    
    std::string r = "";
    while(true) {
        std::vector<std::pair<int, int>> bestPrfx;
        char b = 126;
        while(!q.empty()) {
            auto [i, j] = q.front();
            q.pop();

            if(i == n-1 && j == n-1) return mtx[0][0] + r;

            bool rowInBounds = i + 1 < n, colInBounds = j + 1 < n;
            if(rowInBounds && !visited[i+1][j]) { visited[i+1][j] = 1; bestPrfx.push_back({i+1,j}); b = std::min(b, mtx[i+1][j]); }
            if(colInBounds && !visited[i][j+1]) { visited[i][j+1] = 1; bestPrfx.push_back({i,j+1}); b = std::min(b, mtx[i][j+1]); }
        }
        while(!bestPrfx.empty()) {
            if(mtx[bestPrfx.back().first][bestPrfx.back().second] == b) q.push(bestPrfx.back());
            bestPrfx.pop_back();
        }
        r += b;
    }

    return "";
}

int main() {

    int n;
    scanf("%d", &n);

    char mtx[maxN][maxN];
    for(int i = 0; i < n; i++)
        scanf("%s", mtx[i]);

    puts(bfs(mtx, n).c_str());
    return 0;
}