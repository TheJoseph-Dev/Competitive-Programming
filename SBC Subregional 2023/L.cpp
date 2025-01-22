#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    ios::sync_with_stdio(0);

    string s;
    int k;

    cin >> s >> k;

    vector<string> ss = vector<string>(k+1);
    for(int i = 0; i < s.size(); i++)
        ss[i % k].push_back(s[i]);

    for(int i = 0; i < k; i++)
        sort(ss[i].begin(), ss[i].end());

    for(int c = 0; c < s.size(); c++)
    for(int i = 0; i < k && ss[i].size() > c; i++)
        putchar(ss[i][c]);
    putchar('\n');

    return 0;
}