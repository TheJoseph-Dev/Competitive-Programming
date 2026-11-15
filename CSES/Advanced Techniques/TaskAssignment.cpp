#include <stdio.h>
#include <vector>
using ll = long long;
constexpr ll LLINF = 1e18;
// Returns minimum cost assignment.
// assignment[i] = column assigned to row i.
ll hungarian(const std::vector<std::vector<ll>>& cost, std::vector<int>& assignment) {
    int n = cost.size() - 1; // cost is 1-indexed

    std::vector<ll> u(n + 1), v(n + 1);
    std::vector<int> p(n + 1), way(n + 1);

    for (int i = 1; i <= n; i++) {
        p[0] = i;

        int j0 = 0;
        std::vector<ll> minv(n + 1, LLINF);
        std::vector<bool> used(n + 1, false);

        do {
            used[j0] = true;

            int i0 = p[j0];
            ll delta = LLINF;
            int j1 = 0;

            for (int j = 1; j <= n; j++) {
                if (used[j]) continue;
                ll cur = cost[i0][j] - u[i0] - v[j];
                if (cur < minv[j]) {
                    minv[j] = cur;
                    way[j] = j0;
                }

                if (minv[j] < delta) {
                    delta = minv[j];
                    j1 = j;
                }
            }

            for (int j = 0; j <= n; j++) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else minv[j] -= delta;
            }

            j0 = j1;

        } while (p[j0] != 0);

        // Augment matching.
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0 != 0);
    }

    assignment.assign(n + 1, 0);

    // p[j] = row assigned to column j.
    for (int j = 1; j <= n; j++) assignment[p[j]] = j;
    return -v[0];
}

int main() {
    int n;
    scanf("%d", &n);

    std::vector<std::vector<ll>> mtx(n+1, std::vector<ll>(n+1));
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            scanf("%lld", &mtx[i][j]);
    
    std::vector<int> ass;
    ll mc = hungarian(mtx, ass);
    printf("%lld\n", mc);
    for(int i = 0; i < n; i++) printf("%d %d\n", i+1, ass[i+1]);    
    return 0;
}