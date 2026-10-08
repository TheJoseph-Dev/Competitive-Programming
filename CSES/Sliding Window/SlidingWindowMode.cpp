 #include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

constexpr int maxN = 2e5+4;
int a[maxN];
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++) scanf("%d", a+i);
    std::set<std::pair<int, int>> fst;
    std::map<int, int> fq;
    for(int i = 0; i < k; i++) {
        if(fq.count(a[i]) == 0) fst.insert({-1, a[i]});
        else {
            auto it = fst.find({-fq[a[i]], a[i]});
            int nf = it->first-1;
            fst.erase(it);
            fst.insert({nf, a[i]});
        }
        fq[a[i]]++;
    }
    for(int i = k; i <= n; i++) {
        printf("%d ", fst.begin()->second);
        
        auto it = fst.find({-fq[a[i-k]], a[i-k]});
        int nf = it->first+1;
        fst.erase(it);
        fst.insert({nf, a[i-k]});
        fq[a[i-k]]--;

        if(fq.count(a[i]) == 0) fst.insert({-1, a[i]});
        else {
            auto it = fst.find({-fq[a[i]], a[i]});
            int nf = it->first-1;
            fst.erase(it);
            fst.insert({nf, a[i]});
        }
        fq[a[i]]++;
    }
    return 0;
}