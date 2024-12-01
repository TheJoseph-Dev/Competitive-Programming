#include <stdio.h>
#include <vector>
#include <map>

std::map<int, int> ks(int k, int bags[101], int n) {
    int dp[101][10001] = {{0}};

    for(int i = 1; i <= n; i++)
        for(int c = 1; c <= k; c++)
            if(bags[i-1] > c) dp[i][c] = dp[i-1][c];
            else dp[i][c] = std::max(dp[i-1][c], dp[i-1][c-bags[i-1]] + bags[i-1]);

    std::map<int, int> set = std::map<int, int>();
    if(dp[n][k] != k) return set;
    
    /*
        0 0 0 0 0
        0 1 1 1 1
        0 1 2 3 3
        0 1 2 3 4
        0 1 2 3 4
    */

    int c = k;
    for(int i = n; i >= 1 && c; i--) {
        if(c < bags[i-1]) continue;
        if(dp[i][c] == dp[i-1][c-bags[i-1]]+bags[i-1]) {
            set[bags[i-1]]++;
            c-=bags[i-1];
        }
    }
    
    return set;
}

int main() {

    int n;
    scanf("%d", &n);

    int bags[101], sum = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", bags+i);
        sum += bags[i];
    }

    if(sum&1) {
        puts("-1");
        return 0;
    }

    int target = sum/2;
    std::map<int, int> map = ks(target, bags, n);
    if(map.size() == 0) {
        puts("-1");
        return 0;
    }
    
    std::vector<int> alice = std::vector<int>(), bob = std::vector<int>();
    for(int i = 0; i < n; i++) {
        if(map[bags[i]]-- > 0) {
            alice.push_back(bags[i]);
            continue;
        }
        bob.push_back(bags[i]);
    }
    
    int a = target, b = target, ai=0,bi=0;
    while(a || b) {
        if(a < b) {
            b -= bob[bi];
            printf("%d ", bob[bi++]);
        }
        else {
            a -= alice[ai];
            printf("%d ", alice[ai++]);
        } 
    }

    return 0;
}