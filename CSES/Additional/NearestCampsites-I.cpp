#include <stdio.h>
#include <math.h>
#include <cstring>
#include <queue>
#include <algorithm>
#include <map>

using ll = long long;
constexpr int maxN = 1e5+1, INF = 2e9, MOD = 998244353;
constexpr ll LLINF = 1e18;


struct Point {
    int x, y;
    Point(int x = 0, int y = 0): x(x), y(y) {}
};

struct Node {
    Point p;
    int minx, maxx, miny, maxy;
    Node *l, *r;

    Node(Point p): p(p), minx(p.x), maxx(p.x), miny(p.y), maxy(p.y), l(0), r(0) {}
};

inline int rectDist1(const Point &q, Node* t) {
    if (!t) return INF;
    int dx = 0, dy = 0;
    if (q.x < t->minx) dx = t->minx - q.x;
    else if (q.x > t->maxx) dx = q.x - t->maxx;

    if (q.y < t->miny) dy = t->miny - q.y;
    else if (q.y > t->maxy) dy = q.y - t->maxy;

    return dx + dy;
}

inline int dist1(const Point& a, const Point& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

bool cmpx(const Point& a, const Point& b) {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}

bool cmpy(const Point& a, const Point& b) {
    return a.y != b.y ? a.y < b.y : a.x < b.x;
}

class KDTree2D {
    Node* root;

    std::priority_queue<std::pair<int, Node*>> pq;

    Node* Build(Point* a, int l, int r, bool axis) {
        if (l >= r) return 0;

        int m = (l + r) >> 1;

        std::nth_element(a + l, a + m, a + r, axis ? cmpx : cmpy);

        Node* t = new Node(a[m]);

        t->l = Build(a, l, m, !axis);
        t->r = Build(a, m + 1, r, !axis);

        if (t->l) {
            t->minx = std::min(t->minx, t->l->minx);
            t->maxx = std::max(t->maxx, t->l->maxx);
            t->miny = std::min(t->miny, t->l->miny);
            t->maxy = std::max(t->maxy, t->l->maxy);
        }

        if (t->r) {
            t->minx = std::min(t->minx, t->r->minx);
            t->maxx = std::max(t->maxx, t->r->maxx);
            t->miny = std::min(t->miny, t->r->miny);
            t->maxy = std::max(t->maxy, t->r->maxy);
        }

        return t;
    }

    void GetKNN(Node* t, const Point& p, int k) {
        if (!t) return;

        int d = dist1(p, t->p);

        if ((int)pq.size() < k || d < pq.top().first) {
            pq.push({d, t});
            if ((int)pq.size() > k) pq.pop();
        }

        Node *a = t->l, *b = t->r;
        int da = rectDist1(p, a);
        int db = rectDist1(p, b);

        if (da > db) {
            std::swap(a, b);
            std::swap(da, db);
        }

        GetKNN(a, p, k);

        if ((int)pq.size() < k || db <= pq.top().first) GetKNN(b, p, k);
    }

public:
    KDTree2D(Point a[], int n) {
        root = Build(a, 0, n, true);
    }

    std::vector<Point> QueryKNN(const Point& p, int k = 1) {
        while (!pq.empty()) pq.pop();

        if (k <= 0) return {};

        GetKNN(root, p, std::min(k, INF));

        std::vector<Point> ans;
        while (!pq.empty()) {
            ans.push_back(pq.top().second->p);
            pq.pop();
        }

        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};
 
Point pts[maxN];
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
 
    for(int i = 0; i < n; i++) scanf("%d%d", &pts[i].x, &pts[i].y);
    
    KDTree2D kdtree = KDTree2D(pts, n);
    int d = -1;
    Point q;
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &q.x, &q.y);
        int best = INF;
        auto knn = kdtree.QueryKNN(q);
        d = std::max(d, dist1(knn[0], q));
    }
 
    printf("%d\n", d);
 
    return 0;
}