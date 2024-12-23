#include <stdio.h>
#include <vector>

#define INT_MAX (1<<30)

class MaxSeg {
private:
    int* tree;
public:
    MaxSeg(int arr[200001], int n) {
        this->tree = new int[4*n];
        build(1, 1, n, arr);
    };
    
private:
    void build(int pos,int i,int f, int v[200001]){
        if(i==f){
            tree[pos] = v[i];
            return ;
        }
        int m = (i+f)/2;
        int e = 2*pos, d = 2*pos +1;
        build(e,i,m, v);
        build(d,m+1,f, v);
        tree[pos] = std::max(tree[e],tree[d]);
    }

public:
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
        tree[pos] = std::max(tree[e],tree[d]);
    }

    int query(int pos,int ini,int fim,int a,int b){
        if(b<ini || a>fim) return -INT_MAX;
        if(a<=ini && fim<=b) return tree[pos];
        int m = (ini+fim)/2;
        int e = 2*pos, d = 2*pos+1;
        return std::max(query(e,ini,m,a,b), query(d,m+1,fim,a,b));
    }
};

int main() {

    int n, g, hotels[200001];

    scanf("%d%d", &n, &g);

    for(int i = 1; i <= n; i++)
        scanf("%d", hotels+i);

    MaxSeg seg = MaxSeg(hotels, n);

    int group;
    while(g--) {
        scanf("%d", &group);
        
        if(seg.query(1, 1, n, 1, n) < group) { printf("0 "); continue; }

        int l = 1, r = n, idx = 0;
        while(l <= r) {
            int mid = (l+r)/2;
            if(seg.query(1, 1, n, l, mid) >= group) { r = mid-1; idx = mid; }
            else l = mid+1;
        }

        printf("%d ", idx);

        hotels[idx] -= group;
        seg.update(1, 1, n, idx, hotels[idx]);
    }

    return 0;
}