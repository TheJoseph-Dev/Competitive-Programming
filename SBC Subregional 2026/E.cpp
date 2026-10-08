#include <stdio.h>
#include <vector>
using ll = long long;
constexpr int maxN = 5e2+5;
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

struct N {
    int a, b;
};
N c1[maxN], c2[maxN];
int main() {
    int n, m1, m2;
    scanf("%d%d%d", &n, &m1, &m2);
    for(int i = 0; i < m1; i++) scanf("%d%d", &c1[i].a, &c1[i].b);
    for(int i = 0; i < m2; i++) scanf("%d%d", &c2[i].a, &c2[i].b);
    if(m1 != m2) { puts("-1"); return 0; }
    std::vector<std::vector<ll>> cost(m1+1, std::vector<ll>(m2+1, 1e9));
    for(int i = 0; i < m1; i++) {
        for(int j = 0; j < m2; j++) {
            int c = 0;
            if(c1[i].a != c2[j].a && c1[i].a != c2[j].b && c1[i].b != c2[j].a && c1[i].b != c2[j].b) c = 2;
            else if((c1[i].a == c2[j].a && c1[i].b != c2[j].b) || (c1[i].a != c2[j].a && c1[i].b == c2[j].b) || (c1[i].a == c2[j].b && c1[i].b != c2[j].a) || (c1[i].a != c2[j].b && c1[i].b == c2[j].a)) c = 1;
            //printf("%d =%d=> %d\n", i, c, j);
            cost[i+1][j+1] = c;
        }
    }
    std::vector<int> assignment;
    ll mncst = hungarian(cost, assignment);
    /*
    for(int i = 1; i < assignment.size(); i++) {
        int idx = assignment[i];
        //printf("%d : %d\n", i, idx); continue;
        printf("(%d-%d) =%d=> (%d-%d)\n", c1[i-1].a, c1[i-1].b, cost[i][idx], c2[idx-1].a, c2[idx-1].b);
    }
    */
    printf("%lld\n", mncst >= LLINF ? -1 : mncst);
    return 0;
}