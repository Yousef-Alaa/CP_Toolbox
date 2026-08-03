#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define all(v) v.begin(), v.end()

typedef vector<int> vint;

// ============================================================================
// DSU on Tree (Sack's Algorithm / Heavy-Light Subtree Merging)
//
// Description:
//   An efficient offline subtree query technique. Computes subtree answers by
//   reusing global frequency/state arrays for the "heavy child" (largest subtree)
//   and re-adding "light children".
//
// Complexity:
//   Time:  O(N log N) time with O(1) state updates (e.g. array frequency counters).
//   Space: O(N) auxiliary memory.
// ============================================================================



// Variant 1: Distinct values / general subtree frequency queries
struct Sack {
    int n;
    int currAns;
    vector<vector<int>> adj;
    vector<int> values, sz, heavy, freq, ans;

    Sack(int n_, const vector<int>& c, int max_val = 1e5 + 5) 
        : n(n_), values(c), adj(n_), sz(n_, 0), heavy(n_, -1), 
          freq(max_val, 0), ans(n_, 0), currAns(0) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs_sz(int u, int p) {
        sz[u] = 1;
        heavy[u] = -1;
        int max_sz = 0;
        for (int v : adj[u]) {
            if (v == p) continue;
            dfs_sz(v, u);
            sz[u] += sz[v];
            if (sz[v] > max_sz) {
                max_sz = sz[v];
                heavy[u] = v;
            }
        }
    }

    void add_node(int u, int d) {
        int c = values[u];
        if (freq[c] == 0 && d == 1) currAns++;
        freq[c] += d;
        if (freq[c] == 0 && d == -1) currAns--;
    }

    void add_subtree(int u, int p, int d) {
        add_node(u, d);
        for (int v : adj[u]) {
            if (v != p) add_subtree(v, u, d);
        }
    }

    void dfs_sack(int u, int p, bool keep) {
        
        // light children
        for (int v : adj[u]) {
            if (v != p && v != heavy[u]) dfs_sack(v, u, false);
        }

        // heavy child
        if (heavy[u] != -1) dfs_sack(heavy[u], u, true);

        // Add yourself and light children
        add_node(u, 1);
        for (int v : adj[u]) {
            if (v != p && v != heavy[u]) add_subtree(v, u, 1);
        }

        // Record answer
        ans[u] = currAns;

        // remove u's subtree from global state
        if (!keep) add_subtree(u, p, -1);
        
    }

    vector<int> solve(int root = 0) {
        dfs_sz(root, -1);
        dfs_sack(root, -1, true);
        return ans;
    }
};

// Variant 2: Dominant elements / max frequency sum (e.g. Codeforces 600E)
struct DSUOnTree {
    int n;
    int max_f;
    ll sum_max_f;
    vector<vector<int>> adj;
    vector<int> values, sz, heavy, freq, ans;

    DSUOnTree(int n_, const vector<int>& c, int max_val = 1e5 + 5)
        : n(n_), values(c), adj(n_), sz(n_, 0), heavy(n_, -1),
          freq(max_val, 0), ans(n_, 0), max_f(0), sum_max_f(0) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs_sz(int u, int p) {
        sz[u] = 1;
        heavy[u] = -1;
        int max_sz = 0;
        for (int v : adj[u]) {
            if (v == p) continue;
            dfs_sz(v, u);
            sz[u] += sz[v];
            if (sz[v] > max_sz) {
                max_sz = sz[v];
                heavy[u] = v;
            }
        }
    }

    void add_node(int u, int d) {
        int c = values[u];
        freq[c] += d;
        if (d == 1) {
            if (freq[c] > max_f) {
                max_f = freq[c];
                sum_max_f = c;
            } else if (freq[c] == max_f) {
                sum_max_f += c;
            }
        }
    }

    void add_subtree(int u, int p, int d) {
        add_node(u, d);
        for (int v : adj[u]) {
            if (v != p) add_subtree(v, u, d);
        }
    }

    void dfs_sack(int u, int p, bool keep) {
        for (int v : adj[u]) {
            if (v != p && v != heavy[u]) dfs_sack(v, u, false);
        }

        if (heavy[u] != -1) dfs_sack(heavy[u], u, true);

        add_node(u, 1);
        for (int v : adj[u]) {
            if (v != p && v != heavy[u]) add_subtree(v, u, 1);
        }

        ans[u] = sum_max_f;

        if (!keep) {
            // Reset global state for light subtrees
            add_subtree(u, p, -1);
            max_f = 0;
            sum_max_f = 0;
        }
    }

    vector<ll> solve(int root = 0) {
        dfs_sz(root, -1);
        dfs_sack(root, -1, true);
        return ans;
    }
};
