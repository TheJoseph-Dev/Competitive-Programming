#include <stdio.h>
#include <map>

//#define DEBUG_H
//#include "../../Debug.h"

constexpr int maxN = 2e5+2;
int main() {
    int n, k;
    scanf("%d%d", &n, &k);

    int arr[maxN];
    long long count = 0;
    
    for(int i = 0; i < n; i++) scanf("%d", arr+i);

    std::map<int, int> cMap;
    for(int b = 0, f = 0; f < n; f++) {
        cMap[arr[f]]++;
        while(cMap.size() >= k+1) {
            if(!--cMap[arr[b]]) cMap.extract(arr[b]);
            b++;
        }
        
        count += (f-b+1);
    }

    printf("%lld\n", count);

    return 0;
}