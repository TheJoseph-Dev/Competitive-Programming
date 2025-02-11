#include <stdio.h>
#include <set>

int main() {

    std::set<int> set = std::set<int>();
    int n;
    scanf("%d", &n);

    int x;
    while(n--) {
        scanf("%d", &x);
        set.insert(x);
    }

    printf("%d\n", set.size());

    return 0;
}