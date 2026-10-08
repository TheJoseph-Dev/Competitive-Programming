#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <queue>
#include <algorithm>
#include <map>
#include <array>
#include <set>
#include <string.h>
#include <bitset>
#include <numeric>
#include <unordered_set>
#include <random>
#include <chrono>

using ll = long long;
using pll = std::pair<ll,ll>;
using pii = std::pair<int,int>;
constexpr int maxN = 5e3+4, maxLOG = 20, INF = 1e9+2, MOD = 1e9+7;
constexpr ll LLINF = 1e18;
constexpr double PI = 3.14159265358979323846;
constexpr double DEG2RAD = PI/180.0;

using i128 = ll;

#define f_io() \
    std::ios::sync_with_stdio(0);


constexpr int ALPHABET_SIZE = 26;
class AhoCorasick {
    struct Node {
        int next[ALPHABET_SIZE]; // Trie transitions + Automaton Transitions
        int sfxlink;
        int end;
        int len;
        ll cnt;
        Node() { std::fill(next, next + ALPHABET_SIZE, 0); this->sfxlink = 0; this->end = 0; this->len = 0; this->cnt = 0; }
    };

    std::vector<Node> tree;
    std::vector<int> order;
public:
    AhoCorasick() {
        tree.clear();
        tree.reserve(1e6+5);
        order.reserve(1e6+5);
        tree.emplace_back(); tree.emplace_back();
    }

    void Add(const std::string& pattern) {
        int node = 1;
        for(int i = 0; i < pattern.size(); i++) {
            int c = pattern[i] - 'a';
            //printf("%c\n", c+'a');
            int& nxt = tree[node].next[c];
            if(!nxt) {
                tree.emplace_back();
                nxt = tree.size()-1;
                //tree[nxt].len = i+1;
            }
            node = nxt;
        }
        //printf("%d\n", node);
        tree[node].len = pattern.size();
        tree[node].end++;
    }

    /*
    void Preprocess() {
        std::queue<std::array<int, 3>> q;
        q.push({1, -1, -1});
        while(!q.empty()) {
            auto [node, parent, ch] = q.front();
            q.pop();
            if(parent == 1) tree[node].sfxlink = parent;
            else if(parent == -1) tree[node].sfxlink = node;
            else tree[node].sfxlink = tree[tree[parent].sfxlink].next[ch];
            for(int i = 0; i < ALPHABET_SIZE; i++)
            if(tree[node].next[i]) q.push({tree[node].next[i], node, i});
        }
    }
    */

    void Preprocess() {
        std::queue<int> q;
        tree[1].sfxlink = 1;
        for(int ch = 0; ch < ALPHABET_SIZE; ch++) {
            int e = tree[1].next[ch];
            if(e) {
                tree[e].sfxlink = 1;
                q.push(e);
            }
            else tree[1].next[ch] = 1;
        }
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            order.emplace_back(node);
            for(int ch = 0; ch < ALPHABET_SIZE; ch++) {
                int e = tree[node].next[ch];
                if(e) {
                    tree[e].sfxlink = tree[tree[node].sfxlink].next[ch];
                    q.push(e);
                }
                else tree[node].next[ch] = tree[tree[node].sfxlink].next[ch];
            }
        }
    }

    int Count(const std::string& s) {
        static int dp[maxN];
        dp[0] = 1;
        int node = 1;
        for(int i = 0; i < s.size(); i++) {
            char c = s[i];
            node = tree[node].next[c-'a'];
            if(tree[node].len) dp[i+1] = (dp[i+1] + dp[i+1 - tree[node].len])%MOD;
            int sfx = tree[node].sfxlink;
            while(sfx != 1) {
                if(tree[sfx].len) dp[i+1] = (dp[i+1] + dp[i+1 - tree[sfx].len])%MOD;
                //printf("tree[%d].cnt = %d | %d\n", node, tree[node].cnt, sfx);
                sfx = tree[sfx].sfxlink;
            }
        }
        return dp[s.size()];
    }
};

int n, q, k, t;
std::string s;
int main() {
    f_io();
    std::cin >> s >> t;
    AhoCorasick aho;
    std::vector<std::string> patterns(t);
    for(int i = 0; i < t; i++) {
        std::cin >> patterns[i];
        aho.Add(patterns[i]);
    }
    aho.Preprocess();
    //aho.Query(s);
    printf("%d\n", aho.Count(s));
    return 0;
}