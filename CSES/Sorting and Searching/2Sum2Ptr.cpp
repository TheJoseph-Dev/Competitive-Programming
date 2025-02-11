#include <stdio.h>
#include <algorithm>

constexpr int maxN = 2e5+1;

struct N {
    int v, i;

    bool operator<(const N& other) const {
        return this->v < other.v;
    }
};

int main() {

    int n, x;
    scanf("%d%d", &n, &x);

    N nums[maxN];
    for(int i = 0; i < n; i++) {
        scanf("%d", nums+i);
        nums[i].i = i+1;
    }

    std::sort(nums, nums+n);

    for(int i = 0, j = n-1; i < j;) {
        if(nums[i].v + nums[j].v == x) {
            printf("%d %d\n", nums[i].i, nums[j].i);
            return 0;
        }

        if(nums[i].v + nums[j].v > x) j--;
        else i++;
    }

    puts("IMPOSSIBLE");

    return 0;
}