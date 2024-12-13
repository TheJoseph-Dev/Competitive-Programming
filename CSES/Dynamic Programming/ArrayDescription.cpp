#include <stdio.h>
#include <math.h>

#define MOD 1000000007

int memo[100002][102];
int countArrays(int i, int lastV, int arr[100001], int n, int m) {
    if((i < n-1 && abs(arr[i+1]-arr[i]) > 1 && arr[i] && arr[i+1]) || (0 < i && i < n && arr[i] && abs(arr[i]-lastV) > 1)) return 0;
    if(i == n) return 1;

    if(memo[i][lastV+1] != -1) return memo[i][lastV+1];

    if(arr[i] != 0) return memo[i][lastV+1] = countArrays(i+1, arr[i], arr, n, m);

    int cnt = 0;
    for(int v = (lastV == -1 ? 1 : lastV-1); v <= (lastV == -1 ? m : lastV+2); v++) {
        if(v > m || v <= 0 || (lastV != -1 && abs(v-lastV) > 1)) continue;

        cnt = (cnt + countArrays(i+1, v, arr, n, m))%MOD;
    }


    return memo[i][lastV+1] = cnt;
}

int main() {

    int n, m, arr[100001];
    scanf("%d%d", &n, &m);

    for(int i = 0; i < n; i++)
        scanf("%d", arr+i);

    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= m+1; j++)
            memo[i][j] = -1;
    printf("%d\n", countArrays(0, -1, arr, n, m));

    return 0;
}