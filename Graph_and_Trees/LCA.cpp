#include <bits/stdc++.h>

using namespace std;
#define ll long long

typedef vector<int> vint;

int N = 100;
vint depth(N + 1);
vector<vint> adj;
vector<vint> up(N + 1, vint(30));

void buildAnc(int node, int par) {
    
    up[node][0] = par;

    for (int i = 1;i <= 29;i++) {
        int p = up[node][i - 1];
        up[node][i] = up[p][i - 1];
    }
    
    for (auto it : adj[node]) {
        if (it != par) {
            depth[it] = depth[node] + 1;
            buildAnc(it, node);
        }
    }

}

int kth_anc(int node, int k) {
    for (int i = 29;i >= 0;i--) {
        if ((k >> i) & 1) {
            node = up[node][i];
        }
    }
    return node;
}

int LCA(int u, int v) {

    
    if (depth[u] < depth[v]) swap(u, v);
    u = kth_anc(u, depth[u] - depth[v]);
    
    if (u == v) return u;

    for (int i = 29;i >= 0;i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }

    return up[u][0];
}

// ======================
// LCA In O(1)
// ======================

vector<int> first(N + 1);
vector<pair<int, int>> euler; // Stores {depth, node}
SparseTable st(euler);

void preDfs(int u, int p, int d) {
    first[u] = euler.size();
    euler.push_back({d, u});

    for (int v : adj[u]) {
        if (v != p) {
            preDfs(v, u, d + 1);
            euler.push_back({d, u});
        }
    }
}

int getLCA(int u, int v) {
    int L = first[u];
    int R = first[v];
    if (L > R) swap(L, R);
    pair<int, int> best = st.query(L, R);
    return best.second;
}