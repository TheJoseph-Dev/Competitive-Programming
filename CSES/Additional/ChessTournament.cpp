#include <stdio.h>
#include <algorithm>
#include <queue>

constexpr int maxN = 1e5+2;
struct P {
    int g, i;
    bool operator<(const P& other) const {
        return this->g < other.g;
    }
};
int main() {

    int n;
    scanf("%d", &n);

    P p;
    std::priority_queue<P> pq;
    for(int i = 0; i < n; i++) {
        scanf("%d", &p.g);
        p.i = i;
        if(p.g) pq.push(p);
    }

    std::vector<P> games;
    while(!pq.empty()) {
        P player = pq.top();
        pq.pop();

        std::vector<P> temp;
        while(player.g) {
            if(pq.empty()) { puts("IMPOSSIBLE"); return 0; }
            P match = pq.top();
            pq.pop();
            --player.g;
            if(--match.g) temp.push_back(match);
            games.push_back({player.i+1, match.i+1});
        }
        for(P p : temp) pq.push(p);
    }

    printf("%d\n", games.size());
    for(P g : games) printf("%d %d\n", g.g, g.i);

    return 0;
}