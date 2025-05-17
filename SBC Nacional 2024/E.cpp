#include <stdio.h>
#include <stack>
#include <set>
#include <cstring>

constexpr int maxN = 1e5+1, INF = 0x3f3f3f3f;

int n, m[maxN];
bool isZeroed() {
    for(int i = 0; i < n; i++) if(m[i]) return false;
    return true;
}

int getHighest() {
    int max = 0, ix = -1;
    for(int i = 0; i < n; i++) if(max < m[i]) { max = m[i] ; ix = i; }
    return ix;
}

int getPeak() {
    for(int i = 0; i < n; i++) if(m[i] == n) return i;
    return -1;
}

int ngv[maxN], ngvr[maxN], ngvl[maxN], idx[maxN], m2[maxN]; // m[i] => ngv idx
void nearestGreaterValue() {
    memset(ngvr, -1, sizeof(ngvr));
    std::stack<int> monostk;
    for(int i = 0; i < n; i++) {
        while(!monostk.empty() && m[i] > m[monostk.top()]) {
            ngvr[m[monostk.top()]] = i;
            monostk.pop();
        }
        monostk.push(i);
    }

    while(!monostk.empty()) monostk.pop();

    memset(ngvl, -1, sizeof(ngvl));
    for(int i = n-1; i >= 0; i--) {
        while(!monostk.empty() && m[i] > m[monostk.top()]) {
            ngvl[m[monostk.top()]] = i;
            monostk.pop();
        }
        monostk.push(i);
    }

    for(int i = 1; i <= n; i++)
        if(ngvl[i] != -1 && ngvr[i] != -1) ngv[i] = idx[i]-ngvl[i] > ngvr[i]-idx[i] ? ngvr[i] : ngvl[i];
        else if(ngvl[i] != -1) ngv[i] = ngvl[i];
        else ngv[i] = ngvr[i];
}

bool check(int a[maxN]) {
    bool u = a[0] != n;
    for(int i = 1; i < n; i++) {
        if((u && a[i-1] >= a[i]) || (!u && a[i-1] <= a[i])) return false;
        if(a[i] == n) u = false;
    }
    return true;
}

bool solve() {
    std::set<int> set;
    memset(idx, -1, sizeof(idx));
    for(int i = 0; i < n; i++) { idx[m[i]] = i; m2[i] = m[i]; set.insert(i+1); }
    for(int i = 0; i < n; i++) if(idx[i+1]+1) set.erase(set.find(i+1));

    // Fill in between
    for(int v = n-1; v >= 1; v--) {
        //printf("%d: %d\n", v, ngv[v]);
        if(ngv[v] == -1) continue; 
        if(idx[v] < ngv[v])
            for(int i = ngv[v]-1; i > idx[v]; i--) {
                auto it = set.lower_bound(m[ngv[v]]);
                if(it == set.begin()) return false;
                it--;
                m2[i] = *it;
                set.erase(it);
            }
        else 
            for(int i = ngv[v]+1; i < idx[v]; i++) {
                auto it = set.lower_bound(m[ngv[v]]);
                if(it == set.begin()) return false;
                it--;
                m2[i] = *it;
                set.erase(it);
            }
        
    }

    int peak = getPeak();

    // Fill the borders
    std::set<int> setcpy = set;
    for(int i = 0; i < n; i++) ngv[i] = m2[i];
    for(int i = 0; i < n && !set.empty(); i++)
        if(!m2[i] && i < peak) { m2[i] = *set.begin(); set.erase(set.begin()); }
        else if(!m2[i]) { m2[i] = *set.rbegin(); set.erase(std::prev(set.end())); }

    bool ok = check(m2);
    if(!ok) {
        for(int i = n-1; i >= 0 && !setcpy.empty(); i--)
            if(!ngv[i] && i > peak) { ngv[i] = *setcpy.begin(); setcpy.erase(setcpy.begin()); }
            else if(!ngv[i]) { ngv[i] = *setcpy.rbegin(); setcpy.erase(std::prev(setcpy.end())); }
            ok = check(ngv);
            if(ok) for(int i = 0; i < n; i++) m2[i] = ngv[i];
    }
    return ok;
}

int main() {
    scanf("%d", &n);

    for(int i = 0; i < n; i++) scanf("%d", m+i);

    if(isZeroed()) {
        for(int i = 1; i <= n; i++) printf("%d ", i);
        return 0;
    }

    if(getPeak()+1) {
        nearestGreaterValue();
        if(solve()) for(int i = 0; i < n; i++) printf("%d ", m2[i]);
        else puts("*");
    }
    else {
        int h = getHighest();
        int d = n-m[h]; 
        bool s = false;
        if(h+d < n && !m[h+d]) {
            m[h+d] = n;
            nearestGreaterValue();
            if(s = solve()) for(int i = 0; i < n; i++) printf("%d ", m2[i]);
            m[h+d] = 0;
        }
        if(!s && h-d >= 0 && !m[h-d]) {
            m[h-d] = n;
            nearestGreaterValue();
            if(s = solve()) for(int i = 0; i < n; i++) printf("%d ", m2[i]);
        }
        if(!s) puts("*");
    }

    return 0;
}