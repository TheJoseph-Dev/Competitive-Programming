#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

#define us std::unordered_set

void pMsg(int msg, int bp[], int n, us<int>& pn) {
    if(n <= 0) return;
    pn.insert(msg | (1 << bp[n-1]));
    pn.insert(msg);
    pMsg(msg | (1 << bp[n-1]), bp, n-1, pn);
    pMsg(msg, bp, n-1, pn);
}

bool modM(const std::string& n, int m) {
    // a*b mod m = ((a mod m) * (b mod m)) mod m
    int r = 0;
    for(int i = 0; i < n.size(); i++)
        r = (r*2 + (n[i]-'0'))%m;
    return r==0;
}

void pMsgS(const std::string& msg, int bp[], int n, us<std::string>& pn) {
    if(n <= 0) return;
    std::string nMsg = msg;
    nMsg[bp[n-1]] = '1';
    pn.insert(nMsg);
    pn.insert(msg);
    //printf("%s %s\n", nMsg.c_str(), msg.c_str());
    pMsgS(nMsg, bp, n-1, pn);
    pMsgS(msg, bp, n-1, pn);
}

int main() {

    std::string ms,ns;
    std::cin >> ms >> ns;

    int mbp[501], mbps = 0;
    for(int i = ms.size()-1; i >= 0; i--) {
        if(ms[i] != '*') continue;
        ms[i] = '0';
        mbp[mbps++] = i;
    }

    us<std::string> pm;
    if(mbps == 0) pm.insert(ms);
    pMsgS(ms, mbp, mbps, pm);

    int nbp[17], nbps = 0;
    int hn = 0;
    for(int i = ns.size()-1, j = 0; i >= 0; i--, j++) {
        if(ns[i] == '*') {
            nbp[nbps++] = j;
            continue;
        }

        if(ns[i] == '1') hn |= (1 << j);
    }

    us<int> pn;
    pn.insert(hn);
    pMsg(hn, nbp, nbps, pn);
    
    for(const std::string& m : pm)
        for(int n : pn)
            if(modM(m, n)) {
                printf("%s", m.c_str());
                return 0;
            }
    
    return 0;
}