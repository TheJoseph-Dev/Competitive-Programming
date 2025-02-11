#include <stdio.h>

constexpr int maxN = 2e5+1;

#define ll long long

int main() {
 
    int n;
    scanf("%d", &n);
 
    ll nums[maxN];
    for(int i = 0; i < n; i++)
        scanf("%lli", nums+i);

    ll count = 0, prfx = 0;
    int map[maxN] = {0};
    map[0] = 1;
    for(int i = 0; i < n; i++) {
        prfx += nums[i];
        count += map[((prfx%n)+n)%n]++;
    }

    printf("%lli\n", count);
 
    return 0;
}