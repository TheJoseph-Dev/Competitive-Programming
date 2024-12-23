#include <stdio.h>
#include <set>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
 
using namespace __gnu_pbds;
 
template<class T> using cust_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
cust_set<std::array<int,2>> freq;
 
int getcnt(int x) {
    return freq.order_of_key({x, 0});
}
 
int main()
{
    int n,q;
    scanf("%d%d", &n, &q);
 
    int salaries[200001];
    for(int i = 0; i < n; i++) {
        scanf("%d", salaries+i);
        freq.insert({salaries[i], i});
    }
 
    char op;
    int a, b;
    while(q--) {
        scanf(" %c%d%d", &op, &a, &b);
        if(op == '?') printf("%d\n", getcnt(b+1) - getcnt(a));
        else {
            --a;
            freq.erase({salaries[a], a});
            salaries[a] = b;
            freq.insert({salaries[a], a});
        }
    }
 
    return 0;
}