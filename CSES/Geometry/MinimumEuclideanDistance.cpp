#include <stdio.h>
#include <algorithm>
#include <vector>
#include <climits>

typedef long long ll;
constexpr int maxN = 2e5 + 1;

struct Point {
    int x, y;
};

ll minDist = LLONG_MAX;
int n;
Point points[maxN];
bool isLeft[maxN];

ll square(ll x) {
    return x * x;
}

ll sqrdist(const Point& lhs, const Point& rhs) {
    ll dx = lhs.x - rhs.x;
    ll dy = lhs.y - rhs.y;
    return square(dx) + square(dy);
}

void divideNConquer(int* PX, int* PY, int size) {
    if (size == 1) return;
    int hsz = size / 2 + 1;
    int* LX = new int[hsz], * LY = new int[hsz], * RX = new int[hsz], * RY = new int[hsz], lxn = 0, lyn = 0, rxn = 0, ryn = 0;
    for (int i = 0; i < size; i++) {
        if (i < size / 2) {
            LX[lxn++] = PX[i];
            isLeft[PX[i]] = true;
            continue;
        }

        RX[rxn++] = PX[i];
        isLeft[PX[i]] = false;
    }

    for (int i = 0; i < size; i++)
        if (isLeft[PY[i]])  LY[lyn++] = PY[i];
        else               RY[ryn++] = PY[i];

    divideNConquer(LX, LY, lyn);
    divideNConquer(RX, RY, ryn);

    ll midX = points[LX[lxn - 1]].x;
    int* stripe = new int[size], p = 0;
    for (int i = 0; i < size; i++)
        if (square(points[PY[i]].x - midX) < minDist)
            stripe[p++] = PY[i];

    for (int i = 0; i < p; i++)
        for (int j = i + 1; j < p && square(points[stripe[i]].y - points[stripe[j]].y) < minDist; j++)
            minDist = std::min(minDist, sqrdist(points[stripe[i]], points[stripe[j]]));
}

int main() {
    scanf("%d", &n);

    int sortedX[maxN], sortedY[maxN], size = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &points[i].x, &points[i].y);
        sortedX[size] = i;
        sortedY[size] = i;
        size++;
    }
    
    std::sort(sortedX, sortedX + size, [](int A, int B) {
        return points[A].x < points[B].x;
    });

    std::sort(sortedY, sortedY + size, [](int A, int B) {
        return points[A].y < points[B].y;
    });

    divideNConquer(sortedX, sortedY, n);

    printf("%lld\n", minDist);
}