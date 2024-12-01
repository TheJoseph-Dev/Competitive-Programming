#include <stdio.h>

/*
    A B   A
    0 0 = 0
    0 1 = 1
    1 0 = 0
    1 1 = 1

    ~A&B|A&B
*/

#define ll long long

void bitswap(ll& a, ll& b) {
    ll temp = a;
    a |= b;
    b &= ~(a^temp);
}

int main() {

    int n;
    scanf("%d", &n);

    ll nums[1000001];
    for(int i = 0; i < n; i++)
        scanf("%lli", nums+i);

    for(int b = 0; b < 63; b++) {
        int bits = 0;
        ll mask = (1LL << b);
        for(int i = 0; i < n; i++) {
            bits += ((nums[i]&mask) != 0);
            nums[i]&=~mask;
        }

        for(int i = 0; i < bits; i++)
            nums[i] |= mask;
    }

    for(int i = 0; i < n; i++)
        printf("%lli ", nums[i]);
}