#include <stdio.h>
#include <algorithm>
constexpr int maxN = 2e4+5;
char s[32];
int bs[maxN];
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for(int j = 0; j < n; j++) {
        scanf("%s", s);
        int b = 0;
        for(int i = 0; i < k; i++) b |= (s[i]-'0')<<i;
        bs[j] = b;
    }

    int mn = 32;
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            mn = std::min(mn, __builtin_popcount(bs[i]^bs[j]));
    printf("%d\n", mn);
    return 0;
}