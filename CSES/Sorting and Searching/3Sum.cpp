#include <stdio.h>
#include <algorithm>

constexpr int maxN = 5001;

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
        scanf("%d", &nums[i].v);
        nums[i].i = i;
    }

    std::sort(nums, nums+n);

    for(int i = 0; i < n; i++) {
        if(x < nums[i].v) continue;
        int target = x-nums[i].v;
        for(int j = 0, k = n-1; j < k;) {
            if(j == i) j++;
            if(k == i) k--;
            if(j >= k) break;
            if(nums[j].v + nums[k].v == target) {
                printf("%d %d %d\n", nums[i].i+1, nums[j].i+1, nums[k].i+1);
                return 0;
            }

            if(nums[j].v + nums[k].v > target) k--;
            else j++;
        }
    }

    puts("IMPOSSIBLE");

    return 0;
}