#include <stdio.h>
#include <algorithm>
constexpr int maxN = 1e3+4;
char o[maxN][maxN], t[maxN][maxN], tt[maxN][maxN];
int n, m;
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) scanf("%s", o[i]);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            t[i][j] = o[i][j];

    auto cmp = []() -> bool {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                if(o[i][j] != t[i][j]) return false;
        return true;
    };

    auto rot1 = []() {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                tt[i][j] = t[i][j];
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                t[i][j] = tt[j][m-i-1];
    };

    auto rot2 = []() {
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                tt[i][j] = t[i][j];
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                t[i][j] = tt[j][n-i-1];
    };

    auto mir = []() {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) t[i][j] = o[i][m-j-1];
    };

    int cnt = 0;
    for(int i = 0; i < 4; i++) {
        if(!(i&1) || ((i&1) && n == m)) cnt += cmp();
        if(i&1) rot2(); else rot1(); 
    }

    mir();

    for(int i = 0; i < 4; i++) {
        if(!(i&1) || ((i&1) && n == m)) cnt += cmp();
        if(i&1) rot2(); else rot1(); 
    }

    printf("%d\n", cnt);
    return 0;
}