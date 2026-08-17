#include <stdio.h>
#include <string.h>
constexpr int maxN = 1e6+2;
int main() {
    char s[maxN];
    scanf("%s", s);
    int c[26] = {0};
    int n = strlen(s);
    for(int i = 0; i < n; i++) c[s[i]-'A']++;
    int odd = 0;
    for(int i = 0; i < 26; i++) odd += c[i]&1;
    if(odd > 1) { puts("NO SOLUTION"); return 0; }
    
    int oidx = -1;
    for(int j = 0; j < 26; j++) { if(c[j]&1) { oidx = j; continue; } int h = c[j]>>1; while(h--) putchar(j+'A'); }
    if(oidx+1) while(c[oidx]--) putchar('A'+oidx);
    for(int j = 25; j >= 0; j--) { if(j == oidx) continue; int h = c[j]>>1; while(h--) putchar(j+'A'); }
    return 0;
}