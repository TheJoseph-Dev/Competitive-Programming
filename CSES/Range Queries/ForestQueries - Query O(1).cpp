/*
https://cses.fi/problemset/task/1652
*/
#include <bits/stdc++.h>
using namespace std;
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
 
    int n, q;
    cin >> n >> q;
 
    vector<vector<int>> prefix(n + 1, vector<int>(n + 1, 0));
    for(int i = 1; i <= n; i++) {
        string line;
        cin >> line;
        for(int j = 1; j <= n; j++) {
            prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
            if(line[j - 1] == '*') {
                prefix[i][j]++;
            }
        }
    }
 
    for(int i = 0; i < q; i++) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
 
        int trees = prefix[y2][x2] - prefix[y1 - 1][x2] - prefix[y2][x1 - 1] + prefix[y1 - 1][x1 - 1];
        cout << trees << "\n";
    }
}