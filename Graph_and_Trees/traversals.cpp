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

bool isBipartite(){
    
    queue<pair<int, int>> q;
    vector<int> col(N + 1, -1);
    
    for (int i = 1; i <= N; i++) {
        if (col[i] == -1) {
            q.push({i, 0});
            col[i] = 0;
            while (!q.empty()) {
                auto [v, c] = q.front();
                q.pop();
                for (int j : adj[v]) {
                    if (col[j] == c) return false;
                    if (col[j] == -1) {
                        col[j] = 1 - c;
                        q.push({j, col[j]});
                    }
                }
            }
        }
    }

    return true;
}

// Find Tree Center (node that minimizes max distance to all nodes)
int get_tree_center(int src = 1) {
    
    auto bfs_far = [&](int start, vint& parent) {
        vint dist(N + 1, -1);
        queue<int> q;
        q.push(start);
        dist[start] = 0;
        int farthest = start;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dist[u] > dist[farthest]) farthest = u;
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }
        return farthest;
    };

    vint p1(N + 1, -1), p2(N + 1, -1);
    int u = bfs_far(src, p1);  // 1st BFS: find diameter endpoint 1
    int v = bfs_far(u, p2);    // 2nd BFS: find diameter endpoint 2 & path

    vint path;
    for (int curr = v; curr != -1; curr = p2[curr]) path.push_back(curr);
    return path[path.size() / 2]; // Return center node
}