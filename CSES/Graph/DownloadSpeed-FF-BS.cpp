// Fordfulkerson style with Binary Search O(30(n+m))
// Credits to Huth-0: https://cses.fi/problemset/hack/1694/entry/7124848/

#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int adj[501][501];
int vis[501]={0};
int best=0;
int dfs(int nod,int c){
    if(vis[nod])return 0;
    if(nod==n) {
        best+=c;
        return c;
    }
    vis[nod]=1;
    int v=0;
    for(int i=1;i<=n;i++){
        if(adj[nod][i]>=c){
            int x=dfs(i,c);
            v+=x;
            adj[nod][i]-=x?c:0;
            adj[i][nod]+=x?c:0;
            if(x)break;
        }
    }
    return v;
 
}
int32_t main(){
    cin>>n>>m;
    while(m--){
        int x,y,z;
        cin>>x>>y>>z;
        adj[x][y]+=z;
    }
    int c=1<<30;
    while(c>0){
        memset(vis,0,sizeof(vis));
        if(dfs(1,c)==0)c>>=1;
    }
    cout<<best;
}