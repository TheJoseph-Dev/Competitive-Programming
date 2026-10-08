#include <iostream>
#include <string>
#include <unordered_map>
#include <cstring>

constexpr int INF = 2e9;
constexpr int maxMsk = (1<<8)-1, maxN = 4100;
int n;
std::string s;
#define dbgbin(n) do { printf(#n " = "); for(int bit = 7; bit >= 0; bit--) putchar(((n>>bit)&1)+'0'); putchar('\n'); } while(0)
int readS(int i) {
    int msk = 0;
    for(int j = 0; j < 8; j++)
        if(i-j >= 0 && i-j < n) msk |= ((s[i-j]-'0')<<j);
    //dbgbin(msk);
    return msk;
}
//         11111111
// 0000000000000000
// 0000000000111101
//         00111101
int setMsk(int i, int base, int msk) {
    if(i < 7) return ((msk^(base<<(7-i)))&maxMsk);
    //else if(i >= n) return (msk^(base>>(i-n+1)))&maxMsk;
    else return ((msk^base)<<1)&maxMsk;
}

int smsks[maxN+14];
int memo[(1<<8)][maxN+14];
int mnop(int base, int msk, int i) {
    if(i == n+7) return 0;
    if(memo[msk][i] != -1) return memo[msk][i];
    int mn = INF;
    if(i >= 7) {
        int msb = (msk&(1<<7)), msb2 = (smsks[i]&(1<<7));
        if(msb != msb2 && (base&(1<<7)) ) {
            mn = std::min(mn, mnop(base, setMsk(i, base, msk), i+1)+1);
            return memo[msk][i] = mn;
        }
        else if(msb != msb2) return memo[msk][i] = mn;

        if(msb == msb2 && (base&(1<<7))) {
            mn = std::min(mn, mnop(base, setMsk(i, 0, msk), i+1));
            return memo[msk][i] = mn;
        }
    }
    mn = std::min(mn, mnop(base, setMsk(i, 0, msk), i+1));
    mn = std::min(mn, mnop(base, setMsk(i, base, msk), i+1)+1);
    return memo[msk][i] = mn;
}
int main() {
    std::cin >> n >> s;
    for(int i = 0; i <= n+7; i++) smsks[i] = readS(i);
    int mn = INF, mnb = INF;
    for(int b = (1<<8)-1; b >= 0; b--) {
        memset(memo, -1, sizeof(memo));
        int o = mnop(b, 0, 0);
        if(mn >= o) {
            mn = o;
            mnb = b;
        }
    }
    for(int i = 7; i >= 0; i--) putchar(!!(mnb&(1<<i))+'0');
    printf(" %d\n", mn);
    return 0;
}