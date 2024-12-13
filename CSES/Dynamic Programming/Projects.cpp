#include <stdio.h>
#include <vector>
#include <map>

// Projects: Range Compression
// Source: https://codeforces.com/blog/entry/70018

#define ll long long

struct Project {
    int start, end, reward;
};

struct Pair {
    int start, reward;

    Pair(int start = 0, int reward = 0) : start(start), reward(reward) {};
};

Project projects[200001];
std::vector<Pair> compressedProjects[400001];
ll dp[400001];

int main() {

    int n;
    scanf("%d", &n);

    std::map<int, int> compress = std::map<int, int>();
    for(int i =0 ; i < n; i++) {
        scanf("%d%d%d", &projects[i].start, &projects[i].end, &projects[i].reward);
        projects[i].end++;
        compress[projects[i].start]; compress[projects[i].end]; // Create the keys in the map to access later
    }

    // Assigns each received value to a coordinate
    int coords = 0;
    for(auto& value : compress)
        value.second = coords++;

    // Many projects can end in the same day, so it's needed a list of them
    for(int i = 0; i < n; i++)
        compressedProjects[compress[projects[i].end]].emplace_back(compress[projects[i].start], projects[i].reward);
    
    for(int day = 0; day < coords; day++) {
        dp[day] = (day ? dp[day-1] : 0);
        for(auto project : compressedProjects[day]) // Check the projects that end this day
            dp[day] = std::max(dp[day], dp[project.start] + project.reward); // dp[start] is already calculated
    }

    printf("%lli\n", dp[coords-1]);

    return 0;
}