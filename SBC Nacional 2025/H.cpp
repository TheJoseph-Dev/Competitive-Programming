#include <stdio.h>
#include <cstring>
#include <vector>
constexpr int maxN = 1e5+2;
int main() {
    int n, a[maxN], nge[maxN];
    memset(nge, -1, sizeof(nge));
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", a+i);
    std::vector<int> stk;
    for(int i = 0; i < n; i++) {
        while(stk.size() && a[stk.back()] < a[i]) {
            nge[stk.back()] = i;
            stk.pop_back();
        }
        stk.push_back(i);
    }
    int g = 0;
    for(int i = 0; i+1; g++) i=nge[i]; 
    printf("%d\n", g);
    return 0;
}