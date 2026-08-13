## First Element <= val in range
``` cpp
ll query(ll l, ll r, ll node, ll val, ll lx, ll rx) {
        
    propegate(l, r, node);
    if (r < lx || l > rx || tree[node] > val) return -1;
    if (l >= r) return l;

    ll first = query(l, mid, Left, val, lx, rx);
    if (first != -1) return first;
    return query(mid + 1, r, Right, val, lx, rx);
}
```

## Point Query After Apply all updates
``` cpp
ll find(ll l, ll r, ll node, ll ind) {
    propegate(l, r, node);
    if (l == r) return tree[node];
    
    if (ind <= mid) return find(l, mid, node * 2 + 1, ind);
    return find(mid + 1, r, node * 2 + 2, ind);
}
```

## Max SubArray Sum with updates
``` cpp
struct Node {
    ll ans, sum, pref, suff;
};

class SegmentTree {
    #define Left (node*2+1)
    #define Right (node*2+2)
    #define mid (l+r>>1)
    
    private:
    
    int n, sz;
    ll inf = 1e18;
    const Node iden = {-inf, 0, -inf, -inf};
    vector<ll> arr;
    vector<Node> tree;

    Node merge(Node a, Node b) {

        Node ret;
        ret.sum = a.sum + b.sum;
        ret.pref = max(a.pref, a.sum + b.pref);
        ret.suff = max(b.suff, b.sum + a.suff);
        ret.ans = max({
            a.ans,
            b.ans,
            a.suff + b.pref
        });
        
        return ret;
    }

    void build(int l, int r, int node) {

        if (l == r) {
            tree[node] = {max(0LL, arr[l]), arr[l], max(0LL, arr[l]), max(0LL, arr[l])};
            return;
        }

        build(l, mid, Left);
        build(mid + 1, r, Right);
        tree[node] = merge(tree[Left], tree[Right]);
        
    }
    
    void update(int l, int r, int node, int idx, int val) {
        
        if (l == r) {
            tree[node] = {max(0, val), val, max(0, val), max(0, val)};
            return;
        }

        if (idx <= mid) update(l, mid, Left, idx, val);
        else update(mid + 1, r, Right, idx, val);

        tree[node] = merge(tree[Left], tree[Right]);
    }
    
    public:

    SegmentTree(const vector<ll> &v) {

        sz = 1;
        arr = v;
        n = arr.size();

        while (sz < n) sz *= 2;
        arr.resize(2*sz, 0);
        tree.resize(2*sz, iden);

        build(0, sz - 1, 0);
    }

    void update(int idx, ll val) {
        update(0, sz - 1, 0, idx, val);
    }
    
    ll query() {
        return tree[0].ans;
    }
    
    
    #undef Left
    #undef Right
    #undef mid
};
```

## Max XOR
``` cpp
int query(int x) {

    if (root->child[0] == nullptr && root->child[1] == nullptr) return x;

    int ans = 0;

    Node* curr = root;
    for(int bit = LOG; bit >= 0; bit--) {

        int b = (x >> bit) & 1;
        if(curr->child[b ^ 1] == nullptr) {
            curr = curr->child[b];
        } 
        else {
            ans |= 1 << bit;
            curr = curr->child[b ^ 1];
        }
        
    }
    return ans;
}
```