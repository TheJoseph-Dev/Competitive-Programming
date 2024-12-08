#include <iostream>
#include <string>

int dp[5001][5001];
int levenshtein(const std::string& s1, const std::string& s2) {
    for (int i = 0; i <= s1.size(); i++) dp[i][0] = i;
    for (int j = 0; j <= s2.size(); j++) dp[0][j] = j;

    for (int i = 1; i <= s1.size(); i++)
        for (int j = 1; j <= s2.size(); j++)
            if (s1[i - 1] == s2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else dp[i][j] = std::min( dp[i][j - 1], std::min( dp[i - 1][j], dp[i-1][j-1] )) + 1;

    return dp[s1.size()][s2.size()];
}

int main() {

    std::ios::sync_with_stdio(0);

    std::string s1, s2;
    std::cin >> s1 >> s2;

    int distance = levenshtein(s1, s2);
    printf("%d\n", distance);

    return 0;
}