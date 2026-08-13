#include <bits/stdc++.h>
using namespace std;

#define ll long long


class SegmentLazy {
    #define LF (node*2+1)
    #define RT (node*2+2)
    #define mid (l+r>>1)
    
    private:
    
    int sz;
    const ll iden = -1LL;
    const ll skip_lazy = 0LL;
    vector<ll> tree, lazy, arr;

    
    ll apply(ll a, ll b) {// For Lazy
        return (a | b);
    }
    
    
    ll merge(ll a, ll b) {// For Seg
        return (a & b);
    }

    void propegate(int l, int r, int node) {

        if (lazy[node] == skip_lazy) return;

        if (l != r) {
            lazy[LF] = apply(lazy[LF], lazy[node]);
            lazy[RT] = apply(lazy[RT], lazy[node]);
        }

        tree[node] = apply(tree[node], lazy[node]);
        lazy[node] = skip_lazy;

    }

    void build(int l, int r, int node) {

        if (l == r) {
            tree[node] = arr[l];
            return;
        }

        build(l, mid, LF);
        build(mid + 1, r, RT);
        tree[node] = merge(tree[LF], tree[RT]);
        
    }
    
    void update(int l, int r, int node, int lq, int rq, ll val) {

        propegate(l, r, node);
        
        if (rq < l || lq > r) return;
        
        if (l >= lq && r <= rq) {
            lazy[node] = apply(lazy[node], val);
            propegate(l, r, node);
            return;
        }

        update(l, mid, LF, lq, rq, val);
        update(mid + 1, r, RT, lq, rq, val);

        tree[node] = merge(tree[LF], tree[RT]);

    }

    ll query(int l, int r, int node, int lq, int rq) {

        propegate(l, r, node);
        if (l >= lq && r <= rq) return tree[node];

        ll p1 = iden;
        ll p2 = iden;

        if (lq <= mid) p1 = query(l, mid, LF, lq, rq);
        if (rq > mid)  p2 = query(mid + 1, r, RT, lq, rq);

        return merge(p1, p2);
    }
    
    public:

    SegmentLazy(int nn) {

        sz = 1;
        while (sz < nn) sz *= 2;

        arr.resize(sz, 0);
        lazy.resize(2*sz, skip_lazy);
        tree.resize(2*sz, iden);
        build(0, sz - 1, 0);

    }
    
    SegmentLazy(const vector<ll> &v) {

        sz = 1;
        arr = v;

        while (sz < v.size()) sz *= 2;
        arr.resize(sz, iden);
        lazy.resize(2*sz, skip_lazy);
        tree.resize(2*sz, iden);

        build(0, sz - 1, 0);
    }

    void update(int l, int r, ll val) {
        update(0, sz - 1, 0, l, r, val);
    }
    
    ll query(int l, int r) {
        return query(0, sz - 1, 0, l, r);
    }
    
    
    #undef LF
    #undef RT
    #undef mid
};



int main() {

    #ifndef ONLINE_JUDGE
        // freopen("../input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif
    

    ll n;
    cin >> n;  

    vector<ll> arr = {1, 2, 3, 4, 5};

    SegmentLazy seg(arr);

    cout << seg.query(0, 2) << '\n';
    seg.update(1, 2, 10);
    seg.update(0, 3, 20);
    cout << seg.query(0, 0) << '\n';
    cout << seg.query(1, 1) << '\n';
    cout << seg.query(2, 2) << '\n';
    cout << seg.query(3, 3) << '\n';
    
    
    
    
    
    

    
    
    return 0;
}