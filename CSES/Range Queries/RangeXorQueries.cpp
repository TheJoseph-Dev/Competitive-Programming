#include <stdio.h>
#include <vector>

int v[200001];

class XorSeg {
private:
    std::vector<int> tree;
public:
    XorSeg(int n) {
        tree.resize(4*n);
    }

    void build(int pos,int i,int f) {
        if(i==f){
            tree[pos] = v[i];
            return;
        }
        int m = (i+f)/2;
        int e = 2*pos, d = 2*pos +1;
        build(e,i,m);
        build(d,m+1,f);
        tree[pos] = (tree[e] ^ tree[d]);
    }

    void update(int pos,int ini,int fim,int id,int val) {
        if(id<ini || id>fim) return ;
        if(ini==fim){
            tree[pos] = val;
            return ;
        }
        int m = (ini+fim)/2;
        int e = 2*pos, d = 2*pos +1;
        update(e,ini,m,id,val);
        update(d,m+1,fim,id,val);
        tree[pos] = (tree[e] ^ tree[d]);
    }
    
    int query(int pos,int ini,int fim,int a,int b) {
        if(b<ini || a>fim) return 0;
        if(a<=ini && fim<=b) return tree[pos];
        int m = (ini+fim)/2;
        int e = 2*pos, d = 2*pos+1;
        return (query(e,ini,m,a,b) ^ query(d,m+1,fim,a,b));
    }
};

int main() {
    
    int n, q;
    scanf("%d%d", &n, &q);
 
    for(int i = 1; i <= n; i++)
        scanf("%d", v + i);
 
    XorSeg xorSeg = XorSeg(n);
    xorSeg.build(1, 1, n);
 
    int a, b;
    while(q--) {
        scanf("%d%d", &a, &b);
        printf("%d\n", xorSeg.query(1, 1, n, a, b));
    }
}