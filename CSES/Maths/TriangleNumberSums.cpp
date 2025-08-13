#include <stdio.h>
#include <vector>

using ll = long long;
int main() {

    int t;
    scanf("%d", &t); 

    std::vector<ll> triNums;
    ll i = 1;
    int s = 2;
    while(i <= 1e12) { // ~1e6
        triNums.push_back(i);
        i += s++;
    }

    ll x;
    next:
    while(t--) {
        scanf("%lld", &x);
        
        int l = 0, r = triNums.size()-1;
        while(l <= r) {
            int mid = (l+r) >> 1;
            if(triNums[mid] == x) { puts("1"); goto next; }
            if(triNums[mid] > x) r = mid-1;
            else l = mid+1;
        }

        for(int i = 0, j = triNums.size()-1; i <= j;) {
            if(triNums[i]+triNums[j] == x) { puts("2"); goto next; }
            if(triNums[i]+triNums[j] > x) j--;
            else i++;
        }

        puts("3");
    }

    return 0;
}