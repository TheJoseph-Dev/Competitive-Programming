#include <stdio.h>
#include <algorithm>

#define ll long long

struct Project {
    int start, end, reward;
};

Project projects[200001];
ll dp[400001];

bool byEnd(const Project& lhs, const Project& rhs) {
    return lhs.end < rhs.end;
}

int main() {

    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
        scanf("%d%d%d", &projects[i].start, &projects[i].end, &projects[i].reward);

    std::sort(projects, projects+n, byEnd);
    dp[0] = projects[0].reward;

    for(int day = 1; day < n; day++) {
        int l = 0, r = day-1, lastAvailableProj = -1;
        while(l <= r) {
            int mid = (l+r)/2;
            
            if(projects[mid].end < projects[day].start) {
                lastAvailableProj = mid;
                l = mid + 1;
            }
            else r = mid-1;
        }
        
        dp[day] = std::max(dp[day-1], projects[day].reward + (lastAvailableProj == -1 ? 0 : dp[lastAvailableProj]) );
    }

    printf("%lli\n", dp[n-1]);

    return 0;
}