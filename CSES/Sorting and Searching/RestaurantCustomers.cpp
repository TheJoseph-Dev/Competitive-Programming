#include <stdio.h>
#include <algorithm>

constexpr int maxN = 4e5+1;

struct Event {
    int time;
    bool type;

    bool operator<(const Event& other) const {
        return this->time < other.time;
    }
};

int main() {

    int n;
    scanf("%d", &n);
    n <<= 1;

    int a, b;
    Event events[maxN];
    for(int i = 0; i < n; i+=2) {
        scanf("%d%d", &a, &b);
        events[i] = {a, 0};
        events[i+1] = {b, 1};
    }

    std::sort(events, events+n);

    int max = 0, current = 0;
    for(int i = 0; i < n; i++) {
        if(events[i].type) current--; 
        else current++;
        max = std::max(max, current);
    }

    printf("%d\n", max);

    return 0;
}