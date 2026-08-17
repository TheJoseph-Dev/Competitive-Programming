#include <stdio.h>
#include <string.h>
#include <cmath>
#include <queue>
constexpr int maxN = 1e6+2;
 
size_t n;
char s[maxN];
int c[26] = {0};
bool solve(int i, char l) {
    if(i == n) return true;
    bool good = false;
    
    int f = 0;
    for(int j = 0; j < 26; j++)
        f = std::max(c[j], f);
    if(f > ceil((n-i)/2.0)) return false;
    
    for(int j = 0; j < 26 && !good; j++) {
        if(c[j] > ceil((n-i)/2.0)) return false;
        char ch = 'A'+j;
        if(!c[j] || l == ch) continue;
        s[i] = ch;
        c[j]--;
        good |= solve(i+1, ch);
        if(!good) c[j]++;
    }
    
    return good;
}
 
int main() {
    scanf("%s", s);
    n = strlen(s);
    for(int i = 0; i < n; i++)
        c[s[i]-'A']++;
 
    for(int i = 0; i < 26; i++) {
        if(c[i] <= ceil(n/2.0)) continue;
        puts("-1");
        return 0;
    }
    
    solve(0, 0);
    puts(s);
    return 0;
}