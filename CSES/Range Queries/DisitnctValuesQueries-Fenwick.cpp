#include <stdio.h>
#include <algorithm>
#include <unordered_map>

constexpr int maxN = 2e5+1;


// Sum Fenwick Tree 
// Use 1-index to avoid infinite loops!

class FenwickTree {
    int* tree;
    int size;
 
public:
    FenwickTree(int n) : size(n) {
        tree = new int[n + 1]();  // Indexed from 1 to n
    }

    /* 
    Destructor: Use it when inside a loop or need to avoid memory leak
    ~FenwickTree() {
	    delete[] tree;
    }
    */
 
    // Updates the Fenwick tree at position idx by adding val
    void Update(int idx, int val) {
        while (idx <= size) {
            tree[idx] += val;
            idx += idx & -idx;  // Move to the next index
        }
    }
 
private:

    // Queries the sum in the range [1, idx]
    int Query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & -idx;  // Move to the parent index
        }
        return sum;
    }
 
 public:
    // Queries the sum in the range [a, b]
    int RangeQuery(int a, int b) {
        return Query(b) - Query(a - 1);
    }
};

struct Query {
    int a, b, id, v;

    bool operator<(const Query& other) const {
        return this->b < other.b;
    }
};

bool byID(const Query& lhs, const Query& rhs) {
    return lhs.id < rhs.id;
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

    Query queries[maxN];
    for(int i = 0; i < q; i++) {
        scanf("%d%d", &queries[i].a, &queries[i].b);
        queries[i].id = i; queries[i].v = 0;
    }

    std::sort(queries, queries + q);

    int lastIndex[maxN] = {0};
    FenwickTree fenwick = FenwickTree(n);
    for(int i = 0, j = 0; i < n && j < q; i++) {
        if(lastIndex[arr[i]]) fenwick.Update(lastIndex[arr[i]], -1); //rightMost[lastIndex[arr[i]]-1] = false;

        fenwick.Update(i+1, 1); //rightMost[i] = true;
        lastIndex[arr[i]] = i+1;

        while(queries[j].b == i+1) {
            queries[j].v = fenwick.RangeQuery(queries[j].a, queries[j].b);
            j++;
        }
    }

    std::sort(queries, queries + q, byID);

    for(int i = 0; i < q; i++) printf("%d\n", queries[i].v);

    return 0;
}