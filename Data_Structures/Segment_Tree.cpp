#include <bits/stdc++.h>
using namespace std;

#define ll long long

/*
| Function Type | Identity         |
| ------------- | ---------------- |
| min(a, b)     | +∞ (INT_MAX)     |
| max(a, b)     | -∞ (INT_MIN)     |
| a + b         | 0                |
| a * b         | 1                |
| gcd(a, b)     | 0                |
| lcm(a, b)     | 1                |
| a | b         | 0                |
| a & b         | ~0 (all bits 1)  |
| a ^ b         | 0                |
*/

// Recursive
class SegmentTree {
    #define Left (node*2+1)
    #define Right (node*2+2)
    #define mid (l+r>>1)
    
    private:
    
    int sz;
    const int iden = 1e9;
    vector<ll> tree, arr;

    ll merge(ll a, ll b) {
        return min(a, b);
    }

    void build(int l, int r, int node) {

        if (l == r) {
            tree[node] = arr[l];
            return;
        }

        build(l, mid, Left);
        build(mid + 1, r, Right);
        tree[node] = merge(tree[Left], tree[Right]);
        
    }
    
    void update(int l, int r, int node, int idx, ll val) {
        
        if (l == r) {
            tree[node] = val;
            return;
        }

        if (idx <= mid) update(l, mid, Left, idx, val);
        else update(mid + 1, r, Right, idx, val);

        tree[node] = merge(tree[Left], tree[Right]);
    }

    ll query(int l, int r, int node, int lq, int rq) {

        if (l >= lq && r <= rq) return tree[node];

        ll p1 = iden;
        ll p2 = iden;

        if (lq <= mid) p1 = query(l, mid, Left, lq, rq);
        if (rq > mid) p2 = query(mid + 1, r, Right, lq, rq);

        return merge(p1, p2);
    }
    
    public:

    SegmentTree(const vector<ll> &v) {

        sz = 1;
        arr = v;

        while (sz < v.size()) sz *= 2;
        arr.resize(sz, iden);
        tree.resize(2*sz, iden);

        build(0, sz - 1, 0);
    }

    void update(int idx, ll val) {
        update(0, sz - 1, 0, idx, val);
    }
    
    ll query(int l, int r) {
        return query(0, sz - 1, 0, l, r);
    }
    
    
    #undef Left
    #undef Right
    #undef mid
};

// Iterative
class SegmentTreei {
private:
    int n;
    int size;
    vector<int> tree;
    const int identity = INT_MAX;

    int merge(int a, int b) {
        return min(a, b);
    }

    static int next_pow2(int x) {
        int p = 1;
        while (p < x) p <<= 1;
        return p;
    }

public:
    SegmentTreei(const vector<int>& arr) {

        n = arr.size();
        size = next_pow2(n);
        tree.assign(2 * size, identity);

        for (int i = 0;i < n;i++) tree[size + i] = arr[i];
        for (int i = size - 1; i >= 1; i--) {
            tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
        }

    }

    void update(int pos, int value) {
        
        if (pos < 0 || pos >= n) return;
        int idx = size + pos;
        tree[idx] = value;
        idx >>= 1;
        while (idx >= 1) {
            tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
            idx >>= 1;
        }
    }

    int query(int l, int r) {
        
        if (l < 0 || r < 0 || l >= n || r >= n || l > r) return identity;

        l += size;
        r += size;
        int resL = identity;
        int resR = identity;

        while (l <= r) {
            if (l & 1) {
                resL = merge(resL, tree[l++]);
            }
            if (!(r & 1)) {
                resR = merge(tree[r--], resR);
            }
            l >>= 1;
            r >>= 1;
        }
        return merge(resL, resR);
    }
};

// Range Update, Point Query
class SegTree {
    #define Left (node*2+1)
    #define Right (node*2+2)
    #define mid (l+r>>1)
    
    private:
    
    int sz;
    const ll iden = 0;
    vector<ll> arr;
    vector<ll> tree;

    ll merge(ll a, ll b) {
        return a + b;
    }
    
    void update(int l, int r, int node, int lq, int rq, int val) {
        
        if (l >= lq && r <= rq) {
            tree[node] = merge(tree[node], val);
            return;
        }
        
        if (l == r) {
            tree[node] = merge(tree[node], val);
            return;
        }

        if (lq <= mid) update(l, mid, Left, lq, rq, val);
        if (rq > mid)  update(mid + 1, r, Right, lq, rq, val);

    }

    ll query(int l, int r, int node, int idx) {
        if (l == r) return tree[node];
        if (idx <= mid) return merge(tree[node], query(l, mid, Left, idx));
        return merge(tree[node], query(mid + 1, r, Right, idx));
    }
    
    public:

    SegTree(int n) {

        sz = 1;
        while (sz < n) sz *= 2;
        tree.resize(2*sz, iden);

    }

    void update(int lq, int rq, int val) {
        update(0, sz - 1, 0, lq, rq, val);
    }
    
    ll query(int idx) {
        return query(0, sz - 1, 0, idx);
    }
    
    #undef Left
    #undef Right
    #undef mid
};

int main() {

    #ifndef ONLINE_JUDGE
        // freopen("../input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    vector<long long> a = {1, 3, 1, 8, 5, 6, 7, 2};
    SegmentTree st(a);

    cout << "[0..2] = " << st.query(0, 2) << '\n';
    cout << "[3..7] = " << st.query(3, 7) << '\n';

    st.update(2, 10); // arr[2] = 10
    cout << "after update [0..2] = " << st.query(0, 2) << '\n';

    SegTree seg(8);

    seg.update(0, 5, 10);
    seg.update(2, 6, 5);

    cout << seg.query(1) << '\n';
    cout << seg.query(3) << '\n';
    cout << seg.query(6) << '\n';
    cout << seg.query(7) << '\n';

    return 0;
}
