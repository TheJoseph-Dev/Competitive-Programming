#include <stdio.h>

/*
1
1 = 1

2 (v[i-1]*2)
1+1 = 1
2 = 1

3 (v[i-1]*2)
1+1+1 = 1
1+2 = 2
3 = 1

4 (v[i-1]*2)
1+1+1+1 = 1
2+1+1 = 3
3+1 = 2
4 = 1
2+2 = 1

5 (v[i-1]*2)
1+1+1+1+1 = 1
2+1+1+1 = 4
3+1+1 = 3
4+1 = 2
5 = 1
2+2+1 = 3
3+2 = 2

6 (v[i-1]*2)
1+1+1+1+1+1 = 1
2+1+1+1+1 = 5
3+1+1+1 = 4
4+1+1 = 3
5+1 = 2
6 = 1
2+2+2 = 1
3+3 = 1
3+2+1 = 6
4+2 = 2
2+2+1+1 = 6

7 (v[i-1]*2 - v[i-7])
1+1+1+1+1+1+1 = 1
2+1+1+1+1+1 = 6
3+1+1+1+1 = 5
4+1+1+1 = 4
5+1+1 = 3
6+1 = 2
5+2 = 2
4+3 = 2
4+2+1 = 6
3+2+2 = 3
2+2+2+1 = 4
3+2+1+1 = 12
2+2+1+1+1 = 10
3+3+1 = 3

8 (v[i-1]*2 - v[i-7])

*/

// n <= 10^6, O(n)

#define MOD 1000000007

inline int pMod(int i, int n) {
    return (i % n + n) % n;
}

int countDiceCombination(int sum) {
    int* dp = new int[sum+1];
    dp[0] = dp[1] = 1;
    for(int i = 2; i <= sum; i++)
        dp[i] = pMod((((dp[i-1]*2)%MOD) - (i > 6 ? dp[i-7]%MOD : 0)), MOD);

    return dp[sum];
}

int main() {

    int n;
    scanf("%d", &n);

    printf("%d\n", countDiceCombination(n));

    return 0;
}