#include <stdio.h>
#include <vector>

#define INT_MAX (1<<30)

int v[200001];

class Seg {
private:
    std::vector<int> tree;
public:
    Seg(int n){
        tree.resize(4*n);
    }

    void build(int pos,int i,int f){
        if(i==f){
            tree[pos] = v[i];
            return;
        }
        int m = (i+f)/2;
        int e = 2*pos, d = 2*pos +1;
        build(e,i,m);
        build(d,m+1,f);
        tree[pos] = std::min(tree[e],tree[d]);
    }

    void update(int pos,int ini,int fim,int id,int val){
        if(id<ini || id>fim) return ;
        if(ini==fim){
            tree[pos] = val;
            return ;
        }
        int m = (ini+fim)/2;
        int e = 2*pos, d = 2*pos +1;
        update(e,ini,m,id,val);
        update(d,m+1,fim,id,val);
        tree[pos] = std::min(tree[e],tree[d]);
    }
    
    int queryMin(int pos,int ini,int fim,int a,int b){
        if(b<ini || a>fim) return INT_MAX;
        if(a<=ini && fim<=b) return tree[pos];
        int m = (ini+fim)/2;
        int e = 2*pos, d = 2*pos+1;
        return std::min(queryMin(e,ini,m,a,b), queryMin(d,m+1,fim,a,b));
    }
};

int main() {
    
    int n, q;
    scanf("%d%d", &n, &q);
 
    for(int i = 1; i <= n; i++)
        scanf("%d", v + i);
 
    Seg minSeg = Seg(n);
    minSeg.build(1, 1, n);
 
    int t, a, b;
    while(q--) {
        scanf("%d%d%d", &t, &a, &b);
        if(t == 1) minSeg.update(1, 1, n, a, b);
        else printf("%d\n", minSeg.queryMin(1, 1, n, a, b));
    }
}