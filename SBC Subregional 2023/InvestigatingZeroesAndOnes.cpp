#include <stdio.h>

int main() {

    int n;
    scanf("%d", &n);

    int seen[2] = {1, 0}; // How many subsequences (Even, Odd) were seen up until i
    
    long long count = 0;
    int bit, prfx = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &bit);
        prfx ^= bit; // Because the only thing that matters is the parity of the prefix, just apply XOR

        bool parity = prfx&1;
        seen[parity]++; // Seen another subsequence with given parity
        count += seen[!parity]; // The seen subsequences with opposite parity will count as more subarrays which keep the current parity up until i 
    }

    printf("%lld\n", count);

    return 0;
}