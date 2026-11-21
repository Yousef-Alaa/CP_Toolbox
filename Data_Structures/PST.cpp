#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long

const int MAX_NODES = 1e7; // Safe: 2*N + Q*(log2(N) + 2)

struct Node {
    ll res;
    int L, R;
} tree[MAX_NODES];

class PST {
private:
    int n;
    int node_count;
    vector<int> roots;

    ll merge(ll a, ll b) {
        return a + b;
    }

    int build(int l, int r, const vector<int>& arr) {
        
        int node = ++node_count;
        if (l == r) {
            tree[node].res = arr[l];
            return node;
        }

        int mid = l + (r - l) / 2;
        tree[node].L = build(l, mid, arr);
        tree[node].R = build(mid + 1, r, arr);
        tree[node].res = merge(tree[tree[node].L].res, tree[tree[node].R].res);
        return node;
    }

    int update(int prev_node, int l, int r, int pos, int val) {
        
        int node = ++node_count;
        tree[node] = tree[prev_node];

        if (l == r) {
            tree[node].res = val;
            return node;
        }

        int mid = l + (r - l) / 2;
        if (pos <= mid) tree[node].L = update(tree[prev_node].L, l, mid, pos, val);
        else tree[node].R = update(tree[prev_node].R, mid + 1, r, pos, val);
        

        tree[node].res = merge(tree[tree[node].L].res, tree[tree[node].R].res);
        return node;
    }

    ll query(int node, int l, int r, int lq, int rq) {
        
        if (lq > r || rq < l || !node) return 0;
        if (lq <= l && r <= rq) return tree[node].res;

        int mid = l + (r - l) / 2;

        ll q1 = query(tree[node].L, l, mid, lq, rq);
        ll q2 = query(tree[node].R, mid + 1, r, lq, rq);

        return merge(q1, q2);
    }

public:
    PST(const vector<int>& arr) {
        n = arr.size();
        node_count = 0;
        if (n == 0) {
            roots.push_back(++node_count);
            tree[node_count] = {0, 0, 0};
            return;
        }
        roots.push_back(build(0, n - 1, arr));
    }

    void update(int pos, int val) {
        if (n == 0 || roots.empty() || pos < 0 || pos >= n) return;
        int new_root = update(roots.back(), 0, n - 1, pos, val);
        roots.push_back(new_root);
    }

    ll query(int version, int l, int r) {
        if (version < 0 || version >= (int)roots.size()) return -1;
        return query(roots[version], 0, n - 1, l, r);
    }

    // Reset the shared node pool and all versions
    void clear() {
        node_count = 0;
        roots.clear();
    }

};

// ==================================================================
// Range Update, Range Query (Lazy)

const int MAX_LAZY_NODES = 2e7; // Safe: 2*N + 8*Q*(log2(N) + 1)

struct NodeLazy {
    ll res;
    ll lazy;
    int L, R;
} tree_lazy[MAX_LAZY_NODES];

class PST_Lazy {
private:
    int n;
    int node_count;
    const ll iden = 0LL;
    const ll skip_lazy = 0LL;
    vector<int> roots;

    ll merge(ll a, ll b) {
        return a + b;
    }

    ll apply(ll cur_lazy, ll new_lazy) { // For Lazy
        return cur_lazy + new_lazy;
    }

    ll get_val(int node) {
        return node ? tree_lazy[node].res : iden;
    }

    int create_node() {
        int node = ++node_count;
        tree_lazy[node] = {iden, skip_lazy, 0, 0};
        return node;
    }

    int clone_node(int node) {
        int new_node = ++node_count;
        if (node) tree_lazy[new_node] = tree_lazy[node];
        else tree_lazy[new_node] = {iden, skip_lazy, 0, 0};
        return new_node;
    }

    void propegate(int node, int l, int r) {

        if (tree_lazy[node].lazy == skip_lazy) return;

        if (l == r) {
            tree_lazy[node].lazy = skip_lazy;
            return;
        }

        int mid = l + (r - l) / 2;
        ll lazy_val = tree_lazy[node].lazy;

        tree_lazy[node].L = clone_node(tree_lazy[node].L);
        tree_lazy[node].R = clone_node(tree_lazy[node].R);

        int lc = tree_lazy[node].L;
        int rc = tree_lazy[node].R;

        // Propegate to children
        tree_lazy[lc].res += (ll)(mid - l + 1) * lazy_val;
        tree_lazy[lc].lazy = apply(tree_lazy[lc].lazy, lazy_val);

        tree_lazy[rc].res += (ll)(r - mid) * lazy_val;
        tree_lazy[rc].lazy = apply(tree_lazy[rc].lazy, lazy_val);

        // Reset lazy
        tree_lazy[node].lazy = skip_lazy;
    }

    int build(int l, int r, const vector<int>& arr) {
        
        int node = create_node();
        if (l == r) {
            tree_lazy[node].res = arr[l];
            return node;
        }

        int mid = l + (r - l) / 2;
        tree_lazy[node].L = build(l, mid, arr);
        tree_lazy[node].R = build(mid + 1, r, arr);
        tree_lazy[node].res = merge(get_val(tree_lazy[node].L), get_val(tree_lazy[node].R));
        return node;
    }

