#include <stdio.h>

#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

constexpr int maxN = 1e6;

int main() {

    int n;
    scan(n);

    int x, freq[maxN+1] = {false};
    for(int i = 0; i < n; i++) {
        scan(x);
        freq[x]++;
    }

    for(int gdc = maxN; gdc >= 1; gdc--) {
        int f = 0;
        for(int m = 1; m*gdc <= maxN; m++)
            f += freq[m*gdc];
        
        if(f >= 2) { printf("%d\n", gdc); break; }
    }

    return 0;
}