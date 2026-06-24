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

vector<bool> rec_stack(N);
// Return true if detect a cycle (Directed)
bool cycle_dir(int node) {

    vis[node] = rec_stack[node] = 1;
    bool cycle = 0;
    for (auto it : adj[node]) {
        if (!vis[it]) cycle |= cycle_dir(it);
        else if(rec_stack[it]) return true;
    }

    rec_stack[node] = 0;
    return cycle;

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