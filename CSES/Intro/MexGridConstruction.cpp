#include <stdio.h>
constexpr int maxN = 1e3+2;
int main() {
    int n;
    scanf("%d", &n);

    int m[maxN][maxN] = {};
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            bool mex[maxN] = {};
            for(int k = j-1; k >= 0; k--) mex[m[i][k]] = true;
            for(int k = i-1; k >= 0; k--) mex[m[k][j]] = true;
            while(mex[m[i][j]]) m[i][j]++;
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            printf("%d ", m[i][j]);
        putchar('\n');
    }

    return 0;
}