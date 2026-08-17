#include <iostream>
#include <vector>
#include <string>
#include <cstring>
 
void computeLPS(const std::string& pattern, std::vector<int>& lps) {
    lps[0] = 0;
    int i = 1, len = 0;
    while (i < pattern.size()) {
        if (pattern[i] == pattern[len]) lps[i++] = ++len;
        else if (len != 0) len = lps[len - 1];
        else lps[i++] = 0;
    }
}

constexpr int maxN = 1e6+2;

int z[maxN];
// O(n+m)
void genZ(const std::string& s) {
    memset(z, 0, s.size()*sizeof(int));
    int l = 0, r = 0;
    for(int i = 1; i < s.size(); i++) {
        if(i <= r) z[i] = std::min(z[i-l], r-i+1);
        while(i+z[i] < s.size() && s[z[i]] == s[i+z[i]]) z[i]++; 
        if(i+z[i]-1 > r) { l = i; r = i+z[i]-1; }
    }
}
 
int main() {
    std::ios::sync_with_stdio(0);
    std::string str;
    std::cin >> str;
    size_t n = str.size();
    std::vector<int> lps(n, 0);
    computeLPS(str, lps);
    genZ(str);
    
    for(int i = 0; i < n; i++) printf("%d ", z[i]); putchar('\n');
    for(int i = 0; i < n; i++) printf("%d ", lps[i]); 
    return 0;
}