#include <iostream>
#include <vector>

using namespace std;

#define ll long long

// Safe: DynamicSeg 1 + Q * (log2(maxU) + 2).
// Safe: DynamicLazy 1 + 8 * Q * (log2(maxU) + 1).
const int MAX_NODES = 2e7;

struct Node {
    ll res;
    int L, R;
} tree[MAX_NODES];

class DynamicSeg {
private:
    int root;
    ll iden = 0;
    ll max_range;
    int node_count;

    ll merge(ll a, ll b) {
        return a + b;
    }

    ll get_val(int node) {
        return node ? tree[node].res : iden;
    }

    int update(int node, ll l, ll r, ll pos, ll val) {
        
        if (!node) {
            node = ++node_count;
            tree[node] = {iden, 0, 0};
        }

        if (l == r) {
            tree[node].res += val;
            return node;
        }

        ll mid = l + (r - l) / 2;
        if (pos <= mid) {
            tree[node].L = update(tree[node].L, l, mid, pos, val);
        } else {
            tree[node].R = update(tree[node].R, mid + 1, r, pos, val);
        }

        tree[node].res = merge(get_val(tree[node].L), get_val(tree[node].R));
        return node;
    }

    ll query(int node, ll l, ll r, ll lq, ll rq) {
        if (lq > r || rq < l || !node) return iden;
        if (lq <= l && r <= rq) return tree[node].res;

        ll mid = l + (r - l) / 2;

        ll q1 = query(tree[node].L, l, mid, lq, rq);
        ll q2 = query(tree[node].R, mid + 1, r, lq, rq);

        return merge(q1, q2);
    }

public:
    /**
     * @param max_u The coordinate range bound [0, max_u]. Can handle values up to 1e18.
     */
    DynamicSeg(ll max_u) {
        max_range = max_u;
        node_count = 0;
        root = ++node_count;
        tree[root] = {0, 0, 0};
    }

    void update(ll pos, ll val) {
        if (pos < 0 || pos > max_range) return;
        update(root, 0, max_range, pos, val);
    }

    ll query(ll l, ll r) {
        if (l > r || l < 0 || r > max_range) return 0;
        return query(root, 0, max_range, l, r);
    }

    void clear() {
        node_count = 0;
        root = ++node_count;
        tree[root] = {0, 0, 0};
    }
};

// ==================================================================

struct NodeLazy {
    ll res;
    ll lazy;
    int L, R;
} tree_lazy[MAX_NODES];

class DynamicLazy {
private:
    int root;
    ll max_range;
    int node_count;
    const ll iden = 0LL;
    const ll skip_lazy = 0LL;

    ll merge(ll a, ll b) {
        return a + b;
    }

    ll get_val(int node) {
        return node ? tree_lazy[node].res : iden;
    }

    int create_node() {
        int node = ++node_count;
        tree_lazy[node] = {iden, skip_lazy, 0, 0};
        return node;
    }

    void push(int node, ll l, ll r) {
        if (!node || tree_lazy[node].lazy == skip_lazy) return;

        ll mid = l + (r - l) / 2;

        if (!tree_lazy[node].L) tree_lazy[node].L = create_node();
        if (!tree_lazy[node].R) tree_lazy[node].R = create_node();

        int lc = tree_lazy[node].L;
        int rc = tree_lazy[node].R;
        ll lazy_val = tree_lazy[node].lazy;

        // Propegate to children
        tree_lazy[lc].res += (mid - l + 1) * lazy_val;
        tree_lazy[lc].lazy += lazy_val;

        tree_lazy[rc].res += (r - mid) * lazy_val;
        tree_lazy[rc].lazy += lazy_val;

        // Reset lazy
        tree_lazy[node].lazy = skip_lazy;
    }

    int update(int node, ll l, ll r, ll lq, ll rq, ll val) {
        
        if (!node) node = create_node();

        if (lq <= l && r <= rq) {
            tree_lazy[node].res += (r - l + 1) * val;
            tree_lazy[node].lazy += val;
            return node;
        }

        push(node, l, r);
        ll mid = l + (r - l) / 2;

        if (lq <= mid) tree_lazy[node].L = update(tree_lazy[node].L, l, mid, lq, rq, val);
        if (rq > mid)  tree_lazy[node].R = update(tree_lazy[node].R, mid + 1, r, lq, rq, val);

        tree_lazy[node].res = merge(get_val(tree_lazy[node].L), get_val(tree_lazy[node].R));
        return node;
    }

    ll query(int node, ll l, ll r, ll lq, ll rq) {
        if (lq > r || rq < l || !node) return iden;
        if (lq <= l && r <= rq) return tree_lazy[node].res;

        push(node, l, r);
        ll mid = l + (r - l) / 2;

        ll q1 = query(tree_lazy[node].L, l, mid, lq, rq);
        ll q2 = query(tree_lazy[node].R, mid + 1, r, lq, rq);

        return merge(q1, q2);
    }

public:

    DynamicLazy(ll max_u) {
        max_range = max_u;
        node_count = 0;
        root = create_node();
    }

    void update(ll l, ll r, ll val) {
        if (l > r || l < 0 || r > max_range) return;
        update(root, 0, max_range, l, r, val);
    }

    ll query(ll l, ll r) {
        if (l > r || l < 0 || r > max_range) return iden;
        return query(root, 0, max_range, l, r);
    }

    void clear() {
        node_count = 0;
        root = create_node();
    }
};

int main() {

    #ifndef ONLINE_JUDGE
        // freopen("../input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    DynamicSeg ds(1e9);

    ds.update(1e8, 100);
    ds.update(1e7, 200);
    cout << ds.query(1e6, 1e9) << '\n';

    DynamicLazy dl(1e9);

    dl.update(1e7, 1e7+100, 100);
    cout << dl.query(1e6, 1e9) << '\n';
    
    dl.update(100, 1e8, 1);
    cout << dl.query(1, 1e9) << '\n';

}