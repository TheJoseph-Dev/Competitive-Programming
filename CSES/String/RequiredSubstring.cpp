#include <iostream>
#include <string>
#include <cstring>

typedef long long ll;
constexpr int MOD = 1e9 + 7;

constexpr int maxN = 101, maxM = 101;
int n;
std::string s;

int dp[maxN][maxM][2]; // dp[pos][match_len][occurred]
int next[maxM][26];   // transition table for KMP automaton

// Build KMP prefix table and transition automaton
void buildKMP() {
    int pi[maxM] = {};
    for(int i = 1; i < s.size(); ++i) {
        int j = pi[i-1];
        while(j > 0 && s[i] != s[j])
            j = pi[j-1];
        if(s[i] == s[j]) ++j;
        pi[i] = j;
    }

    for(int len = 0; len <= s.size(); ++len)
        for(int c = 0; c < 26; ++c)
            if(len < s.size() && s[len] == 'A' + c) next[len][c] = len + 1;
            else if(len == 0) next[len][c] = 0;
            else next[len][c] = next[pi[len - 1]][c];
}

int count(int i, int j, bool o) {
    if(i == n) return o;
    if(dp[i][j][o] != -1) return dp[i][j][o];
    int cnt = 0;
    for(int c = 0; c < 26; ++c) {
        if(o && next[j][c] == s.size()) continue;
        cnt = (cnt + count(i + 1, next[j][c], o || (next[j][c] == s.size()))) % MOD;
    }
    return dp[i][j][o] = cnt;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin >> n >> s;
    buildKMP();
    memset(dp, -1, sizeof(dp));
    printf("%d\n", count(0, 0, 0));
    return 0;
}
