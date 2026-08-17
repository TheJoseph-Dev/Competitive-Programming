#include <stdio.h>
#include <algorithm>
#include <set>
#include <queue>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using pbset = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
constexpr int maxN = 1e5+4;
constexpr ll LLINF = 1e18;

struct P {
    int x, y;
};
P sg[maxN][2];

struct E {
    int i;
    bool e;
    bool operator<(const E& other) const { 
        if(e && other.e) return sg[i][1].x < sg[other.i][1].x;
        if(e && !other.e) if(sg[i][1].x != sg[other.i][0].x) return sg[i][1].x < sg[other.i][0].x; else return e > other.e;
        if(!e && other.e) if(sg[i][0].x != sg[other.i][1].x) return sg[i][0].x < sg[other.i][1].x; else return e > other.e;
        if(!e && !other.e) return sg[i][0].x < sg[other.i][0].x;
    }
};

int n;
int main() {
    scanf("%d", &n);
    std::vector<E> events;
    std::vector<int> ps;
    for(int i = 0; i < n; i++) {
        scanf("%d%d%d%d", &sg[i][0].x, &sg[i][0].y, &sg[i][1].x, &sg[i][1].y);
        if(sg[i][0].y == sg[i][1].y) { events.push_back({i, 0}); events.push_back({i, 1}); }
        else ps.push_back(i);
    }
    std::sort(events.begin(), events.end());
    std::sort(ps.begin(), ps.end(), [&](int a, int b){if(sg[a][0].x != sg[b][0].x) return sg[a][0].x < sg[b][0].x; return sg[a][0].y < sg[b][0].y;});
    if(events.empty() || ps.empty()) { puts("0"); return 0; }
    ll cnt = 0;
    pbset<int> on;
    int i = 0;
    const int offset = 1e6+1;
    for(E e : events) {
        int x = sg[e.i][e.e].x, y = sg[e.i][0].y + offset;
        while(i < ps.size() && sg[ps[i]][0].x < x) { 
            int yl = sg[ps[i]][0].y + offset, yr = sg[ps[i]][1].y + offset;
            if(yl > yr) std::swap(yl, yr);
            cnt += (on.order_of_key(yr+1)-on.order_of_key(yl));
            i++;
        }
        if(!e.e) on.insert(y); else on.erase(y);
    }
    
    printf("%lld\n", cnt);
    
    return 0;
}