#include <stdio.h>
#include <vector>
#include <algorithm>

constexpr int maxN = 2e5+1;
int n;
int arr[maxN];

int countLIS() {
    std::vector<int> lis = std::vector<int>();

    for(int i = 0; i < n; i++) {
        auto it = std::lower_bound(lis.begin(), lis.end(), arr[i]);
        if(it == lis.end()) lis.push_back(arr[i]);
        else *it = arr[i];
    }

    return lis.size();
}

int main() {
    scanf("%d", &n);

    for(int i = 0; i < n; i++) scanf("%d", arr+i);

    printf("%d\n", countLIS());

    return 0;
}