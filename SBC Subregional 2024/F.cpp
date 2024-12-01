#include <stdio.h>

// 1 1 2 3 ...

#define ll long long int

ll fib(int n) {
    ll dp[2] = {0,1};
    bool f = false;
    while(n--) {
        dp[f] = dp[0]+dp[1];
        f = !f;
    }

    return dp[!f];
}

int main() {

    int n;
    scanf("%d", &n);

    ll num = fib(n);
    printf("%lli\n", num);

    return 0;
}