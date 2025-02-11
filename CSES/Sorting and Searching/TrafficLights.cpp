#include <stdio.h>
#include <set>

struct Segment {
    int i, f;

    bool operator<(const Segment& other) const {
        return this->i < other.i;
    }
};

int main() {

    int len, n;
    scanf("%d%d", &len, &n);

    std::set<Segment> segments;
    std::multiset<int> lengths;
    segments.insert({0, len});
    lengths.insert(len);

    int p;
    while(n--) {
        scanf("%d", &p);
        auto seg = segments.upper_bound({p, 0});
        if(seg != segments.begin()) seg = std::prev(seg);
        Segment current = *seg;
        segments.erase(seg);
        segments.insert({current.i, p});
        segments.insert({p, current.f});

        lengths.erase(lengths.find(current.f-current.i));
        lengths.insert(p-current.i);
        lengths.insert(current.f-p);
        printf("%d ", *std::prev(lengths.end()));
    }

    return 0;
}