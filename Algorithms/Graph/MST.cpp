#include <bits/stdc++.h>

using namespace std;
#define ll long long

typedef vector<int> vint;
typedef vector<long long> vll;

int N = 20;
vector<vint> adj;
vector<bool> vis;


// MST
ll kruskal(int n, vector<tuple<int, int, int>> &edges) {
    
    DSU ds(n);
    ll total = 0;
    int used = 0;
    vector<tuple<int, int, int>> mst;
    
    sort(all(edges));
    
    for (auto [w, u, v] : edges) {
        if (ds.find_root(u) != ds.find_root(v)) {
            total += w;
            ds.unite(u, v);
            mst.push_back({w, u, v});
            if (++used == n - 1) break;
        }
    }

    return total;
}

ll primMST() {
    
    vector<bool> in_mst(N + 1);
    vector<vector<pair<int, int>>> adj; // u, w
    
    ll total = 0;
    int used = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // w, u
    
    pq.emplace(0, 1);
    
    while (!pq.empty() && used < N) {
        
        auto [w, u] = pq.top();
        pq.pop();

        if (in_mst[u]) continue;
        
        used++;
        total += w;
        in_mst[u] = true;
        
        for (auto [v, wt] : adj[u]) {
            if (!in_mst[v]) pq.emplace(wt, v);
            
        }
    }
    return total;
}