    void update(int node, int l, int r, int lq, int rq, ll val) {
        
        if (lq <= l && r <= rq) {
            tree_lazy[node].res += (r - l + 1) * val;
            tree_lazy[node].lazy = apply(tree_lazy[node].lazy, val);
            return;
        }

        bool pushed = tree_lazy[node].lazy != skip_lazy; // Check if propegate() created a new nodes
        propegate(node, l, r); // Pushing clones both children

        int mid = l + (r - l) / 2;
        if (lq <= mid) {
            if (!pushed) tree_lazy[node].L = clone_node(tree_lazy[node].L);
            update(tree_lazy[node].L, l, mid, lq, rq, val);
        }
        if (rq > mid) {
            if (!pushed) tree_lazy[node].R = clone_node(tree_lazy[node].R);
            update(tree_lazy[node].R, mid + 1, r, lq, rq, val);
        }

        tree_lazy[node].res = merge(get_val(tree_lazy[node].L), get_val(tree_lazy[node].R));
    }

    // carry holds lazy values from ancestors, so old versions are never mutated
    ll query(int node, int l, int r, int lq, int rq, ll carry) {
        
        if (lq > r || rq < l) return iden;
        if (!node) {
            int ql = max(l, lq);
            int qr = min(r, rq);
            return carry * (qr - ql + 1);
        }
        
        if (lq <= l && r <= rq) return tree_lazy[node].res + carry * (r - l + 1);

        carry = apply(carry, tree_lazy[node].lazy);
        int mid = l + (r - l) / 2;

        ll q1 = query(tree_lazy[node].L, l, mid, lq, rq, carry);
        ll q2 = query(tree_lazy[node].R, mid + 1, r, lq, rq, carry);

        return merge(q1, q2);
    }

public:
    PST_Lazy(const vector<int>& arr) {
        n = arr.size();
        node_count = 0;
        if (n == 0) {
            roots.push_back(create_node());
            return;
        }
        roots.push_back(build(0, n - 1, arr));
    }

    void update(int l, int r, ll val) {
        if (roots.empty() || l > r || l < 0 || r >= n) return;
        int new_root = clone_node(roots.back());
        update(new_root, 0, n - 1, l, r, val);
        roots.push_back(new_root);
    }

    ll query(int version, int l, int r) {
        if (version < 0 || version >= (int)roots.size()) return -1;
        if (l > r || l < 0 || r >= n) return 0;
        return query(roots[version], 0, n - 1, l, r, 0);
    }

    // Reset the shared node pool and all versions
    void clear() {
        node_count = 0;
        roots.clear();
    }

};

/*
** Note:
** we can enhance PST_Lazy::update() (in case of order of operations doesn't matters)
** by remove propegate() and accumulates ancestor lazy tags via the carry parameter
*/

/*
** Example
int update(int node, int l, int r, int lq, int rq, ll val) {
    if (lq <= l && r <= rq) {
        tree_lazy[node].res += (ll)(r - l + 1) * val;
        tree_lazy[node].lazy = apply(tree_lazy[node].lazy, val);
        return node;
    }

    int mid = l + (r - l) / 2;
    if (lq <= mid) {
        tree_lazy[node].L = clone_node(tree_lazy[node].L);
        tree_lazy[node].L = update(tree_lazy[node].L, l, mid, lq, rq, val);
    }
    if (rq > mid) {
        tree_lazy[node].R = clone_node(tree_lazy[node].R);
        tree_lazy[node].R = update(tree_lazy[node].R, mid + 1, r, lq, rq, val);
    }

    // Recompute res from children AND preserve this node's own lazy tag
    tree_lazy[node].res = merge(get_val(tree_lazy[node].L), get_val(tree_lazy[node].R)) 
                          + (r - l + 1) * tree_lazy[node].lazy;
    return node;
}
*/


int main() {

    #ifndef ONLINE_JUDGE
        // freopen("../input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    vector<int> data = {1, 2, 3, 4, 5};
    
    PST pst(data); // Version 0
    pst.update(1, 10); // Version 1
    pst.update(4, 10); // Version 2
    
    cout << "Ver 0, Range [1,4]: " << pst.query(0, 1, 4) << '\n';
    cout << "Ver 1, Range [0,4]: " << pst.query(1, 0, 4) << '\n';
    cout << "Ver 2, Range [3,4]: " << pst.query(2, 3, 4) << '\n';

    PST_Lazy pst_lazy(data); // Version 0
    pst_lazy.update(1, 3, 10); // Version 1
    pst_lazy.update(2, 4, 5); // Version 2

    cout << "Lazy Ver 0, Range [0,4]: " << pst_lazy.query(0, 0, 4) << '\n';
    cout << "Lazy Ver 1, Range [1,3]: " << pst_lazy.query(1, 1, 3) << '\n';
    cout << "Lazy Ver 2, Range [2,4]: " << pst_lazy.query(2, 2, 4) << '\n';
    cout << "Lazy Ver 0, Range [1,3]: " << pst_lazy.query(0, 1, 3) << '\n';

    return 0;
}
