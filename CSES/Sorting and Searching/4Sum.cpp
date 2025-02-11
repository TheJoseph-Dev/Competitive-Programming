#include <stdio.h>
#include <map>

constexpr int maxN = 1e3+1;

int main() {

    int n, x;
    scanf("%d%d", &n, &x);

    int nums[maxN];
    for(int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    std::map<int, std::pair<int, int>> map;
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            if(nums[i]+nums[j] < x)
                map[nums[i]+nums[j]] = {i, j};

    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++) {
            int target = x-(nums[i]+nums[j]);
            if(map.find(target) == map.end()) continue;
            auto p = map[target];
            if(i == p.first || i == p.second || j == p.first || j == p.second) continue;
            printf("%d %d %d %d\n", i+1, j+1, p.first+1, p.second+1);
            return 0;
        }

    puts("IMPOSSIBLE");

    return 0;
}