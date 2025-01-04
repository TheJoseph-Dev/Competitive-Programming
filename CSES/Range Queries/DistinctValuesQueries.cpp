#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <unordered_map>

constexpr int maxN = 2e5+1;

struct Query {
    int l, r, id, block, v;
};

bool mocmp(const Query& lhs, const Query& rhs) {
    if(lhs.block != rhs.block) return lhs.block < rhs.block;
    return lhs.r < rhs.r;
}

bool byID(const Query& lhs, const Query& rhs) {
    return lhs.id < rhs.id;
}

void MO(int arr[maxN], Query queries[maxN], int n) {
    int distinct = 0, freqMap[maxN] = {0};
    
    int l = 0, r = -1; // Iterators
    for(int q = 0; q < n; q++) {
        while(l > queries[q].l) distinct += (++freqMap[arr[--l]] == 1);
        while(r < queries[q].r) distinct += (++freqMap[arr[++r]] == 1);
        while(l < queries[q].l) distinct -= (--freqMap[arr[l++]] == 0);
        while(r > queries[q].r) distinct -= (--freqMap[arr[r--]] == 0);
        queries[q].v = distinct;
    }
}

int main() {

    int n, q;
    scanf("%d%d", &n, &q);

    std::unordered_map<int, int> compress = std::unordered_map<int, int>();
    int arr[maxN];
    for(int i = 0; i < n; i++) {
        scanf("%d", arr+i);
        compress[arr[i]];
    }

    int coord = 0;
    for(auto& v : compress)
        v.second = coord++;
    
    for(int i = 0; i < n; i++) arr[i] = compress[arr[i]];

    const int blockSize = sqrt(n); 
    Query queries[maxN];

    int a, b;
    for(int i = 0; i < q; i++) {
        scanf("%d%d", &a, &b);
        queries[i] = {a-1, b-1, i, a/blockSize, 0};
    }

    std::sort(queries, queries + q, mocmp);

    MO(arr, queries, q);

    std::sort(queries, queries + q, byID);

    for(int i = 0; i < q; i++) printf("%d\n", queries[i].v);

    return 0;
}