#include <stdio.h>
#include <map>

constexpr int maxN = 2e5+2;
int main() {
    int n;
    scanf("%d", &n);

    int arr[maxN];
    long long count = 0;
    
    for(int i = 0; i < n; i++) scanf("%d", arr+i);

    std::map<int, bool> cMap;
    for(int b = 0, f = 0; f < n; f++) {
        while(cMap[arr[f]]) {
            cMap[arr[b]] = false;
            if(arr[b++] == arr[f]) break;
        }
        
        cMap[arr[f]] = true;
        count += (f-b+1);
    }

    printf("%lld\n", count);

    return 0;
}