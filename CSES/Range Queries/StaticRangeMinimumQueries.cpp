#include <stdio.h>
#include <vector>
 
class SparseTable {
 
    int n;
    std::vector<std::vector<int>> minTable;
 
private:
    int flog(int x) {
    	return 31 - __builtin_clz(x);
    }
 
public:
    SparseTable(int arr[], int n): n(n) {
        int k = flog(n) + 1;  // Number of levels in the sparse table
        this->minTable = std::vector<std::vector<int>>(k, std::vector<int>(n));
 
        for (int i = 0; i < n; i++)
            minTable[0][i] = arr[i];
 
        // Build
        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                minTable[j][i] = std::min(minTable[j - 1][i], minTable[j - 1][i + (1 << (j - 1))]);
    }
 
    int RangeMin(int L, int R) {
        int j = flog(R - L + 1);
        return std::min(minTable[j][L], minTable[j][R - (1 << j) + 1]);
    }
};
 
int main() {
 
    int n, q;
    scanf("%d%d", &n, &q);
 
    int nums[200001];
    for(int i = 0; i < n; i++)
        scanf("%d", nums + i);
 
    SparseTable minST = SparseTable(nums, n);
 
    int a, b;
    while(q--) {
        scanf("%d%d", &a, &b);
        printf("%d\n", minST.RangeMin(a-1, b-1));
    }
 
    return 0;
}