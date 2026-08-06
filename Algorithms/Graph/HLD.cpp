#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long

struct HLD {
    int n;
    int timer;
    // SegmentTree seg;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, head, pos, tout, sz;

    HLD(int n) : n(n), adj(n), parent(n), depth(n), 
                heavy(n, -1), head(n), pos(n), tout(n), sz(n), timer(0) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs1(int v, int p = -1, int d = 0) {
        parent[v] = p;
        depth[v] = d;
        sz[v] = 1;
        int max_c = 0;
        for (int c : adj[v]) {
            if (c != p) {
                dfs1(c, v, d + 1);
                sz[v] += sz[c];
                if (sz[c] > max_c) {
                    max_c = sz[c];
                    heavy[v] = c;
                }
            }
        }
    }

    void dfs2(int v, int h, int p = -1) {
        
        head[v] = h;
        pos[v] = timer++;
        
        if (heavy[v] != -1) dfs2(heavy[v], h, v);

        for (int c : adj[v]) {
            if (c != p && c != heavy[v]) dfs2(c, c, v);
        }
        tout[u] = timer - 1;
    }

    void init(int root = 0, const vector<ll>& values = {}) {
        dfs1(root);
        dfs2(root, root);
        // seg = SegmentTree(n);
        if (!values.empty()) {
            for (int i = 0; i < n; i++) {
                // seg.update(pos[i], values[i]);
            }
        }
    }

    void update_node(int u, ll val) {
        // seg.update(pos[u], val);
    }

    ll query_path(int u, int v) {
        
        ll res = -1e18; // Identity
        for (; head[u] != head[v]; v = parent[head[v]]) {
            if (depth[head[v]] < depth[head[u]]) swap(u, v);
            // ll q = seg.query(pos[head[v]], pos[v]);
            res = max(res, q);
        }

        if (depth[v] < depth[u]) swap(u, v);

        // Note: if values on edge query(pos[u] + 1, pos[v])
        // ll q = seg.query(pos[u], pos[v]);
        res = max(res, q);
        return res;
    }

    ll query_subtree(int u) {
        // return seg.query(pos[u], pos[u] + sz[u] - 1);
    }

    vector<pair<int, int>> path(int u, int v) {
        vector<pair<int, int> > res;
        for (;; v = parent[head[v]]) {
            if (depth[head[u]] > depth[head[v]]) swap(u, v);
            if (head[u] != head[v]) {
                res.emplace_back(pos[head[v]], pos[v]);
            } else {
                if (depth[u] > depth[v]) swap(u, v);
                res.emplace_back(pos[u], pos[v]);
                return res;
            }
        }
    }

    pair<int, int> subtree(int u) {
        return {pos[u], tout[u]};
    }

    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    int lca(int u, int v) {
        for (;; v = parent[head[v]]) {
            if (depth[head[u]] > depth[head[v]]) swap(u, v);
            if (head[u] == head[v]) return u;
        }
    }

    bool isAncestor(int u, int v) {
        return pos[u] <= pos[v] && tout[u] >= tout[v];
    }
};