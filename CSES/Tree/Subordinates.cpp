#include <stdio.h>
#include <vector>

constexpr int maxN = 2e5+1;

std::vector<int> adj[maxN];

int subordinates[maxN]; // DP
int countSubordinates(int node) {
    if(subordinates[node] != -1) return subordinates[node];

    int s = adj[node].size();
    for(int e : adj[node]) s += countSubordinates(e);

    return subordinates[node] = s;
}

int main() {

    int n;
    scanf("%d", &n);

    int boss;
    for(int i = 0; i < n-1; i++) {
        scanf("%d", &boss);
        adj[boss].push_back(i+2);
    }

    for(int i = 1; i <= n; i++) subordinates[i] = -1;
    countSubordinates(1);

    for(int i = 1; i <= n; i++) printf("%d ", subordinates[i]);

    return 0;
}