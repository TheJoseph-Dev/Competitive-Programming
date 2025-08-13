#include <stdio.h>

constexpr int maxN = 1e6+1, maxM = 1e5+2;

short mobius[maxN];
int count[maxN], x[maxM];
void genMobius() {
    mobius[1] = -1;
    for (int i = 1; i < maxN; i++) {
        if (mobius[i] == 0) continue;
        mobius[i] *= -1;
        for (int j = (i<<1); j < maxN; j += i)
            mobius[j] += mobius[i];
    }
}


int main() {
    genMobius();

    int n;
    scanf("%d", &n);

    /*
        \sum{i=1}^n \sum{j=i+1}^n gcd(ai, aj) == 1
    */
   
    for(int i = 0; i < n; i++) {
        scanf("%d", x+i);
        for(int p = 1; p*p <= x[i]; p++)
            if(x[i]%p == 0) {
                count[p]++;
                if(x[i]/p != p) count[x[i]/p]++;
            }
    }

    long long c = 0;
    for(int i = 1; i < maxN; i++)
        c += ((long long)count[i]*(count[i]-1))/2*mobius[i];

    printf("%lld\n", c);

    return 0;
}