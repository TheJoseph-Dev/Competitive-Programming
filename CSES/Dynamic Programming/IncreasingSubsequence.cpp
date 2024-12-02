#include <stdio.h>
#include <vector>
#include <algorithm>

int lis(const std::vector<int>& arr) {
    std::vector<int> aux = std::vector<int>();
    
    for(int e : arr) {
        if(aux.empty()) { aux.push_back(e); continue; }
        auto it = std::lower_bound(aux.begin(), aux.end(), e);
        if(it == aux.end()) aux.push_back(e);
        else (*it) = e;
    }

    return aux.size();
}

int main() {

    int n;
    scanf("%d", &n);

    std::vector<int> arr = std::vector<int>(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("%d\n", lis(arr));

    return 0;
}