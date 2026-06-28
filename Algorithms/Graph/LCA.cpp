#include <bits/stdc++.h>

using namespace std;
#define ll long long

typedef vector<int> vint;

int N = 100;
vint depth(N + 1);
vector<vint> adj;
vector<vint> anc(N + 1, vint(30));

void buildAnc(int node, int par) {
    
    anc[node][0] = par;

    for (int i = 1;i <= 29;i++) {
        int p = anc[node][i - 1];
        anc[node][i] = anc[p][i - 1];
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
            node = anc[node][i];
        }
    }
    return node;
}

int LCA(int u, int v) {

    
    if (depth[u] < depth[v]) swap(u, v);
    u = kth_anc(u, depth[u] - depth[v]);
    
    if (u == v) return u;

    for (int i = 29;i >= 0;i--) {
        if (anc[u][i] != anc[v][i]) {
            u = anc[u][i];
            v = anc[v][i];
        }
    }

    return anc[u][0];
}