#include <stdio.h>

class Seg {
private:
    int* tree;
public:
    Seg(int v[200001], int n){
        tree = new int[n*4];
        build(1, 1, n, v);
    }

private:
    void build(int pos,int i,int f, int v[200001]){
        if(i==f){
            tree[pos] = v[i];
            return;
        }
        int m = (i+f)/2;
        int e = 2*pos, d = 2*pos +1;
        build(e,i,m, v);
        build(d,m+1,f, v);
        tree[pos] = (tree[e] + tree[d]);
    }

public:
    
    void update(int pos,int ini,int fim,int id,int val){
        if(id<ini || id>fim) return ;
        if(ini==fim){
            tree[pos] = val;
            return;
        }
        int m = (ini+fim)/2;
        int e = 2*pos, d = 2*pos +1;
        update(e,ini,m,id,val);
        update(d,m+1,fim,id,val);
        tree[pos] = (tree[e] + tree[d]);
    }


    int query(int pos,int ini,int fim,int a,int b){
        if(b<ini || a>fim) return 0;
        if(a<=ini && fim<=b) return tree[pos];
        int m = (ini+fim)/2;
        int e = 2*pos, d = 2*pos+1;
        return (query(e,ini,m,a,b) + query(d,m+1,fim,a,b));
    }
};

int main() {

    int n;
    scanf("%d", &n);

    int arr[200001], present[200001];
    for(int i = 1; i <= n; i++) {
        scanf("%d", arr+i);
        present[i] = 1;
    }

    Seg seg = Seg(present, n);

    int p;
    for(int i = 0; i < n; i++) {
        scanf("%d", &p);
        
        int l = 1, r = n, idx = 0;
        while(l <= r) {
            int mid = (l+r)/2;

            int q = seg.query(1, 1, n, 1, mid);
            if(q < p) l = mid+1;
            else { r = mid-1; idx = mid; }
        }

        printf("%d ", arr[idx]);
        seg.update(1, 1, n, idx, 0);
    }

    return 0;
}