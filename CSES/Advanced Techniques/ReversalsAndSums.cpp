#include <stdio.h>
#include <random>
#include <chrono>

using ll = long long;

/*
    All operations are done in O(log n)
*/

class Treap {
    struct Node {
        ll val, sum, lazyAdd;
        int sz;
        uint32_t priority;
        bool reversed;

        Node *left, *right;

        Node(ll val, uint32_t priority) {
            this->val = val;
            this->sum = val;
            this->lazyAdd = 0;
            this->sz = 1;
            this->priority = priority;
            this->reversed = false;
            this->left = this->right = nullptr;
        }
    };

    Node* root = nullptr;

    static std::mt19937 rng;

    // Returns the size of a subtree
    int GetSize(Node* t) {
        return t ? t->sz : 0;
    }

    // Returns the sum of a subtree
    ll GetSum(Node* t) {
        return t ? t->sum : 0;
    }

    // Recalculates subtree information
    void Pull(Node* t) {
        if (!t) return;
        t->sz = 1 + GetSize(t->left) + GetSize(t->right);
        t->sum = t->val + GetSum(t->left) + GetSum(t->right);
    }

    // Applies lazy addition to a subtree
    void ApplyAdd(Node* t, ll val) {
        if (!t) return;
        t->val += val;
        t->sum += val * t->sz;
        t->lazyAdd += val;
    }

    // Applies lazy reversal to a subtree
    void ApplyReverse(Node* t) {
        if (!t) return;
        std::swap(t->left, t->right);
        t->reversed ^= 1;
    }

    // Propagates lazy operations to children
    void Push(Node* t) {
        if (!t) return;

        if (t->reversed) {
            ApplyReverse(t->left);
            ApplyReverse(t->right);
            t->reversed = false;
        }

        if (t->lazyAdd != 0) {
            ApplyAdd(t->left, t->lazyAdd);
            ApplyAdd(t->right, t->lazyAdd);
            t->lazyAdd = 0;
        }
    }

    // Splits t into the first k elements and the remaining elements
    void Split(Node* t, int k, Node*& a, Node*& b) {
        if (!t) {
            a = b = nullptr;
            return;
        }
        Push(t);
        if (GetSize(t->left) >= k) {
            Split(t->left, k, a, t->left);
            b = t;
            Pull(b);
        } else {
            Split(t->right, k - GetSize(t->left) - 1, t->right, b);
            a = t;
            Pull(a);
        }
    }

    // Merges two trees (all elements in a precede those in b)
    Node* Merge(Node* a, Node* b) {
        if (!a) return b;
        if (!b) return a;

        if (a->priority > b->priority) {
            Push(a);
            a->right = Merge(a->right, b);
            Pull(a);
            return a;
        } else {
            Push(b);
            b->left = Merge(a, b->left);
            Pull(b);
            return b;
        }
    }

    // Returns the element at position pos
    ll Get(Node* t, int pos) {
        Push(t);
        int leftSize = GetSize(t->left);
        if (pos < leftSize) return Get(t->left, pos);
        if (pos == leftSize) return t->val;
        return Get(t->right, pos - leftSize - 1);
    }

    // Updates the element at position pos
    void Set(Node* t, int pos, ll val) {
        Push(t);

        int leftSize = GetSize(t->left);
        if (pos < leftSize) Set(t->left, pos, val);
        else if (pos == leftSize) t->val = val;
        else Set(t->right, pos - leftSize - 1, val);
        Pull(t);
    }

    // Deletes all nodes
    void Destroy(Node* t) {
        if (!t) return;
        Destroy(t->left);
        Destroy(t->right);
        delete t;
    }

    void Print(Node* t) {
        if (!t) return;

        Push(t);

        Print(t->left);
        printf("%c", (char)t->val);
        Print(t->right);
    }

public:

    Treap() = default;
    Treap(const std::vector<ll>& a) {
        for (ll x : a) Insert(Size(), x);
    }

    ~Treap() { Destroy(root); }

    // Treaps own their nodes, so copying is forbidden.
    Treap(const Treap&) = delete;
    Treap& operator=(const Treap&) = delete;

    // Transfers ownership of the nodes.
    Treap(Treap&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }

    // Transfers ownership, destroying the previous tree.
    Treap& operator=(Treap&& other) noexcept {
        if (this != &other) {
            Destroy(root);
            root = other.root;
            other.root = nullptr;
            rng = std::move(other.rng);
        }
        return *this;
    }

    // Returns the number of elements
    int Size() {
        return GetSize(root);
    }

    // Inserts val at position pos
    void Insert(int pos, ll val) {
        Node *a, *b;
        Split(root, pos, a, b);
        Node* t = new Node(val, rng());
        root = Merge(Merge(a, t), b);
    }

    // Removes the element at position pos
    void Erase(int pos) {
        Node *a, *b, *c;
        Split(root, pos, a, b);
        Split(b, 1, b, c);
        Destroy(b);
        root = Merge(a, c);
    }

    // Returns the element at position pos
    ll Get(int pos) {
        return Get(root, pos);
    }

    // Updates the element at position pos
    void Set(int pos, ll val) {
        Set(root, pos, val);
    }

    // Reverses the range [l, r)
    void Reverse(int l, int r) {
        Node *a, *b, *c;
        Split(root, l, a, b);
        Split(b, r - l, b, c);
        ApplyReverse(b);
        root = Merge(Merge(a, b), c);
    }

    // Adds val to every element in [l, r)
    void RangeAdd(int l, int r, ll val) {
        Node *a, *b, *c;
        Split(root, l, a, b);
        Split(b, r - l, b, c);
        ApplyAdd(b, val);
        root = Merge(Merge(a, b), c);
    }

    // Returns the sum of elements in [l, r)
    ll RangeQuery(int l, int r) {
        Node *a, *b, *c;
        Split(root, l, a, b);
        Split(b, r - l, b, c);
        ll ans = GetSum(b);
        root = Merge(Merge(a, b), c);
        return ans;
    }

    // Concatenates another sequence to the end
    void Append(ll val) {
        Insert(Size(), val);
    }

    // Splits the sequence after k elements.
    // Returns {first k elements, remaining elements}.
    std::pair<Treap, Treap> Split(int k) {
        Treap a, b;
        Split(root, k, a.root, b.root);
        root = nullptr;
        return {std::move(a), std::move(b)};
    }

    // Concatenates another Treap to the end.
    void Merge(Treap&& other) {
        root = Merge(root, other.root);
        other.root = nullptr;
    }

    void Print() {
        Print(root);
    }
};

std::mt19937 Treap::rng(
    std::chrono::steady_clock::now().time_since_epoch().count()
);

int n, m;
int main() {
    scanf("%d%d", &n, &m);
    std::vector<ll> arr(n);
    for(int i = 0; i < n; i++) scanf("%lld", &arr[i]);
    Treap tp = Treap(arr);
    int t, a, b;
    while(m--) {
        scanf("%d%d%d", &t, &a, &b);
        if(t-1) printf("%lld\n", tp.RangeQuery(a-1, b));
        else tp.Reverse(a-1, b);
    }
    return 0;
}