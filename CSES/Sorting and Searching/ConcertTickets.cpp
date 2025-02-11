#include <stdio.h>
#include <set>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    int p;
    std::multiset<int> tickets;
    while(n--) {
        scanf("%d", &p);
        tickets.insert(p);
    }

    int customer;
    while(m--) {
        scanf("%d", &customer);
        auto ticket = tickets.upper_bound(customer);
        if(ticket == tickets.begin()) { puts("-1"); continue; }
        printf("%d\n", *--ticket);
        tickets.erase(ticket);
    }

    return 0;
}