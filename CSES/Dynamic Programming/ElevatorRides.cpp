#include <stdio.h>
/*
    1 <= n <= 20
    1 <= x <= 10^9
    1 <= wi <= x
*/

#define ll long long

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define MAXBIN 21

struct Bin {
    int count, capacity;
    bool operator<(const Bin& other) const {
        if(this->count != other.count) return this->count < other.count;
        else return this->capacity < other.capacity;
    }
};

Bin dp[1048577];
int binpk(int n, int w[21], int k) {
    dp[0] = {1, 0};
    for(int mask = 1; mask < (1<<n); mask++) {
        dp[mask] = {MAXBIN, 0};
        for(int b = 0; b < n; b++) {
            if(!(mask&(1<<b))) continue;
            Bin bin = dp[mask^(1<<b)]; // Gets the submask
            if(bin.capacity + w[b] <= k) bin.capacity += w[b]; // Fits in the bin
            else { bin.count++; bin.capacity = w[b]; } // Goes to next bin
            dp[mask] = MIN(dp[mask], bin); // Get the most optimal
        }
    }

    return dp[(1<<n)-1].count;
}

int main() {

    int n, k, w[21];
    scanf("%d%d", &n, &k);

    for(int i = 0; i < n; i++)
        scanf("%d", w+i);

    int rides = binpk(n, w, k);
    printf("%d\n", rides);

    return 0;
}