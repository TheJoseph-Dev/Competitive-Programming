#include <stdio.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
constexpr int maxN = 1e3+1;

int main() {
    
    int n, m;
    scanf("%d%d", &n, &m);
    
    int a[maxN], b[maxN];
    for(int i = 0; i < n; i++) scanf("%d", a+i);
    for(int i = 0; i < m; i++) scanf("%d", b+i);
    
    int lcs[maxN][maxN] = {0};
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            lcs[i][j] = a[i-1] == b[j-1] ? lcs[i-1][j-1]+1 : MAX(lcs[i-1][j], lcs[i][j-1]);
    
    printf("%d\n", lcs[n][m]);
    int stk[maxN], ptr = 0;
    for(int i = n, j = m; i >= 1 && j >= 1;)
        if(a[i-1] == b[j-1]) { stk[ptr++] = a[i-1]; i--; j--; }
        else if (lcs[i - 1][j] >= lcs[i][j - 1]) i--;
        else j--;

    while(ptr--) printf("%d ", stk[ptr]);
    return 0;
}