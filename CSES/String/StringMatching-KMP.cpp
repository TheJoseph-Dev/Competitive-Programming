#include <iostream>
#include <vector>
#include <string>
 
void computeLPS(const std::string& pattern, std::vector<int>& lps) {
    lps[0] = 0;
    int i = 1, len = 0;
    while (i < pattern.size()) {
        if (pattern[i] == pattern[len]) lps[i++] = ++len;
        else if (len != 0) len = lps[len - 1];
        else lps[i++] = 0;
    }
}

int KMP(std::string& str, std::string& pattern) {
    int M = pattern.length(), N = str.length();
    std::vector<int> lps(M);

    computeLPS(pattern, lps);

    int i = 0, j = 0, c = 0;
    while ((N - i) >= (M - j)) {
        if (pattern[j] == str[i]) { j++; i++; }
        if (j == M) {
            c++;
            j = lps[j - 1];
        }
        else if (i < N && pattern[j] != str[i]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    return c;
}
 
int main() {
    std::ios::sync_with_stdio(0);
    std::string str, pattern;
 
    std::cin >> str;
    std::cin >> pattern;
 
    std::cout << KMP(str, pattern) << std::endl;
 
    return 0;
}