#include <bits/stdc++.h>

using namespace std;
#define ll long long

typedef vector<int> vint;
typedef vector<long long> vll;

int N = 20;
vector<vint> adj;
vector<bool> vis;

void bfs(int start) {

    queue<int> q; 
    
    q.push(start);
    vis[start] = true;

    while(!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for(auto it : adj[node]) {
            if(!vis[it]) {
                vis[it] = true;
                q.push(it);
            }
        }
    }
}

ll bfs_shortest_path(int i, int j) {

    vll cost(N + 1, 1e18);
    queue<pair<int, int>> q;
    vis[i] = 1;
    q.push({i, 0});

    while (!q.empty()) {

        auto [nx, c] = q.front();
        q.pop();

        for (auto it : adj[nx]) {
            if (!vis[it]) {
                vis[it] = 1;
                q.push({it, c + 1});
                cost[it] = c + 1;
            }
        }
    }

    return cost[j];
}

void dfs(int node) {

    vis[node] = true;
    cout << node << " ";

    for(auto it : adj[node]) {
        if(!vis[it]) {
            dfs(it);
        }
    }
}

// Undirected
bool dfsCycle(int node, int parent) {
    
    vis[node] = true;

    for (auto it : adj[node]) {
        
        if (!vis[it]) {
            if (dfsCycle(it, node)) return true;
        }
        else if (it != parent) {
            return true;
        }
    }
    return false;
}


stack<int> topo_sort;
vector<bool> rec_stack(N);
// Return true if detect a cycle (Directed)
bool topoSort(int node) {

    vis[node] = rec_stack[node] = 1;
    bool cycle = 0;
    for (auto it : adj[node]) {
        if (!vis[it]) cycle |= topoSort(it);
        else if(rec_stack[it]) return true;
    }

    topo_sort.push(node);
    rec_stack[node] = 0;
    return cycle;

}


// Topo Sort lexicographically smallest one
void topoSortLex() {


    vector<int> indeg(N+1, 0);
    priority_queue<int, vector<int>, greater<int>> pq;

    for(int i = 1; i <= N; i++) {
        if(indeg[i] == 0) pq.push(i);
    }

    vector<int> ans;

    while(!pq.empty()) {
        int u = pq.top();
        pq.pop();
        ans.push_back(u);

        for(int it : adj[u]) {
            indeg[it]--;
            if(indeg[it] == 0) pq.push(it);
        }
    }

    if(ans.size() != N) {
        cout << "Cycle Detected";
        return;
    }

    for(int x : ans) cout << x << " ";

}


void dijkstra(int start) {


    vint parent(N + 1, -1);
    vll cost(N + 1, 1e18);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq; // cost, node


    pq.push({0, start});
    cost[start] = 0;

    while (!pq.empty()) {
        
        auto [c, node] = pq.top();
        pq.pop();

        if (cost[node] < c) continue;

        for (auto [it, cs] : adj[node]) {
            if (c + cs < cost[it]) {
                parent[it] = node;
                cost[it] = c + cs;
                pq.push({c + cs, it});
            }
        }

    }

}

int kruskal(int n, vector<tuple<int, int, int>> &edges) {
    
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


int main() {

    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    int n, m, x, y;
    cin >> n >> m;

    adj.resize(n + 1);
    vis.resize(n + 1);

    while (m--) {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    cout << "Hello Graph\n";
    dfs(adj, vis, 0);
    cout << "\n";
    bfs(adj, 0);
    cout << "\n";

    for (int i = 0;i < n;i++) vis[i] = false;
    cout << (dfsCycle(0, -1, adj, vis) ? "Cycle\n" : "No Cycle\n");



}