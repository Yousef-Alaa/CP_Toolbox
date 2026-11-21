#include <iostream>
#include <vector>

using namespace std;

// Persistent Dynamic Segment Tree

#define ll long long

const int MAX_NODES = 1e7; // Safe: 2*N + 1 + Q*(log2(maxU + 1) + 2)

struct Node {
    ll res;
    int L, R;
} tree[MAX_NODES];

class PDST {
private:
    int n = 0;
    ll iden = 0;
    ll max_range;
    int node_count;
    vector<int> roots;

    ll merge(ll a, ll b) {
        return a + b;
    }

    ll get_val(int node) {
        return node ? tree[node].res : iden;
    }

    int create_node() {
        int node = ++node_count;
        tree[node] = {iden, 0, 0};
        return node;
    }

    int build(int l, int r, const vector<ll>& arr) {
        
        int node = create_node();
        if (l == r) {
            tree[node].res = arr[l];
            return node;
        }

        int mid = l + (r - l) / 2;
        tree[node].L = build(l, mid, arr);
        tree[node].R = build(mid + 1, r, arr);
        tree[node].res = merge(get_val(tree[node].L), get_val(tree[node].R));
        return node;
    }

    int update(int prev_node, ll l, ll r, ll pos, ll val) {
        
        int node = ++node_count;
        tree[node] = tree[prev_node];

        if (l == r) {
            tree[node].res = val;
            return node;
        }

        ll mid = l + (r - l) / 2;
        if (pos <= mid) tree[node].L = update(tree[prev_node].L, l, mid, pos, val);
        else tree[node].R = update(tree[prev_node].R, mid + 1, r, pos, val);

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
    PDST(ll max_u) {
        max_range = max_u;
        node_count = 0;
        roots.push_back(create_node());
    }
    
    PDST(const vector<ll>& arr) {
        n = arr.size();
        max_range = n - 1;
        node_count = 0;
        if (n == 0) {
            roots.push_back(create_node());
            return;
        }
        roots.push_back(build(0, n - 1, arr));
    }

    void update(ll pos, ll val) {
        if (pos < 0 || pos > max_range) return;
        int new_root = update(roots.back(), 0, max_range, pos, val);
        roots.push_back(new_root);
    }

    ll query(int version, ll l, ll r) {
        if (version < 0 || version >= (int)roots.size()) return -1;
        if (l > r || l < 0 || r > max_range) return 0;
        return query(roots[version], 0, max_range, l, r);
    }

    void clear() {
        node_count = 0;
        roots.clear();
        roots.push_back(create_node());
    }

};

int main() {

    #ifndef ONLINE_JUDGE
        // freopen("../input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    // Build from an array, then create versions with point updates
    vector<ll> data = {1, 2, 3, 4, 5};

    {
        PDST pst(data); // Version 0
        pst.update(1, 10); // Version 1
        pst.update(4, 10); // Version 2

        cout << "Ver 0, Range [1,4]: " << pst.query(0, 1, 4) << '\n';
        cout << "Ver 1, Range [0,4]: " << pst.query(1, 0, 4) << '\n';
        cout << "Ver 2, Range [3,4]: " << pst.query(2, 3, 4) << '\n';
    }

    // Empty tree over a huge range, nodes are created on demand
    {
        PDST pdst(1e18); // Version 0

        pdst.update(1e8, 100); // Version 1
        pdst.update(1e7, 200); // Version 2

        cout << "Ver 0, Range [1e6,1e18]: " << pdst.query(0, 1e6, 1e18) << '\n';
        cout << "Ver 1, Range [1e6,1e18]: " << pdst.query(1, 1e6, 1e18) << '\n';
        cout << "Ver 2, Range [1e6,1e18]: " << pdst.query(2, 1e6, 1e18) << '\n';
    }

    return 0;
}
