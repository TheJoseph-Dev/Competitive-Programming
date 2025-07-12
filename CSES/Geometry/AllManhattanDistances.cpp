#include <stdio.h>
#include <algorithm>

/*
    sum_{i=0}^n sum_{j=i+1}^n |x_i - x_j| + |y_i - y_j|
    sum_{i=0}^n sum_{j=i+1}^n |x_i - x_j| +  sum_{i=0}^n sum_{j=i+1}^n |y_i - y_j|
    Let x[i] be the sorted array. Then:
    sum_{i=0}^n sum_{j=i+1}^n (x_j - x_i) + ...
    One can see that x[k] appears (n-k) times with minus sign and 
    k | times with + sign
    0 | 0 
    1 | 1
    2 | 2
    ...
    k times with plus sign 
    so now you can rewrite as: sum_{k=0}^n x[k]*k - x[k]*(n-k) => sum_{k=0}^n x[k]*(2*k-n)
*/

using i128 = __int128; 
void printi128(i128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) printi128(x / 10);
    putchar(x % 10 + '0');
}

constexpr int maxN = 2e5+1;
int x[maxN], y[maxN];
int main() {
    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
        scanf("%d%d", x+i, y+i);

    i128 sum = 0;
    std::sort(x, x+n);
    std::sort(y, y+n);

    for(int i = 0; i < n; i++)
        sum += (i128)(x[i] + y[i])*(2*i-n+1);

    printi128(sum);
    return 0;
}