#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using ll = long long;

struct SuffixAutomaton {
    struct State {
        int next[26];
        int link;
        int len;
        ll occ;

        State() {
            memset(next, -1, sizeof(next));
            link = -1;
            len = 0;
            occ = 0;
        }
    };

    std::vector<State> st;
    int last;

    SuffixAutomaton(const std::string& s) {
        st.reserve(2 * s.size());
        st.emplace_back();
        last = 0;
        for (char ch : s) extend(ch);
        build();
    }

    void extend(char ch) {
        int c = ch - 'a';

        int cur = st.size();
        st.emplace_back();

        st[cur].len = st[last].len + 1;
        st[cur].occ = 1;

        int p = last;

        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];

            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = st.size();
                st.push_back(st[q]);

                st[clone].len = st[p].len + 1;
                st[clone].occ = 0;

                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }

                st[q].link = st[cur].link = clone;
            }
        }

        last = cur;
    }

    void build() {
        int maxLen = 0;

        for (auto& state : st) maxLen = std::max(maxLen, state.len);
        std::vector<int> cnt(maxLen + 1);
        for (auto& state : st) cnt[state.len]++;
        for (int i = 1; i <= maxLen; i++) cnt[i] += cnt[i - 1];
        std::vector<int> order(st.size());
        for (int i = st.size() - 1; i >= 0; i--) order[--cnt[st[i].len]] = i;
        for (int i = order.size() - 1; i > 0; i--) {
            int v = order[i];
            int p = st[v].link;
            st[p].occ += st[v].occ;
        }
    }

    ll count(const std::string& pattern) const {
        int v = 0;
        for (char ch : pattern) {
            int c = ch - 'a';
            if (st[v].next[c] == -1) return 0;
            v = st[v].next[c];
        }

        return st[v].occ;
    }
};


int main() {
    std::ios::sync_with_stdio(0);
    std::string s;
    int n;
    std::cin >> s >> n;
    SuffixAutomaton sa(s);
    while(n--) {
        std::cin >> s;
        printf("%lld\n", sa.count(s));
    }
}