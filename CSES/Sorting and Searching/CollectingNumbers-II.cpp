#include <stdio.h>
#include <algorithm>

constexpr int maxN = 2e5+1;

struct N {
    int v, i;

    bool operator<(const N& other) const {
        return this->v < other.v;
    }
};

int arr[maxN];
N nums[maxN];
int main() {

    int n, q;
    scanf("%d%d", &n, &q);

    for(int i = 0; i < n; i++) {
        scanf("%d", &nums[i].v);
        nums[i].i = i;
        arr[i] = nums[i].v;
    }

    std::sort(nums, nums+n);

    int rounds = 1;
    for(int i = 1; i < n; i++)
        rounds += (nums[i].i < nums[i-1].i);

    /*
        4 2 1 5 3 | 3
        4 1 2 5 3 | 2
        3 1 2 5 4 | 3
        3 2 1 5 4 | 4
    */

    int a, b;
    while(q--) {
        scanf("%d%d", &a, &b);
        a--; b--;
        //printf("r: %d\n", rounds);
        if(a > b) std::swap(a,b);
        int ai = arr[a]-1;
        int bi = arr[b]-1;
        std::swap(arr[a], arr[b]);
        //printf("(%d, %d)\n", ai, bi);
        auto update = [&](bool contrib) {
            //for(int i = 0; i < n; i++) printf("%d ", nums[i].i); putchar('\n');
            if(ai) rounds += (nums[ai].i < nums[ai-1].i) * (contrib ? 1 : -1);
            if(ai < n-1) rounds += (nums[ai+1].i < nums[ai].i) * (contrib ? 1 : -1);
            if(ai < bi) {
                if(bi && bi-ai > 1) rounds += (nums[bi].i < nums[bi-1].i) * (contrib ? 1 : -1);
                if(bi < n-1) rounds += (nums[bi+1].i < nums[bi].i) * (contrib ? 1 : -1);
            }
            else {
                if(bi) rounds += (nums[bi].i < nums[bi-1].i) * (contrib ? 1 : -1);
                if(bi < n-1 && ai-bi > 1) rounds += (nums[bi+1].i < nums[bi].i) * (contrib ? 1 : -1);
            }
        };
        update(0);
        nums[ai].i = b;
        nums[bi].i = a;
        update(1);
        printf("%d\n", rounds);
    }

    return 0;
}