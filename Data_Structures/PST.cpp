#include <iostream>
#include <vector>

using namespace std;

#define ll long long

const int MAX_NODES = 1e7; // N + Q * logN

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

        int q1 = query(tree[node].L, l, mid, lq, rq);
        int q2 = query(tree[node].R, mid + 1, r, lq, rq);

        return merge(q1, q2);
    }

public:
    PST(const vector<int>& arr) {
        n = arr.size();
        node_count = 0;
        roots.push_back(build(0, n - 1, arr));
    }

    void update(int pos, int val) {
        int new_root = update(roots.back(), 0, n - 1, pos, val);
        roots.push_back(new_root);
    }

    ll query(int version, int l, int r) {
        if (version >= roots.size()) return -1;
        return query(roots[version], 0, n - 1, l, r);
    }

};

int main() {

    #ifndef ONLINE_JUDGE
        // freopen("input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    vector<int> data = {1, 2, 3, 4, 5};
    
    PST pst(data); // Version 0
    pst.update(1, 10); // Version 1
    pst.update(4, 10); // Version 2
    
    cout << "Ver 0, Range [1,4]: " << pst.query(0, 1, 4) << '\n';
    cout << "Ver 1, Range [0,4]: " << pst.query(1, 0, 4) << '\n';
    cout << "Ver 2, Range [3,4]: " << pst.query(2, 3, 4) << '\n';

    return 0;
}