#include <iostream>
#include <vector>
#include <algorithm>
using ll = long long;
int main() {
    ll y, k;
    scanf("%lld%lld", &y, &k);

    std::vector<ll> divs;
    for(int i = 1; i*i <= y; i++)
        if(y%i == 0) {
            divs.push_back(i);
            if(y/i == i) continue;
            divs.push_back(y/i);
        }
    std::sort(divs.begin(), divs.end());
    
    ll x = 1, i = 0;
    ll cd = divs[0];
    for(; i < divs.size()-1; i++) {
        if((divs[i+1]-x)/cd <= k) {
            if((divs[i+1]-x)%cd == 0) {
                k -= (divs[i+1]-x)/cd;
                x = divs[i+1];
                cd = divs[i+1];
            }
        }
        else break;
    }
    
    x += k*divs[i];
    printf("%lld\n", x);
    
    return 0;
}