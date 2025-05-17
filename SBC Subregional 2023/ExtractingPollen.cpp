#include <stdio.h>

constexpr int maxN = 1e6+1;

int dSum(int n) {
    int sum = 0;
    while(n) {
        sum += n%10;
        n/=10;
    }
    return sum;
}

int main() {

    int n, k, flower;
    scanf("%d%d", &n, &k);

    int freq[maxN] = {0};
    while(n--) {
        scanf("%d", &flower);
        freq[flower]++;
    }

    for(int i = maxN-1; i >= 0; i--) {
        if(k <= freq[i]) {
            printf("%d\n", dSum(i));
            return 0;
        }
        k -= freq[i];
        freq[i-dSum(i)] += freq[i];
    }
    puts("0");

    return 0;
}