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

// Kahn’s Algorithm
// Topo Sort lexicographically smallest one
void topoSortLex() {


    vector<int> indegree(N+1, 0);
    priority_queue<int, vector<int>, greater<int>> pq;

    int u, v, m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        indegree[v]++;
    }

    for(int i = 1; i <= N; i++) {
        if(indegree[i] == 0) pq.push(i);
    }

    vector<int> ans;

    while(!pq.empty()) {
        int u = pq.top();
        pq.pop();
        ans.push_back(u);

        for(int it : adj[u]) {
            indegree[it]--;
            if(indegree[it] == 0) pq.push(it);
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

bool BellmanFord(int V, int E, int src) {
    
    vector<vint> edges(E, vint(3));// u, v, w

    vll cost(V, 1e18);
    cost[src] = 0;

    for (int i = 1;i <= V - 1;i++) {
        bool flag = true;
        for (int j = 0;j < E;j++) {
            
            int u = edges[j][0];
            int v = edges[j][1];
            int w = edges[j][2];

            if (cost[u] != 1e18 && w + cost[u] < cost[v]) {
                flag = false;
                cost[v] = w + cost[u];
            }
        }

        if (flag) break;
    }
    
    for (int j = 0;j < E;j++) {
        auto [u, v, w] = edges[j];
        if (cost[u] != 1e18 && w + cost[u] < cost[v]) {
            cout << "Negative Cycle Detected";
            return true;
        }
    }

    return false;

}

// Floyd:
// all to all shortest path in O(n^3) with memory of O(n^2)
// input is dist[i][j] for all i,j in (1:n) as weight between node i and node j
// initialize the matrix first with INF and zeros in the diagonal where (i == j)
// output :
// same matrix dist[i][j] will be shortest path between i, j
int n;
const int M = 500 + 5;
const int INF = 1e9;
int dist[M][M];
void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

void solveFloyd() {
    cin >> n;
    int m, x;
    cin >> m >> x;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == j) dist[i][i] = 0;
            else dist[i][j] = INF;
        }
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        dist[a][b] = 1;
        dist[b][a] = 1;
    }
    floyd();
}

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

int reroot_tree() {
    
    
    int node1 = 0;
    int node2 = 0;
    int maxDepth = 0;
    queue<pair<int, int>> q;


    q.push({1, 0}); // Pick random node
    while (!q.empty()) {
        
        auto [f, cost] = q.front();
        
        q.pop();
        vis[f] = 1;

        if (cost > maxDepth) {
            maxDepth = cost;
            node1 = f;
        }
        

        for (auto it : adj[f]) {
            if (!vis[it]) q.push({it, cost + 1});
        }

    }
    
    maxDepth = 0;
    vis = vector<bool>(N + 1);

    q.push({node1, 0});
    vint parent(N + 1, -1);

    while (!q.empty()) {
        
        auto [f, cost] = q.front();
        q.pop();
        vis[f] = 1;

        if (cost > maxDepth) {
            maxDepth = cost;
            node2 = f;
        }
        

        for (auto it : adj[f]) {
            if (!vis[it]) {
                parent[it] = f;
                q.push({it, cost + 1});
            }
        }

    }
    


    vint path;
    int x = node2;

    while (parent[x] != -1) {
        path.push_back(x);
        x = parent[x]; 
    }
    path.push_back(x);

    return path[ path.size() / 2 ];

}