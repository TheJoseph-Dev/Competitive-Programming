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

    int n;
    scanf("%d", &n);

    N nums[maxN];
    for(int i = 0; i < n; i++) {
        scanf("%d", &nums[i].v);
        nums[i].i = i;
    }

    std::sort(nums, nums+n);

    int rounds = 1;
    for(int i = 1; i < n; i++)
        rounds += (nums[i].i < nums[i-1].i);

    printf("%d\n", rounds);

    return 0;
}