#include <iostream>
#include <string>
#include <vector>
#include <map>
constexpr int maxN = 1e3+2;
struct P {
    int x,y;
};
int dot(P p1, P p2) {
    return p1.x*p2.x + p1.y*p2.y;
}
struct DW {
    std::string w;
    P p;
} d[maxN];


int n,m;
std::string kb[maxN];
std::vector<std::string> getCandidates(const std::vector<std::string>& pattern, int k) {
    std::vector<std::string> c;
    //for(int i = 0; i < m; i++) puts(kb[i].c_str());
    int o = pattern.size()-k;
    for(int i = 0; i+k < m; i++) {
        int j = 0;
        for(; j+o < pattern.size(); j++)
            if(pattern[j+o] != kb[i+j]) break;
        //printf("(%d) j %d %d\n", i, j, o);
        if(j+o == pattern.size()) c.push_back(kb[i+j]);
    }
    return c;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::map<std::string, P> dmp;
    std::cin >> n;
    for(int i = 0; i < n; i++) {
        std::cin >> d[i].w >> d[i].p.x >> d[i].p.y;
        dmp[d[i].w] = d[i].p;
    }
    
    std::cin >> m;
    for(int i = 0; i < m; i++) std::cin >> kb[i];

    int q,k,f;
    std::cin >> q >> k;
    while(q--) {
        std::cin >> f;
        std::vector<std::string> qry;
        std::string w;
        while(f--) { std::cin >> w; qry.push_back(w); }

        int kk = k;
        std::vector<std::string> c;
        do c = getCandidates(qry, kk); 
        while(c.empty() && --kk);
        //for(auto ss : c)
        //printf("ci: %s\n", ss.c_str());
        for(auto qw : qry) printf("%s ", qw.c_str());
        if(c.empty()) { puts("*"); continue; }

        int mxS = -1e9;
        std::string sw;
        for(int i = 0; i < n; i++) {
            int S = 0;
            for(auto ci : c) {
                if(!dmp.count(ci)) continue;
                S += dot(d[i].p, dmp[ci]);
            }
            //printf("(%s): %d\n", d[i].w.c_str(), S);
            if(mxS < S) {
                mxS = S;
                sw = d[i].w;
            }
        }
        puts(sw.c_str());
    }
    return 0;
}